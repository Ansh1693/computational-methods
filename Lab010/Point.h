#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED
#include <cmath>
#include <iostream>
#include <iomanip>
#define strSIGN(x) (((x) >= (0)) ? "+" : "-")
#define SIGN(x) (((x) >= (0)) ? 1 : -1)
#define ABS(x) ((SIGN(x)) * (x))
#define ACCURACY 1.0e-10
#define SET_PRECISION 15

struct myPoint{
    double x,y;
myPoint() {
        x = std::nan("Not Initialized");
        y = std::nan("Not Initialized");
    }
myPoint(double a, double b): x(a), y(b) {}
   // myPoint(const myPoint& P): x(P.x), y(P.y) {}
    //myPoint& operator = (const myPoint& P) { x = P.x; y = P.y; return *this;}
    bool operator == (const myPoint& P) {
        if (x == P.x && y == P.y) return true;
        else return false;
    }
    bool isZero() { if (!isInitialized()) return false; return (x == 0 && y == 0); }
    bool isInitialized() { if (std::isnan(x) || std::isnan(y)) return false; return true;}
    friend std::ostream& operator << (std::ostream& os, myPoint& P){
        return os << " (" <<std::setprecision(SET_PRECISION) << P.x << ", "
<<std::setprecision(SET_PRECISION) << P.y << ")";
    }
    void Clear() { x = y = 0;}
};

class tInterval: public myPoint {
public:
tInterval(): myPoint() {}
tInterval(double a, double b): myPoint(a,b)  {}
tInterval(const myPoint& P): myPoint(P.x,P.y) {}
tInterval(const tInterval& P): myPoint(P.x,P.y) {}
    bool isZero() { return ABS(x - y) < ACCURACY; }
};
#endif // POINT_H_INCLUDED /*
