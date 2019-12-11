// lab8.c
// @author: Chen Ang(PB17061250)
// @description: for Numerical Analysis(B) lab8

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 5
#define MAX_ITERATION 100000

void Jacobi(double A[N][N], double e)
{
    int i, j, k, p, q;
    double s, t, c, d;
    double bp[N], bq[N];
    double V[N][N];
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (i == j)
            {
                V[i][j] = 1;
            }
            else
            {
                V[i][j] = 0;
            }
        }
    }
    for (k = 0; k < MAX_ITERATION; k++)
    {
        // get p, q
        p = 0;
        q = 1;
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < i; j++)
            {
                if (fabs(A[i][j]) > fabs(A[p][q]))
                {
                    p = i;
                    q = j;
                }
            }
        }
        // calc s->tan->sin & cos
        if (A[p][q] != 0)
        {
            s = (A[q][q] - A[p][p]) / (2 * A[p][q]);
            if (s >= 0)
            {
                t = -s + sqrt(s * s + 1);
            }
            else
            {
                t = -s - sqrt(s * s + 1);
            }
            c = 1 / sqrt(1 + t * t);
            d = t * c;
        }
        else
        {
            c = 1;
            d = 0;
        }
        // renew Q, A, V
        // A = Q^T * A * Q
        for (i = 0; i < N; i++)
        {
            bp[i] = c * A[p][i] - d * A[q][i];
            bq[i] = d * A[p][i] + c * A[q][i];
        }
        bp[p] = A[p][p] - t * A[p][q];
        bq[q] = A[q][q] + t * A[p][q];
        bp[q] = bq[p] = 0;
        for (i = 0; i < N; i++)
        {
            A[p][i] = A[i][p] = bp[i];
            A[q][i] = A[i][q] = bq[i];
        }

        // V = V * Q, changes col
        for (i = 0; i < N; i++)
        {
            s = V[i][p];
            t = V[i][q];
            V[i][p] = c * s - d * t;
            V[i][q] = c * t + d * s;
        }

        // break if ||A-diag(A)||_2 < epsilon
        s = 0;
        for (i = 0; i < N; i++)
        {
            for (j = i + 1; j < N; j++)
            {
                s += pow(A[i][j], 2);
            }
        }
        if (2 * s < e)
        {
            break;
        }
    }
    printf("k = %d\n", k);
    // print results
    for (i = 0; i < N; i++)
    {
        printf("r%d = %.15e,\n v%d = (", i + 1, A[i][i], i + 1);
        for (j = 0; j < N - 1; j++)
        {
            printf("%.15e, ", V[j][i]);
        }
        printf("%.15e)\n", V[N - 1][i]);
    }
}

int main()
{
    double A[N][N] = {
        3, 2, 5, 4, 6,
        2, 1, 3, -7, 8,
        5, 3, 2, 5, -4,
        4, -7, 5, 1, 3,
        6, 8, -4, 3, 8};
    double e = 1e-10;
    Jacobi(A, e);

    return 0;
}
