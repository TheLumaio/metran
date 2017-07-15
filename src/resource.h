#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>
#include <vector>
#include <map>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "image.h"

class ResourceManager
{
    private:
        std::map<std::string, Image*> m_images;

    public:
        ResourceManager(std::string="assets");

        Image* getImage(std::string);
        void loadResource(std::string, SDL_Renderer*);

};

#endif

