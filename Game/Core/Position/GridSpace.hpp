//
//  GridSpace.hpp
//  Game
//
//  Created by Cai Smaldon on 19/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef GridSpace_hpp
#define GridSpace_hpp

#include "Includes.h"
#include "PositionUtility.h"

class GridSpace
{
public:
    GridSpace(SDL_Rect* positionHitbox, float* depth);
    ~GridSpace();
    
    void update();
    
    bool pollTouchingTiles(GridPosition* gridPosition);
    bool pollOverlappingTiles(GridPosition* gridPosition);
    GridPosition* getCentreGridPosition(){return &centre;}
    
private:
    SDL_Rect* hitbox;
    std::vector<GridPosition*> gridSpace;
    GridPosition centre, oldCentre;
    int numOfTouchingTilesIndex;
    int numOfTouchingTiles;
    int tileCounter;
    float* z;
    
    std::vector<GridPosition*> stepSpace; //Tiles currently being stood on
    int numOfOverlappedTiles;
};

#endif /* GridSpace_hpp */
