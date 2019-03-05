//
//  EventManager.cpp
//  Game
//
//  Created by Cai Smaldon on 10/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "EventManager.h"

EventManager::EventManager(Game* game_, SDL_Window* window)
{
    game = game_;
    player = game->getEntityList();
    renderDistance = game->getRenderDistance();
    
    mainWindow = window;
    is_Running = true;
}

bool EventManager::handleEvents()
{
    while (SDL_PollEvent(&event)) // Event loop
    {
        Action action;
        
        switch (event.type)
        {
                
            case SDL_QUIT: is_Running = false; break;
            case SDL_WINDOWEVENT:
            switch(event.window.event)
            {
                    case SDL_WINDOWEVENT_MAXIMIZED:
                    case SDL_WINDOWEVENT_RESIZED:
                    game->setRenderDistance(mainWindow);
                    game->getPlayer()->getPosition()->setScreenCentre(mainWindow);
                    break;
            }
            case SDL_MOUSEMOTION:
                game->getPlayer()->getPosition()->rotateTowardsMouse(event.motion.x, event.motion.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                game->getPlayer()->shoot(&action);
                
            case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
                case SDLK_w: action.type = ACTION_MOVE; action.subType = DIRECTION_NORTH; player->queueAction(action); break;
                case SDLK_s: action.type = ACTION_MOVE; action.subType = DIRECTION_SOUTH; player->queueAction(action); break;
                case SDLK_a: action.type = ACTION_MOVE; action.subType = DIRECTION_WEST; player->queueAction(action); break;
                case SDLK_d: action.type = ACTION_MOVE; action.subType = DIRECTION_EAST; player->queueAction(action); break;
                case SDLK_e: action.type = ACTION_UPDOWN; action.subType = DIRECTION_DOWN; player->queueAction(action); break;
                case SDLK_q: action.type = ACTION_UPDOWN; action.subType = DIRECTION_UP; player->queueAction(action); break;
            }
            break;
                
            case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
                case SDLK_w: action.type = ACTION_HALT; action.subType = DIRECTION_NORTH; player->queueAction(action); break;
                case SDLK_s: action.type = ACTION_HALT; action.subType = DIRECTION_SOUTH; player->queueAction(action); break;
                case SDLK_a: action.type = ACTION_HALT; action.subType = DIRECTION_WEST; player->queueAction(action); break;
                case SDLK_d: action.type = ACTION_HALT; action.subType = DIRECTION_EAST; player->queueAction(action); break;
            }
            break;
        }
    }
    
    return is_Running;
}
