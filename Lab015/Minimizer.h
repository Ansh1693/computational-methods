/* ****************************************************************************** */
#ifndef MINIMIZER_H_INCLUDED
#define MINIMIZER_H_INCLUDED
#include "Point.h"
#include "Polynomial.h"
#include "myFunction.h"
/* ******************************************************************** */
/* Auxiliary enumerations                                               */
/* ******************************************************************** */

typedef enum fnType {POLYNOMIAL, FUNCTION} fnType;

typedef enum MINIMA_METHOD {
    LINEAR,
    VARIABLE_LINEAR,
    GOLDEN_SECTION,
    FIBONACCI,
    NEWTON,
    BINARY,
    GRADIENT
} ROOT_METHOD;

class Minimizer{
    tInterval I; // interval in which minimization to be done
    double Minima; // The minima point
    Polynomial P;
    myFunction F;
    fnType T;
    MINIMA_METHOD M;
    double eps;
Minimizer() {}
    long (Minimizer::*Minimize)();
    double Fn(double x){
        if (T == POLYNOMIAL) {
            if (P.isZero()) return nan("Polynomial is zero");
            return P(x);
        }
        else if (T == FUNCTION) {
            if (F.isZero()) return nan("Function is NULL");
            return F(x);
        }
        else throw myException("Minimizer: Wrong type in Fn\n");
    }
    double dF(double x) {//finds the first derivative
        const static double h = 0.5e-4;
        const static double h2 = 1.0e-4;
        const static double d = 1.0/(6 * h2);
        if (T == POLYNOMIAL) {
            if (P.isZero()) return nan("Polynomial is zero");
            return (-P(x+h2) + 8.0*P(x+h)-8.0*P(x-h)+P(x-h2)) * d;
        }
        else if (T == FUNCTION) {
            if (F.isZero()) return nan("Function is NULL");
            return (-F(x+h2) + 8.0*F(x+h)-8.0*F(x-h)+F(x-h2)) * d;
        }
        else throw myException("Minimizer: Wrong type in Fn\n");
    }

    double d2F(double x) {//finds the second derivative
        const static double h = 0.5e-4;
        const static double h2 = 1.0e-4;
        const static double d = 1.0/(3 * 1.0e-8);
        if (T == POLYNOMIAL) {
            if (P.isZero()) return nan("Polynomial is zero");
            return (-P(x+h2) + 16*P(x+h)-30.0*P(x)+ 16.0*P(x-h)-P(x-h2)) * d;
        }
        else if (T == FUNCTION) {
            if (F.isZero()) return nan("Function is NULL");
            return (-F(x+h2) + 16*F(x+h)-30.0*F(x)+ 16.0*F(x-h)-F(x-h2)) * d;
        }
        else throw myException("Minimizer: Wrong type in Fn\n");
    }
protected:
    void SetMinFunction(MINIMA_METHOD m) {
        switch (m) {
            case LINEAR : Minimize = &Minimizer::LinearSearch; break;
            case VARIABLE_LINEAR : Minimize = &Minimizer::VarLinearSearch; break;
            // case GOLDEN_SECTION : Minimize = &Minimizer::Golden; break;
            // case FIBONACCI : Minimize = &Minimizer::Fibonacci; break;
            // case BINARY : Minimize = &Minimizer::Binary; break;
            case NEWTON : Minimize = &Minimizer::Newton; break;
            // case GRADIENT: Minimize = &Minimizer::GradientDescent; break;
            default: Minimize = NULL; break;
        }
    }
    /* ************************************************************* */
    /* Search functions: TO BE IMPLEMENTED                           */
    /* ************************************************************* */
    // Finds the root sets Root.R, nan if no zero, returns the number
    // of function evaluation return is negative if no root found
    // 'A' is the interval of search
    long LinearSearch(tInterval A);		//LAB010
    long VarLinearSearch(tInterval A);	//LAB011
    // long Golden(tInterval A);			//LAB012
    // long Fibonacci(tInterval A);		//LAB013
    // long Binary(tInterval A);			//LAB014
    long Newton(tInterval A);			//LAB015
    // long GradientDescent(tInterval A);	//LAB016
public:

Minimizer(myFunction f, tInterval interval, MINIMA_METHOD m=LINEAR)
            : F(f), I(interval), T(FUNCTION), M(m) {
        if (m==LINEAR) eps = 1.0e-3;
        else if (m==VARIABLE_LINEAR) eps = 1.0e-6;
        else eps = 1.0e-10;
        SetMinFunction(m);
    }
Minimizer(double (*f)(double), tInterval interval, MINIMA_METHOD m=LINEAR)
            : F(f), I(interval), T(FUNCTION), M(m) {
        if (m==LINEAR) eps = 1.0e-3;
        else if (m==VARIABLE_LINEAR) eps = 1.0e-6;
        else eps = 1.0e-10;
        SetMinFunction(m);
    }

Minimizer(Polynomial p, tInterval interval, MINIMA_METHOD m=LINEAR)
            : P(p), I(interval), T(POLYNOMIAL), M(m) {
        if (m==LINEAR) eps = 1.0e-3;
        else if (m==VARIABLE_LINEAR) eps = 1.0e-6;
        else eps = 1.0e-10;
        SetMinFunction(m);
    }

