//
//  GridSpace.cpp
//  Game
//
//  Created by Cai Smaldon on 19/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "GridSpace.hpp"

GridSpace::GridSpace(SDL_Rect* positionHitbox, float* depth)
{
    hitbox = positionHitbox;
    tileCounter = 0;
    numOfTouchingTilesIndex = 0;
    z = depth;
}

GridSpace::~GridSpace()
{
    for (int x = 0; x < gridSpace.size(); x++)
    {
        delete gridSpace[x];
    }
    std::cout << "GridSpace deleted" << std::endl;
}

void GridSpace::update()
{
    //TOUCHING TILES CALCULATIONS
    GridPosition topLeftCornerGridPosition, botRightCornerGridPosition;
    PositionUtility::getGridPosition(&topLeftCornerGridPosition, hitbox->x, hitbox->y);
    PositionUtility::getGridPosition(&botRightCornerGridPosition, (hitbox->x+hitbox->w), (hitbox->y+hitbox->h));
    
    int w = (botRightCornerGridPosition.x - topLeftCornerGridPosition.x)+1;
    int h = (botRightCornerGridPosition.y - topLeftCornerGridPosition.y)+1;
    
    numOfTouchingTiles = w * h;
    
    while(numOfTouchingTiles > gridSpace.size())
    {
        gridSpace.push_back(new GridPosition);
    }
    
    int i = 0;
    for(int x = 0; x < w; x++)
    {
        for(int y = 0; y < h; y++)
        {
            gridSpace[i]->x = topLeftCornerGridPosition.x + x;
            gridSpace[i]->y = topLeftCornerGridPosition.y + y;
            gridSpace[i]->z = *z;
            i++;
        }
    }
    
    //OVERLAPPING TILES CALCULATIONS
    int tilesWide = hitbox->w * TILE_SIZE_MULTIPLIER;
    int tilesHigh = hitbox->h * TILE_SIZE_MULTIPLIER;
    
    numOfOverlappedTiles = tilesWide * tilesHigh;
    if(numOfOverlappedTiles < 1) numOfOverlappedTiles = 1;
    
    while(numOfOverlappedTiles > stepSpace.size())
    {
        stepSpace.push_back(new GridPosition);
    }
    
    centre.x = hitbox->x + (hitbox->w*0.5);
    centre.y = hitbox->y + (hitbox->h*0.5);
    centre.z = *z;
    
    PositionUtility::getGridPosition(&centre, centre.x, centre.y);
    
    if(numOfOverlappedTiles > 1)
    {
        GridPosition tl_centre, br_centre, target;
        
        tl_centre.x = hitbox->x + (TILE_SIZE*0.5);
        tl_centre.y = hitbox->y + (TILE_SIZE*0.5);
        tl_centre.z = *z;
        
        br_centre.x = hitbox->x+hitbox->w - (TILE_SIZE*0.5);
        br_centre.y = hitbox->y+hitbox->h - (TILE_SIZE*0.5);
        br_centre.z = *z;
        
        int row = 0;
        int column = 0;
        int index = 0;
        int side = 0;
        
        target = tl_centre;
        
        while(index < numOfOverlappedTiles)
        {
            if(side == 0)
            {
                target.x = tl_centre.x + (column*TILE_SIZE);
                target.y = tl_centre.y + (row*TILE_SIZE);
                side = 1;
            }
            else if(side == 1)
            {
                target.x = br_centre.x - (column*TILE_SIZE);
                target.y = br_centre.y - (row*TILE_SIZE);
                column++;
                side = 0;
            }
            
            if(target.x > br_centre.x)
            {
                side = 0;
                column = 0;
                row++;
            }
            else
            {
                *stepSpace[index] = target;
                index++;
            }
        }
    }
    else
    {
        *stepSpace[0] = centre;
    }
}

bool GridSpace::pollTouchingTiles(GridPosition* gridPosition)
{
    bool tilesRemaining;
    
    if(tileCounter == 0) update();
    
    if(tileCounter < numOfTouchingTiles)
    {
        *gridPosition = *gridSpace[numOfTouchingTilesIndex];
        numOfTouchingTilesIndex++;
        tileCounter++;
        tilesRemaining = true;
    }
    else
    {
        tileCounter = 0;
        numOfTouchingTilesIndex = 0;
        tilesRemaining = false;
    }
    
    return tilesRemaining;
}

bool GridSpace::pollOverlappingTiles(GridPosition *gridPosition)
{
    bool tilesRemaining;
    
    if(tileCounter == 0) update();
    
    if(tileCounter < numOfTouchingTiles)
    {
        *gridPosition = *stepSpace[numOfTouchingTilesIndex];
        numOfTouchingTilesIndex++;
        tileCounter++;
        tilesRemaining = true;
    }
    else
    {
        tileCounter = 0;
        numOfTouchingTilesIndex = 0;
        tilesRemaining = false;
    }
    
    return tilesRemaining;
}
