//
//  CollisionUtility.hpp
//  Game
//
//  Created by Cai Smaldon on 27/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef CollisionUtility_hpp
#define CollisionUtility_hpp

#include "Includes.h"
#include "GridSpace.hpp"
#include "Map.hpp"
#include "Tile.h"

class CollisionManager
{
public:
    static bool handleCollision(float velocity,
                                int directionPlane,
                                float *physicalPos,
                                int *hitboxPos,
                                int *prevHitboxPosX,
                                int *prevHitboxPosY,
                                int *hitboxLength,
                                int *textureLength,
                                int *texturePos,
                                GridSpace* gridSpace,
                                Map *map);
};

#endif /* CollisionUtility_hpp */
