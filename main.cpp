#include <stdio.h>
#include <iostream.h>
#include "nonlinear.h"


struct Table : Data
{
  double func(Vector param, double x)
    // {return param[0]*exp(-sq(x/param[1])) + param[2];}
	{return param[0]*x+param[1];} //if change parameter number change N in linear.h
  bool read_file(const char[]);
  Table(){Npts = 0;}
  ~Table(){if (Npts != 0)free(x);free(y);}
};



int main(int Nargs, char **arg)
{
  Table table;
  Vector param;
  Simplex simplex;

	char fname[200];

	strcpy(fname,"/Users/amandamartin/Documents/work/luhman/JCMT/code/Jason/data");
  if (table.read_file(fname) == NO)
    {
      cout << "Unable to read data.\n";
      return 0;
    }

  simplex.TOL = 1e-8; // ARE THE FITTER
  param = simplex.minimize(&table); // ARE THE FITTER
  for (int i=0; i<N; i++)  // ARE THE FITTER
    cout << param[i] << endl;  // ARE THE FITTER

  return 1;
}




bool Table::read_file(const char filename[])
{
  FILE *file;

  //open the data file
  file = fopen(filename, "r");
  if (file == NULL)
    return NO;

  // count the number of data points
  for (Npts = 0; !feof(file); Npts++)
    fscanf(file, "%*f\t%*f\n");

  //allocate memory for the data
  if (Npts == 0)
    return NO;
  x = new double[Npts];
  y = new double[Npts];
  if (x == NULL || y == NULL)
    return NO;

  // go back and actually read the data points in
  rewind(file);
  for (unsigned long i=0; i<Npts; i++)
    fscanf(file, "%lf\t%lf\n", &x[i], &y[i]);

  //close file and return
  fclose(file);
  return YES;
}
