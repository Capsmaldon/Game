//
//  Projectile.hpp
//  Game
//
//  Created by Cai Smaldon on 05/09/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef Projectile_hpp
#define Projectile_hpp

#include "Includes.h"
#include "Position.h"
#include "PositionUtility.h"

class Projectile
{
public:
    Projectile(Position* gunPosition, TextureManager* textureManager);
    ~Projectile();
    
    bool move();
    void handleAnimations();
    
    int getTextureNum(){return textureNum;}
    int getAnimationCount(){return animationCount;}
    Position* getPosition(){return &position;}
    
private:
    Position position;
    float xVelocity;
    float yVelocity;
    float speed;
    
    bool collision;
    
    int textureNum;
    int animationNum;
    int animationCount;
    int tickCounter;
    int animationSpeed;
};

#endif /* Projectile_hpp */
