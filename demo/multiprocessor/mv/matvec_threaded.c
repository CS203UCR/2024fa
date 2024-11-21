#include <stdio.h>
#include <stdlib.h>
#include "perfstats.h"
#include <pthread.h>

struct thread_args
{
    double **a; 
    double *b; double *c; 
    int start; 
    int end;
    int ARRAY_SIZE;
};
void mv_threaded(void *args){
  /* Do matrix vector multiplications */
    struct thread_args *pars = (struct thread_args *)args;
    double **a = pars->a;
    double *b = pars->b;
    double *c = pars->c;
    int start = pars->start; 
    int end = pars->end;
    int ARRAY_SIZE = pars->ARRAY_SIZE;
    int NUM_OF_THREADS =2;
    double result;
    for(int i = start; i < end; i++)
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
  int i,j,start=0;
  pthread_t *thread;
  int *tids; 
  int NUM_OF_THREADS=2;
  thread = (pthread_t *)malloc(sizeof(pthread_t)*NUM_OF_THREADS);
  struct thread_args *pars = (struct thread_args *)malloc(sizeof(struct thread_args)*NUM_OF_THREADS);
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
    for(i = 0 ; i < NUM_OF_THREADS-1 ; i++)
    {
        pars[i].a = a;
        pars[i].b = b;
        pars[i].c = c;
        pars[i].ARRAY_SIZE = ARRAY_SIZE;
        pars[i].start = start;
        pars[i].end = start+ARRAY_SIZE/NUM_OF_THREADS;
        start = pars[i].end;
        pthread_create(&thread[i], NULL, mv_threaded, &pars[i]);
    }
        pars[i].a = a;
        pars[i].b = b;
        pars[i].c = c;
        pars[i].ARRAY_SIZE = ARRAY_SIZE;
        pars[i].start = start;
        pars[i].end = start+ARRAY_SIZE/NUM_OF_THREADS;
        start = pars[i].end;
    mv_threaded(&pars[i]);
    for(i = 0 ; i < NUM_OF_THREADS-1 ; i++)
        pthread_join(thread[i], NULL);
    perfstats_disable(1);
    sprintf(epilogue,"\n");
    sprintf(preamble,"");
    perfstats_print(preamble, stat_file, epilogue);
    perfstats_deinit();
  printf("%lf,%d\n",c[rand()%ARRAY_SIZE],(int)c[rand()%ARRAY_SIZE]);
  return 0;
}
