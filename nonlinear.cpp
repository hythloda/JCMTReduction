#include "nonlinear.h"
#include <stdio.h>

static const unsigned short N_1 = N+1;

static void contract(Vector[N_1], unsigned short);
static Vector reflect(Vector[N_1], unsigned short, double, bool);


Vector Simplex::minimize(Data *data)
{
  Vector amoeba[N_1], test, second_test;
  double eval[N_1], eval_test, factor, second_eval;
  unsigned short i,j,hi,low, second;
  bool redo;

  //set initial guess
  for (i=0; i<N; i++)
    amoeba[N][i] = 1;
  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
    {
      if (j==i)
        amoeba[i][j] = amoeba[N][j] + LAMBDA;
      else
        amoeba[i][j] = amoeba[N][j];
    }


  for (i=0; i<N_1; i++)
    eval[i] = data->chi2(amoeba[i]);


  for(;;)
    {
      if (redo == YES)
        for (i=0; i<N_1; i++)
          eval[i] = data->chi2(amoeba[i]);


      for (i=hi=low=0; i<N_1; i++)
      {
        if (eval[i] > eval[hi])
	  hi = i;
        if (eval[i] < eval[low])
	  low = i;
      }
      for (i=0; i<N_1; i++)
	if (i!=low && i!=hi)
	  {
	    second = i;
	    break;
	  }
      for (i=second; i<N_1; i++)
        if (i!=low && i!=hi && eval[i] > eval[second])
	  second = i;

      if (eval[hi] - eval[low] < TOL)
	return amoeba[low];


      test = reflect(amoeba,hi,1,YES);
      eval_test = data->chi2(test);
      redo = NO;

      if (eval_test < eval[low])
      {
	second_test = reflect(amoeba,hi,1.5,NO);
	second_eval = data->chi2(second_test);
	if (second_eval < eval_test)
	{
	  amoeba[hi] = second_test;
	  eval[hi] = second_eval;
	  continue;
	}
      }
      else if (eval_test > eval[second])
      {
        test = reflect(amoeba,hi,.5,NO);
        eval_test = data->chi2(test);
	if (eval_test > eval[hi])
	{
	  contract(amoeba,low);
	  redo = YES;
	  continue;
	}
      }
      amoeba[hi] = test;
      eval[hi] = eval_test;

    }
}



static Vector reflect(Vector amoeba[N_1], unsigned short point, double mag, bool redo)
{
  static Vector average;

  if (redo == YES)
  {
    average = 0;
    for (unsigned short i=0; i<N_1; i++)
      if (i != point)
       average = average + amoeba[i];
    average = average / N;
  }

  return (average - amoeba[point])*mag + average;
}


static void contract(Vector amoeba[N_1], unsigned short low)
{
  for (unsigned short i=0; i<N_1; i++)
    if (i != low)
      amoeba[i] = (amoeba[i] + amoeba[low])/2;
}







Simplex::Simplex()
{
  LAMBDA = 1e-2;
  TOL = 1e-5;
}


Simplex::Simplex(double tol, double lambda)
{
  LAMBDA = lambda;
  TOL = tol;
}



double Data::chi2(Vector param)
{
  double result = 0, diff;

  for (unsigned long i=0; i<Npts; i++)
  {
    diff = func(param,x[i]) - y[i];
    result += diff*diff;
  }
  return result;
}




char *number::operator () ()
{
  static char string[100];
  sprintf(string,"%f%c%f\0",val,plus_minus,err);
  return string;
}


number make_number(double _val, double _err)
{
  number result;

  result.val = _val;
  result.err = _err;
  return result;
}
