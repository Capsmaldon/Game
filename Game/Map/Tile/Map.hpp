//
//  Map.hpp
//  Game
//
//  Created by Cai Smaldon on 17/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include "Includes.h"
#include "Tile.h"
#include "TileList.h"

class Map
{
public:
    
    Map();
    ~Map();
    
    void createMap(TextureManager* textureManager);
    void setTile(Tile* tile, int x, int y, int z);
    
    int getCurrentWidth(){return width;}
    int getCurrentHeight(){return height;}
    Tile* getTile(int x, int y, int z);
    
protected:
    void updateLightLevel(GridPosition position);
    void createAirBoundaries(GridPosition position);
    
private:
    int width;
    int height;
    int depth;
    std::vector<std::vector<std::vector<Tile*>>> map; //x, y, z
};

#endif /* Map_hpp */
