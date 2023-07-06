#include <iostream>
#include "Trigo.h"

#include <math.h>
using namespace std;


int main()
{
    // Implementing the Trigonometric functions
    double x = -5.0;
    cout<<"*************************************************************"<<endl<<endl;
    cout<<" | value of x |"<<" | Result Calculated | "<<" | Result Expected |"<<endl<<endl;
    while(x <= 5.0){

        double toRadian = x * myPI / 180.0;

        cout<<" |\t"<<x<<"\t|  "<<Exp(x)<<"\t|\t"<<exp(x)<<"\t|"<<endl;
        cout<<" |\t"<<x<<"\t|  "<<Sine(x)<<"\t|\t"<<sin(toRadian)<<"\t|"<<endl;
        cout<<" |\t"<<x<<"\t|  "<<Cosine(x)<<"\t|\t"<<cos(toRadian)<<"\t|"<<endl;
        cout<<" |\t"<<x<<"\t|  "<<Tangent(x)<<"\t|\t"<<tan(toRadian)<<"\t|"<<endl;
        cout<<" |\t"<<x<<"\t|  "<<CoTangent(x)<<"\t|\t"<<1/tan(toRadian)<<"\t|"<<endl;
        cout<<" |\t"<<x<<"\t|  "<<Cosec(x)<<"\t|\t"<<1/sin(toRadian)<<"\t|"<<endl;
        cout<<" |\t"<<x<<"\t|  "<<Secant(x)<<"\t|\t"<<1/cos(toRadian)<<"\t|"<<endl;
        cout<<" |\t"<<x<<"\t|  "<<Cosh(x)<<"\t|\t"<<cosh(toRadian)<<"\t|"<<endl;
        cout<<" |\t"<<x<<"\t|  "<<Sinh(x)<<"\t|\t"<<sinh(toRadian)<<"\t|"<<endl;
        cout<<" |\t"<<x<<"\t|  "<<Tanh(x)<<"\t|\t"<<tanh(toRadian)<<"\t|"<<endl;
        cout<<" |\t"<<x<<"\t|  "<<Cosech(x)<<"\t|\t"<<1/sinh(toRadian)<<"\t|"<<endl;
        cout<<" |\t"<<x<<"\t|  "<<Sech(x)<<"\t|\t"<<1/cosh(toRadian)<<"\t|"<<endl;
        cout<<" |\t"<<x<<"\t|  "<<Coth(x)<<"\t|\t"<<1/tanh(toRadian)<<"\t|"<<endl;
        
        x += 0.5;
    }

    return 0;
}