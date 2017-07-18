#include "playstate.h"

Playstate::Playstate(Engine* engine) :
    Gamestate(engine),
    m_text("assets/cherry.ttf", 24)
{
    m_woodimage = m_resource->getImage("assets/wood.png");
    m_treeimage = m_resource->getImage("assets/tree.png");
    
    for (int i = 0; i < 500; i++)
    {
        m_trees.emplace_back(tree{float(rand()%1280), float(rand()%720)});
    }
    
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
    draw_color(20, 30, 20, 255);
    draw_rectangle(renderer, FILLED, 0, 0, 1280, 720);
    
    // tree zsorting
    std::sort(m_trees.begin(), m_trees.end(), [&](tree& a, tree& b) {
            return a.y+m_treeimage->height < b.y+m_treeimage->height;
            });
    std::sort(m_wood.begin(), m_wood.end(), [&](wood& a, wood& b) {
            return a.y+m_woodimage->height < b.y+m_woodimage->height;
            });

    for (auto& w : m_wood) {
        m_woodimage->render(renderer, w.x, w.y);
    }


    for (auto& t : m_trees)
    {
        if (t.shake > 0) {
            t.shake -= m_engine->getDeltaTime();
            t.r = cos(0.3*t.shake)*t.shake;//-20+rand()%40;
        } else {
            t.r = 0;
        }
        m_treeimage->render(renderer, t.x, t.y, t.r, 32, 64);
    }
    
    m_text.setText(m_renderer, "I think kerning might be just a bit off");
    m_text.render(m_renderer, 50, 50);
}

void Playstate::mousepressed(Sint32 x, Sint32 y, Uint8 b)
{
    if (b == 3) {
        m_trees.emplace_back(tree{(float)x, (float)y});
    }
    if (b == 1) {
        // break tree
        for (int i = m_trees.size()-1; i >= 0; i--)
        {
            auto& t = m_trees[i];
            if (x > t.x && x < t.x+m_treeimage->width && y > t.y && y < t.y+m_treeimage->height) {
                t.shake = 20;
                t.health -= 1;
                if (t.health <= 0) {
                    int num = rand()%5;
                    for (int i=0; i<num; i++) {
                        int offx = -20+rand()%40;
                        int offy = -20+rand()%40;
                        m_wood.emplace_back(wood{t.x+m_treeimage->width/2, t.y+m_treeimage->height});
                    }
                    m_trees.erase(m_trees.begin()+i);
                }
                std::cout << "shake" << std::endl;;
                break;
            }
        }
        // collect wood
        for (int i = m_wood.size()-1; i >= 0; i--)
        {
            auto& w = m_wood[i];
            if (x > w.x && x < w.x+m_woodimage->width && y > w.y && y < w.y+m_woodimage->height) {
                m_wood.erase(m_wood.begin()+i);
                break;
            }
        }
    }
}

