#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "debugmalloc.h"
#include "utils.h"

char *read_line(FILE *f) {
    char *s = NULL;
    size_t len = 0; //without null
    size_t cap = 0; //without null
    while (1) {
        char c = getc(f);
        if (c == EOF || c == '\n') return s;

        len++;
        if (len > cap) {
            if (cap < 10)
                cap = 10;
            else
                cap *= 2;
            size_t new_size = (cap + 1) * sizeof(char);
            s = (char*)realloc(s, new_size);
        }

        s[len - 1] = c;
        s[len] = (long)NULL;
    }
}

Rect add_margin(Rect rect, int horizontal, int vertical) {
    rect.x += horizontal;
    rect.y += vertical;
    rect.w -= horizontal * 2;
    rect.h -= vertical * 2;
    return rect;
}
