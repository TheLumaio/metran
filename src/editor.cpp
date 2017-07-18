#include "editor.h"

Editor::Editor(Engine* engineref) :
    Gamestate(engineref)
{
    m_engine = engineref;


}

void Editor::render(SDL_Renderer* renderer)
{
    draw_color(255, 100, 100, 255);
    draw_circle(renderer, FILLED, 100, 100, 50);
    draw_color(0, 0, 0, 255);
}

void Editor::keypressed(SDL_Scancode scan, SDL_Keycode key, Uint16 mods)
{
    if (key == SDLK_ESCAPE) {
       m_engine->close();
    }
}

