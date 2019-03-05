//
//  Grass.hpp
//  Game
//
//  Created by Cai Smaldon on 09/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef Grass_h
#define Grass_h

#include "Tile.h"

class Dirt : public Tile
{
public:
    Dirt(TextureManager* mainTextureManager, int x, int y);
};

#endif /* Grass_hpp */
