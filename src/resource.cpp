#include "resource.h"

ResourceManager::ResourceManager(std::string folder)
{

}

Image* ResourceManager::getImage(std::string file)
{
    return m_images[file];
}

void ResourceManager::loadResource(std::string file, SDL_Renderer* renderer)
{
    if (m_images[file] == nullptr) {
        m_images[file] = new Image(file, renderer);
    }
}


