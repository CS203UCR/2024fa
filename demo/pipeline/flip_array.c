#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "perfstats.h"

void (*swap)(int* a, int* b);
void regswap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void xorswap(int* a, int* b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void flip_array(int64_t *a, int64_t *b, int64_t count)
{
    for(size_t i = 0; i < count; i++) {
    int64_t temp = a[i];
    a[i] = b[i];
    b[i] = temp;
    }
    return;
}

int main(int argc, char **argv)
{
    unsigned array_size = 131072;
    int *data;
    struct timeval time_start, time_end;
    // command: swap array_size method
    if(argc > 1)
        array_size = atoi(argv[1]);
    if(argc > 2 && atoi(argv[2])==1)
        swap = xorswap;
    else
        swap = regswap;
    data = (int *)malloc(sizeof(int)*array_size);
    for (unsigned i = 0; i < array_size; ++i)
        data[i] = rand();
   gettimeofday(&time_start, NULL);
    perfstats_init();
    perfstats_enable(1);
   for (unsigned i = 0; i < array_size; i++)
   {
        swap(&data[i],&data[array_size-1-i]);
   }
    perfstats_disable(1);
    perfstats_print();
    perfstats_deinit();
   gettimeofday(&time_end, NULL);
    fprintf(stderr,"\n");
   printf("data[array_size/2] = %d\n", data[rand()%array_size]);
   printf("flipped in %lf seconds\n",((time_end.tv_sec * 1000000 + time_end.tv_usec) - (time_start.tv_sec * 1000000 + time_start.tv_usec))/1000000.0);
   return 0;
}