
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 2048
#define M 2048
double a[N][M], b[M][N], c[N][N];
int main(void)
{
    int i, j, k;
    double time1, time2;

    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            a[i][j] = b[j][i] = rand() % 1000;
    time1 = omp_get_wtime();
    int num = 16;
    omp_set_num_threads(num);

#pragma omp parallel for shared(a, b, c) private(i, j, k)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            c[i][j] = 0.0;
            for (k = 0; k < N; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }
    time2 = omp_get_wtime();

    //Время:
    printf(" % lf \n", time2 - time1);
    return 0;
}