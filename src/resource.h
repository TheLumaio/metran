#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>
#include <vector>
#include <map>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <streambuf>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "image.h"

enum RESOURCE_TYPE {
    RESOURCE_IMAGE,
    RESOURCE_AUDIO,
    RESOURCE_UNDEFINED
};
        
class ResourceManager
{
    private:
        std::map<std::string, Image*> m_images;
        
        RESOURCE_TYPE getResourceType(std::string);
        int isDirectory(std::string);
        void loadResources(std::string);
        
        SDL_Renderer* m_renderer;

    public:
        ResourceManager(SDL_Renderer*, std::string="assets");

        Image* getImage(std::string);
        void loadResource(std::string);

};

#endif

