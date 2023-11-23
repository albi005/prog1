#ifndef CONSOLE_H
#define CONSOLE_H

#include "utils.h"
#include <stddef.h>
#include <stdbool.h>

// https://alb1.hu/#materialcolorutilities btw
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

void text_color(unsigned int rgb);
void background_color(unsigned int rgb);
size_t count_utf8_code_points(const char *s);
Vec2i get_terminal_size();
void draw_rect(Rect rect, unsigned int rgb);
bool confirm(const char *message);

#endif // CONSOLE_H
