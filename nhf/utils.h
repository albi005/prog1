#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <time.h>

typedef struct {
    int x, y;
} Vec2i;

typedef struct {
    int x, y, w, h;
} Rect;

char *read_line(FILE *f);
Rect add_margin(Rect rect, int horizontal, int vertical);
char* copy_string(char* s);
int days_since(time_t date, time_t now);

#endif
