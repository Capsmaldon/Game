//
//  Air.hpp
//  Game
//
//  Created by Cai Smaldon on 24/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef Air_hpp
#define Air_hpp

#include "Tile.h"

class Air : public Tile
{
public:
    Air(TextureManager* mainTextureManager, int x, int y);
    void onEnter() override;
};

#endif /* Air_hpp */
