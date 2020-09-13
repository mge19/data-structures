#include <stdio.h>
#include <stdlib.h>
bool sudokuchecker(int sudoku[9][9])
{
  bool control=true;
  int i,j,a,square[3][3];
  for(a=0;a<9;a++)
  {
    for(i=0;i<9;i++)
    {
      for(j=i+1;j<9;j++)
      {
        if(sudoku[i][a]==sudoku[j][a] ||     sudoku[a][i]==sudoku[a][j]) control=false;
      }
    }
  }
  if(control)   
  {
    for(a=0;a<3;a++)
    {
      for(int b=0;b<3;b++)   
        {
          for(i=0;i<3;i++)
          {
            for(j=0;j<3;j++)
            {
              square[i][j]=sudoku[3*a+i]    [3*b+j];
            }          
          }
          for(i=0;i<3;i++)
          {
            for(j=0;j<3;j++)
            {
              for(int c=0;c<3;c++)
              {
                for(int d=0;d<3;d++)
                {
                  if(!(i==c && j==d) && sudoku[i][j]==sudoku[c][d]) control=false;
                }
              }
            }          
          }         
       }
    }
  }
  return control;
}
int main()
{
  int sudoku1[9][9],sudoku2[9][9],sudoku3[9][9];
  FILE* input1=fopen("sudoku1.txt","r+");
  FILE* input2=fopen("sudoku2.txt","r+");
  FILE* input3=fopen("sudoku3.txt","r+");
  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      fscanf(input1,"%d ",&sudoku1[i][j]);
      fscanf(input2,"%d ",&sudoku2[i][j]);
      fscanf(input3,"%d ",&sudoku3[i][j]);
    }
  }
  if(sudokuchecker(sudoku1)) printf("The sudoku #1 is VALID\n");
  else printf("The sudoku #1 is INVALID\n");
  if(sudokuchecker(sudoku2)) printf("The sudoku #2 is VALID\n");
  else printf("The sudoku #2 is INVALID\n");
  if(sudokuchecker(sudoku3)) printf("The sudoku #3 is VALID\n");
  else printf("The sudoku #3 is INVALID\n");
  fclose(input1);
  fclose(input2);
  fclose(input3);
  system("PAUSE"); 
  return 0;
}
