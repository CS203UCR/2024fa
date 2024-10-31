#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void (*arithmetrics)(void* a, void* b, int size);
void init_int(void* a, void* b, int size)
{
    int i = 0,offset=0;
    int64_t *target = (int64_t *)a;
    offset = rand();
    for(i=0;i<size;i++)
        target[i] = i+offset;
    return;
}

void init_int_mul(void* a, void* b, int size)
{
    int i = 0,offset=0;
    int64_t *target = (int64_t *)a;
    offset = rand();
    for(i=0;i<size;i++)
        target[i] = i*offset;
    return;
}

void init_int_memory(void* a, void* b, int size)
{
    int i = 0,offset=0;
    int64_t *target = (int64_t *)a;
    int64_t *source = (int64_t *)b;
    offset = rand();
    for(i=0;i<size;i++)
        target[i] = source[i]+offset;
    return;
}

void init_double(void* a, void* b, int size)
{
    int i = 0;
    double offset=0;
    double *target = (double *)a;
    offset = rand()/100;
    for(i=0;i<size;i++)
        target[i] = i*offset;
    return;
} 
 

int main(int argc, char **argv)
{
    unsigned array_size = 131072;
    int64_t *source, *target;
    struct timeval time_start, time_end;
    // command: swap array_size method
    if(argc > 1)
        array_size = atoi(argv[1]);
    target = (int64_t *)malloc(sizeof(double)*array_size);
    source = (int64_t *)malloc(sizeof(double)*array_size);
    if(argc > 2 && atoi(argv[2])==1)
        arithmetrics = init_int;
    else if(argc > 2 && atoi(argv[2])==2)
        arithmetrics = init_int_mul;
    else if(argc > 2 && atoi(argv[2])==3)
        arithmetrics = init_int_memory;
    else
        arithmetrics = init_double;
    for (unsigned i = 0; i < array_size; ++i)
        source[i] = rand();
   gettimeofday(&time_start, NULL);
   arithmetrics(target, source, array_size-1);
   gettimeofday(&time_end, NULL);
   fprintf(stderr, "data[rand()] = %d\n", target[rand()%array_size]);
   fprintf(stderr, "Initialization %lf seconds\n",((time_end.tv_sec * 1000000 + time_end.tv_usec) - (time_start.tv_sec * 1000000 + time_start.tv_usec))/1000000.0);
   return 0;
}