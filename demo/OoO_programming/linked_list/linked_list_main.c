#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "perfstats.h"
#include <sched.h>
#include <unistd.h>
cpu_set_t  mask;


struct node
{
    int value;
    int linked;
    struct node *next;
};

int depth_of_list(struct node *start);

int depth_of_array(struct node *start, int size);

int main(int argc, char **argv)
{
    unsigned long array_size = 131072, depth;
    struct node *data;
    struct timeval time_start, time_end;
        char preamble[1024];
        char epilogue[1024];
        char header[1024];
        char stat_file[1024] = "stats.csv";
    int list = 0, linked=0, toLink, iterations=1;
    if(argc >= 2)
        array_size = atoi(argv[1]);
    if(argc >= 3)
        list = atoi(argv[2]);
    if(argc >= 4)
        iterations = atoi(argv[3]);
    data = (struct node*)calloc(array_size, sizeof(struct node));
    for (unsigned i = 0; i < array_size; ++i)
        data[i].value = rand();
    data[linked].linked = 1;

    for (unsigned i = 0; i < array_size-1; ++i)
    {
        do {
        toLink = rand() & (array_size-1);}
        while(data[toLink].linked != 0);
        //if(i!=array_size-1)
        data[linked].next = &data[toLink];
        data[toLink].linked = 1;
        linked = toLink;
    }
    CPU_ZERO(&mask);
    CPU_SET(4, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);

    gettimeofday(&time_start, NULL);
    perfstats_init();
    perfstats_enable(1);
    for (unsigned k = 0; k < iterations; ++k)
    {
        if(list)
            depth = depth_of_list(data);
        else
            depth = depth_of_array(data, array_size);
    }
    gettimeofday(&time_end, NULL);
    perfstats_disable(1);
    sprintf(epilogue,"\n");
    sprintf(preamble,"");
    perfstats_print(preamble, stat_file, epilogue);
    perfstats_deinit();
    fprintf(stderr, "depth: %lu\n", depth);
//   fprintf(stderr, "sorted %lf seconds\n",((time_end.tv_sec * 1000000 + time_end.tv_usec) - (time_start.tv_sec * 1000000 + time_start.tv_usec))/1000000.0);
   return 0;
}

