#include <stdio.h>
 
int main() {
    int szorzat = 1;
    int n = 8;
    while (n > 1) {
        szorzat *= n;
        n -= 1;
        // szorzat = 6720, miután n 3-ra változik
    }
    printf("%d\n", szorzat);
    return 0;
}
