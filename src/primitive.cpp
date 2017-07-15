#include "primitive.h"
#include <iostream>

void draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    _color = 
        ((unsigned char)(a) << 24) +
        ((unsigned char)(b) << 16) +
        ((unsigned char)(g) <<  8) +
         (unsigned char)(r);
}

void draw_rectangle(SDL_Renderer* renderer, DRAW_TYPE type, float x, float y, int w, int h)
{
    static SDL_Rect rect = {0, 0, 0, 0};
    
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    
    if (type == FILLED) {
        //SDL_RenderFillRect(renderer, &rect);
        rectangleColor(renderer, x, y, x+w, y+h, _color);
    } else if (type == OUTLINE) {
        //SDL_RenderDrawRect(renderer, &rect);
        boxColor(renderer, x, y, x+w, y+h, _color);
    }
}

void draw_circle(SDL_Renderer* renderer, DRAW_TYPE type, float x, float y, int radius)
{
    if (type == FILLED) {
        circleColor(renderer, x, y, radius, _color);
    } else if (type == OUTLINE) {
        filledCircleColor(renderer, x, y, radius, _color);
    }
}

