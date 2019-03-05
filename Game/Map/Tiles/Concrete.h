//
//  Slate.hpp
//  Game
//
//  Created by Cai Smaldon on 13/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef Slate_hpp
#define Slate_hpp

#include "Tile.h"

class Concrete : public Tile
{
public:
    Concrete(TextureManager* mainTextureManager, int x, int y);
    void onHardCollision() override;
    void onEnter() override;
};

#endif /* Slate_hpp */
