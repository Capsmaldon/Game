//
//  GameCore
//
//  Created by Cai Smaldon on 09/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef GameCore_h
#define GameCore_h

#include "Includes.h"
#include "TileList.h"
#include "Map.hpp"
#include "Player.h"
#include "Projectile Manager.hpp"

class Game
{
public:
    Game(SDL_Window* window);
    ~Game();
    
    SDL_Rect* getRenderDistance(){return &renderWindow;}
    Player* getEntityList(){return player;}
    void tick();
    void renderTiles();
    void renderPlayer();
    SDL_Rect* placeTile(SDL_Rect* tile, int x, int y);
    void setRenderDistance(SDL_Window* window);
    void calculateTileRenderDistance();
    Player* getPlayer(){return player;}
    
private:
    SDL_Renderer* mainRenderer;
    
    Map map;
    
    Player* player;
    ProjectileManager* projectileManager;
    
    SDL_Rect* textureSelector;
    SDL_Rect destTile;
    
    SDL_Rect renderWindow;
    SDL_Rect windowSize;
    Borders borders;
    
    TextureManager* textureManager;
    
    PhysicalPosition cameraPosition;
    
    SDL_Event event;
};

#endif /* GameCore_h */
