//
//  Void.cpp
//  Game
//
//  Created by Cai Smaldon on 13/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "Void.h"

Void::Void(TextureManager* mainTextureManager, int x, int y) : Tile(mainTextureManager, x , y)
{
    Void::loadMainTexture(TILE_VOID, "assets/void.png", 1);
    Void::setType(TILE_VOID);
}
