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
char* new_empty_string();
char* copy_string(char* s);
int days_since(time_t date, time_t now);

// ensures index is less than count
void fit(size_t* index, size_t count);

// open file for reading while ensuring it exists, exit on error
FILE* open_file(char* filename);

#endif
