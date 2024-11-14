#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#include "perfstats.h"
#endif
void (*array_swap)(uint64_t* a, uint64_t* b, uint64_t size);
void inline swap(uint64_t* a, uint64_t* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
} 

void swap_array_1(uint64_t *a, uint64_t *b, uint64_t size)
{
    for (uint64_t i = 0; i < size; ++i) {
        swap(&a[i],&b[i]);
    }

}
void swap_array_2(uint64_t *a, uint64_t *b, uint64_t size)
{
    uint64_t real_size = size >> 1;
    for (uint64_t i = 0; i < real_size*2; i+=2) {
        swap(&a[i],&b[i]);
        swap(&a[i],&b[i]);
    }
}

void swap_array_3(uint64_t *a, uint64_t *b, uint64_t size)
{
    uint64_t real_size = size / 4;
    for (uint64_t i = 0; i < real_size*4; ++i) {
        swap(&a[i],&b[i]);
    }
}
#ifdef __cplusplus
}
#endif

int main(int argc, char **argv)
{
    unsigned array_size = 131072;
    int *data_a, *data_b;
    // command: swap array_size method
    if(argc > 1)
        array_size = atoi(argv[1]);
    if(argc > 2 && atoi(argv[2])==1)
        array_swap = swap_array_1;
    else
        array_swap = swap_array_2;
    data_a = (int *)malloc(sizeof(int)*array_size);
    data_b = (int *)malloc(sizeof(int)*array_size);
    for (unsigned i = 0; i < array_size; ++i) {
        data_a[i] = rand();
        data_b[i] = rand();
    }
    perfstats_init();
    perfstats_enable(1);
    perfstats_disable(1);
    perfstats_print();
    perfstats_deinit();
    return 0;
}