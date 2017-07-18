#ifndef EDITOR_H
#define EDITOR_H

#include "engine.h"
#include "image.h"
#include "primitive.h"

class Editor : public Gamestate
{
    private:
        TTF_Font* m_font;

        int m_pixelsize;

    public:
        Editor(Engine*);
        ~Editor()=default;

        void render(SDL_Renderer*) override;
        void keypressed(SDL_Scancode, SDL_Keycode, Uint16) override;
};

#endif

