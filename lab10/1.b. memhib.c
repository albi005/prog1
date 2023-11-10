#include <stdio.h>
#include "debugmalloc.h"
 
int *f1(int i) {
    return &i;
}
 
int main(void) {
    int x = 10;
    int *p = f1(x);
    printf("%d\n", *p);
    printf("%d\n", *p);
    return 0;
}
