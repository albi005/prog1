#include <stdio.h>

void print_szr(int n, int szr) {
    if (n == 0) return;
    int c = n % szr;
    print_szr(n / szr, szr);
    printf("%d", c);
}

int main() {
    print_szr(10, 10);
    printf("\n");
}
