//
//  Player.hpp
//  Game
//
//  Created by Cai Smaldon on 09/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Entity.hpp"

class Player : public Entity
{
public:
    Player(TextureManager* textureManager, Map* inputMap, ProjectileManager* inputProjectileManager);
};

#endif /* Player_hpp */