    MINIMA_METHOD getMethod() { return M; }
    MINIMA_METHOD setMethod(MINIMA_METHOD method) {
        M = method;
        SetMinFunction(M);
        return M;
    }

    double&myEPS() {return eps;}
    Polynomial&Poly() { return P;}
    myFunction&Function() { return F;}
    double getMinima() {return Minima;}
    /* ************************************************************* */
    /* Search functions:                                             */
    /* ************************************************************* */
    // Finds the root sets Root.R, nan if no zero,
    // returns the number of function evaluation
    // return is negative of the COUNT of fn evaluation if no root found
    long LinearSearch() { return LinearSearch(I); }
    long VarLinearSearch() { return VarLinearSearch(I); }
    // long Golden() { return Golden(I); }
    // long Fibonacci() { return Fibonacci(I); }
    // long Binary() { return Binary(I); }
    long Newton() { return Newton(I); }
    // long GradientDescent() {return GradientDescent(I); }
         //Count returned equals both function and derivative call
         //Remember to set dF or dP as the case may be
    /* ************************************************************* */
    /* Virtual functions                                             */
    /* ************************************************************* */
    virtual long findMinima() { return (this->*Minimize)(); }
};
#endif // MINIMIZER_H_INCLUDED/* ****************************************************************************** */


long Minimizer::LinearSearch(tInterval A){
    if (I.isZero())
        throw myException("Error:- LinearSearch: Zero interval for search.\n");
    if (!I.isInitialized())
        throw myException("Error:- LinearSearch: Interval not initialized for search.\n");
    if (T == POLYNOMIAL && P.isZero()) throw myException("Error:- LinearSearch: Polynomial not initialized.\n");
    if (T == FUNCTION && F.isZero()) throw myException("Error:- LinearSearch: Function not initialized.\n");
    long COUNT = 0;
    double a=A.x,b=A.y,fa,fb,x,y;
    double tol= eps;
    x=A.x;
    y=x+tol;
    fa= Fn(a);
    fb= Fn(y);
    do{
        fa=fb;
        x=y;
        y=y+tol;
        fb=Fn(y);
        COUNT++;
        if(ABS(fb-fa)< tol)
        {
            Minima = x;
            return COUNT;
        }
    }while(fb<fa && y<b);
    Minima = std::nan("Not Converge");
    return -COUNT;
}

long Minimizer::VarLinearSearch(tInterval A) {
    if (I.isZero())
        throw myException("Error:- LinearSearch: Zero interval for search.\n");
    if (!I.isInitialized())
        throw myException("Error:- LinearSearch: Interval not initialized for search.\n");
    if (T == POLYNOMIAL && P.isZero()) throw myException("Error:- LinearSearch: Polynomial not initialized.\n");
    if (T == FUNCTION && F.isZero()) throw myException("Error:- LinearSearch: Function not initialized.\n");
    double a=A.x,b=A.y,fa,fb,x,y;
    long COUNT = 0;
    double tol= eps;
    double STEPSIZE = eps, EPSILON=eps;
    double factor = 2.0;
    long MAXITER = 100000;
    x=a;
    fa= Fn(a);
    while(COUNT < MAXITER)
    {
        y=x+ STEPSIZE;
        while(y>b || y<a){
            STEPSIZE/= factor;
            y=x+ STEPSIZE;
        }
        fb= Fn(y);
        if(fb < fa){
            fa=fb;
            x=y;
            if(Fn(y+EPSILON)> fb){
                EPSILON= -EPSILON;
                STEPSIZE= -STEPSIZE / factor;
            }
            else{
                STEPSIZE= STEPSIZE * factor;
            }
        }
        else{
            STEPSIZE= STEPSIZE / factor;
        }
        COUNT++;
        if(ABS(STEPSIZE)<eps){
            Minima = y;
            return COUNT;
        }
    }
    Minima = std::nan("Not Converge");
    return -COUNT;
}

long Minimizer::Newton(tInterval A) {
    // TO BE IMPLEMENTED LAB015
    if (I.isZero())
        throw myException("Error:- NewtonSearch: Zero interval for search.\n");
    if (!I.isInitialized())
        throw myException("Error:- NewtonSearch: Interval not initialized for search.\n");
    if (T == POLYNOMIAL && P.isZero()) throw myException("Error:- NewtonSearch: Polynomial not initialized.\n");
    if (T == FUNCTION && F.isZero()) throw myException("Error:- NewtonSearch: Function not initialized.\n");
    long COUNT = 0;
    Minima = std::nan("Root not initialized");
    double x0 = A.x,f0,d0,x1=A.y,f1,d1,d2,x;
    int N= 1000;
    double step = eps;
    x= x0;
    do{
      f0= Fn(x0);
      d1= dF(x0);
      d2= d2F(x0);
      x0 = x0 - (d1/d2);
      step = step+1;
      if(ABS(x0-x)<eps){break;}
      if(step > N){break;}
      x= x0;
    }while(ABS(f0) > eps);
    Minima = x0;
    return step;
}