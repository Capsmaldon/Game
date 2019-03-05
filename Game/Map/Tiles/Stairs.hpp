//
//  Stairs.hpp
//  Game
//
//  Created by Cai Smaldon on 27/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef Stairs_hpp
#define Stairs_hpp

#include "Tile.h"

class Stairs : public Tile
{
public:
    Stairs(TextureManager* mainTextureManager, int x, int y);
    void onHardCollision() override;
    void onEnter() override;
};

#endif /* Stairs_hpp */
