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
        
    public:
        int width;
        int height;

        Image(std::string filename, SDL_Renderer* renderer) {
            SDL_Surface* surface = IMG_Load(filename.c_str());
            m_texture = SDL_CreateTextureFromSurface(renderer, surface);
            
            width = surface->w;
            height = surface->h;

            SDL_FreeSurface(surface);

            src = new SDL_Rect{0, 0, width, height};
            dest = new SDL_Rect{0, 0, width, height};

        }
        void render(SDL_Renderer* renderer, float x, float y, float r=0, int cx=0, int cy=0, SDL_RendererFlip f=SDL_FLIP_NONE) {
            dest->x = x;
            dest->y = y;
            //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderCopyEx(renderer, m_texture, src, dest, (double)r, new SDL_Point{cx,cy}, f);
        }
};

#endif

