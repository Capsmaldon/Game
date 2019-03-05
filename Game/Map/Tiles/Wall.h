//
//  Wall.hpp
//  Game
//
//  Created by Cai Smaldon on 15/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef Wall_hpp
#define Wall_hpp

#include "Tile.h"

class Wall : public Tile
{
public:
    Wall(TextureManager* mainTextureManager, int x, int y);
    void onHardCollision() override;
    void onEnter() override;
};

#endif /* Wall_hpp */
