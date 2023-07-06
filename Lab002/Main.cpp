/* *********************************************************** */
#include <iostream>
#include <math.h>
#include "myFunction.h"
using namespace std;

double f1(double x) {
    return (4*pow(x,4) + 2*pow(x,3) - 3*pow(x,2) + x);
}

double f2(double x) {
    return (5*pow(x,2) + 4*x + 3);
}


int main() {
    myFunction f(f1), g(f2);
    cout <<f(3) << endl << g(3) << endl;
    g = f;
    cout <<f(3) << endl << g(3);
    return 0;
}
/* *********************************************************** */

