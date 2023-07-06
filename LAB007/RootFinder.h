#ifndef ROOTFINDER_H_INCLUDED
#define ROOTFINDER_H_INCLUDED

#include <iostream>
#include <iomanip>

// #include "AuxiliaryFunction.h"
// #include "myException.h"
// #include "myFunction.h"
#include "Polynomial.h"
#include "Root.h"
#include "Point.h"

/* ******************************************************************** */
/* Auxiliary enumerations                                               */
/* ******************************************************************** */

typedef enum fnType {POLYNOMIAL, FUNCTION} fnType;

typedef enum ROOT_METHOD {
    LINEAR,
    VARIABLE_LINEAR,
    BISECTION,
    REGULA_FALSI,
    SECANT,
    NEWTON_RAPHSON
} ROOT_METHOD;

/* ******************************************************************** */
/* RootFinder Class                                                     */
/* ******************************************************************** */

class RootFinder: public Root{
private:
    double eps;
    Polynomial Poly;
    public:
    myFunction Func;
    private:
    Polynomial dP;
    myFunction dF;
    fnType t;
    ROOT_METHOD m;
    long (RootFinder::*RootFn)();

    double Fn(double x){
        if (t == POLYNOMIAL) return Poly(x);
        else if (t == FUNCTION) return Func(x);
        else throw myException("RootFinder: Wrong type in Fn\n");
    }

    double dFn(double x){
        if (t == POLYNOMIAL &&dP.isZero()) return nan("Derivative Polynomial is zero");
        else if (t == FUNCTION &&dF.isZero()) return nan("Derivative Function is Null");
        if (t == POLYNOMIAL) return dP(x);
        else if (t == FUNCTION) return dF(x);
        else throw myException("RootFinder: Wrong type in dFn\n");
    }

protected:
RootFinder() {}
    void SetRootFunction(ROOT_METHOD m) {
        switch (m) {
            case LINEAR : RootFn = &RootFinder::LinearSearch; break;
            case VARIABLE_LINEAR : RootFn = &RootFinder::VarLinearSearch; break;
            case BISECTION : RootFn = &RootFinder::Bisection; break;
            case REGULA_FALSI : RootFn = &RootFinder::RegulaFalsi; break;
            // case SECANT : RootFn = &RootFinder::Secant; break;
            // case NEWTON_RAPHSON : RootFn = &RootFinder::Newton; break;
            default: RootFn = NULL; break;
        }
        if (t == POLYNOMIAL) dP = Poly.Derivative();
    }

    /* ************************************************************* */
    /* Search functions: TO BE IMPLEMENTED*/
    /* ************************************************************* */
    // Finds the root sets Root.R, nan if no zero, returns the number
    // of function evaluation return is negative if no root found
    // 'A' is the interval of search
    long LinearSearch(tInterval A);          // LAB004
    long VarLinearSearch(tInterval A);       // LAB005
    long Bisection(tInterval A);             // LAB006
    long RegulaFalsi(tInterval A);           // LAB007
    // long Secant(tInterval A);                // LAB008
    // long Newton(tInterval A);                // LAB009
//Count returned equals both function and derivative call
                            //Remember to set dF or dP as the case may be
    /* ************************************************************* */
    /* Search functionsabove only to be implemented*/
    /* ************************************************************* */

public:
    //Constructors
RootFinder(tInterval interval, Polynomial P, ROOT_METHOD Method = LINEAR) :
        Root(interval), Poly(P), t(POLYNOMIAL), m(Method) {
        if (m==LINEAR) eps = 1.0e-3;
        else if (m==VARIABLE_LINEAR) eps = 1.0e-6;
        else eps = 1.0e-10;
        SetRootFunction(m);
    }

RootFinder(tInterval interval, double (*f)(double), ROOT_METHOD Method = LINEAR) :
        Root(interval), Func(f), t(FUNCTION), m(Method){
        if (m==LINEAR) eps = 1.0e-3;
        else if (m==VARIABLE_LINEAR) eps = 1.0e-6;
        else eps = 1.0e-10;
        SetRootFunction(m);
    }

RootFinder(double x, double y, Polynomial P, ROOT_METHOD Method = LINEAR) :
        Root(x,y), Poly(P), t(POLYNOMIAL), m(Method) {
        if (m==LINEAR) eps = 1.0e-3;
        else if (m==VARIABLE_LINEAR) eps = 1.0e-6;
        else eps = 1.0e-10;
        SetRootFunction(m);
    }
RootFinder(double x, double y, double (*f)(double) , ROOT_METHOD Method = LINEAR) :
        Root(x,y), Func(f), t(FUNCTION), m(Method){
        if (m==LINEAR) eps = 1.0e-3;
        else if (m==VARIABLE_LINEAR) eps = 1.0e-6;
        else eps = 1.0e-10;
        SetRootFunction(m);
    }

    //set or get the parameters for controlling
    ROOT_METHOD getMethod() { return m; }
    ROOT_METHOD setMethod(ROOT_METHOD method) {
        m = method;
        SetRootFunction(m);
        return m;
    }

    double&myEPS() {return eps;}
    Polynomial&P() { return Poly;}
    myFunction&F() { return Func;}
    Polynomial&dPoly(){ return dP;}
    myFunction&dFunc(){ return dF;}

