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
    
    m_camera.setZoom(3);
    
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
    
    if (m_engine->isKeyDown(SDLK_a)) {
        m_camera.move(500*dt, 0);
    }
    else if (m_engine->isKeyDown(SDLK_d)) {
        m_camera.move(-500*dt, 0);
    }
    if (m_engine->isKeyDown(SDLK_w)) {
        m_camera.move(0, 500*dt);
    }
    else if (m_engine->isKeyDown(SDLK_s)) {
        m_camera.move(0, -500*dt);
    }
}

void Playstate::render(SDL_Renderer* renderer)
{
    
    m_camera.attach();
    
    draw_color(20, 30, 20, 255);
    draw_rectangle(renderer, FILLED, 0, 0, 1280, 720);
    
    // tree zsorting
    std::sort(m_trees.begin(), m_trees.end(), [&](tree& a, tree& b) {
            return a.y+m_treeimage->height < b.y+m_treeimage->height;
            });
    std::sort(m_wood.begin(), m_wood.end(), [&](wood& a, wood& b) {
            return a.y+m_woodimage->height < b.y+m_woodimage->height;
            });
    
    for (auto& t : m_trees)
    {
        // shadows
        m_treeimage->setColorMod(0, 0, 0, 50);
        m_treeimage->render(renderer, t.x, t.y+64, -t.r, 32, 0, SDL_RendererFlip::SDL_FLIP_VERTICAL);
        m_treeimage->setColorMod();
    }

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
    
    m_camera.detach();
    
    std::string fps =  "FPS: " + std::to_string(m_engine->m_framerate->rate);
    m_text.setText(m_renderer, fps);
    m_text.render(m_renderer, 50, 50);
}

void Playstate::mousepressed(Sint32 x, Sint32 y, Uint8 b)
{
    auto cx = m_camera.getX();
    auto cy = m_camera.getY();
    
    Sint32 dx = (-cx+x)/3;
    Sint32 dy = (-cy+y)/3;
    
    if (b == 3) {
        m_trees.emplace_back(tree{(float)x, (float)y});
    }
    if (b == 1) {
        // break tree
        for (int i = m_trees.size()-1; i >= 0; i--)
        {
            auto& t = m_trees[i];
            if (dx > t.x && dx < t.x+m_treeimage->width && dy > t.y && dy < t.y+m_treeimage->height && t.shake <= 0) {
                t.shake = 10;
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
                break;
            }
        }
        // collect wood
        for (int i = m_wood.size()-1; i >= 0; i--)
        {
            auto& w = m_wood[i];
            if (dx > w.x && dx < w.x+m_woodimage->width && dy > w.y && dy < w.y+m_woodimage->height) {
                m_wood.erase(m_wood.begin()+i);
                break;
            }
        }
    }
}

