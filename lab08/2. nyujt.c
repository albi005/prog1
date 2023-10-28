#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugmalloc.h"

// lemasolja s-t egy ujonnan foglalt memoria teruletre, es visszaadja egy pointer-t a legelso karakterre.
// A kapott pointer-t majd fell kell szabaditani.
char *masolat(char *s) {
    int len = strlen(s) + 1;
    char *uj = (char*)malloc(sizeof(char) * len);
    strcpy(uj, s);
    return uj;
}

// hozzafuzi src-t dst-hez, es visszaadja dst-t.
// A kapott pointer-t majd fell kell szabaditani.
char *hozzafuz(char *dst, char *src) {
    int len = strlen(dst) + strlen(src) + 1;
    dst = (char*)realloc(dst, len);
    strcat(dst, src);
    return dst;
}
    
int main() {
    char *x = masolat("alma");  /* az előző feladatból */
 
    x = hozzafuz(x, "fa");
    printf("%s\n", x);    /* almafa */

    free(x);
}

