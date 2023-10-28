#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>

double eps = 1;
 
int main(int argc, char *argv[]) {
    /* SDL inicializálása és ablak megnyitása */
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("SDL peldaprogram", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
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
 
    int x0 = 320, y0 = 240;
    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 480; y++) {
            double d = sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0));
            d = fabs(d - 200);
            if (d < eps)
                pixelRGBA(renderer, x, y, 135, 50, 40, 255);
       }
    }
    stringRGBA(renderer, 90, 220, "kor", 135, 50, 40, 255);

    int x1 = 240, y1 = 200, x2 = 400, y2 = 280;
    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 480; y++) {
            double d1 = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
            double d2 = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
            double d = d1 + d2;
            d = fabs(d - 250);
            if (d < eps)
                pixelRGBA(renderer, x, y, 50, 110, 70, 255);
       }
    }
    stringRGBA(renderer, 140, 260, "ellipszis", 50, 110, 70, 255);
 
    x1 = 240, y1 = 240, x2 = 400, y2 = 240;
    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 480; y++) {
            double d1 = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
            double d2 = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
            double d = fabs(d1 - d2);
            d = fabs(d - 100);
            if (d < eps)
                pixelRGBA(renderer, x, y, 90, 110, 200, 255);
       }
    }
    stringRGBA(renderer, 144, 8, "hiperbola", 90, 110, 200, 255);

    x0 = 320, y0 = 240, x1 = 400;
    for (int x = 0; x < 640; x++) {
        for (int y = 0; y < 480; y++) {
            double d1 = sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0));
            double d2 = fabs((double)x - x1);
            double d = fabs(d1 - d2);
            if (d < eps)
                pixelRGBA(renderer, x, y, 255, 255, 255, 255);
       }
    }
    stringRGBA(renderer, 58, 54, "parabola", 255, 255, 255, 255);

    /* szoveg */
    stringRGBA(renderer, 390, 460, "Kilepeshez: piros x az ablakon", 255, 255, 255, 255);
 
    /* az elvegzett rajzolasok a kepernyore */
    SDL_RenderPresent(renderer);
 
    /* varunk a kilepesre */
    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        /* SDL_RenderPresent(renderer); - MacOS Mojave esetén */
    }
 
    /* ablak bezarasa */
    SDL_Quit();
 
    return 0;
}

