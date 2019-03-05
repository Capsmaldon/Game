//
//  Window.cpp
//  Game
//
//  Created by Cai Smaldon on 08/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "Window.h"

Window::Window()
{
    is_running = true;
    
    if(SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_PNG))
    {
        std::cout << "SDL failed to initialise" << std::endl;
        terminate();
    }
    else
    {
        window = SDL_CreateWindow("Game",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  WINDOW_W,
                                  WINDOW_H,
                                  SDL_WINDOW_RESIZABLE);
        if(window == NULL)
        {
            std::cout << "SDL failed to create window" << std::endl;
            terminate();
        }
        else
        {
            game = new Game(window);
            eventManager = new EventManager(game, window);
        }
    }
}

Window::~Window()
{
    delete game;
    delete eventManager;
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::run()
{
    Uint32 frameStartTime, nextFrameTime, currentTime;
    
    //Game loop
    while (is_running)
    {
        frameStartTime = SDL_GetTicks();
        
        is_running = eventManager->handleEvents();
        
        //Process frames here
        game->tick();
        
        //Delay if ahead of schedule
        nextFrameTime = frameStartTime + WINDOW_FRAME_DURATION;
        currentTime = SDL_GetTicks();
        
        if(currentTime < nextFrameTime)
        {
            SDL_Delay(nextFrameTime - currentTime);
        }
    }
}

void Window::terminate()
{
    is_running = false;
}
