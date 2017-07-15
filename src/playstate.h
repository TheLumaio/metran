#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "engine.h"
#include "image.h"
#include "primitive.h"
#include "math.h"

struct tree {
    int health;
    int shake;
    float x;
    float y;
    float r;
    tree(float x, float y) :
        health(5),
        shake(0),
        x(x),
        y(y),
        r(0)
    {};
};

struct wood {
    float x;
    float y;
    float r;
    float v;
    wood(float x, float y) :
        x(x),
        y(y)
    {
        v = (50+rand()%100);
        r = to_radians(rand()%360);
    }
};

class Playstate : public Gamestate
{
    private:
        std::vector<tree> m_trees;
        std::vector<wood> m_wood;

        Image m_treeimage;
        Image m_woodimage;

    public:
        Playstate(Engine*);
        ~Playstate()=default;
    
        void update(float) override;
        void render(SDL_Renderer*) override;
        void mousepressed(Sint32, Sint32, Uint8) override;

};

#endif

