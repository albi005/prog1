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

// Read a line from a file. Consumes the newline character but doesn't return it.
char *read_line(FILE *f);

Rect add_margin(Rect rect, int horizontal, int vertical);

Rect add_margin_trbl(Rect rect, int top, int right, int bottom, int left);

// Returns a newly allocated non-null empty string
char* new_empty_string();

// Returns a newly allocated copy of s
char* copy_string(char* s);

// Returns days between date and now
int days_since(time_t date, time_t now);

// Ensures index is less than count
void fit(size_t* index, size_t count);

// Open file for reading while ensuring it exists, exit on error
FILE* open_file(char* filename);

#endif