    /* ************************************************************* */
    /* Search functions:                                             */
    /* ************************************************************* */
    // Finds the root sets Root.R, nan if no zero,
    // returns the number of function evaluation
    // return is negative of the COUNT of fn evaluation if no root found
    long LinearSearch() { return LinearSearch(I); }
    long VarLinearSearch() { return VarLinearSearch(I); }
    long Bisection() { return Bisection(I); }
    long RegulaFalsi() { return RegulaFalsi(I); }
    // long Secant() { return Secant(I); }
    // long Newton() { return Newton(I); }
         //Count returned equals both function and derivative call
         //Remember to set dF or dP as the case may be
    /* ************************************************************* */
    /* Virtual functions                                             */
    /* ************************************************************* */
    virtual long findRoot() { return (this->*RootFn)(); }
};
#endif // ROOTFINDER_H_INCLUDED

long RootFinder::LinearSearch(tInterval A){
    if (I.isZero())
        throw myException("Error:- LinearSearch: Zero interval for search.\n");
    if (!I.isInitialized())
        throw myException("Error:- LinearSearch: Interval not initialized for search.\n");
    if (t == POLYNOMIAL && Poly.isZero()) throw myException("Error:- LinearSearch: Polynomial not initialized.\n");
    if (t == FUNCTION && Func.isZero()) throw myException("Error:- LinearSearch: Function not initialized.\n");
    long COUNT = 0;
    R = std::nan("Root not initialized");
    double a = A.x, b = A.y,c;
    double step = eps;
    c = a;
    int currSign = SIGN(Fn(a)), newSign;
    COUNT++;
    while (c < b) {
        c += step;
        newSign = SIGN(Fn(c));
        COUNT++;
        if (currSign != newSign) {
            R = (a+c)*0.5;
            return COUNT;
        }
        else a = c;
    }
    R = std::nan("Root not Found");
    return -COUNT;
}

long RootFinder::VarLinearSearch(tInterval A){
    if (I.isZero())
        throw myException("Error:- LinearSearch: Zero interval for search.\n");
    if (!I.isInitialized())
        throw myException("Error:- LinearSearch: Interval not initialized for search.\n");
    if (t == POLYNOMIAL && Poly.isZero()) throw myException("Error:- LinearSearch: Polynomial not initialized.\n");
    if (t == FUNCTION && Func.isZero()) throw myException("Error:- LinearSearch: Function not initialized.\n");
    long COUNT = 0;
    R = std::nan("Root not initialized");
    double a = A.x, b = A.y,c,fx;
    double step = eps,d=eps;
    double factor = 1.1;
    c = a;
    int currSign = SIGN(Fn(a)), newSign;
    while (c < b) {
        fx=Fn(c);
        currSign=SIGN(fx);
        c += d;
        newSign = SIGN(Fn(c));
        COUNT++;
        if(dAbs(fx)<step*10){
            R = c;
            return COUNT;
        }
        if(currSign != newSign){
            d=-SIGN(d)*step;
        }
        else{
            d=d*factor;
        }
    }
    R = std::nan("Root not Found");
    return -COUNT;
}

long RootFinder::Bisection(tInterval A){
    if (I.isZero())
        throw myException("Error:- BisectionSearch: Zero interval for search.\n");
    if (!I.isInitialized())
        throw myException("Error:- BisectionSearch: Interval not initialized for search.\n");
    if (t == POLYNOMIAL && Poly.isZero()) throw myException("Error:- BisectionSearch: Polynomial not initialized.\n");
    if (t == FUNCTION && Func.isZero()) throw myException("Error:- BisectionSearch: Function not initialized.\n");
    double a = A.x;
    double b = A.y;
    double c = 0;
    double eps = 1e-9; // set the desired precision

    while (b - a > eps) {
        c = (a + b) / 2;
        if (Func(c) == 0) {
            break;
        } else if (Func(a) * Func(c) < 0) {
            b = c;
        } else {
            a = c;
        }
    }
    return c;
}

long RootFinder::RegulaFalsi(tInterval A) {
     if (I.isZero())
        throw myException("Error:- LinearSearch: Zero interval for search.\n");
    if (!I.isInitialized())
        throw myException("Error:- LinearSearch: Interval not initialized for search.\n");
    if (t == POLYNOMIAL && Poly.isZero()) throw myException("Error:- LinearSearch: Polynomial not initialized.\n");
    if (t == FUNCTION && Func.isZero()) throw myException("Error:- LinearSearch: Function not initialized.\n");
    long COUNT = 0;
    R = std::nan("Root not initialized");
    double x1 = A.x;
    double x2 = A.y;
    double f1 = Fn(x1);
    double f2 = Fn(x2);
    double x3 = 0.0;
    double f3 = 0.0;
    long count = 0;

    if (f1 * f2 > 0) {
        throw myException("RegulaFalsi: Function has same sign at both endpoints of the interval.");
    }

    while (fabs(x2 - x1) > eps) {
        x3 = x1 - (x2 - x1) * f1 / (f2 - f1);
        f3 = Fn(x3);
        count += 2; // Two function evaluations in each iteration

        if (f3 == 0.0 || fabs(x2 - x1) / 2 < eps) {
            R = x3;
            return count;
        }

        if (f3 * f1 < 0) {
            x2 = x3;
            f2 = f3;
        } else {
            x1 = x3;
            f1 = f3;
        }
    }

    return -count; // No root found within the given interval
}
