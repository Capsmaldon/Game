//
//  Tile.cpp
//  Game
//
//  Created by Cai Smaldon on 13/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "Tile.h"

Tile::Tile(TextureManager* mainTextureManager, int x, int y)
{
    textureManager = mainTextureManager;
    setType(0);
    mainTexture = 0;
    surfaceTexture = 0;
    
    tilePosition.x = x * TILE_SIZE;
    tilePosition.y = y * TILE_SIZE;
    tilePosition.w = TILE_SIZE;
    tilePosition.h = TILE_SIZE;
    
    tileProperties.isSolid = true;
    tileProperties.isGas = false;
    tileProperties.isPassable = false;
    tileProperties.isAscendable = false;
    tileProperties.isTransparent = false;
    tileProperties.transparency = 255;
    tileProperties.lightLevel = 255;
    tileProperties.isHidden = true;
    tileProperties.isInUse = false;
    tileProperties.markedForLightUpdate = false;
    
}

void Tile::setType(int tileID)
{
    type = tileID;
}

void Tile::loadMainTexture(int textureID, const char* mainTextureFilename, int numOfTextureVariations)
{
    textureVariationNum = std::rand()%numOfTextureVariations;
    mainTexture = textureManager->addTexture(textureID, mainTextureFilename, numOfTextureVariations);
    if(surfaceTexture == 0)surfaceTexture = textureID;
}

void Tile::loadSurfaceTexture(int textureID, const char* surfaceTextureFilename, int numOfTextureVariations)
{
    surfaceTexture = textureManager->addTexture(textureID, surfaceTextureFilename, numOfTextureVariations);
}
