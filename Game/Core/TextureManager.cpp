//
//  TextureList.cpp
//  Game
//
//  Created by Cai Smaldon on 13/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "TextureManager.h"

TextureManager::TextureManager(SDL_Renderer* mainRenderer, SDL_Rect **gameTextureSelector)
{
    renderer = mainRenderer;
    addTexture(TILE_WATER, "assets/water.png", 1);
    addTexture(TILE_AIR, "assets/air.png", 1);
    
    textureSelector.x = 0;
    textureSelector.y = 0;
    textureSelector.h = TILE_SIZE;
    textureSelector.w = TILE_SIZE;
    
    *gameTextureSelector = &textureSelector;
}

TextureManager::~TextureManager()
{
    for (int i = 0; i < textureList.size(); ++i)
    {
        SDL_DestroyTexture(textureList[i].texture);
    }
}

SDL_Texture* TextureManager::getTextureByID(int textureID, int textureVariationNum)
{
    SDL_Texture* texture = nullptr;
    bool textureFound = false;
    
    for(int i = 0; i < textureList.size(); ++i) // Should definitely upgrade this to a better search algorithm (Binary sort)
    {
        if(textureID == textureList[i].uniqueID)
        {
            if(textureVariationNum < 0 && textureVariationNum > textureList[i].textureVariations) textureVariationNum = 0;
            textureSelector = textureList[i].textureTileSize;
            textureSelector.x = textureVariationNum * textureList[i].textureTileSize.w;
            texture = textureList[i].texture;
            textureFound = true;
            break;
        }
    }
    
    if (!textureFound)
    {
        std::cout << "Texture number '" << textureID << "' not found" << std::endl;
    }
    
    return texture;
}

int TextureManager::addTexture(int textureID, const char* textureFilename, int numOfTextureVariations)
{
    TextureEntry textureEntry;
    int uniqueID = 0;
    bool unique = true;
    
    for(int i = 0; i < textureList.size(); ++i)
    {
        if(textureID == textureList[i].uniqueID)
        {
            uniqueID = textureList[i].uniqueID;
            unique = false;
        }
    }
    
    if(unique)
    {
        textureEntry.uniqueID = textureID;
        uniqueID = textureID;
        textureEntry.texture = Utility::loadTexture(textureFilename, renderer);
        int totalTextureWidth;
        SDL_QueryTexture(textureEntry.texture, NULL, NULL, &totalTextureWidth, &textureEntry.textureTileSize.h);
        textureEntry.textureVariations = numOfTextureVariations;
        textureEntry.textureTileSize.w = totalTextureWidth / numOfTextureVariations;
        textureEntry.textureTileSize.y = 0;
        
        textureList.push_back(textureEntry);
        std::cout << "Entry added with ID " << textureID << std::endl;
    }
    
    return uniqueID;
}
