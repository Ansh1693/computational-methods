#ifndef MYFUNCTION_H_INCLUDED
#define MYFUNCTION_H_INCLUDED
#include "myException.h"
/* *********************************************************** */
/* This class provides a framework for providing a consistent  */
/* interface to a single independent value function            */
/* *********************************************************** */
class myFunction{
    double (*f)(double); //the function place holder
public:
myFunction(){f = NULL;}
myFunction(double (*g)(double)) { f = g; }
myFunction(const myFunction& x) { f = x.f; }
    myFunction& operator = (myFunction &x){ f = x.f; return *this;}
    myFunction& operator = (double (*g)(double)){ f = g; return *this;}
    bool isZero() {return f == NULL;}
    double operator () (double x){
        if (isZero()) throw myException("Calling a null function\n");
        return f(x);
    }
};
#endif // MYFUNCTION_H_INCLUDED /*
