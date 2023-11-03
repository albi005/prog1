#include <stdio.h>
#include <math.h>

int main() {
    printf("a = ");
    double a;
    scanf("%lf", &a);

    printf("b = ");
    double b;
    scanf("%lf", &b);

    printf("c = ");
    double c;
    scanf("%lf", &c);

    double d = b*b-4*a*c;

    if (d < 0) {
        printf("Nincs megoldas");
        return 0;
    }

    double x1 = (-b + sqrt(d)) / (2*a);
    if (d == 0) {
        printf("x = %lf", x1);
        return 0;
    }

    double x2 = (-b - sqrt(d)) / (2*a);
    printf("x1 = %lf\n", x1);
    printf("x2 = %lf\n", x2);
}