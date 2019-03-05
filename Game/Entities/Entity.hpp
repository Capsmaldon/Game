//
//  Entity.hpp
//  Game
//
//  Created by Cai Smaldon on 02/09/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include "Includes.h"
#include "Position.h"
#include "Tile.h"
#include "Projectile Manager.hpp"

class Entity
{
public:
    Entity(TextureManager* inputTextureManager, Map* map, ProjectileManager* inputProjectileManager);
    
    int act();
    void queueAction(Action action);
    void processAction();
    void handleAnimations();
    
    void move(Action* action);
    void halt(Action* action);
    void upDown(Action* action);
    void shoot(Action* action);
    
    int getTextureNum(){return textureNum;}
    int getAnimationCount(){return animationCount;}
    Position* getPosition(){return &position;}
    SDL_Rect* getScreenPosition(SDL_Rect* renderWindow);
    
protected:
    int textureNum;
    int animationNum;
    int animationCount;
    int tickCounter;
    int animationSpeed;
    
    ProjectileManager* projectileManager;
    TextureManager* textureManager;
    std::vector<Action> actionList;
    Position position;
    float speed;
    
private:
    int velocity;
};

#endif /* Entity_hpp */
