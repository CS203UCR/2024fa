#define _GNU_SOURCE
#include <stddef.h>
struct node
{
    int value;
    int linked;
    struct node *next;
};

int depth_of_list(struct node *start)
{
    int number_of_nodes = 0;
    unsigned long sum=0;
    struct node *node = start;
    while(node)
    {
        node = node->next;
        number_of_nodes++;
    }
    return number_of_nodes;
}

int depth_of_array(struct node *start, int size)
{
    int number_of_nodes = 0, i;
    unsigned long sum=0;
    struct node *node = start;
    if(node!=NULL) number_of_nodes=1;
    for(i=0;i<size;i++)
    {
        if(node[i].next)
            number_of_nodes++;
    }
    return number_of_nodes;
}
