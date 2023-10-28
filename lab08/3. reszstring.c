#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugmalloc.h"

// Kivágja s-ből a paraméterként kapott két index közötti részt.
// Az első index az első olyan karakterre mutat, ami már kell, a második index pedig az első olyanra, ami már nem.
// A visszatérített stringet fell kell szabadítani.
char *substring(char *s, int start, int end) {
    if (start < 0) start = 0;
    int len = end - start + 1;
    char *new = (char*)malloc(len * sizeof(char*));
    strncpy(new, s + start, len - 1);
    new[len - 1] = (long)NULL;
    return new;
}
    
int main() {
    char *s = "hello, vilag";
    char *sub = substring(s, 3, 9);
 
    printf("%s\n", sub);

    free(sub);
}

