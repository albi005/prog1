#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "debugmalloc.h"
#include "utils.h"

Rect add_margin(Rect rect, int horizontal, int vertical) {
    rect.x += horizontal;
    rect.y += vertical;
    rect.w -= horizontal * 2;
    rect.h -= vertical * 2;
    return rect;
}

char* new_empty_string() {
    char* s = malloc(sizeof(char));
    s[0] = 0;
    return s;
}

char *read_line(FILE *f) {
    char *s = new_empty_string();
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
        s[len] = 0;
    }
}

char* copy_string(char* s) {
    if (s == NULL)
        return NULL;
    
    char* copy = malloc(sizeof(char) * (strlen(s) + 1));
    strcpy(copy, s);
    return copy;
}

int days_since(time_t date, time_t now) {
    return (now - date) / (60 * 60 * 24);
}

void fit(size_t* index, size_t count) {
    if (*index >= count)
        *index = count - 1;
}

FILE* open_file(char* filename) {
    FILE* f = fopen(filename, "a+");
    if (f == NULL) {
        printf("Error opening file %s!\n", filename);
        exit(1);
    }
    return f;
}

