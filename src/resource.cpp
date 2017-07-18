#include "resource.h"

RESOURCE_TYPE ResourceManager::getResourceType(std::string path)
{
    std::ifstream file;
    std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    if (
        strncmp(data.c_str(), "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A", 8) ||
        strncmp(data.c_str(), "\xFF\xD8\xFF", 3) ||
        strncmp(data.c_str(), "\x42\x4D", 2)
    ) {
        return RESOURCE_IMAGE;
    }
    
    if (
        strncmp(data.c_str(), "\x4F\x67\x67\x53", 4) ||
        strncmp(data.c_str(), "\x52\x49\x46\x46", 4)
    ) {
        return RESOURCE_AUDIO;
    }
    
    return RESOURCE_UNDEFINED;
}

int ResourceManager::isDirectory(std::string path)
{
    struct stat statbuffer;
    stat(path.c_str(), &statbuffer);
    return !S_ISREG(statbuffer.st_mode);
}

void ResourceManager::loadResources(std::string folder)
{
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(folder.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (isDirectory(folder+"/"+std::string(ent->d_name))) {
                if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
                    loadResources(folder+"/"+std::string(ent->d_name));
                }
            } else {
                printf("%s/%s\n", folder.c_str(), ent->d_name);
                // find resource type
                RESOURCE_TYPE type = getResourceType(folder+"/"+std::string(ent->d_name));
                
                switch (type) {
                    case RESOURCE_IMAGE:
                        m_images.emplace(folder+"/"+std::string(ent->d_name), new Image(folder+"/"+std::string(ent->d_name), m_renderer));
                        break;
                    case RESOURCE_AUDIO:
                        break;
                    default:
                        break;
                }
            }
        }
        closedir(dir);
    }
}

ResourceManager::ResourceManager(SDL_Renderer* renderer, std::string folder)
{
    // TODO: remove from constructor
    m_renderer = renderer;
    loadResources(folder);
}

Image* ResourceManager::getImage(std::string file)
{
    return m_images[file];
}

void ResourceManager::loadResource(std::string file)
{
    if (m_images[file] == nullptr) {
        m_images[file] = new Image(file, m_renderer);
    }
}


