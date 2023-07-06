#ifndef TRIGO_H_INCLUDED
#define TRIGO_H_INCLUDED
#include "AuxiliaryFunction.h"
#include <iostream>
using namespace std;


double Exp(double x) {
    // Check if x is negative, and if so, compute 1 / exp(-x)
    if (x < 0) {
        x = -x;
        // Define the number of terms for Taylor series approximation
        const int numTerms = 10;
        // Initialize the result to 1.0, which is the first term in the series
        double result = 1.0;
        // Initialize the term to 1.0, which is the first term in the series
        double term = 1.0;
        // Loop through each term in the Taylor series
        for (int i = 1; i <= numTerms; ++i) {
            // Compute the next term in the series
            term *= x / i;
            // Add the term to the result
            result += term;
        }
        // Return the reciprocal of the result, since exp(x) = 1 / exp(-x)
        return 1.0 / result;
    }
    else {
        // x is non-negative, compute exp(x) using Taylor series
        // Define the number of terms for Taylor series approximation
        const int numTerms = 10;
        // Initialize the result to 1.0, which is the first term in the series
        double result = 1.0;
        // Initialize the term to 1.0, which is the first term in the series
        double term = 1.0;
        // Loop through each term in the Taylor series
        for (int i = 1; i <= numTerms; ++i) {
            // Compute the next term in the series
            term *= x / i;
            // Add the term to the result
            result += term;
        }
        // Return the final result
        return result;
    }
}


double Sine(double x)
{
    // Convert x to radians
    x = x * myPI / 180.0;
    // Compute sine using Taylor series expansion
    double result = 0.0;
    double term = x;
    double sign = 1.0;
    for (int i = 1; i <= 10; i++) {
        result += sign * term;
        term *= -(x * x) / ((2 * i) * (2 * i + 1));
        sign *= -1.0;
    }
    
    return result;
}

double Cosine(double x){
    // Convert x to radians
    x = x * myPI / 180.0;

    // Reduce x to the range [0, 2*pi]
    while (x < 0) {
        x += 2 * myPI;
    }
    while (x >= 2 * myPI) {
        x -= 2 * myPI;
    }

    // Taylor series approximation of cosine
    double result = 1.0;
    double term = 1.0;
    double sign = -1.0;
    double power = 2.0;
    for (int i = 1; i <= 10; ++i) {
        term *= (x * x) / (power * (power - 1));
        result += sign * term;
        sign *= -1.0;
        power += 2.0;
    }

    return result;
}

double Tangent(double x){
    // Check if cosine is zero
    if (Cosine(x) == 0) {
        // Division by zero, return NaN (Not a Number)
        return 0.0 / 0.0;
    }
    else {
        // Compute tangent using the identity: tan(x) = sin(x) / cos(x)
        double sine = Sine(x);
        double cosine = Cosine(x);
        double tangent = sine / cosine;
        return tangent;
    }
}

double CoTangent(double x){
    // Check if cosine is zero
    if (Sine(x) == 0) {
        // Division by zero, return NaN (Not a Number)
        return 0.0 / 0.0;
    }
    else {
        // Compute tangent using the identity: tan(x) = sin(x) / cos(x)
        double sine = Sine(x);
        double cosine = Cosine(x);
        double cotangent = cosine / sine;
        return cotangent;
    }
}

double Cosec(double x){
    // Check if cosine is zero
    if (Sine(x) == 0) {
        // Division by zero, return NaN (Not a Number)
        return 0.0 / 0.0;
    }
    else {
        // Compute tangent using the identity: tan(x) = sin(x) / cos(x)
        double sine = Sine(x);
        double cosec = 1 / sine;
        return cosec;
    }
}

double Secant(double x){
    // Check if cosine is zero
    if (Cosine(x) == 0) {
        // Division by zero, return NaN (Not a Number)
        return 0.0 / 0.0;
    }
    else {
        // Compute tangent using the identity: tan(x) = sin(x) / cos(x)
        double cosine = Cosine(x);
        double secant = 1 / cosine;
        return secant;
    }
}

double Cosh(double x){
    double ex = Exp(x);
    double e_minusx = Exp(-1*x);
    double cosh = (1/2)*(ex + e_minusx);  
    return cosh;
}

double Sinh(double x){
    double ex = Exp(x);
    double e_minusx = Exp(-1*x);
    double sinh = (1/2)*(ex - e_minusx);  
    return sinh;
}

double Tanh(double x){
    // Check if cosine is zero
    if (Cosh(x) == 0) {
        // Division by zero, return NaN (Not a Number)
        return 0.0 / 0.0;
    }
    else {
        // Compute tangent using the identity: tan(x) = sin(x) / cos(x)
        double sinh = Sinh(x);
        double cosh = Cosh(x);
        double tanh = sinh / cosh;
        return tanh;
    }
}

double Cosech(double x){
    // Check if cosine is zero
    if (Sinh(x) == 0) {
        // Division by zero, return NaN (Not a Number)
        return 0.0 / 0.0;
    }
    else {
        // Compute tangent using the identity: tan(x) = sin(x) / cos(x)
        double sinh = Sine(x);
        double cosech = 1 / sinh;
        return cosech;
    }
}

double Sech(double x){
    // Check if cosine is zero
    if (Cosh(x) == 0) {
        // Division by zero, return NaN (Not a Number)
        return 0.0 / 0.0;
    }
    else {
        // Compute tangent using the identity: tan(x) = sin(x) / cos(x)
        double cosh = Cosh(x);
        double sech = 1 / cosh;
        return sech;
    }
}

double Coth(double x){
    // Check if cosine is zero
    if (Sinh(x) == 0) {
        // Division by zero, return NaN (Not a Number)
        return 0.0 / 0.0;
    }
    else {
        // Compute tangent using the identity: tan(x) = sin(x) / cos(x)
        double sinh = Sinh(x);
        double cosh = Cosh(x);
        double coth = cosh / sinh;
        return coth;
    }
}

#endif // POLYNOMIAL_H_INCLUDED