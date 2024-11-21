#include <stdio.h>
#include <stdlib.h>
#include "perfstats.h"
void mv(double **a, double *b, double *c, int ARRAY_SIZE){
  /* Do matrix vector multiplications */
    double result;
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
      result = 0.0;    
      for(int j = 0; j < ARRAY_SIZE; j++)
      {
        result += a[i][j]*b[j];
      }
      c[i] = result;
    }
    return;
}

int ARRAY_SIZE = 8192;

int main(int argc, char **argv)
{
  double **a, *b, *c, result;
  int i,j,dump=0,i_first=1;
  /* initialize a, b */
        char preamble[1024];
        char epilogue[1024];
        char header[1024];
        char stat_file[1024] = "stats.csv";
  if(argc >= 2)
    ARRAY_SIZE = atoi(argv[1]);
  a = (double **)malloc(ARRAY_SIZE*sizeof(double *));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    a[i] = (double *)malloc(ARRAY_SIZE*sizeof(double));
    for(j = 0; j < ARRAY_SIZE; j++)
      a[i][j] = (rand()%100)+1;
  }

  b = (double *)malloc(ARRAY_SIZE*sizeof(double));
  for(i = 0; i < ARRAY_SIZE; i++)
      b[i] = (rand()%100)+1;

  c = (double *)malloc(ARRAY_SIZE*sizeof(double));

  for(i = 0; i < ARRAY_SIZE; i++)
      c[i] = 0.0;
    perfstats_init();
    perfstats_enable(1);
  mv(a, b, c, ARRAY_SIZE);
    perfstats_disable(1);
    sprintf(epilogue,"\n");
    sprintf(preamble,"");
    perfstats_print(preamble, stat_file, epilogue);
    perfstats_deinit();
  printf("%lf,%d\n",c[rand()%ARRAY_SIZE],(int)c[rand()%ARRAY_SIZE]);
  return 0;
}
