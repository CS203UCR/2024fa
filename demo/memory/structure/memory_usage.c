#include <stdio.h>
#include <stdlib.h>

#ifdef A
//START_1
struct student
{
  int id;
  double *homework;
  int participation;
  double midterm;
  double average;
};
//END_1
#else
//START_2
struct student
{
  int id;

  double *homework;
  double midterm;
  double average;
      int participation;
};
#endif
//END_2

int size=65533;
int max=65538;

int main(int argc, char **argv)
{
  int i;
  struct student *students;
  students = malloc(sizeof(struct student)*size);
/*  for(i=0;i<size;i++)
  {
    students[i].id = rand();
    students[i].year = 2016;
    students[i].sold = 0.0;
    students[i].viewers = 3000;
    students[i].score = 0.0;          
  }*/
    printf("%lu\n",sizeof(struct student));
//  printf("Hello, world! %d %lf\nHow big is a \"student?\" %lu\n",students[rand()%size].id,students[rand()%size].score,sizeof(struct student));
  return 0;
}