#ifdef HAVE_LINUX_PERF_EVENT_H
#ifdef __cplusplus
extern "C" {
#endif
#include "perfstats.h"

#include <linux/perf_event.h>
#include <linux/unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <linux/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sched.h>
#include <string.h>
#define CACHE_CONTROL_FLUSH_CACHES _IO('q', 1)
int cpu=0;

struct timeval time_start, time_end;
double elapsed_time;
enum {
    COUNTER_CPU_CYCLES,
//    STALLED_CYCLES_FRONTEND,
//    STALLED_CYCLES_BACKEND,
    INSTRUCTIONS,    
//    DTLB_ACCESSES,
//    DTLB_MISSES,
    DL1_LOAD_ACCESSES,
    DL1_LOAD_MISSES,
    DL1_STORE_ACCESSES,
    DL1_STORE_MISSES,
    DL1_PREFETCH_ACCESSES,
    DL1_PREFETCH_MISSES,
};


static struct perf_event_attr attrs[] = {
    { .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_CPU_CYCLES},
//    { .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_STALLED_CYCLES_FRONTEND},
//    { .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_STALLED_CYCLES_BACKEND},
    { .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_INSTRUCTIONS},
//    { .type = PERF_TYPE_HW_CACHE, .config = PERF_COUNT_HW_CACHE_DTLB | (PERF_COUNT_HW_CACHE_OP_READ << 8) | (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16) },
//    { .type = PERF_TYPE_HW_CACHE, .config = PERF_COUNT_HW_CACHE_DTLB | (PERF_COUNT_HW_CACHE_OP_READ << 8) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16) },
    { .type = PERF_TYPE_HW_CACHE, .config = PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8) | (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16) },
    { .type = PERF_TYPE_HW_CACHE, .config = PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16) },
    { .type = PERF_TYPE_HW_CACHE, .config = PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_WRITE << 8) | (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16) },
    { .type = PERF_TYPE_HW_CACHE, .config = PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_WRITE << 8) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16) },
    { .type = PERF_TYPE_HW_CACHE, .config = PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_PREFETCH << 8) | (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16) },
    { .type = PERF_TYPE_HW_CACHE, .config = PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_PREFETCH << 8) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16) },
    };

#define STAT_COUNT (sizeof(attrs) / sizeof(*attrs))
unsigned long long performance_counters[STAT_COUNT];
double total_time;
static int fds[STAT_COUNT];

static inline int
sys_perf_event_open(struct perf_event_attr *attr,
                    pid_t pid, int cpu, int group_fd,
                    unsigned long flags)
{
    attr->size = sizeof(*attr);
    return syscall(__NR_perf_event_open, attr, pid, cpu,
                   group_fd, flags);
}

void perfstats_init(void)
{
    int pid = getpid();
    int i;

    for (i = 0; i < STAT_COUNT; i++) {
        attrs[i].inherit = 1;
        attrs[i].disabled = 1;
        attrs[i].exclude_kernel = 0;
        attrs[i].enable_on_exec = 0;
        fds[i] = sys_perf_event_open(&attrs[i], pid, -1, -1, 0);
//        fprintf(stderr,"PC: %d %d %X\n",i, fds[i], attrs[i].config);
    }
}

void perfstats_deinit(void)
{
    int i;
    for (i = 0; i < STAT_COUNT; i++) {
        close(fds[i]);
        fds[i] = -1;
    }
}


void perfstats_enable(void)
{
    int i, ret;
    unsigned long long *garbage = NULL;
    for (i = 0; i < STAT_COUNT; i++) {
        if (fds[i] <= 0)
            continue;

        ioctl(fds[i], PERF_EVENT_IOC_ENABLE);
    }
//    return garbage;
//    garbage = flush_caches();
    for (i = 0; i < STAT_COUNT; i++) {
        if (fds[i] > 0)
            ret = read(fds[i], &performance_counters[i], sizeof(performance_counters[i]));
    }
    gettimeofday(&time_start, NULL);
}
void perfstats_reenable(void)
{
    int i, ret;
    for (i = 0; i < STAT_COUNT; i++) {
        if (fds[i] <= 0)
            continue;

        ret = ioctl(fds[i], PERF_EVENT_IOC_ENABLE);
    }
}

void perfstats_disable()
{
    int i;
    gettimeofday(&time_end, NULL);
    for (i = 0; i < STAT_COUNT; i++) {
        if (fds[i] <= 0)
            continue;

        ioctl(fds[i], PERF_EVENT_IOC_DISABLE);
    }
//    gettimeofday(&time_end, NULL);
    elapsed_time = ((time_end.tv_sec * 1000000.0 + time_end.tv_usec) - (time_start.tv_sec * 1000000.0 + time_start.tv_usec));
    elapsed_time/=1000000.0;
//    free(garbage);
}

static unsigned long long readcounter(int i)
{
    unsigned long long ret;
    if(fds[i] <= 0)    
        return 0;
    read(fds[i], &ret, sizeof(ret));
//        fprintf(stderr,"PC: %d %lu\n",i, ret);

    return ret;
}

static unsigned long long readall()
{
    unsigned long long ret;
    int r;
    int i;
    for (i = 0; i < STAT_COUNT; i++) {
        if (fds[i] > 0)
        {
            r = read(fds[i], &ret, sizeof(ret));
            performance_counters[i]=ret-performance_counters[i];
        }
    }

    return i;
}

void perfstats_print_header(char *filename, char *header)
{
    FILE *fout;
    fout = fopen(filename, "w");
    fprintf(fout, "%s\n", header);
    fclose(fout);
}

void perfstats_print()
{
    FILE *fout;
    unsigned long long ic, cycles, loads=0, load_misses=0, stores=0, store_misses=0, prefetches=0, prefetch_misses=0;
//    fout = fopen(filename, "a");
    readall();
    ic = performance_counters[INSTRUCTIONS];
    cycles = performance_counters[COUNTER_CPU_CYCLES];
    loads = performance_counters[DL1_LOAD_ACCESSES];
    load_misses = performance_counters[DL1_LOAD_MISSES];
    stores = performance_counters[DL1_STORE_ACCESSES];
    store_misses = performance_counters[DL1_STORE_MISSES];
    prefetches = performance_counters[DL1_PREFETCH_ACCESSES];
    prefetch_misses = performance_counters[DL1_PREFETCH_MISSES];

/*    ic = readcounter(INSTRUCTIONS);
    cycles = readcounter(COUNTER_CPU_CYCLES);
    loads = readcounter(DL1_LOAD_ACCESSES);
    load_misses = readcounter(DL1_LOAD_MISSES);
    stores = readcounter(DL1_STORE_ACCESSES);
    store_misses = readcounter(DL1_STORE_MISSES);*/
//    prefetches = readcounter(DL1_PREFETCH_ACCESSES);
//    prefetch_misses = readcounter(DL1_PREFETCH_MISSES);

    fprintf(stderr,"%llu,%llu,%lf,%lf,%lf,%lf,%llu,%llu\n", 
                     ic, 
                     cycles,
                     (double)cycles/ic,
                     ((double)elapsed_time*1000000000.0)/cycles, 
                      elapsed_time,(double)(load_misses+store_misses+prefetch_misses)/(double)(loads+stores+prefetches),load_misses+store_misses+prefetch_misses,loads+stores+prefetches);
//    fclose(fout);
}
#ifdef __cplusplus
}
#endif

#endif
