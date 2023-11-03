#include <stdio.h>
#include <stdbool.h>
#include "econio.h"

// https://alb1.hu/#materialcolorutilities
#define PRIMARY 0x9BD595
#define ON_PRIMARY 0x00390A
#define PRIMARY_CONTAINER 0x1C511F
#define ON_PRIMARY_CONTAINER 0xB6F2AF
#define SECONDARY 0xEEB8CA
#define ON_SECONDARY 0x492534
#define SECONDARY_CONTAINER 0x623B4A
#define ON_SECONDARY_CONTAINER 0xFFD9E4
#define TERTIARY 0xBEC3FA
#define ON_TERTIARY 0x272C5A
#define TERTIARY_CONTAINER 0x3E4372
#define ON_TERTIARY_CONTAINER 0xDFE0FF
#define ERROR 0xFFB4AB
#define ON_ERROR 0x690005
#define ERROR_CONTAINER 0x93000A
#define ON_ERROR_CONTAINER 0xFFB4AB
#define SURFACE 0x12131A
#define ON_SURFACE 0xE3E1EC
#define SURFACE_VARIANT 0x454654
#define ON_SURFACE_VARIANT 0xC7C5D0
#define OUTLINE 0x91909A
#define INVERSE_SURFACE 0xE3E1EC
#define INVERSE_ON_SURFACE 0x2F3038
#define INVERSE_PRIMARY 0x356A35
#define SURFACE_DIM 0x12131A
#define SURFACE_BRIGHT 0x383841
#define SURFACE_CONTAINER_LOWEST 0x0D0E15
#define SURFACE_CONTAINER_LOW 0x1A1B23
#define SURFACE_CONTAINER 0x1F1F27
#define SURFACE_CONTAINER_HIGH 0x292931
#define SURFACE_CONTAINER_HIGHEST 0x34343C
#define OUTLINE_VARIANT 0x46464F

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

// https://stackoverflow.com/a/32936928
size_t count_utf8_code_points(const char *s) {
    size_t count = 0;
    while (*s) {
        count += (*s++ & 0xC0) != 0x80;
    }
    return count;
}

typedef struct {
    int selected_tab;
} Tabs;

void draw_tabs(Tabs* tabs) {
    char* tabs_text[] = {"Oltás", "Tulajdonos", "Állat"};
    int x = 0;
    for (int i = 0; i < 3; i++) {
        econio_gotoxy(x, 0);
        if (i == tabs->selected_tab) {
            text_color(ON_PRIMARY_CONTAINER);
            background_color(SURFACE_CONTAINER);
        } else {
            text_color(ON_SURFACE_VARIANT);
            background_color(SURFACE_CONTAINER_LOWEST);
        }
        printf("%s", tabs_text[i]);
        x += count_utf8_code_points(tabs_text[i]) + 2;
    }
}

void draw_background() {
    background_color(SURFACE_CONTAINER_LOWEST);
    econio_clrscr();
}

int main() {
    draw_background();
    
    Tabs tabs = {0};
    
    draw_tabs(&tabs);

    econio_rawmode();

    while (true) {
        int key = econio_getch();
        if (key == 'q') {
            break;
        }
        if (key == KEY_TAB) {
            tabs.selected_tab = (tabs.selected_tab + 1) % 3;
            draw_tabs(&tabs);
        }
    }

    econio_normalmode();
}
