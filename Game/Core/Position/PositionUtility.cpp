//
//  PositionUtility.cpp
//  Game
//
//  Created by Cai Smaldon on 16/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "PositionUtility.h"

void PositionUtility::getGridPosition(GridPosition* gridPosition, SDL_Rect* hitbox)
{
    int xHitboxCentre = hitbox->x + (hitbox->w/2);
    int yHitboxCentre = hitbox->y + (hitbox->h/2);
    
    if(xHitboxCentre >= 0)
    {
        gridPosition->x = xHitboxCentre/TILE_SIZE; //Calculates based on centre of tile
    }
    else
    {
        gridPosition->x = xHitboxCentre/TILE_SIZE -1;
    }
    
    
    if(yHitboxCentre >= 0)
    {
        gridPosition->y = yHitboxCentre/TILE_SIZE;
    }
    else
    {
        gridPosition->y = yHitboxCentre/TILE_SIZE -1;
    }
}

void PositionUtility::getGridPosition(GridPosition* gridPosition, int x, int y)
{
    if(x >= 0)
    {
        gridPosition->x = x/TILE_SIZE; //Calculates based on centre of tile
    }
    else
    {
        gridPosition->x = x/TILE_SIZE -1;
    }
    
    
    if(y >= 0)
    {
        gridPosition->y = y/TILE_SIZE;
    }
    else
    {
        gridPosition->y = y/TILE_SIZE -1;
    }
}

SDL_Rect* PositionUtility::getTileDestination(SDL_Rect* tileDestination, PhysicalPosition* cameraPosition, SDL_Rect* windowSize, GridPosition* gridPosition)
{
    tileDestination->x = ((gridPosition->x-(cameraPosition->x/TILE_SIZE)) * TILE_SIZE) + (windowSize->w*0.5);
    tileDestination->y = ((gridPosition->y-(cameraPosition->y/TILE_SIZE)) * TILE_SIZE) + (windowSize->h*0.5);
    
    return tileDestination;
}
