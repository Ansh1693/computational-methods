/********************************************************************************/
#ifndef AUXILIARYFUNCTION_H_INCLUDED
#define AUXILIARYFUNCTION_H_INCLUDED
#include <cstddef>
#include <cstring>
/* ******************************************************************** */
/* Auxiliary defined function Macros                                          */
/* ******************************************************************** */

#define strSIGN(x) (((x) >= (0)) ? "+" : "-")
#define SIGN(x) (((x) >= (0)) ? 1 : -1)
#define ABS(x) ((SIGN(x)) * (x))

/* ******************************************************************** */
/* Some constants                                                       */
/* ******************************************************************** */
#define myPI 3.14159265359
#define invPI 0.31830988618
#define SQRT2 1.41421356237
#define invSQRT2 0.70710678119

/* ******************************************************************** */

/* Some constants defined for use in code                               */
/* ******************************************************************** */
#define ACCURACY 1.0e-10
#define SET_PRECISION 15 // for printing
/* ******************************************************************** */
/* Useful functions: GIVEN                                              */
/* ******************************************************************** */
double Power(double x, long n); // Calculates x^n
/* Absolute Value Functions                                             */
long double ldAbs(long double x);
double dAbs(double x);
float fAbs(float x);
int iAbs(int x);
short sAbs(short x);
long lAbs(long x);
long long llAbs(long long x);
/* Swap functions                                                       */
void ldSwap(long double *x, long double *y);
void dSwap(double *x, double *y);
void fSwap(float *x, float *y);
void llSwap(long long *x, long long *y);
void lSwap(long *x, long *y);
void iSwap(int *x, int *y);
void Swap(void *x, void *y, size_t n); // assumes x and y of same size and type
/* ******************************************************************** */
/* Transcendental functions: TO BE IMPLEMENTED IN LAB003                */
double Exp(double);
double Sine(double);
double Cosine(double);
double Tangent(double);
double CoTangent(double);
double Cosec(double);
double Secant(double);
double Cosh(double);
double Sinh(double);
double Tanh(double);
double Cosech(double);
double Sech(double);
double Coth(double);
#endif // AUXILIARYFUNCTION_H_INCLUDED
/********************************************************************************/




/////////////////////////////////////////////////////////////////////


/* ******************************************************************** */
/* Useful functions                                                     */
/* ******************************************************************** */
double Power(double x, long n) {
    if (n < 0) {x = 1.0/x; n = -n;}
    if (n == 0) return 1.0;
    else {
        double y = 1.0;
        while(n) {
            if ((n%2) == 1) y *= x;
            x *= x;
            n >>= 1;
        }
        return y;
    }
}
/* AUXILIARY FUNCTIONS                                                                                */
long double ldAbs(long double x) { return x* (SIGN(x)); }
double dAbs(double x) {return (SIGN(x)) * x;}
float fAbs(float x) {return (SIGN(x)) * x;}
int iAbs(int x) {return (SIGN(x)) * x;}
short sAbs(short x) {return (SIGN(x)) * x;}
long lAbs(long x) {return (SIGN(x)) * x;}
long long llAbs(long long x) {return (SIGN(x)) * x;}
void ldSwap(long double *x, long double *y) { long double t = *x; *x = *y; *y = t;}
void dSwap(double *x, double *y) { double t = *x; *x = *y; *y = t;}
void fSwap(float *x, float *y) { float t = *x; *x = *y; *y = t;}
void llSwap(long long *x, long long *y) { long long t = *x; *x = *y; *y = t;}
void lSwap(long *x, long *y) { long t = *x; *x = *y; *y = t;}
void iSwap(int *x, int *y) { int t = *x; *x = *y; *y = t;}
void Swap(void *x, void *y, size_t n){
    void *t = ::operator new(n); //ideally check for allocation error
    memmove(t,x,n);
    memmove(x,y,n);
    memmove(y,t,n);
::operator delete(t);
}
