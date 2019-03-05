//
//  CollisionUtility.cpp
//  Game
//
//  Created by Cai Smaldon on 27/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "CollisionManager.hpp"

bool CollisionManager::handleCollision(float velocity,
                                      int directionPlane,
                                      float *physicalPos,
                                      int *hitboxPos,
                                      int *prevHitboxPosX,
                                      int *prevHitboxPosY,
                                      int *hitboxLength,
                                      int *textureLength,
                                      int *texturePos,
                                      GridSpace* gridSpace,
                                      Map *map)
{
    bool moved = false;
    bool collision = false;
    int* prevHitboxPos = nullptr;
    if(directionPlane == PLANE_EW) prevHitboxPos = prevHitboxPosX;
    else if(directionPlane == PLANE_NS) prevHitboxPos = prevHitboxPosY;
    
    GridPosition gridPositions;
    while(gridSpace->pollTouchingTiles(&gridPositions) /*&& !moved*/)
    {
        Tile* tile = map->getTile(gridPositions.x, gridPositions.y, gridPositions.z);
        if(tile == nullptr)
        {
            collision = true;
            GridPosition topLeftGridPosition;
            PositionUtility::getGridPosition(&topLeftGridPosition, *prevHitboxPosX, *prevHitboxPosY);
            
            if(*hitboxPos <= *prevHitboxPos && !moved)
            {
                if(directionPlane == PLANE_EW)*physicalPos = topLeftGridPosition.x*TILE_SIZE;
                else if(directionPlane == PLANE_NS) *physicalPos = topLeftGridPosition.y*TILE_SIZE;
                moved = true;
            }
            else if(*hitboxPos > *prevHitboxPos && !moved)
            {
                int tileRemainder = (TILE_SIZE - (*hitboxLength % TILE_SIZE))-1;
                
                if(directionPlane == PLANE_EW)*physicalPos = (topLeftGridPosition.x*TILE_SIZE) + tileRemainder;
                else if(directionPlane == PLANE_NS) *physicalPos = (topLeftGridPosition.y*TILE_SIZE) + tileRemainder;
                moved = true;
            }
            
            if(moved)
            {
                *hitboxPos = (int)*physicalPos;
                *texturePos = *hitboxPos - (*textureLength-*hitboxLength)*0.5;
            }
        }
        else if(!tile->getTileProperties()->isPassable)
        {
            collision = true;
            tile->onHardCollision();
            
            if(velocity > 0)
            {
                SDL_Rect *tilePosition = tile->getTilePosition();
                
                if(directionPlane == PLANE_EW) *physicalPos = (tilePosition->x-*hitboxLength)-1;
                else if(directionPlane == PLANE_NS) *physicalPos = (tilePosition->y-*hitboxLength)-1;
            }
            else if(velocity < 0)
            {
                SDL_Rect *tilePosition = tile->getTilePosition();
                if(directionPlane == PLANE_EW)*physicalPos = tilePosition->x+tilePosition->w;
                else if(directionPlane == PLANE_NS)*physicalPos = tilePosition->y+tilePosition->h;
            }
            *hitboxPos = (int)*physicalPos;
            *texturePos = *hitboxPos - (*textureLength-*hitboxLength)*0.5;
        }
    }
    
    return collision;
}
