#include <stdio.h>
#include <math.h>

double kob(double x) {
    return x * x * x;
}

double abszolut(double x) {
    if (x >= 0)
        return x;
    else
        return -x;
}

int main() {
    printf("x\tx^3\t|x|\tsin(x)\n");
    for (double i = -1; i <= 1; i += .1) {
        double a = i;
        double kob_a = kob(a);
        double abs_a = abszolut(a);
        double sin_a = sin(a);
        printf("%.4lf\t%.4lf\t%.4lf\t%.4lf\n", a, kob_a, abs_a, sin_a);
    }
}

