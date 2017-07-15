#pragma once
#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_framerate.h>

class Engine;

class Gamestate
{
protected:
    Engine* m_engine;
public:
	virtual ~Gamestate(){}
	virtual void update(float){}
	virtual void render(SDL_Renderer*){}
	virtual void keypressed(SDL_Scancode, SDL_Keycode, Uint16){}
	virtual void keyreleased(SDL_Scancode, SDL_Keycode, Uint16){}
	virtual void mousepressed(Sint32, Sint32, Uint8){}
	virtual void mousereleased(Sint32, Sint32, Uint8){}
	virtual void resized(int, int){}
	virtual void textentered(char[32]){}
};

class Engine
{
public:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    std::string m_title;
    int m_width;
    int m_height;

    FPSmanager* m_framerate;


	Engine()=default;

	void init(std::string title, int width, int height) {
        m_deltatime = 0.0;
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            printf("Failed to init SDL Video\n");
            return;
        }
    
        if (SDL_CreateWindowAndRenderer(
                    width,
                    height,
                    SDL_WINDOW_SHOWN,
                    &m_window,
                    &m_renderer
                    ) != 0) {
            printf("Failed to create window and renderer\n");
            SDL_Quit();
            return;
        }

        TTF_Init();
        IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG);

        SDL_initFramerate(m_framerate);
        SDL_setFramerate(m_framerate, 60);

	}

	void start() {
        m_running = true;

        Uint32 NOW = SDL_GetTicks(); //SDL_GetPerformanceCounter();
        Uint32 LAST = 0;

        while (m_running)
        {
            NOW = SDL_GetTicks();
            if (NOW > LAST) {
                m_deltatime = ((float)(NOW-LAST))/1000;
                LAST = NOW;
            }

            // Events
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_KEYDOWN:
                        if (m_states[m_id] != nullptr) {
                            m_states[m_id]->keypressed(
                                    event.key.keysym.scancode,
                                    event.key.keysym.sym,
                                    event.key.keysym.mod
                                    );
                        }
                        break;
                    case SDL_KEYUP:
                        if (m_states[m_id] != nullptr) {
                            m_states[m_id]->keyreleased(
                                    event.key.keysym.scancode,
                                    event.key.keysym.sym,
                                    event.key.keysym.mod
                                    );
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (m_states[m_id] != nullptr) {
                            m_states[m_id]->mousepressed(
                                    event.button.x,
                                    event.button.y,
                                    event.button.button
                                    );
                        }
                        break;
                    case SDL_MOUSEBUTTONUP:
                        if (m_states[m_id] != nullptr) {
                            m_states[m_id]->mousereleased(
                                    event.button.x,
                                    event.button.y,
                                    event.button.button
                                    );
                        }
                        break;
                    case SDL_TEXTINPUT:
                        if (m_states[m_id] != nullptr) {
                            m_states[m_id]->textentered(
                                    event.text.text
                                    );
                        }
                        break;
                    case SDL_QUIT:
                        m_running = false;
                        break;
                    default:
                        break;
                }
            }

            if (m_states[m_id] != nullptr) {
                m_states[m_id]->update(m_deltatime);
            }

            // Rendering
            SDL_RenderClear(m_renderer);
            if (m_states[m_id] != nullptr) {
                m_states[m_id]->render(m_renderer);
            }
            SDL_RenderPresent(m_renderer);

            SDL_framerateDelay(m_framerate);
        }

        // Do cleanup
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
	}

	void changeState(std::string id, Gamestate* state=nullptr) {
		if (m_states[id] != nullptr) m_id = id;
		else {
			m_states[id] = state;
			m_id = id;
		}
	}

    void close() {
        m_running = false;
    }

    float getDeltaTime() {
        return m_deltatime;
    }

private:
    float m_deltatime;
    bool m_running;
	std::string m_id;
	Gamestate* m_stateref;
	std::map<std::string, Gamestate*> m_states;
};
