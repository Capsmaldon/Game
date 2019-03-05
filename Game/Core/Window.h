//
//  Window.h
//  Game
//
//  Created by Cai Smaldon on 08/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef Window_h
#define Window_h

#include "Includes.h"
#include "Game.h"
#include "EventManager.h"

class Window
{
public:
    Window();
    ~Window();

    void run();
    void terminate();
    
private:
    SDL_Window* window;
    SDL_Event event;
    Game* game;
    EventManager* eventManager;
    SDL_Rect windowSize;
    bool is_running = true;
};

#endif /* Window_h */
