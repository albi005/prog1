#include <stdio.h>

void print(size_t n) {
    if (n == 0) return;
    int c = n % 1000;
    print(n / 1000);
    if (n >= 1000) {
        if (c < 100) printf("0");
        if (c < 10) printf("0");
    }
    printf("%d ", c);
}

int main() {
    print(200200206);
    printf("\n");
}
