#include <stdio.h>

void kocka(double a, double* felulet, double* terfogat) {
    *felulet = 6 * a * a;
    *terfogat = a * a * a;
}

int main() {
    double felulet, terfogat;
    kocka(2.7, &felulet, &terfogat);
    printf("felulet = %lf\n", felulet);
    printf("terfogat = %lf\n", terfogat);
}
