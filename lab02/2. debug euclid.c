#include <stdio.h>
 
int main() {
    int a = 11220;
    int b = 2002;
    while (b > 0) {
        int temp = b;
        b = a % b;
        a = temp;
        // amikor a = 374, b = 44
    }
 
    printf("lnko = %d\n", a);
    return 0;
}
