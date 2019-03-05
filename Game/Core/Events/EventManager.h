//
//  EventManager.hpp
//  Game
//
//  Created by Cai Smaldon on 10/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef EventManager_hpp
#define EventManager_hpp

#include "Includes.h"
#include "Game.h"

class Game;

class EventManager
{
public:
    EventManager(Game* game_, SDL_Window* window);
    
    void attachWindow(SDL_Window* window);
    bool handleEvents();
    
private:
    Game* game;
    SDL_Event event;
    
    SDL_Window* mainWindow;
    SDL_Rect* renderDistance;
    
    Player* player;
    
    Action userAction;
    bool is_Running;
};

#endif /* EventManager_hpp */
