#include <stdio.h>
#include <stdlib.h>

int ARRAY_SIZE = 4096*4096;

int main(int argc, char **argv)
{
  int *a, *b, *c, *d, *e, *f;
  int i, j, base, iters=1;
  base = rand()%100;
  /* initialize a, b */
  if(argc >= 2)
    ARRAY_SIZE = atoi(argv[1]);
  if(argc == 3)
    iters = atoi(argv[2]);
  a = (int *)malloc(ARRAY_SIZE*sizeof(int));
  for(i = 0; i < ARRAY_SIZE; i++)
      a[i] = (base)+1;
  b = (int *)malloc(ARRAY_SIZE*sizeof(int));
  for(i = 0; i < ARRAY_SIZE; i++)
      b[i] = (base)+1;
  c = (int *)malloc(ARRAY_SIZE*sizeof(int));
  for(i = 0; i < ARRAY_SIZE; i++)
      c[i] = (base)+1;
  d = (int *)malloc(ARRAY_SIZE*sizeof(int));
  for(i = 0; i < ARRAY_SIZE; i++)
      d[i] = (base)+1;
  e = (int *)malloc(ARRAY_SIZE*sizeof(int));
  for(i = 0; i < ARRAY_SIZE; i++)
      e[i] = (base)+1;

//  mm(a, b, c);
  /* Do matrix addition */
#ifdef A
for(j=0;j<iters;j++)
{
    for(i = 0; i < ARRAY_SIZE; i++)
    {
        e[i] = a[i]*b[i]+c[i];
    }
    for(i = 0; i < ARRAY_SIZE; i++)
    {
        e[i] /=(d[i]);
    }
}
#else
#ifndef NO
for(j=0;j<iters;j++)
    for(i = 0; i < ARRAY_SIZE; i++)
    {
        e[i] = (a[i]*b[i]+c[i])/(d[i]);
    }
#endif
#endif
  printf("%d\n",e[rand()%256]);
  free(a);
  free(b);
  free(c);
  free(d);
  free(e);
  
  return 0;
}
