// lab2.c
// @author: Chen Ang(PB17061250)
// @description: for Numerical Analysis(B) lab2

#include <stdio.h>
#include <math.h>

#define MAX_LENGTH 40
#define PI 3.14159265358979323846
#define PI_C acos(-1)

double Fx(double x)
{
    return (double)1 / (1 + x * x);
}

// get interpolation points array X-Y & num & x
// return Ln(x)
// NOTE: actually has n+1 points
double Lagrange(double *X, double *Y, int n, double x)
{
    int i, j;
    double L = 0, l;
    for (i = 0; i <= n; i++)
    {
        l = 1;
        for (j = 0; j < i; j++)
        {
            l = l * (x - X[j]) / (X[i] - X[j]);
        }
        for (j = i + 1; j <= n; j++)
        {
            l = l * (x - X[j]) / (X[i] - X[j]);
        }
        L = L + l * Y[i];
    }
    return L;
}

// get interpolation points X & num
// return max error
double LError(double *X, double *Y, int n)
{
    int i;
    double y = -5;
    double maxError = 0;
    double error;
    for (i = 0; i <= 500; i++)
    {
        error = fabs(Fx(y) - Lagrange(X, Y, n, y));
        if (error > maxError)
        {
            maxError = error;
        }
        y += 0.02;
    }
    return maxError;
}

int main()
{
    int i, n, count;
    int N[4] = {5, 10, 20, 40};
    double X1[MAX_LENGTH + 1], X2[MAX_LENGTH + 1];
    double Y1[MAX_LENGTH + 1], Y2[MAX_LENGTH + 1];

    // init interpolation points' arrays
    for(count = 0; count < 4; count++)
    {
        n = N[count];
        for (i = 0; i <= n; i++)
        {
            X1[i] = (double)-5 + (double)10 * i / n;
            X2[i] = -5 * cos((2 * i + 1) * PI / (2 * n + 2));
            Y1[i] = Fx(X1[i]);
            Y2[i] = Fx(X2[i]);
        }
        printf("n = %d\n", n);
        printf("Points array 1: maxError = %.15e\n", LError(X1, Y1, n));
        printf("Points array 2: maxError = %.15e\n", LError(X2, Y2, n));
    }

    return 0;
}
