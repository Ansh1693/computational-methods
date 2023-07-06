#ifndef ROOT_H_INCLUDED
#define ROOT_H_INCLUDED
#include "Point.h"

#include <iostream>
#include <vector>
#include <cmath>

class Root{
protected:
    double R;   // roots array, set to NaN if not found
    tInterval I; //list of Intervals in which root is to be found

public:
Root(): I(0,0) { R = std::nan("Root not initialized"); }
Root(double x, double y): I(x,y) {R = std::nan("Root not initialized");}
Root(tInterval x): I(x) {R = std::nan("Root not initialized");}

    double getRoot() { return R; }
    tInterval&Interval() {return I;}

    double setRoot(double x){ R = x; return x; }
    tInterval setInterval(double a, double b){
        tInterval c(a,b);
        I = c;
        return c;
    }

    void RemoveRoot(){ R = std::nan("Root not initialized");}
    void RemoveInterval(){ I.Clear(); }

    virtual long findRoot() = 0;
    long findRoot(tInterval OriginalInterval) { I = OriginalInterval; return findRoot();};
    long findRoot(double OriginalA, double OriginalB) {
        I.x = OriginalA;
        I.y = OriginalB;
        return findRoot();
    }
};

#endif // ROOT_H_INCLUDED
