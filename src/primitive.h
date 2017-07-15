#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>


enum DRAW_TYPE {
    FILLED,
    OUTLINE
};

static Uint32 _color;

void draw_color(Uint8, Uint8, Uint8, Uint8);
void draw_rectangle(SDL_Renderer*, DRAW_TYPE, float, float, int, int);
void draw_circle(SDL_Renderer*, DRAW_TYPE, float, float, int);

#endif

