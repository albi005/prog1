#include <stdio.h>

int main() {
    unsigned long int x = 29;
    for (int i = 31; i >= 0; i--)
        printf("%d", 0 != (x & (1 << i)));
    printf("\n");
}
