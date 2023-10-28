#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    double *p = (double*)malloc(sizeof(double) * n);
    if (p == NULL) return -1;
    for (int i = 0; i < n; i++) {
        scanf("%lf", p + i);
    }
    for (int i = n - 1; i >= 0; i--)
        printf("%g ", p[i]);
}

