#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *id;
    double **homeworks; // 1-d->homework item; 2-d->student
    double *averages;
}gradesheet;

int main(int argc, char **argv)
{
  gradesheet sheet;
  int i,j; 
  int total_number_students = 28800;
  int homework_items = 10000;
  double average = 0;
  int student_average = 1;
  double 
  if(argc >= 3)
  {
    total_number_students = atoi(argv[1]);
    homework_items = atoi(argv[2]);
  }
  else
  {
    fprintf(stderr,"%s total_number_students homework_items",argv[0]);
    exit(1);
  }
  if(argc >= 4)
    student_average = 0;
  sheet = (gradesheet *)malloc((total_number_students + 1)*sizeof(gradesheet));
  for(i=0;i<total_number_students+1; i++)
  {
      sheet[i].homework = (double *)malloc((total_number_students)*sizeof(double));
      for(j=0;j<homework_items;j++)
        gradesheet[i].homework[j] = rand();
  }
  /* Counting average for each student */
  if(student_average)
  {
    for(i=0;i<total_number_students; i++)
    {
      average = 0.0;
      for(j=0;j<homework_items;j++)
      {
        average+=gradesheet[i].homework[j];
      }
      gradesheet[i].average = average/homework_items;
    }
  }
  /* Counting average for each homework */
  else
  {
    for(i=0;i<homework_items; i++)
    {
      gradesheet[total_number_students].homework[i] = 0.0;
      for(j=0;j<total_number_students;j++)
        gradesheet[total_number_students].homework[i] +=gradesheet[j].homework[i];
      gradesheet[total_number_students].homework[i] /= (double)total_number_students;
    }
  }

    return 0;    
}