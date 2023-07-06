#include <iostream>
#include "Polynomial.h"
#include "myTimer.h"
#include "myException.h"

using namespace std;

int main()
{
    myTimer T;
T.StartTimer();
    cout << "CONSTRUCTORS-----POLYNOMIAL CONSTRUCTION\n";
{ // A zero polynomial
        Polynomial A;
        cout << "1. A = " << A << " A.Degree = " << A.Degree() << endl;
        double a[] = {0,0,0};
        Polynomial B(a,3);
        cout << "2. B = " << B << " B.Degree = " << B.Degree() << endl;
        // enter a sequence of zeros followed by ENTER
        //Polynomial C;
        //cin >> C;
        //cout << "3. C = " << C << " C.Degree = " << C.Degree() << endl;
        Polynomial D(10);
        cout << "4. D = " << D << " D.Degree = " << D.Degree() << endl;
        double b[] = {1,2,0,4};
        Polynomial E(b,4);
        cout << "5. E = " << E << " E.Degree = " << E.Degree() << endl;
        Polynomial F(20,7);
        cout << "6. F = " << F << " F.Degree = " << F.Degree() << endl;
    }
    cout << "-----POLYNOMIAL ADDITION------\n";
    {
        double a[] = {1,-1,3,-2};
        Polynomial A(a,4);
        double b[] = {2,1,-3,5};
        Polynomial B(b,4);
        cout << "7. A= " << A << endl
<< "   B = " << B << endl
<< "   A+B = " << (A+B) << endl;
        cout << "8. A+= B :" << (A+=B) << endl
<< "   A = " << A << endl;
    }
    cout << "-----POLYNOMIAL SUBTRACTION------\n";
    {
        double a[] = {1,-1,3,-2};
        Polynomial A(a,4);
        double b[] = {2,1,-3,5};
        Polynomial B(b,4);
        cout << "9. A= " << A << endl
<< "   B = " << B << endl
<< "   A-B = " << (A-B) << endl;
        cout << "10.A+= B :" << (A-=B) << endl
<< "   A = " << A << endl;
    }
        cout << "-----POLYNOMIAL MULTIPLICATION------\n";
    {
        double a[] = {1,1,1};
        Polynomial A(a,3);
        double b[] = {1,1};
        Polynomial B(b,2);
        cout << "11.A= " << A << endl
<< "   B = " << B << endl
<< "   A*B = " << (A*B) << endl;
        cout << "12.A*= B :" << (A*=B) << endl << "   A = " << A << endl;
    }
        cout << "-----POLYNOMIAL DIVISON/REMAINDER------\n";
    {
        double a[] = {2,0,3,4,5};
        Polynomial A(a,5);
        double b[] = {1,1,-2};
        Polynomial B(b,3);
        cout << "13.A= " << A << endl
<< "   B = " << B << endl
<< "   A/B = " << (A/B) << endl
<< "   A%B = " << (A%B) << endl;
        cout << "14.(A/B)*A + A%B = :" << (A/B)*B + A%B << endl;
    }
        cout << "-----POLYNOMIAL DIVISON BY ZERO------\n";
    {
        double a[] = {2,0,3,4,5};
        Polynomial A(a,5);
        double b[] = {0,0,-0};
        Polynomial B(b,3);
try{
            Polynomial C = B / A;
            cout << "15. C = " << C << endl;
            Polynomial D = A / B;
            cout << "16. D = " << D << endl;
        } catch (myException &e) {
            cout <<e.what() << endl;
        }
    }
    cout << "-----POLYNOMIAL REMAINDER BY ZERO------\n";
    {
        double a[] = {2,0,3,4,5};
        Polynomial A(a,5);
        double b[] = {0,0,-0};
        Polynomial B(b,3);
try{
            Polynomial C = B % A;
            cout << "15. C = " << C << endl;
            Polynomial D = A % B;
            cout << "16. D = " << D << endl;
        } catch (myException &e) {
            cout <<e.what() << endl;
        }
    }
        cout << "-----POLYNOMIAL EVALUATION ETC------\n";
    {
        double a[] = {1,2,1};
        Polynomial A(a,3);
        cout << "17.A = " << A << endl
<< "   A(1) = " << A(1) << " A(-1) = " << A(-1) << endl;
        Polynomial B;
        double x = 1;
//         cout << "18.A = " << A << endl;
//         B = A.Deflate(x);
//         cout << "   Deflate A at -1: " << B << "; A(1) =" << x << endl
// << "   Deflated Poly  : " << B << endl;
        B = A;
        cout << "19. B = " << B << endl;
        // B = B.Integrate(5);
        // cout << "20. Integrate(B) = " << B << endl;
        B = B.Derivative();
        cout << "21. Diff(B) = " << B << endl;
    }
T.EndTimer();
    cout << "Time Taken = " <<T.GetInterval() << "(Seconds)" << endl;
    return 0;
}
/* ****************************************************************************** */
