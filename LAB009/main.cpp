#include <iostream>
// #include "AuxiliaryFunction.h"
// #include "Polynomial.h"
#include "Point.h"
#include "myFunction.h"

#include "RootFinder.h"
using namespace std;

double A[5][7] = {
                    {-2,0,0,1,0,0,0},
                    {-1,-1,0,0,0,0,1},
                    {-5,-2,0,1,0,0,0},
                    {-1.0/2.0,0,3.0/2.0,0,0,0,0},
                    {-3.0/8.0,0, 15.0/4.0,0, 35.0/8.0,0,0}
                };
Polynomial P[] = { Polynomial(A[0],7),
                    Polynomial(A[1],7),
                    Polynomial(A[2],7),
                    Polynomial(A[3],7),
                    Polynomial(A[4],7)
                  };
tInterval pInterval[] = {
myPoint(0,2),
myPoint(0,2),
myPoint(0,3),
myPoint(0.5,4),
myPoint(0.1,0.8)
};

double f1(double x){ return Exp(x) - 2.0;}
double f2(double x){ return x - Exp(-x*x);}
double f3(double x){ return 1.0 - 2.0*x * Exp(-x/2);}
double f4(double x){ return 5.0 - 1/x;}
double f5(double x){ return x*x - Sine(x);}

double df1(double x){ return Exp(x);}
double df2(double x){ return 1 + 2*x*Exp(-x*x);}
double df3(double x){ return  - Exp(-x/2);}
double df4(double x){ return  1.0/(x*x);}
double df5(double x){ return 2.0*x - Cosine(x);}

tInterval fInterval[] = {
myPoint(0,1),
myPoint(0,1),
myPoint(0,2),
myPoint(0.1,0.25),
myPoint(0.1,myPI)
                        };

typedef double (*dFunction)(double);

dFunction f[5] = {f1,f2,f3,f4,f5};
dFunction df[5] = {df1,df2,df3,df4,df5};

int main() {
    //CODE FOR FUNCTIONS

    cout << "FUNCTIONS:" << "----------\n";
    cout <<setw(5) << "FN NO" << setw(10) << "COUNT" << setw(25) << "ROOT AT" << setw(25) << "Function Value" << endl;
    for (int i = 0; i < 5; i++) {
try{
            RootFinder R(fInterval[i], f[i],NEWTON_RAPHSON); // You need to change only the LINEAR
                                                  // for other root finding functions
            long COUNT = R.findRoot();
            cout <<setw(5) << i + 1
<<setw(10) << COUNT
<<setw(25) << setprecision(15) << R.getRoot()
<<setw(25) << setprecision(15) << f[i](R.getRoot()) << endl;
        }
        catch (myException &e) {
            cout << "Error in function " << i << endl
<<e.what() << endl;
        }
    }

    //CODE FOR Polynomials
    cout << "POLYNOMIALS:" << "------------\n";
    cout <<setw(5) << "P. NO" << setw(10) << "COUNT" << setw(25) << "ROOT AT" << setw(25) << "Poly. Value" << endl;
    for (int i = 0; i < 5; i++) {
try{
            RootFinder R(pInterval[i], P[i],NEWTON_RAPHSON); // You need to change only the LINEAR
                                                        // for other root finding functions
            long COUNT = R.findRoot();
            cout <<setw(5) << i + 1
<<setw(10) << COUNT
<<setw(25) << setprecision(15) << R.getRoot()
<<setw(25) << setprecision(15) << P[i](R.getRoot()) << endl;
        }
        catch (myException &e) {
            cout << "Error in function " << i << endl
<<e.what() << endl;
        }
    }
    return 0;
}
