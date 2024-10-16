#ifdef __cplusplus
extern "C" {
#endif
#ifndef HAVE_LINUX_PERF_EVENT_H

static inline void perfstats_init(void) {}
static inline void perfstats_deinit(void) {}
static inline void perfstats_enable(void) {}
static inline void perfstats_disable(void) {}
static void perfstats_print_header(char *filename, char *header){};
static void perfstats_print(){};
//static void perfstats_print(char *preamble, char *filename, char *epilogue){};

#else
void perfstats_init(void);
void perfstats_deinit(void);
void perfstats_enable(void);
void perfstats_disable(void);
void perfstats_print_header(char *filename, char *header);
void perfstats_print();


#endif
#ifdef __cplusplus
}
#endif