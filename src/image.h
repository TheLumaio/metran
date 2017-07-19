#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <SDL2/SDL_image.h>

class Image
{
    private:
        SDL_Texture* m_texture;
        SDL_Rect* src;
        SDL_Rect* dest;
        SDL_Point* origin;
        
    public:
        int width;
        int height;

        Image(std::string filename, SDL_Renderer* renderer) {
            SDL_Surface* surface = IMG_Load(filename.c_str());
            if (surface == nullptr) {
                printf("FAILED TO CREATE IMAGE\n");
                return;
            }
            
            m_texture = SDL_CreateTextureFromSurface(renderer, surface);
            
            width = surface->w;
            height = surface->h;

            SDL_FreeSurface(surface);

            src = new SDL_Rect{0, 0, width, height};
            dest = new SDL_Rect{0, 0, width, height};
            
            origin = new SDL_Point{0, 0};

        }
        void render(SDL_Renderer* renderer, float x, float y, float r=0, int cx=0, int cy=0, SDL_RendererFlip f=SDL_FLIP_NONE) {
            dest->x = x;
            dest->y = y;
            origin->x = cx;
            origin->y = cy;
            SDL_RenderCopyEx(renderer, m_texture, src, dest, (double)r, origin, f);
        }
        
        void setColorMod(Uint8 r=255, Uint8 g=255, Uint8 b=255, Uint8 a=255) {
            SDL_SetTextureColorMod(m_texture, r, g, b);
            SDL_SetTextureAlphaMod(m_texture, a);
        }
};

#endif

