// lab4.c
// @author: Chen Ang(PB17061250)
// @description: for Numerical Analysis(B) lab4

#include <stdio.h>
#include <math.h>

// Note: actually there're [n+1] points
double T(double(*func)(double), double a, double b, int n)
{
    int i;
    double h = (b - a) / n;
    double I = 0;
    for (i = 1; i < n; i++)
    {
        I += func(a + i * h);
    }
    I += (func(a) + func(b)) / 2;
    I *= h;
    return I;
}

// Note: n = 2m
double S(double(*func)(double), double a, double b, int n)
{
    int i;
    double h = (b - a) / n;
    double I = 0;
    for (i = 2; i < n - 1; i++)
    {
        I += 2 * func(a + i++ * h);     // 2k
        I += 4 * func(a + i * h);       // 2k + 1
    }
    I += func(a) + func(b) + 4 * func(a + h);
    I *= h / 3;
    return I;
}

double Calc_o_k(double e1, double e2, double k)
{
    return log(fabs(e1 / e2)) / log(k);
}

int main()
{
    int i, N;
    double a = 1, b = 5;
    double I = cos(a) - cos(b);
    double Tn[13], Sn[13], errorT[13], errorS[13];

    for(i = 0; i < 13; i++)
    {
        N = pow(2, i + 1);
        Tn[i] = T(sin, a, b, N);
        errorT[i] = I - Tn[i];
        Sn[i] = S(sin, a, b, N);
        errorS[i] = I - Sn[i];
    }

    for(i = 0; i < 12; i++)
    {
        N = pow(2, i + 1);
        printf("l = %d, N = %d:\n", i + 1, N + 1);
        printf("T = %.15e, Error = %.15e, o2 = %.15e\n", Tn[i], errorT[i],
            Calc_o_k(errorT[i], errorT[i + 1], 2));

        printf("S = %.15e, Error = %.15e, o2 = %.15e\n", Sn[i], errorS[i],
            Calc_o_k(errorS[i], errorS[i + 1], 2));
        printf("---------------------------------\n");
    }
    
    return 0;
}
