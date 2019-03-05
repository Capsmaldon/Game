//
//  Projectile.cpp
//  Game
//
//  Created by Cai Smaldon on 05/09/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "Projectile.hpp"

Projectile::Projectile(Position* gunPosition, TextureManager* textureManager)
{
    double rotation = gunPosition->getRotation();
    
    tickCounter = 0;
    animationSpeed = 10;
    animationCount = 0;
    speed = 1;
    
    position = *gunPosition;
    
    position.setSize(16, 4);
    position.overwriteHitboxSize(2, 2);
    
    GridPosition* playerCentre = gunPosition->getGridSpace()->getCentreGridPosition();
    
    position.moveToGridPosition(playerCentre->x, playerCentre->y, playerCentre->z);
    
    double xProportion, yProportion;
    xProportion = cos(rotation);
    yProportion = sin(rotation);
    
    xVelocity = xProportion * speed;
    yVelocity = yProportion * speed;
    
    animationNum = 4;
    textureNum = textureManager->addTexture(PROJECTILE_GENERIC, "assets/projectile.png", animationNum);
    
    collision = false;
}
Projectile::~Projectile()
{
    
}

bool Projectile::move()
{
    if(position.moveX(xVelocity)) collision = true;
    if(position.moveY(yVelocity)) collision = true;
    
    handleAnimations();
    
    return collision;
}

void Projectile::handleAnimations()
{
    if(tickCounter > animationSpeed)
    {
        animationCount++;
        if(animationCount > animationNum-1)
        {
            animationCount = 0;
        }
        tickCounter = 0;
    }
    tickCounter++;
}
