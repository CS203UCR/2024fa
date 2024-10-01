#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "perfstats.h"

void blockmm_transpose(double **a, double **b, double **c, uint64_t M, uint64_t N, uint64_t K);
uint64_t tile_size=1;
int ARRAY_SIZE=500;
int main(int argc, char **argv)
{
  double **a, **b, **c, **b_t;
  uint64_t i, j, k, M, K, N;
  /* initialize a, b */
  if(argc == 2)
    tile_size = atoi(argv[1]);
  if(argc >= 3)
  {
    ARRAY_SIZE = atoi(argv[1]);
    tile_size = atoi(argv[2]);
  }
  M=K=N=ARRAY_SIZE;
  a = (double **)malloc(ARRAY_SIZE*sizeof(double *));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    a[i] = (double *)malloc(ARRAY_SIZE*sizeof(double));
    for(j = 0; j < ARRAY_SIZE; j++)
      a[i][j] = i+j;
  }
  b = (double **)malloc(ARRAY_SIZE*sizeof(double *));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    b[i] = (double *)malloc(ARRAY_SIZE*sizeof(double));
    for(j = 0; j < ARRAY_SIZE; j++)
      b[i][j] = i+j;
  }
  b_t = (double **)malloc(ARRAY_SIZE*sizeof(double *));
  //TRAN_START
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    b_t[i] = (double *)malloc(ARRAY_SIZE*sizeof(double));
    for(j = 0; j < ARRAY_SIZE; j++)
      b_t[i][j] = b[j][i];
  }
  //TRAN_END
  c = (double **)malloc(ARRAY_SIZE*sizeof(double *));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    c[i] = (double *)malloc(ARRAY_SIZE*sizeof(double));
    for(j = 0; j < ARRAY_SIZE; j++)
      c[i][j] = 0;
  }
  printf("%d,%lu,",ARRAY_SIZE,tile_size);
  perfstats_init();
  perfstats_enable();
  blockmm_transpose(a, b_t, c, M, N, K);
  perfstats_disable();
  perfstats_print();
  perfstats_deinit();
  fprintf(stderr,"%lf,",c[rand()%ARRAY_SIZE][rand()%ARRAY_SIZE]);
  return 0;
}
//START
void blockmm_transpose(double **a, double **b, double **c, uint64_t M, uint64_t N, uint64_t K)
{
  int i,j,k, ii, jj, kk;
  for(i = 0; i < M; i+=tile_size)
  {
    for(j = 0; j < K; j+=tile_size)
    {
      for(k = 0; k < N; k+=tile_size)
      {        
          for(ii = i; ii < i+tile_size; ii++)
            for(jj = j; jj < j+tile_size; jj++)
              for(kk = k; kk < k+tile_size; kk++)
                c[ii][jj] += a[ii][kk]*b[jj][kk];
      }
    }
  }  
}
//END