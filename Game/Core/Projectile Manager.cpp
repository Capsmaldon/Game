//
//  Projectile Manager.cpp
//  Game
//
//  Created by Cai Smaldon on 07/09/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "Projectile Manager.hpp"

ProjectileManager::ProjectileManager(TextureManager* inputTextureManager, SDL_Rect** inputTextureSelector)
{
    textureManager = inputTextureManager;
    textureSelector = *inputTextureSelector;
}

void ProjectileManager::addProjectile(Position* gunPosition)
{
    projectileList.push_back(new Projectile(gunPosition, textureManager));
}

void ProjectileManager::draw(SDL_Renderer* mainRenderer)
{
    for(int i = 0; i < projectileList.size(); i++)
    {
        Projectile* projectile = projectileList[i];
        SDL_RenderCopyEx(mainRenderer,
                         textureManager->getTextureByID(projectile->getTextureNum(),
                                                        projectile->getAnimationCount()),
                         textureSelector,
                         projectile->getPosition()->getTexturePosition(),
                         projectile->getPosition()->getRotation(),
                         NULL,
                         SDL_FLIP_NONE);
    }
}

void ProjectileManager::tick()
{
    for(int i = 0; i < projectileList.size(); i++)
    {
        if(projectileList[i]->move())
        {
            delete projectileList[i];
            projectileList.erase(projectileList.begin() + i);
            i--;
        }
    }
}
