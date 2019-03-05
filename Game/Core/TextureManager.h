//
//  TextureList.hpp
//  Game
//
//  Created by Cai Smaldon on 13/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef TextureList_hpp
#define TextureList_hpp

#include "Includes.h"
#include <stdlib.h>

struct TextureEntry
{
    int uniqueID;
    SDL_Texture* texture;
    SDL_Rect textureTileSize;
    int textureVariations;
};

class TextureManager
{
public:
    TextureManager(SDL_Renderer* mainRenderer, SDL_Rect **gameTextureSelector);
    ~TextureManager();
    
    SDL_Texture* getTextureByID(int textureID, int textureVariationNum);
    int addTexture(int textureID, const char* textureFilename, int numOfTextureVariations);
    
private:
    std::vector<TextureEntry> textureList;
    SDL_Renderer* renderer;
    SDL_Rect textureSelector;
};

#endif /* TextureList_hpp */
