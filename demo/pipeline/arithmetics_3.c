#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "perfstats.h"

int main()
{
    int i,sum=0,data[131072],index=0;
    struct timeval time_start, time_end, program_start, program_end;
    for(i=0;i<131072;i++)
        data[i]=rand()%8738;
    fprintf(stderr,"Mul,");
    gettimeofday(&time_start, NULL);
    perfstats_init();
    perfstats_enable(1);
    //START_MUL
    for(i=0;i<1000000000;i++)
    {
        sum+=data[index];
        index = (data[index]*15)%131072;
    }
    //END_MUL
    perfstats_disable(1);
    perfstats_print();
    gettimeofday(&time_end, NULL);
    fprintf(stderr,"\n");
    printf("%lf seconds\n",((time_end.tv_sec * 1000000 + time_end.tv_usec) - (time_start.tv_sec * 1000000 + time_start.tv_usec))/1000000.0);
    fprintf(stderr,"Shift,");
    gettimeofday(&time_start, NULL);
    perfstats_enable(1);
    //START_SHIFT
    for(i=0;i<1000000000;i++)
    {
        sum+=data[index];
        index = ((data[index] << 4) - data[index])%131072;
    }
    //END_SHIFT
    perfstats_disable(1);
    perfstats_print();
    perfstats_deinit();
    gettimeofday(&time_end, NULL);
    fprintf(stderr,"\n");
    printf("%lf seconds\n",((time_end.tv_sec * 1000000 + time_end.tv_usec) - (time_start.tv_sec * 1000000 + time_start.tv_usec))/1000000.0);
    printf("%d\n",sum);
    return 0;
}
