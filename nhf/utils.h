#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

typedef struct {
    int x, y;
} Vec2i;

typedef struct {
    int x, y, w, h;
} Rect;

char *read_line(FILE *f);
Rect add_margin(Rect rect, int horizontal, int vertical);

#endif
