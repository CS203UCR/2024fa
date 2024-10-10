#include <stdio.h>
#include <stdlib.h>
#include "perfstats.h"

int ARRAY_SIZE = 512;
void mm(double **a, double **b, double **c);

int main(int argc, char **argv)
{
  double **a, **b, **c, *temp;
  int i, j, k;
  /* initialize a, b */
  if(argc >= 2)
    ARRAY_SIZE = atoi(argv[1]);
  temp = (double *)valloc(ARRAY_SIZE*ARRAY_SIZE*sizeof(double)*3);
  a = (double **)malloc(ARRAY_SIZE*sizeof(double *));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    a[i] = temp;
    temp += ARRAY_SIZE;
    for(j = 0; j < ARRAY_SIZE; j++)
      a[i][j] = i+j;
  }
  b = (double **)malloc(ARRAY_SIZE*sizeof(double *));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    b[i] = temp;
    temp += ARRAY_SIZE;
    for(j = 0; j < ARRAY_SIZE; j++)
      b[i][j] = i+j;
  }
  c = (double **)malloc(ARRAY_SIZE*sizeof(double *));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    c[i] = temp;
    temp += ARRAY_SIZE;
    for(j = 0; j < ARRAY_SIZE; j++)
      c[i][j] = 0;
  }
//	sprintf(header,"size,rep,arg1,function,IC,Cycles,CPI,CT,ET,L1_dcache_miss_rate,L1_dcache_misses,L1_dcache_accesses,branches,branch_misses");
//        perfstats_print_header(stat_file, header);
        perfstats_init();
        perfstats_enable();
        mm(a, b, c);
        perfstats_disable();
        perfstats_print();
        perfstats_deinit();
  /* Do matrix multiplication */
/*  for(i = 0; i < ARRAY_SIZE; i++)
  {
    for(j = 0; j < ARRAY_SIZE; j++)
    {
      for(k = 0; k < ARRAY_SIZE; k++)
      {
        c[i][j] += a[i][k]*b[k][j];
      }
    }
  }*/  
/*
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    for(j = 0; j < ARRAY_SIZE; j++)
    {
      printf("%d ",c[i][j]);
    }
    printf("\n");
  }
*/
  return 0;
}
//START
void mm(double **a, double **b, double **c)
{
  int i,j,k;
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    for(j = 0; j < ARRAY_SIZE; j++)
    {
      for(k = 0; k < ARRAY_SIZE; k++)
      {
        c[i][j] += a[i][k]*b[k][j];
        #ifdef DUMP
          fprintf(stderr, "a[%d][%d], %p\n",i,k, &a[i][k]);
          fprintf(stderr, "b[%d][%d], %p\n",k,j, &b[k][j]);
          fprintf(stderr, "c[%d][%d], %p\n",i,j, &c[i][j]);
        #endif
      }
    }
  }
  return;
}
//END