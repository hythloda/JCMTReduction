#include <Carbon/Carbon.h>
#include <math.h>

#ifndef linear_dot_h
#define linear_dot_h

#define N 2

#ifndef sq
#define sq(x)(((x)*(x)))
#endif


static unsigned short i;


struct Vector
{
  double pt[N];
  double &operator [] (unsigned short i){return pt[i];}

  void operator =(double arg)
  {
    for (i=0; i<N; i++)
      pt[i] = arg;
  }

  double length()
  {
    double result = 0;

    for (i=0; i<N; i++)
      result += sq(pt[i]);

    return sqrt(result);
  }
  double signed_length()
  {
    double result = 0;

    for (i=0; i<N; i++)
      result += sq(pt[i]);

    result = sqrt(result);

    for (i=0; i<N; i++)
      if (pt[i] < 0)
	result = -result;

    return result;
  }
  char *print();
  void operator = (Vector arg)
  {
    for (i=0; i<N; i++)
      pt[i] = arg.pt[i];
  }
  Vector operator - (Vector arg)
  {
    Vector difference;

    for (i=0; i<N; i++)
      difference[i] = pt[i] - arg.pt[i];
    return difference;
  }
  Vector operator + (Vector arg)
  {
    Vector difference;

    for (i=0; i<N; i++)
      difference[i] = pt[i] + arg.pt[i];
    return difference;
  }
  Vector operator * (double arg)
  {
    Vector difference;

    for (i=0; i<N; i++)
      difference[i] = pt[i] ? pt[i] * arg : 0;
    return difference;
  }
  Vector operator / (double arg)
  {
    Vector difference;

    for (i=0; i<N; i++)
      difference.pt[i] = pt[i] / arg;
    return difference;
  }
};


struct Matrix
{
  Vector pt[N];
  Vector &operator [] (unsigned short i){return pt[i];}

  Matrix inv();
  Vector operator * (Vector arg)
  {
    Vector result;
    for (unsigned short i=0; i<N; i++)
      {
	result[i] = 0;
	for (unsigned short j=0; j<N; j++)
	  result[i] += pt[i][j]*arg[j];
      }
    return result;
  }
};


Vector vector(double,...);


const double dx = 1e-5;

#define grad(f,x)  (*vpt,({       \
       static Vector g;           \
       double buffer = f;         \
       for (unsigned short K=0; K<N; K++)    \
       {                          \
        x[K]-=dx;                 \
        g[K]=(buffer-f)/dx;       \
        x[K]+=dx;                 \
       }                          \
       vpt = &g;}),*vpt)          \

#endif
