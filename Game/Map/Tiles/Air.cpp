//
//  Air.cpp
//  Game
//
//  Created by Cai Smaldon on 24/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "Air.hpp"

Air::Air(TextureManager* mainTextureManager, int x, int y) : Tile(mainTextureManager, x , y)
{
    Tile::loadMainTexture(TILE_AIR, "assets/air.png", 1);
    Tile::setType(TILE_AIR);
    tileProperties.isSolid = false;
    tileProperties.isGas = true;
    tileProperties.isPassable = true;
    tileProperties.isTransparent = true;
    tileProperties.transparency = 64;
}

void Air::onEnter()
{
    std::cout << "That's air" << std::endl;
}


