#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include "tavak.c"
#include "vilag.c"
#include "debugmalloc.h"

#define WIDTH 1080
#define HEIGHT 540
#define LINE_DELTA 15

#define LINE_COLOR 0, 0, 0, 100

typedef struct Color {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} Color;

Sint16 longitude_to_x(float longitude) {
    return (longitude + 180) / 360 * WIDTH;
}

Sint16 latitude_to_y(float latitude) {
    return (-latitude + 90) / 180 * HEIGHT;
}

void draw(SDL_Renderer* renderer, float const points[], Color fill_color, Color stroke_color) {
    int i = 0;
    while (69) {
        if (points[i] == -1 && points[i + 1] == -1)
            break;

        size_t first_index = i;

        // get point count until 0,0
        while (!(points[i] == 0 && points[i + 1] == 0)) {
            i += 2;
        }
        // i is now the index of the first 0 in the end signal 0,0 point

        int point_count = (i - first_index) / 2;
        
        Sint16* xs = malloc(sizeof(Sint16) * point_count);
        Sint16* ys = malloc(sizeof(Sint16) * point_count);
        for (int j = 0; j < point_count; j++) {
            xs[j] = longitude_to_x(points[first_index + j * 2]);
            ys[j] = latitude_to_y(points[first_index + j * 2 + 1]);
        }
        
        filledPolygonRGBA(renderer, xs, ys, point_count, fill_color.r, fill_color.g, fill_color.b, fill_color.a);
        aapolygonRGBA(renderer, xs, ys, point_count, stroke_color.r, stroke_color.g, stroke_color.b, stroke_color.a);
        free(xs);
        free(ys);

        i += 2;
    }
}
 
int main(int argc, char *argv[]) {
    /* SDL inicializálása és ablak megnyitása */
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("SDL peldaprogram", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);



    // "általad választott színekkel"
    Color land = {255, 255, 255, 255};
    Color water = {71, 112, 80, 255};
    Color outline = {0, 0, 0, 255};
    
    Sint16 xs[] = {0, WIDTH - 1, WIDTH - 1, 0};
    Sint16 ys[] = {0, 0, HEIGHT - 1, HEIGHT - 1};
    filledPolygonRGBA(renderer, xs, ys, 4, 206, 41, 57, 255);

    draw(renderer, vilag, land, outline);
    draw(renderer, tavak, water, outline);
 
    for (int i = -180; i < 180; i += LINE_DELTA) {
        Sint16 x = longitude_to_x(i);
        aalineRGBA(renderer, x, 0, x, HEIGHT - 1, LINE_COLOR);
    }

    for (int i = -90; i < 90; i += LINE_DELTA) {
        Sint16 y = latitude_to_y(i);
        aalineRGBA(renderer, 0, y, WIDTH - 1, y, LINE_COLOR);
    }

    /* az elvegzett rajzolasok a kepernyore */
    SDL_RenderPresent(renderer);
 
    /* varunk a kilepesre */
    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT && ev.type != SDL_MOUSEBUTTONUP) {
        /* SDL_RenderPresent(renderer); - MacOS Mojave esetén */
    }
 
    /* ablak bezarasa */
    SDL_Quit();
 
    return 0;
}

