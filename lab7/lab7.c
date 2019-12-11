// lab7.c
// @author: Chen Ang(PB17061250)
// @description: for Numerical Analysis(B) lab7

#include <stdio.h>
#include <math.h>

#define N 9
#define MAX_ITERATION 100000

double InfNorm(double a[N], double b[N])
{
    int i;
    double max = 0, t;
    for (int i = 0; i < N; i++)
    {
        t = fabs(a[i] - b[i]);
        if (t > max)
        {
            max = t;
        }
    }
    return max;
}

// Gauss-Seidel
int GS(double A[N][N], double b[N], double x[N], double e)
{
    double x1[N];
    double t;
    int i, j, count;

    for (count = 0; count < MAX_ITERATION;)
    {
        for (i = 0; i < N; i++)
        {
            x1[i] = x[i];
        }
        for (i = 0; i < N; i++)
        {
            t = 0;
            for (j = 0; j < N; j++)
            {
                t += A[i][j] * x[j];
            }
            x[i] = (b[i] - t) / A[i][i] + x[i];
        }
        count++;
        if (InfNorm(x, x1) < e)
        {
            return count;
        }
    }
    return -1;
}

int SOR(double A[N][N], double b[N], double x[N], double w, double e)
{
    int i, j, count;
    double x1[N];
    for (count = 0; count < MAX_ITERATION; )
    {
        for (i = 0; i < N; i++)
        {
            x1[i] = x[i];
        }
        for (i = 0; i < N; i++)
        {
            x[i] = (1 - w) * x[i] + w * b[i] / A[i][i];
            for (j = 0; j < N; j++)
            {
                if(j != i)
                {
                    x[i] -= w * A[i][j] * x[j] / A[i][i];
                }
            }
        }
        count++;
        if (InfNorm(x, x1) < e)
        {
            return count;
        }
    }
    return -1;
}

int main()
{
    int i, j, gs_n, sor_n;
    double w, e = 1e-7;
    double A[9][9] = {
          31, -13,   0,   0,   0, -10,   0,   0,   0,
         -13,  35,  -9,   0, -11,   0,   0,   0,   0,
           0,  -9,  31, -10,   0,   0,   0,   0,   0,
           0,   0, -10,  79, -30,   0,   0,   0,  -9,
           0,   0,   0, -30,  57,  -7,   0,  -5,   0,
           0,   0,   0,   0,  -7,  47, -30,   0,   0,
           0,   0,   0,   0,   0, -30,  41,   0,   0,
           0,   0,   0,   0,  -5,   0,   0,  27,  -2,
           0,   0,   0,  -9,   0,   0,   0,  -2,  29
        };
    double b[] = {-15, 27, -23, 0, -20, 12, -7, 7, 10};
    double x[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    // G-S
    gs_n = GS(A, b, x, e);
    printf("Gauss-Seidel 迭代--------------------\n");
    printf("迭代步数:%d\n", gs_n);
    for (i = 0; i < N; i++)
    {
        printf("x%d = %.15e\n", i + 1, x[i]);
    }
    
    // SOR
    printf("SOR 迭代-----------------------------\n");
    for (i = 1; i <= 99; i++)
    {
        w = (double)i / 50;
        printf("[%d] w = %.2f-------------------------\n", i, w);
        for (j = 0; j < N; j++)
        {
            x[j] = 0;
        }
        sor_n = SOR(A, b, x, w, e);
        if(sor_n > 0)
        {
            printf("迭代步数:%d\n", sor_n);
            for (j = 0; j < N; j++)
            {
                printf("x%d = %.15e\n", j + 1, x[j]);
            }
        }
        else
        {
            printf("迭代在 %d 次内没有收敛\n", MAX_ITERATION);
        }
        
    }

    return 0;
}
