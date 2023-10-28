#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "debugmalloc.h"

int main() {
    char *s = NULL;
    size_t len = 1;
    char c;
    while (scanf("%c", &c) > 0) {
        len++;
        s = (char*)realloc(s, sizeof(char) * len);
        s[len - 2] = c;
        s[len - 1] = 0;
    }
    printf("%s\n", s);
    free(s);
}
