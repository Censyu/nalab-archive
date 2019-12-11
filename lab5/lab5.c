// lab5.c
// @author: Chen Ang(PB17061250)
// @description: for Numerical Analysis(B) lab5

#include <stdio.h>
#include <math.h>

#define Epsilon 1e-8

double f(double x)
{
    return pow(x, 3) / 3 - x;
}

double f1(double x)
{
    return pow(x, 2) - 1;
}

double Newton(double x)
{
    return x - f(x) / f1(x);
}

double Secant(double xn, double xn_1)
{
    return xn - f(xn) * (xn - xn_1) / (f(xn) - f(xn_1));
}

int main()
{
    int i, count;
    double x, x1, x2, e;
    double X0_n[4] = {0.1, 0.2, 0.9, 9.0};
    double X0[4] = {-0.1, -0.2, -2, 0.9};
    double X1[4] = {0.1, 0.2, 0.9, 9.0};

    printf("Newton's Method:\n");
    for (i = 0; i < 4; i++)
    {
        count = 0;
        x1 = X0_n[i];
        printf("初值 = %.1f, ", x1);
        do
        {
            count++;
            x = x1;
            x1 = Newton(x);
            e = fabs(x - x1);
        } while (e > Epsilon);
        printf("根 = %.15e, ", x1);
        printf("迭代次数 = %d\n", count);
    }

    printf("Secant Method:\n");
    for (i = 0; i < 4; i++)
    {
        count = 0;
        x1 = X0[i];
        x2 = X1[i];
        printf("初值 = (%.1f, %.1f), ", x1, x2);
        do
        {
            count++;
            x = x1;
            x1 = x2;
            x2 = Secant(x1, x);
            e = fabs(x2 - x1);
        } while (e > Epsilon);
        printf("根 = %.15e, ", x2);
        printf("迭代次数 = %d\n", count);
    }

    return 0;
}
