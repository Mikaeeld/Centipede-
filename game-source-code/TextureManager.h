#pragma once

#include "ResourceManager.h"
#include "SFML/Graphics.hpp"

class TextureManager : public ResourceManager<TextureManager, sf::Texture>
{
public:
    TextureManager() : ResourceManager("textures.cfg") {}

    sf::Texture *load(const string& path)
    {
        sf::Texture *texture = new sf::Texture();
        if (!texture->loadFromFile(path))
        {
            delete texture;
            texture = nullptr;
            cerr << "failed to load texture";
        }
        return texture;
    }
};