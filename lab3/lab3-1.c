// lab3.c
// @author: Chen Ang(PB17061250)
// @description: for Numerical Analysis(B) lab3
// 
// idea:
// Q = Sum((asinxi+bcosxi-yi)^2) 
//      (xi,yi) from samples, i from 0 to 9
// let:
//      partial Q / partial a = 0
//      partial Q / partial b = 0
// then get the equation Am = B
// m = [a;b]
// A = [Sum((sinxi)^2),   Sum(sinxi*cosxi);
//    Sum(sinxi*cosxi), Sum((cosxi)^2)]
// B = [Sum(sinxi*yi);    Sum(cosxi*yi)]

#include <stdio.h>
#include <math.h>

#define MAX_LENGTH 10

int main()
{
    double X[MAX_LENGTH] = {
        0.25, 0.50, 0.75, 1.00, 1.25,
        1.50, 1.75, 2.00, 2.25, 2.50};
    double Y[MAX_LENGTH] = {
        1.284, 1.648, 2.117, 2.718, 3.427,
        2.798, 3.534, 4.456, 5.465, 5.894};

    int i;
    double A[2][2], B[2];
    double a, b, MSE;

    // calc matrix A & B
    A[0][0] = 0;
    A[0][1] = 0;
    A[1][0] = 0;
    A[1][1] = 0;
    for(i = 0; i < MAX_LENGTH; i++)
    {
        A[0][0] += pow(sin(X[i]),2);
        A[0][1] += sin(X[i]) * cos(X[i]);
        A[1][1] += pow(cos(X[i]),2);
    }
    A[1][0] = A[0][1];

    B[0] = 0;
    B[1] = 0;
    for(i = 0; i < MAX_LENGTH; i++)
    {
        B[0] += sin(X[i]) * Y[i];
        B[1] += cos(X[i]) * Y[i];
    }

    // solve the equation - get (a, b)
    a = (B[0] * A[1][1] - B[1] * A[0][1]) / (A[0][0] * A[1][1] - A[0][1] * A[1][0]);
    b = (A[0][0] * B[1] - A[1][0] * B[0]) / (A[0][0] * A[1][1] - A[0][1] * A[1][0]);

    // calc MSE
    MSE = 0;
    for (i = 0; i < MAX_LENGTH; i++)
    {
        MSE += pow(Y[i] - (a * sin(X[i]) + b * cos(X[i])), 2);
    }
    MSE /= MAX_LENGTH;

    printf("a   = %.15e\nb   = %.15e\nMSE = %.15e\n", a, b, MSE);
    return 0;
}
