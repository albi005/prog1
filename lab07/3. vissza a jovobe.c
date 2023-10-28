#include <stdio.h>

#include "debugmalloc.h"

int main() {
    int n = 0;
    double *p = NULL;
    double k;
    while (scanf("%lf", &k) > 0) {
        n++;
        double *new = (double*)malloc(sizeof(double) * n);
        for (int j = 0; j < n - 1; j++)
            new[j] = p[j];
        free(p);
        p = new;
        p[n-1] = k;
    }

    for (int j = n - 1; j >= 0; j--)
        printf("%g ", p[j]);

    free(p);


}
