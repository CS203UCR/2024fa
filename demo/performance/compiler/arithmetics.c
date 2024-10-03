#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include "perfstats.h"
// A function to implement bubble sort
int64_t a_div_43(int64_t a)
{
    return a/43;
}
int64_t a_mul_43(int64_t a)
{
    return a*43;
}
int64_t __attribute__((optimize("O0"))) a_mul_43_no_opt(int64_t a)
{
    return a*43;
}
int64_t a_mod_43(int64_t a)
{
    return a%43;
}
// Function to print an array
void print_elapsed(clock_t start, clock_t stop)
{
  double elapsed = ((double) (stop - start)) / CLOCKS_PER_SEC;
  printf("Elapsed time: %.3fs\n", elapsed);
}

int main(int argc, void **argv)
{
    clock_t start, stop;
    unsigned N = 16777216;
    int64_t *data, *data_2, i, r;
    if(argc > 1)
        N = atoi(argv[1]);
    data = (int64_t *)malloc(sizeof(int64_t) *N);
    data_2 = (int64_t *)malloc(sizeof(int64_t) *N);
    memcpy(data, data_2, sizeof(int64_t) *N);
    r = rand();
    start = clock();
    perfstats_init();
    perfstats_enable();
    for(i=0;i<N;i++)
        data[i] = a_mul_43_no_opt(data[i]);
    perfstats_disable();
    perfstats_print();
    perfstats_deinit();
    stop = clock();
    printf("No optimization\n");
    print_elapsed(start, stop);
    start = clock();
    perfstats_init();
    perfstats_enable();
    for(i=0;i<N;i++)
        data_2[i] = a_mul_43(data_2[i]);
    perfstats_disable();
    perfstats_print();
    perfstats_deinit();
    stop = clock();
    printf("Optimized\n");
    print_elapsed(start, stop);
    r = r%N;
    printf("%ld\n",a_mul_43(data[r]));
    printf("%ld\n",a_div_43(data[r]));
    printf("%ld\n",a_mod_43(data[r]));
    printf("%ld\n",a_mul_43(data_2[r]));
    printf("%ld\n",a_div_43(data_2[r]));
    printf("%ld\n",a_mod_43(data_2[r]));    
    return 0;
}