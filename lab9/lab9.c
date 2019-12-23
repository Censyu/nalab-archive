// lab9.c
// @author: Chen Ang(PB17061250)
// @description: for Numerical Analysis(B) lab9

#include <stdio.h>
#include <math.h>

double f(double x, double y)
{
    return -pow(x * y, 2);
}

double RK4(double a, double b, double h, double y0)
{
    int n = (b - a) / h, i;
    double x, y;
    double k1, k2, k3, k4;
    x = a;
    y = y0;
    for (i = 0; i < n; i++)
    {
        k1 = f(x, y);
        k2 = f(x + h / 2, y + h * k1 / 2);
        k3 = f(x + h / 2, y + h * k2 / 2);
        k4 = f(x + h, y + h * k3);
        x += h;
        y += (k1 + 2 * k2 + 2 * k3 + k4) * h / 6;
    }
    return y;
}

double Adams4_implicit(double a, double b, double h, double y0)
{
    int n = (b - a) / h, i;
    double x = a;
    double y[5] = {y0, y0, y0, y0, y0};
    double k1, k2, k3, k4;
    for (i = 0; i < n; i++)
    {
        y[0] = y[1];
        y[1] = y[2];
        y[2] = y[3];
        y[3] = y[4];

        if (i < 3)
        {
            // R-K(4)
            k1 = f(x, y[3]);
            k2 = f(x + h / 2, y[3] + h * k1 / 2);
            k3 = f(x + h / 2, y[3] + h * k2 / 2);
            k4 = f(x + h, y[3] + h * k3);
            y[4] = y[3] + (k1 + 2 * k2 + 2 * k3 + k4) * h / 6;
        }
        else
        {
            // calc y_bar(y[4])
            y[4] = y[3] + (55 * f(x, y[3]) - 59 * f(x - h, y[2]) + 37 * f(x - 2 * h, y[1]) - 9 * f(x - 3 * h, y[0])) * h / 24;
            
            // calc y_n+1
            y[4] = y[3] + (9 * f(x + h, y[4]) + 19 * f(x, y[3]) - 5 * f(x - h, y[2]) + f(x - 2 * h, y[1])) * h / 24;
        }
        x += h;
    }

    return y[4];
}

int main()
{
    int l;
    double h[5];
    double err[5];

    printf("Runge-Kutta(4):\n");
    for (l = 0; l <= 4; l++)
    {
        h[l] = 0.1 / pow(2, l);
        err[l] = 3 / (1 + pow(1.5, 3)) - RK4(0, 1.5, h[l], 3);
    }
    for (l = 0; l <= 3; l++)
    {
        printf("h = %lf, err = %.15e, o2 = %.15e\n", h[l], err[l], log(err[l] / err[l + 1]) / log(2));
    }

    printf("\nAdams(implicit, 4):\n");
    for (l = 0; l <= 4; l++)
    {
        err[l] = 3 / (1 + pow(1.5, 3)) - Adams4_implicit(0, 1.5, h[l], 3);
    }
    for (l = 0; l <= 3; l++)
    {
        printf("h = %lf, err = %.15e, o2 = %.15e\n", h[l], err[l], log(err[l] / err[l + 1]) / log(2));
    }

    return 0;
}
