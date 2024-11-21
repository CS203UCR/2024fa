#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

volatile int loop;
pthread_mutex_t loop_mutex;
void* modifyloop(void *x)
{
  sleep(1);

  while(loop < 100)
  {
    pthread_mutex_lock(&loop_mutex);
    loop++;
    pthread_mutex_unlock(&loop_mutex);
  }
  return NULL;
}

int main()
{
  pthread_t thread;
  loop = 1;
  
  pthread_create(&thread, NULL, modifyloop, NULL);
  
  while(loop<100)
  {
    pthread_mutex_lock(&loop_mutex);
    fprintf(stderr,"%d ", loop);
    pthread_mutex_unlock(&loop_mutex);
  }
  pthread_join(thread, NULL);
  
  fprintf(stderr,"%4d finished\n", loop);
  return 0;
}
