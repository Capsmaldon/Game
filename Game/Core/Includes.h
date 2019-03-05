//
//  Includes.h
//  Game
//
//  Created by Cai Smaldon on 09/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef Includes_h
#define Includes_h

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Settings.h"
#include <iostream>
#include <vector>

class Utility
{
public:
    
    static SDL_Texture* loadTexture(const char* textureFilename, SDL_Renderer* renderer)
    {
        SDL_Surface* imageSurface = IMG_Load(textureFilename);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        
        if(texture == NULL)
            std::cout << "Error:" << textureFilename << "failed to load" << std::endl;
        else
            std::cout << textureFilename << " loaded" << std::endl;
        
        SDL_FreeSurface(imageSurface);
        
        return texture;
    }
};

#endif /* Includes_h */
