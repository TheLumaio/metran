#include "playstate.h"

Playstate::Playstate(Engine* engine) :
    m_treeimage("tree.png", engine->m_renderer),
    m_woodimage("wood.png", engine->m_renderer)
{
    m_engine = engine;
}

void Playstate::update(float dt)
{
    for (auto& w : m_wood) {
        if (w.v < 0) w.v = 0;
        double dx = cos(w.r);
        double dy = sin(w.r);
        if (w.v > 0) {
            w.x += dx*w.v*dt;
            w.y += dy*w.v*dt;
            w.v -= 500*dt;
        }
    }
}

void Playstate::render(SDL_Renderer* renderer)
{
    draw_color(100, 100, 100, 255);
    draw_rectangle(renderer, FILLED, 0, 0, 1280, 720);
    for (auto& t : m_trees)
    {
        if (t.shake > 0) {
            t.shake -= m_engine->getDeltaTime();
            t.r = cos(t.shake)*20;//-20+rand()%40;
            std::cout << "shook " << t.shake << " " << t.r << " " << m_engine->getDeltaTime() << std::endl;
        } else {
            t.r = 0;
        }
        m_treeimage.render(renderer, t.x, t.y, t.r, 16, 64);
    }

    for (auto& w : m_wood) {
        m_woodimage.render(renderer, w.x, w.y);
    }
}

void Playstate::mousepressed(Sint32 x, Sint32 y, Uint8 b)
{
    if (b == 3) {
        m_trees.emplace_back(tree{x, y});
    }
    if (b == 1) {
        // break tree
        for (int i = m_trees.size()-1; i >= 0; i--)
        {
            auto& t = m_trees[i];
            if (x > t.x && x < t.x + 32 && y > t.y && y < t.y + 64) {
                t.shake = 250;
                t.health -= 1;
                if (t.health <= 0) {
                    int num = rand()%5;
                    for (int i=0; i<num; i++) {
                        int offx = -20+rand()%40;
                        int offy = -20+rand()%40;
                        m_wood.emplace_back(wood{x, y});
                    }
                    m_trees.erase(m_trees.begin()+i);
                }
                std::cout << "shake" << std::endl;;
            }
        }
        // collect wood
        for (int i = m_wood.size()-1; i >= 0; i--)
        {
            auto& w = m_wood[i];
            if (x > w.x && x < w.x+16 && y > w.y && y < w.y+8) {
                m_wood.erase(m_wood.begin()+i);
                break;
            }
        }
    }
}

