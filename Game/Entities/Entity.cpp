//
//  Entity.cpp
//  Game
//
//  Created by Cai Smaldon on 02/09/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "Entity.hpp"

Entity::Entity(TextureManager* inputTextureManager, Map* map, ProjectileManager* inputProjectileManager)
{
    velocity = 0;
    tickCounter = 0;
    animationSpeed = 10;
    animationCount = 0;
    textureManager = inputTextureManager;
    projectileManager = inputProjectileManager;
}

int Entity::act()
{
    int trigger = ACTION_TRIGGER_NONE;
    
    while(actionList.size() > 0) processAction(); //While?
    
    if(velocity > 0)
    {
        position.move(velocity, speed);
        handleAnimations();
        trigger = position.checkGridPositionChange();
    }
    else animationCount = 0;
    
    return trigger;
}

void Entity::queueAction(Action action)
{
    actionList.push_back(action);
}

void Entity::processAction()
{
    switch(actionList[0].type)
    {
        case ACTION_MOVE: move(&actionList[0]); break;
        case ACTION_HALT: halt(&actionList[0]); break;
        case ACTION_UPDOWN: upDown(&actionList[0]); break;
    }
    actionList.erase(actionList.begin());
}

void Entity::handleAnimations()
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

void Entity::move(Action* action)
{
    velocity |= 1 << action->subType;
}

void Entity::halt(Action* action)
{
    velocity &= ~(1 << action->subType);
}

void Entity::upDown(Action* action)
{
    
    if(action->subType == DIRECTION_DOWN)
    {
        position.moveZ(-1);
    }
    else if (action->subType == DIRECTION_UP)
    {
        position.moveZ(1);
    }
}

void Entity::shoot(Action* action)
{
    projectileManager->addProjectile(&position);
}


