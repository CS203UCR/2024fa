#include <stdio.h>
#include <stdlib.h>

struct movie
{
  int id; // 4B
  int participation; // 4B
  double *homework; // 8B
  double midterm; // 8B
  double average; // 8B
};
      
int size=65533;
int max=65538;

int main(int argc, char **argv)
{
  int i;
  struct movie *movies;
  movies = malloc(sizeof(struct movie)*1);
/*  for(i=0;i<size;i++)
  {
    movies[i].id = rand();
    movies[i].year = 2016;
    movies[i].sold = 0.0;
    movies[i].viewers = 3000;
    movies[i].score = 0.0;          
  }*/
    printf("%lu\n",sizeof(struct movie));
//  printf("Hello, world! %d %lf\nHow big is a \"movie?\" %lu\n",movies[rand()%size].id,movies[rand()%size].score,sizeof(struct movie));
  return 0;
}