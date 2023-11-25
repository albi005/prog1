#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "console.h"
#include "debugmalloc.h"
#include "econio.h"
#include "utils.h"

void text_color(unsigned int rgb) {
    unsigned int b = rgb & 0xFF;
    unsigned int g = (rgb >> 8) & 0xFF;
    unsigned int r = (rgb >> 16) & 0xFF;
    printf("\x1b[38;2;%d;%d;%dm", r, g, b);
}

void background_color(unsigned int rgb) {
    unsigned int b = rgb & 0xFF;
    unsigned int g = (rgb >> 8) & 0xFF;
    unsigned int r = (rgb >> 16) & 0xFF;
    printf("\x1b[48;2;%d;%d;%dm", r, g, b);
}

void reset_colors() {
    printf("\x1b[0m");
}

// https://en.wikipedia.org/wiki/UTF-8#Encoding
bool is_continuation_byte(char c) {
    return (c & 0b11000000) == 0b10000000;
}

// https://stackoverflow.com/a/32936928
size_t count_utf8_code_points(const char *s) {
    size_t count = 0;
    while (*s)
        count += !is_continuation_byte(*s++);
    return count;
}

Vec2i get_terminal_size() {
    printf("\e[9999;9999H"); // go to 9999, 9999
    printf("\e[6n"); // ask for cursor position
    char c;
    while ((c = getchar()) != '['); // response is ESC[y;xR
    Vec2i size;
    scanf("%d;%d", &size.y, &size.x);
    getchar(); // consume R
    printf("\e[3J"); // clear screen
    return size;
}
void draw_rect(Rect rect, unsigned int rgb) {
    background_color(rgb);
    for (int i = 0; i < rect.h; i++) {
        econio_gotoxy(rect.x, rect.y + i);
        for (int j = 0; j < rect.w; j++) {
            printf(" ");
        }
    }
}

bool confirm(const char *message) {
    abort(); // TODO
}
