#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

class Text
{
    private:
        TTF_Font* m_font;
        SDL_Surface* m_surface;
        SDL_Texture* m_texture;
        SDL_Rect* m_src;
        SDL_Rect* m_dst;
        SDL_Point* m_origin;
        SDL_Color m_color;
        std::string m_text;
        
    public:
        Text(std::string file="", int size=16) {
            m_font = TTF_OpenFont(file.c_str(), size);
            
            // color
            m_color.r = 255;
            m_color.g = 255;
            m_color.b = 255;
            m_color.a = 255;
            
            // rects
            m_src = new SDL_Rect{0, 0, 0, 0};
            m_dst = new SDL_Rect{0, 0, 0, 0};
            
            // origin
            m_origin = new SDL_Point{0, 0};
        }
        ~Text()=default;
        
        void setText(SDL_Renderer* renderer, std::string text)
        {
            if (text != m_text) {
                m_text = text;
                m_surface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_color);
                m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
                
                m_src->w = m_surface->w;
                m_src->h = m_surface->h;
                m_dst->w = m_surface->w;
                m_dst->h = m_surface->h;
                
                SDL_FreeSurface(m_surface);
            }
        }
        
        void render(SDL_Renderer* renderer, float x, float y, float r=0, int cx=0, int cy=0)
        {
            m_dst->x = x;
            m_dst->y = y;
            
            m_origin->x = cx;
            m_origin->y = cy;
            
            if (m_surface != nullptr) {
                SDL_RenderCopyEx(renderer, m_texture, m_src, m_dst, r, m_origin, SDL_RendererFlip::SDL_FLIP_NONE);
            }
        }
        
        SDL_Rect* getSize() {
            return m_src;
        }
        
};

#endif
