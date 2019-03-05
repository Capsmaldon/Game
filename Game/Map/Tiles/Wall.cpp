//
//  Wall.cpp
//  Game
//
//  Created by Cai Smaldon on 15/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "Wall.h"

Wall::Wall(TextureManager* mainTextureManager, int x, int y) : Tile(mainTextureManager, x , y)
{
    Tile::loadMainTexture(TILE_WALL, "assets/wall.png", 1);
    Tile::setType(TILE_WALL);
    tileProperties.isSolid = true;
}

void Wall::onHardCollision()
{
    std::cout << "Oof that's a wall" << std::endl;
}

void Wall::onEnter()
{
    std::cout << "That's not supposed to happen" << std::endl;
}
