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

int main() {
    char *s = "uwu";
    char *mas = masolat(s);
    printf("%s", mas);
    free(mas);
}

