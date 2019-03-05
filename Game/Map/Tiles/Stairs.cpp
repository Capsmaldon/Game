//
//  Stairs.cpp
//  Game
//
//  Created by Cai Smaldon on 27/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "Stairs.hpp"

Stairs::Stairs(TextureManager* mainTextureManager, int x, int y) : Tile(mainTextureManager, x ,y)
{
    Tile::loadMainTexture(TILE_STAIRS, "assets/VerticalStairs.png", 1);
    Tile::setType(TILE_STAIRS);
    tileProperties.isSolid = false;
    tileProperties.isGas = false;
    tileProperties.isPassable = true;
    tileProperties.isAscendable = true;
    tileProperties.isTransparent = true;
    tileProperties.transparency = 127;
}

void Stairs::onHardCollision()
{
    std::cout << "Overridden" << std::endl;
}

void Stairs::onEnter()
{
    std::cout << "Stepped on Slate" << std::endl;
}
