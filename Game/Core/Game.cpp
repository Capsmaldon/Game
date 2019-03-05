//
//  GameCore.cpp
//  Game
//
//  Created by Cai Smaldon on 09/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "Game.h"

Game::Game(SDL_Window* window)
{
    mainRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);
    
    textureSelector = nullptr;
    textureManager = new TextureManager(mainRenderer, &textureSelector);
    
    projectileManager = new ProjectileManager(textureManager, &textureSelector);
    
    //Temp map fill
    map.createMap(textureManager);
    
    player = new Player(textureManager, &map, projectileManager);
    player->getPosition()->setScreenCentre(window);
    
    setRenderDistance(window);
    
    //Configure rect sizes
    destTile.w = TILE_SIZE;
    destTile.h = TILE_SIZE;
}

Game::~Game()
{
    delete player;
    SDL_DestroyRenderer(mainRenderer);
}

void Game::tick()
{
    //Game logic
    while(int trigger = player->act())
    {
        switch(trigger)
        {
            case ACTION_TRIGGER_GRIDPOSITIONCHANGED:
                calculateTileRenderDistance();
                if(Tile* tile = map.getTile((int)player->getPosition()->getGridSpace()->getCentreGridPosition()->x,
                                            (int)player->getPosition()->getGridSpace()->getCentreGridPosition()->y,
                                            (int)player->getPosition()->getGridSpace()->getCentreGridPosition()->z))
                {
                    tile->onEnter();
                }
                break;
        }
    }
    projectileManager->tick();
    
    SDL_RenderClear(mainRenderer); // Render graphics
    
    renderTiles();
    projectileManager->draw(mainRenderer);
    renderPlayer();
    
    //Deal with the graphics
    SDL_RenderPresent(mainRenderer);
}

void Game::renderTiles()
{
    for (int y = borders.north; y <= borders.south; ++y)
    {
        for(int x = borders.west; x <= borders.east; ++x)
        {
            int z = player->getPosition()->getGridSpace()->getCentreGridPosition()->z;
            player->getPosition()->getCentrePosition(&cameraPosition);
            
            GridPosition tileGridPosition;
            tileGridPosition.x = x;
            tileGridPosition.y = y;
            
            SDL_Rect* tileDestination = PositionUtility::getTileDestination(&destTile, &cameraPosition, &windowSize, &tileGridPosition);
            Tile* tile = map.getTile(x, y, z);
            
            //If the tile is not on the map render water and air
            if (tile == nullptr)
            {
                PhysicalPosition cameraPosition;
                player->getPosition()->getCentrePosition(&cameraPosition);
                int alphaMod = 255;
                
                if(cameraPosition.z < 5)
                {
                    alphaMod = (int)cameraPosition.z * 60;
                    SDL_Texture* water = textureManager->getTextureByID(TILE_WATER, 0);
                    SDL_SetTextureAlphaMod(water, 255);
                    SDL_RenderCopy(mainRenderer, water, textureSelector, tileDestination);
                }
                
                SDL_Texture* air = textureManager->getTextureByID(TILE_AIR, 0);
                SDL_SetTextureAlphaMod(air, alphaMod);
                SDL_RenderCopy(mainRenderer, air, textureSelector, tileDestination);
            }
            //If the tile is transparent overlay transparent tiles until an opaque tile
            else if(tile->getTileProperties()->isTransparent)
            {
                std::vector<Tile*> transparentTiles;
                
                int zOfOpaqueTile = z;
                while(tile != nullptr && tile->getTileProperties()->isTransparent && transparentTiles.size() < 5)
                {
                    transparentTiles.push_back(tile);
                    tile = map.getTile(x, y, zOfOpaqueTile--);
                }
                
                if (tile != nullptr)
                {
                    SDL_Texture* opaqueTileTexture = textureManager->getTextureByID(tile->getSurfaceTextureID(), 0);
                    SDL_SetTextureAlphaMod(opaqueTileTexture, tile->getTileProperties()->lightLevel);
                    SDL_RenderCopy(mainRenderer, opaqueTileTexture, textureSelector, tileDestination);
                }
                while(transparentTiles.size() > 0)
                {
                    int textureID = transparentTiles.back()->getMainTextureID();
                    int transparency = transparentTiles.back()->getTileProperties()->transparency;
                    if(textureID == TILE_AIR && transparentTiles.size() <= 2) transparency = 0;
                    
                    SDL_Texture* transparentTile = textureManager->getTextureByID(textureID, 0);
                    SDL_SetTextureAlphaMod(transparentTile, transparency);
                    SDL_RenderCopy(mainRenderer, transparentTile, textureSelector, tileDestination);
                    transparentTiles.pop_back();
                }
            }
            //If the tile is not hidden, render it with full opacity
            else if(!tile->getTileProperties()->isHidden)
            {
                SDL_Texture* tileTexture = textureManager->getTextureByID(map.getTile(x, y, z)->getMainTextureID(), tile->getTextureVariation());
                SDL_SetTextureAlphaMod(tileTexture, tile->getTileProperties()->lightLevel);
                SDL_RenderCopy(mainRenderer,
                               tileTexture,
                               textureSelector,
                               tileDestination);
            }
        }
    }
}

void Game::renderPlayer()
{
    SDL_Rect playerSize;
    playerSize.x = 0;
    playerSize.y = 0;
    playerSize.w = TILE_SIZE;
    playerSize.h = TILE_SIZE;
    
    SDL_Texture* playerTexture = textureManager->getTextureByID(player->getTextureNum(), player->getAnimationCount());
    SDL_RenderCopyEx(mainRenderer, playerTexture, textureSelector, player->getPosition()->getScreenPosition(), player->getPosition()->getRotation(), NULL, SDL_FLIP_NONE);
}

void Game::setRenderDistance(SDL_Window* window)
{
    int w, h;
    
    SDL_GetWindowSize(window, &w, &h);

    windowSize.w = w;
    windowSize.h = h;
    renderWindow.w = (w/TILE_SIZE);
    renderWindow.h = (h/TILE_SIZE);
    
    calculateTileRenderDistance();
}

void Game::calculateTileRenderDistance()
{
    borders.north = (player->getPosition()->getGridSpace()->getCentreGridPosition()->y - renderWindow.h*0.5)-1;
    borders.south = (player->getPosition()->getGridSpace()->getCentreGridPosition()->y + renderWindow.h*0.5)+1;
    borders.west = (player->getPosition()->getGridSpace()->getCentreGridPosition()->x - renderWindow.w*0.5)-1;
    borders.east = (player->getPosition()->getGridSpace()->getCentreGridPosition()->x + renderWindow.w*0.5)+1;
}
