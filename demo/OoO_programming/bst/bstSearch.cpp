#include <algorithm>
#include <ctime>
#include <iostream>
#include <climits>
#include "bst.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "perfstats.h"
#ifdef __cplusplus
}
#endif

int main(int argc, char **argv)
{
    // generate data
//    const unsigned arraySize = 262144;
    int arraySize = atoi(argv[1]);
    int data[arraySize];
    long long sum = 0;
    char preamble[1024];
    char epilogue[1024];
    char header[1024];
    char stat_file[] = "stats.csv";

    int iterations = atoi(argv[2]);
    int option = atoi(argv[3]);
    Node* root = NULL;
    for (unsigned c = 0; c < arraySize; ++c)
        insert(&root, std::rand());



#ifdef COUNT_SORTING
    perfstats_init();
    perfstats_enable(1);
#endif
    //START
    if(option)
        std::sort(data, data + arraySize);
#ifndef COUNT_SORTING
    perfstats_init();
    perfstats_enable(1);
#endif
    for (unsigned i = 0; i < iterations; ++i) {
        sum = inorderTraversal(root);
    }
    //END
    perfstats_disable(1);
    sprintf(epilogue,"\n");
    sprintf(preamble,"");
    perfstats_print(preamble, stat_file, epilogue);
    perfstats_deinit();
    std::cout << "sum = " << sum << std::endl;
}
