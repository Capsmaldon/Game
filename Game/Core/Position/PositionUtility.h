//
//  PositionUtility.hpp
//  Game
//
//  Created by Cai Smaldon on 16/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef PositionUtility_hpp
#define PositionUtility_hpp

#include "Includes.h"

class PositionUtility
{
public:
    static void getGridPosition(GridPosition* gridPosition, SDL_Rect* hitbox);
    static void getGridPosition(GridPosition* gridPosition, int x, int y);
    static SDL_Rect* getTileDestination(SDL_Rect* tileDestination, PhysicalPosition* cameraPosition, SDL_Rect* windowSize, GridPosition* gridPosition);
};

#endif /* PositionUtility_hpp */
