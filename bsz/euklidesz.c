#include <stdio.h>

int main() {
    int a = 567;
    int m = 1238;
    int r;
    while (1) {
        r = m % a;
        if (r == 0)
            break;
        m = a;
        a = r;
    }
    printf("lnko: %d\n", a);
}
