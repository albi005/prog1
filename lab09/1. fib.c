#include <stdio.h>

size_t fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    return fib(n-1) + fib(n-2);
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%zu", fib(n));
}
