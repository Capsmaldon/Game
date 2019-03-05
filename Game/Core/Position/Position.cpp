//
//  Position.cpp
//  Game
//
//  Created by Cai Smaldon on 16/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "Position.h"

Position::Position()
{
    gridSpace = new GridSpace(&hitbox, &hitBoxPhysicalPosition.z);
}

void Position::setMap(Map *inputMap)
{
    map = inputMap;
}

void Position::setSize(int w, int h)
{
    texturePosition.w = w;
    texturePosition.h = h;
    
    screenPosition.w = w;
    screenPosition.h = h;
    
    hitbox.w = w-1;
    hitbox.h = h-1;
    
    hitbox.x = (int)hitBoxPhysicalPosition.x;
    hitbox.y = (int)hitBoxPhysicalPosition.y;
}

void Position::overwriteHitboxSize(int w, int h)
{
    hitbox.w = w;
    hitbox.h = h;
    
    hitbox.x = (int)hitBoxPhysicalPosition.x;
    hitbox.y = (int)hitBoxPhysicalPosition.y;
}

void Position::move(int direction, float speed)
{
    int xDirection = 0, yDirection = 0;
    
    if(direction & (1 << DIRECTION_SOUTH)) yDirection = 1;
    else if (direction & (1 << DIRECTION_NORTH)) yDirection = -1;
    
    if(direction & (1 << DIRECTION_EAST)) xDirection = 1;
    else if (direction & (1 << DIRECTION_WEST)) xDirection = -1;
    
    float xVelocity = xDirection * speed;
    float yVelocity = yDirection * speed;
    
    moveX(xVelocity);
    moveY(yVelocity);
    
    gridSpace->update();
}

void Position::moveToGridPosition(float x, float y, float z)
{
    if(map->getTile(x, y, z) != nullptr && !map->getTile(x, y, z)->getTileProperties()->isSolid)
    {
        hitBoxPhysicalPosition.x = x * TILE_SIZE;
        hitBoxPhysicalPosition.y = y * TILE_SIZE;
        hitBoxPhysicalPosition.z = z;
        
        hitbox.x = (int)hitBoxPhysicalPosition.x;
        hitbox.y = (int)hitBoxPhysicalPosition.y;
        
        texturePosition.x = hitbox.x - (texturePosition.w-hitbox.w)*0.5;
        texturePosition.y = hitbox.y - (texturePosition.h-hitbox.h)*0.5;
        
        gridSpace->update();
    }
}

bool Position::moveX(float xVelocity)
{
    
    if(xVelocity == 0) return false;
    
    prevHitbox.x = hitbox.x;
    hitBoxPhysicalPosition.x += xVelocity;
    hitbox.x = (int)hitBoxPhysicalPosition.x;
    texturePosition.x = hitbox.x - (texturePosition.w-hitbox.w)*0.5;
    
    return CollisionManager::handleCollision(xVelocity,
                                      PLANE_EW,
                                      &hitBoxPhysicalPosition.x,
                                      &hitbox.x,
                                      &prevHitbox.x,
                                      &prevHitbox.y,
                                      &hitbox.w,
                                      &texturePosition.w,
                                      &texturePosition.x,
                                      gridSpace,
                                      map);
}

bool Position::moveY(float yVelocity)
{
    if(yVelocity == 0) return false;
    
    prevHitbox.y = hitbox.y;
    hitBoxPhysicalPosition.y += yVelocity;
    hitbox.y = (int)hitBoxPhysicalPosition.y;
    texturePosition.y = hitbox.y - (texturePosition.h-hitbox.h)*0.5;
    
    return CollisionManager::handleCollision(yVelocity,
                                      PLANE_NS,
                                      &hitBoxPhysicalPosition.y,
                                      &hitbox.y, &prevHitbox.x,
                                      &prevHitbox.y,
                                      &hitbox.h,
                                      &texturePosition.h,
                                      &texturePosition.y,
                                      gridSpace,
                                      map);
}

void Position::moveZ(float zVelocity)
{
    
    bool stairsFound = false;
    bool collision = false;
    Tile* ascendableTile = nullptr;
    Tile* targetTile = nullptr;
    int direction = 0;
    
    float newZPosition = hitBoxPhysicalPosition.z + zVelocity;
    
    GridPosition gridPositions;
    while(gridSpace->pollTouchingTiles(&gridPositions))
    {
        targetTile = map->getTile(gridPositions.x, gridPositions.y, (int)hitBoxPhysicalPosition.z);
        if(targetTile == nullptr){collision = true;}
            else if(targetTile->getTileProperties()->isAscendable)
            {
                ascendableTile = targetTile;
                stairsFound = true;
                direction = zVelocity;
            }
            else if(!targetTile->getTileProperties()->isPassable)
            {
                collision = true;
            }
        
        targetTile = map->getTile(gridPositions.x, gridPositions.y, (int)newZPosition);
        if(targetTile == nullptr){collision = true;}
        else if(targetTile->getTileProperties()->isAscendable)
        {
            ascendableTile = targetTile;
            stairsFound = true;
            direction = zVelocity;
        }
        
        else if(!targetTile->getTileProperties()->isPassable)
        {
            collision = true;
        }
    }
    
    if(stairsFound && !collision)
    {
        hitBoxPhysicalPosition.z += direction;
        gridSpace->update();
    }
}

void Position::rotateTowardsMouse(int mouseX, int mouseY)
{
    int deltaX = windowCenter.x - mouseX;
    int deltaY = windowCenter.y - mouseY;
    rotation = (atan2(deltaY, deltaX)*180)/3.1416;
}

int Position::checkGridPositionChange()
{
    GridPosition gridSpaceCentre = *gridSpace->getCentreGridPosition();

    int trigger = ACTION_TRIGGER_NONE;

    if(gridCentre.x != gridSpaceCentre.x || gridCentre.y != gridSpaceCentre.y || gridCentre.z != gridSpaceCentre.z)
    {
        gridCentre = *gridSpace->getCentreGridPosition();
        trigger = ACTION_TRIGGER_GRIDPOSITIONCHANGED;
    }
    return trigger;
}

void Position::setScreenCentre(SDL_Window* window)
{
    int w;
    int h;
    SDL_GetWindowSize(window, &w, &h);
    windowCenter.x = w*0.5;
    windowCenter.y = h*0.5;
    
    screenPosition.x = windowCenter.x - (texturePosition.w*0.5);
    screenPosition.y = windowCenter.y - (texturePosition.h*0.5);
    screenPosition.w = texturePosition.w;
    screenPosition.h = texturePosition.h;
}

void Position::getCentrePosition(PhysicalPosition* centrePosition)
{
    centrePosition->x = hitbox.x+((hitbox.w+0.5)*0.5);
    centrePosition->y = hitbox.y+((hitbox.h+0.5)*0.5);
    centrePosition->z = hitBoxPhysicalPosition.z;
}
