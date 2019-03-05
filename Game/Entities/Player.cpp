//
//  Player.cpp
//  Game
//
//  Created by Cai Smaldon on 09/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "Player.h"

Player::Player(TextureManager* textureManager, Map* inputMap, ProjectileManager* inputProjectileManager) : Entity(textureManager, inputMap, inputProjectileManager)
{
    float sizeMultiplier = 0.8;
    position.setMap(inputMap);
    position.setSize(TILE_SIZE*1.333*sizeMultiplier, TILE_SIZE*sizeMultiplier);
    position.overwriteHitboxSize(TILE_SIZE*sizeMultiplier*0.6, TILE_SIZE*sizeMultiplier*0.6);
    position.moveToGridPosition(1, 1, 2);
    
    animationNum = 4;
    textureNum = textureManager->addTexture(ENTITY_PLAYER, "assets/playerWpistol2.png", animationNum);
    speed = BASE_SPEED*2;
}
