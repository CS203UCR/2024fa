#include <stdio.h>
#include <stdlib.h>
#include <ctime>

//#define D_TYPE float
#ifndef D_TYPE 
#define D_TYPE float
#endif

void cpumm(D_TYPE *a, D_TYPE *b, D_TYPE *c);
int n=512;
int ARRAY_SIZE=128;
double getCurrentTimestamp();
int main(int argc, char **argv)
{
  D_TYPE *a, *b, *c;
  int i, j, k;
  /* initialize a, b */
  if(argc == 2)
    ARRAY_SIZE = atoi(argv[1]);
  if(argc >= 3)
  {
    ARRAY_SIZE = atoi(argv[1]);
    n = atoi(argv[2]);
  }
  a = (D_TYPE *)malloc(ARRAY_SIZE*ARRAY_SIZE*sizeof(D_TYPE));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    for(j = 0; j < ARRAY_SIZE; j++)
      a[i*ARRAY_SIZE+j] = rand();
  }
  b = (D_TYPE *)malloc(ARRAY_SIZE*ARRAY_SIZE*sizeof(D_TYPE));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    for(j = 0; j < ARRAY_SIZE; j++)
      b[i*ARRAY_SIZE+j] = rand();
  }
  c = (D_TYPE *)malloc(ARRAY_SIZE*ARRAY_SIZE*sizeof(D_TYPE));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    for(j = 0; j < ARRAY_SIZE; j++)
      c[i*ARRAY_SIZE+j] = 0;
  }
  /* Do matrix multiplication */
  printf("Data type size: %d\n", sizeof(D_TYPE));
  cpumm(a, b, c);
  
#ifdef OUTPUT
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    for(j = 0; j < ARRAY_SIZE; j++)
    {
      fprintf(stderr,"%lf ",c[i*ARRAY_SIZE+j]);

    }
    fprintf(stderr,"\n");
  }
#endif
  return 0;
}
void cpumm(D_TYPE *a, D_TYPE *b, D_TYPE *c)
{
  int i,j,k, ii, jj, kk;
    double start_time = getCurrentTimestamp();
  for(i = 0; i < ARRAY_SIZE; i+=(ARRAY_SIZE/n))
  {
    for(j = 0; j < ARRAY_SIZE; j+=(ARRAY_SIZE/n))
    {
      for(k = 0; k < ARRAY_SIZE; k+=(ARRAY_SIZE/n))
      {        
          for(ii = i; ii < i+(ARRAY_SIZE/n); ii++)
            for(jj = j; jj < j+(ARRAY_SIZE/n); jj++)
              for(kk = k; kk < k+(ARRAY_SIZE/n); kk++)
                c[ii*ARRAY_SIZE+jj] += a[ii*ARRAY_SIZE+kk]*b[kk*ARRAY_SIZE+jj];
      }
    }
  }  
  double end_time = getCurrentTimestamp();
  double total_time = end_time - start_time;

  // Wall-clock time taken.
  printf("\nTime: %0.3f ms\n", total_time * 1e3);
  const float flops = (float)(2.0f * ARRAY_SIZE * ARRAY_SIZE * ARRAY_SIZE/ total_time);
  printf("\nThroughput: %0.2f GFLOPS\n\n", flops * 1e-9);
    fprintf(stderr,"%ld, %0.2f, 0, %lf\n", ARRAY_SIZE, flops * 1e-9, total_time);
}
// High-resolution timer.
double getCurrentTimestamp() {
#ifdef _WIN32 // Windows
  // Use the high-resolution performance counter.

  static LARGE_INTEGER ticks_per_second = {};
  if(ticks_per_second.QuadPart == 0) {
    // First call - get the frequency.
    QueryPerformanceFrequency(&ticks_per_second);
  }

  LARGE_INTEGER counter;
  QueryPerformanceCounter(&counter);

  double seconds = double(counter.QuadPart) / double(ticks_per_second.QuadPart);
  return seconds;
#else         // Linux
  timespec a;
  clock_gettime(CLOCK_MONOTONIC, &a);
  return (double(a.tv_nsec) * 1.0e-9) + double(a.tv_sec);
#endif
}
