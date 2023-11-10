#include <stdio.h>
#include "debugmalloc.h"
 
int *f1(int i) {
    return &i;
}
 
int main(void) {
    int *p;
    p = f1(10);
    printf("%d\n", *p);
    printf("%d\n", *p);
    return 0;
}
// stack memory address returned
