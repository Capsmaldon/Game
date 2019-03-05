//
//  Grass.cpp
//  Game
//
//  Created by Cai Smaldon on 09/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "Dirt.h"

Dirt::Dirt(TextureManager* mainTextureManager, int x, int y) : Tile(mainTextureManager, x, y)
{
    Tile::loadMainTexture(TILE_DIRT, "assets/dirt.png", 1);
    Tile::loadSurfaceTexture(TILE_GRASS, "assets/grass.png", 1);
    Tile::setType(TILE_DIRT);
    tileProperties.isSolid = true;
    tileProperties.isTransparent = false;
}
