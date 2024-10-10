#include <stdio.h>
#include <stdlib.h>

//START
struct grades
{
  int *id;
  double **homework;
  double *average;
};

int main(int argc, char **argv)
{
  struct grades gradesheet;
  int i,j; 
  int total_number_students = 28800;
  int homework_items = 10000;
  double average = 0;
  int student_average = 1;
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

  gradesheet.id = (int *)malloc(total_number_students*sizeof(int));
  for(i=0;i<total_number_students;i++)
    gradesheet.id[i] = rand();

  gradesheet.homework = (double **)malloc((homework_items+1)*sizeof(double *));
//END

  for(i=0;i<homework_items;i++)
  {
    gradesheet.homework[i] = (double *)malloc(total_number_students*sizeof(double));
    for(j=0;j<total_number_students;j++)
      gradesheet.homework[i][j] = rand();
  }

  gradesheet.average = (double *)malloc(total_number_students*sizeof(double));
  
  /* Counting average for each student */
  if(student_average)
  {
    for(i=0;i<total_number_students; i++)
    {
      gradesheet.average[i] = 0.0;
      for(j=0;j<homework_items;j++)
      {
        gradesheet.average[i]+=gradesheet.homework[j][i];
      }
      gradesheet.average[i] /= homework_items;
    }
  }  
  /* Counting average for each homework */
  else
  {
//START_SELECT
    for(i = 0;i < homework_items; i++)
    {
      gradesheet.homework[i][total_number_students] = 0.0;
      for(j = 0; j < total_number_students;j++)
      {
        gradesheet.homework[i][total_number_students] += gradesheet.homework[i][j];
      }
      gradesheet.homework[i][total_number_students] /= total_number_students;
    }
//END_SELECT
  }
  return 0;
}
