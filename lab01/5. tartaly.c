#include <stdio.h>

int main() {
    printf("Tartaly festese\n\n");

    printf("Milyen magas? ");
    double h;
    scanf("%lf", &h);


    printf("Mennyi az atmeroje? ");
    double d;
    scanf("%lf", &d);
    double r = d / 2;

    double pi = 3.14159;
    double m2PerBox = 2;
    double surface = 2*r*pi*h + 2*r*r*pi;
    double boxCount = surface / m2PerBox;
    printf("%f doboz festek kell", boxCount);
}