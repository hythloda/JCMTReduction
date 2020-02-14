#include <string.h>
#include "linear.h"
#include <stdio.h>
#include <stdarg.h>

Matrix Matrix::inv()
{
  static Matrix Idt;
  static Matrix Mtrx;
  unsigned short s,r,c;
  double fraction;

  //create inverse matrix
  for (r=0; r<N; r++)
    for (c=0; c<N; c++)
    {
      Idt.pt[r][c] = r == c;
      Mtrx[r][c] = pt[r][c];
    }

// run the matrix inversion algorithm
  for (s=0; s<N; s++)
    for (r=0; r<N; r++)
      if (r!=s)
	for (fraction = Mtrx[r][s]/Mtrx[s][s], c=0; c<N; c++)
	  {
            Mtrx[r][c] =    Mtrx[r][c] -  Mtrx[s][c]*fraction;
	    Idt[r][c] =   Idt[r][c] - Idt[s][c]*fraction;
	  }


  for (r=0; r<N; r++)
    for (c=0; c<N; c++)
     {
       //           printf("Idt[%d][%d] = %lf\n", r,c,Mtrx[r][c]/Mtrx[r][r]);
             Idt[r][c] = Idt[r][c]/Mtrx[r][r];
     }

  return Idt;

}




char *Vector::print()
{
  static char string[200];
  char buffer[30];

  for (unsigned short i=0; i<N; i++)
    {
      sprintf(buffer,"%f",pt[i]);
      strcat(string,buffer);
      strcat(string,"  ");
    }

  return string;
}



Vector vector(double zeroeth,...)
{
  Vector result;
  va_list list;

  result[0] = zeroeth;
  va_start(list, zeroeth);
  for(unsigned short i=1; i<N; i++)
      result[i] = va_arg(list, double);
  va_end(list);

  return result;
}
