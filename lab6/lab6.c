// lab6.c
// @author: Chen Ang(PB17061250)
// @description: for Numerical Analysis(B) lab6

#include <stdio.h>
#include <math.h>

#define N 9

// Ax = b , A(n*n), b(n*1)
void Gauss(double A[][9], int n, double b[])
{
    int i, j, k;
    double t;
    for (i = 0; i < n; i++)
    {
        k = i;
        for (j = i + 1; j < n; j++)
        {
            if(A[i][j] > A[i][k])
            {
                k = j;
            }
        }
        
        // exchange row
        for (j = i; j < n; j++)
        {
            t = A[i][j];
            A[i][j] = A[k][j];
            A[k][j] = t;
        }
        t = b[i];
        b[i] = b[k];
        b[k] = t;
        
        // Gauss
        for (j = i + 1; j < n; j++) // rows
        {
            A[j][i] = A[j][i] / A[i][i];
            for (k = i + 1; k < n; k++) // cols
            {
                A[j][k] -= A[i][k] * A[j][i];
            }
            b[j] -= A[j][i] * b[i];
        }

    }

    // calc x, save into b
    for (i = n - 1; i >=0 ; i--) // rows
    {
        for (j = i + 1; j < n; j++)
        {
            b[i] -= b[j] * A[i][j];
        }
        b[i] /= A[i][i];
    }
}

int main()
{
    int i;
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

    Gauss(A, 9, b);

    for (i = 0; i < 9; i++)
    {
        printf("x%d = %.15e\n", i + 1, b[i]);
    }
    return 0;
}
