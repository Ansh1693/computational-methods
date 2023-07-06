#include <iostream>
#include "Minimizer.h"

using namespace std;


double A[3][7] = {
                    {5,-20,0,-5,0,1,0},
                    {0,-27.0/4,0,1/16.0,0,0,0},
                    {0,-70,60,-14,1,0,0}
                };
Polynomial P[] = { Polynomial(A[0],7),
                    Polynomial(A[1],7),
                    Polynomial(A[2],7)
                  };
tInterval pInterval[] = {
myPoint(-1,3),
myPoint(5,10),
myPoint(0,2)
                        };
double f1(double x) {
    double x2 = x*x;
    double x3 = x2 *x;
    double x5 = x3 * x2;
    return x5 - 5 * x3 - 20 * x + 5;
}

double f2(double x) { return x*x*x/16.0 - 27.0*x/4.0; }

double f3(double x) { return x*(-70.0 + x * (60.0 + x *(-14.0 + x) )); }

double f4(double x) { return -2*Sine(x) + x*x / 10.0; }

double f5(double x) { return Exp(x) - 5*x; }

tInterval fInterval[] = {
myPoint(-1,3),
myPoint(5,10),
myPoint(0,2),
myPoint(0,4),
myPoint(-1.5,3.5)
                        };

typedef double (*dFunction)(double);

dFunction f[5] = {f1,f2,f3,f4,f5};

int main() {
    //CODE FOR FUNCTIONS

    cout << "FUNCTIONS:" << "----------\n";
    cout <<setw(5) << "FN NO" << setw(10) << "COUNT" << setw(25) << "MINIMA AT" << setw(25) << "Function Value" << endl;
    for (int i = 0; i < 5; i++) {
try{
            Minimizer R(f[i],fInterval[i], VARIABLE_LINEAR); // You need to change only the LINEAR
                                                  // for other Minima finding functions
            long COUNT = R.findMinima();
            cout <<setw(5) << i + 1
<<setw(10) << COUNT
<<setw(25) << setprecision(15) << R.getMinima()
<<setw(25) << setprecision(15) << f[i](R.getMinima()) << endl;
        }
        catch (myException &e) {
            cout << "Error in function " << i << endl
<<e.what() << endl;
        }
    }

    //CODE FOR Polynomials
    cout << "POLYNOMIALS:" << "------------\n";
    cout <<setw(5) << "P. NO" << setw(10) << "COUNT" << setw(25) << "MINIMA AT" << setw(25) << "Poly. Value" << endl;
    for (int i = 0; i < 3; i++) {
try{
            Minimizer R(P[i],fInterval[i], VARIABLE_LINEAR); // You need to change only the LINEAR
                                                        // for other Minima finding functions
            long COUNT = R.findMinima();
            cout <<setw(5) << i + 1
<<setw(10) << COUNT
<<setw(25) << setprecision(15) << R.getMinima()
<<setw(25) << setprecision(15) << P[i](R.getMinima()) << endl;
        }
        catch (myException &e) {
            cout << "Error in function " << i << endl
<<e.what() << endl;
        }
    }
    return 0;
}
/* ****************************************************************************** */

