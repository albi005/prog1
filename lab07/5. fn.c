#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "debugmalloc.h"

char *hosszu_sort_olvas() {
    char *s = NULL;
    size_t len = 1;
    char c;
    while (scanf("%c", &c) > 0) {
        len++;
        s = (char*)realloc(s, sizeof(char) * len);
        s[len - 2] = c;
        s[len - 1] = 0;
    }
    return s;
}


int main() {
    char *s = hosszu_sort_olvas();
    printf("%s\n", s);
    free(s);
}
