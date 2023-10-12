#include <stdio.h>

int main() {
    int a = 37;
    int b = 42;
    int m = 69;

    int c = 1;
    while (1) {
        if (b % 2 == 1)
            c = (c * a) % m;
        b /= 2;
        if (b == 0) {
            printf("%d^%d mod %d = %d\n", a, b, m, c);
            break;
        }
        a = (a*a) % m;
    }
}
    
