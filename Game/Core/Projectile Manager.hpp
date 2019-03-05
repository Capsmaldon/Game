//
//  Projectile Manager.hpp
//  Game
//
//  Created by Cai Smaldon on 07/09/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef Projectile_Manager_hpp
#define Projectile_Manager_hpp

#include "Includes.h"
#include "Projectile.hpp"

class ProjectileManager
{
public:
    ProjectileManager(TextureManager* inputTextureManager, SDL_Rect** inputTextureSelector);
    void addProjectile(Position* gunPosition);
    void draw(SDL_Renderer* mainRenderer);
    void tick();
private:
    std::vector<Projectile*> projectileList;
    SDL_Rect* textureSelector;
    TextureManager* textureManager;
};

#endif /* Projectile_Manager_hpp */
