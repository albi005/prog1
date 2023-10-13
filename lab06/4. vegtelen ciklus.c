#include <stdio.h>
 
int main(void) {
    int i = 1;
    while (i > 0) {
        ++i;
    }
    printf("%d\n", i);
    // túlcsordulás miatt az adott egész típus maximuma után a minimuma jön
 
    return 0;
}
