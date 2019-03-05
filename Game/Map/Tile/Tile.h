//
//  Tile.hpp
//  Game
//
//  Created by Cai Smaldon on 13/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#include "TextureManager.h"

class Tile
{
public:
    Tile(TextureManager* mainTextureManager, int x, int y);
    
    int getMainTextureID(){return mainTexture;}
    int getSurfaceTextureID(){return surfaceTexture;}
    virtual void onHardCollision(){std::cout << "Hard Collision" << std::endl;}
    virtual void onSoftCollision(){std::cout << "Soft Collision" << std::endl;}
    virtual void onEnter(){}
    SDL_Rect* getTilePosition(){return &tilePosition;}
    TileProperties* getTileProperties(){return &tileProperties;}
    int getType(){return type;}
    int getTextureVariation(){return textureVariationNum;}
    
protected:
    void loadMainTexture(int textureID, const char* mainTextureFilename, int numOfTextureVariations);
    void loadSurfaceTexture(int textureID, const char* surfaceTextureFilename, int numOfTextureVariations);
    void setType(int tileID);
    TileProperties tileProperties;
    int textureCount;
    
private:
    int type;
    int mainTexture, surfaceTexture;
    TextureManager* textureManager;
    SDL_Rect tilePosition;
    int textureVariationNum;
};

#endif /* Tile_hpp */
