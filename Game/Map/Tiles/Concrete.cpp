//
//  Slate.cpp
//  Game
//
//  Created by Cai Smaldon on 13/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "Concrete.h"

Concrete::Concrete(TextureManager* mainTextureManager, int x, int y) : Tile(mainTextureManager, x ,y)
{
    textureCount = 3;
    Tile::loadMainTexture(TILE_SLATE, "assets/concrete.png", textureCount);
    Tile::loadSurfaceTexture(TILE_SLATE_SURFACE, "assets/slateSurface.png", 1);
    Tile::setType(TILE_SLATE);
    tileProperties.isSolid = true;
    tileProperties.isTransparent = false;
}

void Concrete::onHardCollision()
{
    std::cout << "Overridden" << std::endl;
}

void Concrete::onEnter()
{
    std::cout << "Stepped on Slate" << std::endl;
}
