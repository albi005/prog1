#include <stdio.h>

int main() {
    int a = 13;
    int b = 53;
    int m = 97;

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
    
