// lab3.c
// @author: Chen Ang(PB17061250)
// @description: for Numerical Analysis(B) lab3

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
    double X1[MAX_LENGTH], Y1[MAX_LENGTH];

    int i;
    double a, b, MSE;
    double X1_bar, Y1_bar, X1Y1_bar, X1_square_bar;

    // y' = y / sin(x); x' = cot(x); y' = a + bx'
    X1_bar = 0;
    Y1_bar = 0;
    X1Y1_bar = 0;
    X1_square_bar = 0;
    for (i = 0; i < MAX_LENGTH; i++)
    {
        Y1[i] = Y[i] / sin(X[i]);
        X1[i] = 1 / tan(X[i]);
        X1_bar += X1[i];
        Y1_bar += Y1[i];
        X1Y1_bar += X1[i] * Y1[i];
        X1_square_bar += X1[i] * X1[i];
    }
    X1_bar /= MAX_LENGTH;
    Y1_bar /= MAX_LENGTH;
    X1Y1_bar /= MAX_LENGTH;
    X1_square_bar /= MAX_LENGTH;

    // calc a, b, MSE
    b = (X1Y1_bar - X1_bar * Y1_bar) / (X1_square_bar - X1_bar * X1_bar);
    a = Y1_bar - b * X1_bar;

    MSE = 0;
    for (i = 0; i < MAX_LENGTH; i++)
    {
        MSE += pow(Y[i] - (a * sin(X[i]) + b * cos(X[i])), 2);
    }
    MSE /= MAX_LENGTH;

    printf("a   = %.15e\nb   = %.15e\nMSE = %.15e\n", a, b, MSE);
    return 0;
}
