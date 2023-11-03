#include <stdio.h>

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

    if (d > 0)
        printf("2 megoldas");
    if (d == 0)
        printf("1 megoldas");
    if (d < 0)
        printf("0 megoldas");
}