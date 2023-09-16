#include <stdio.h>

int main() {
    int n = 1;
    int product = 1;
    while (n<=8) {
        printf("%d %d\n", n, product);
        product *= n;
        n++;
    }
    //n = 9
    printf("%d\n", product);
}
