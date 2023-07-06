#include "RootFinder.h"
const int MAX_ITERATIONS = 1000; // Maximum number of iterations
const double eps = 1e-6; // Epsilon for convergence

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



// long RootFinder::Bisection(tInterval A){
//     // TO BE IMPLEMENTED LAB006
//     return -1; //dummy value
// }

// long RootFinder::RegulaFalsi(tInterval A){
//     // TO BE IMPLEMENTED LAB007
//     return -1; //dummy value
// }

// // Secant method for finding the root
// long RootFinder::Secant(tInterval A) {
// }



// long RootFinder::Newton(tInterval A){
// // TO BE IMPLEMENTED LAB005
//     return -1; //dummy value
// }
