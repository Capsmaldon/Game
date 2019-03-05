//
//  Position.hpp
//  Game
//
//  Created by Cai Smaldon on 16/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef Position_hpp
#define Position_hpp

#include "Includes.h"
#include "Tile.h"
#include "Map.hpp"
#include "GridSpace.hpp"
#include "PositionUtility.h"
#include "CollisionManager.hpp"

class Position
{
public:
    Position();
    
    void setMap(Map* inputMap);
    void setSize(int w, int h);
    void overwriteHitboxSize(int w, int h);
    void setScreenCentre(SDL_Window* window);
    void move(int direction, float speed);
    bool moveX(float xVelocity);
    bool moveY(float yVelocity);
    void moveZ(float zVelocity);
    void rotateTowardsMouse(int mouseX, int mouseY);
    void moveToGridPosition(float x, float y, float z);
    int checkGridPositionChange();
    
    SDL_Rect* getTexturePosition(){return &texturePosition;}
    void getCentrePosition(PhysicalPosition* centrePosition);
    SDL_Rect* getScreenPosition(){return &screenPosition;}
    SDL_Rect* getHitbox(){return &hitbox;}
    GridSpace* getGridSpace(){return gridSpace;}
    double getRotation(){return rotation;}
    
private:
    double rotation;
    SDL_Rect texturePosition;
    PhysicalPosition hitBoxPhysicalPosition;
    GridSpace* gridSpace;
    GridPosition gridCentre;
    PhysicalPosition physicalCentre;
    SDL_Rect screenPosition;
    SDL_Rect windowCenter;
    SDL_Rect hitbox, prevHitbox;
    Map* map;
};

#endif /* Position_hpp */
