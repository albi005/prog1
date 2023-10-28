#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugmalloc.h"

char *beszur(char *s1, int start, char *s2) {
    int len = strlen(s1) + strlen(s2) + 1;
    char *s = (char*)malloc(sizeof(char) * len);
    strncpy(s, s1, start);
    strcpy(s + start, s2);
    strcat(s, s1 + start);
    return s;
}

int main() {
    char *s = beszur("hello!", 5, ", vilag");
    printf("%s\n", s);
    free(s);
}
