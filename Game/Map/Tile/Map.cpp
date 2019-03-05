//
//  Map.cpp
//  Game
//
//  Created by Cai Smaldon on 17/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#include "Map.hpp"

Map::Map()
{
    height = 0;
    width = 0;
}

Map::~Map()
{
    for(int x = 0; x < map.size(); x++)
    {
        for(int y = 0; y < map[x].size(); y++)
        {
            for(int z = 0; z < map[x][y].size(); z++)
            {
                if(map[x][y][z] != nullptr)
                {
                    delete map[x][y][z];
                }
            }
        }
    }
}

void Map::createMap(TextureManager* textureManager)
{
    for (int z = 0; z < 8; ++z)
    {
        for(int y = 0; y < 20; y++)
        {
            for(int x = 0; x < 25; x++)
            {
                Tile* tile = new Concrete(textureManager, x, y);
                setTile(tile, x, y, z);
            }
        }
    }
    
    for (int z = 6; z < 8; ++z)
    {
        for(int y = 10; y < 15; y++)
        {
            for(int x = 10; x < 22; x++)
            {
                Tile* tile = new Dirt(textureManager, x, y);
                setTile(tile, x, y, z);
            }
        }
    }
    
    for (int z = 8; z < 10; ++z)
    {
        for(int y = 0; y < 20; y++)
        {
            for(int x = 0; x < 25; x++)
            {
                Tile* tile = new Air(textureManager, x, y);
                setTile(tile, x, y, z);
            }
        }
    }
    
    for (int z = 1; z < 10; ++z)
    {
        for(int y = 1; y < 2; y++)
        {
            for(int x = 1; x < 2; x++)
            {
                Tile* tile = new Stairs(textureManager, x, y);
                setTile(tile, x, y, z);
            }
        }
    }
    
    for (int z = 6; z < 8; ++z)
    {
        for(int y = 1; y < 3; y++)
        {
            for(int x = 2; x < 18; x++)
            {
                Tile* tile = new Air(textureManager, x, y);
                setTile(tile, x, y, z);
            }
        }
    }
    
    for (int z = 6; z < 7; ++z)
    {
        for(int y = 3; y < 20; y++)
        {
            for(int x = 16; x < 18; x++)
            {
                Tile* tile = new Air(textureManager, x, y);
                setTile(tile, x, y, z);
            }
        }
    }
    
    for (int z = 1; z < 9; ++z)
    {
        for(int y = 19; y < 20; y++)
        {
            for(int x = 17; x < 18; x++)
            {
                Tile* tile = new Stairs(textureManager, x, y);
                setTile(tile, x, y, z);
            }
        }
    }
}

void Map::setTile(Tile* tile, int x, int y, int z)
{
    while(map.size() <= x)
    {
        map.push_back(std::vector<std::vector<Tile*>>());
        if(height<=x)height++;
    }
    
    while(map[x].size() <= y)
    {
        map[x].push_back(std::vector<Tile*>());
        if(height<=y)height++;
    }
    while(map[x][y].size() <= z)
    {
        map[x][y].push_back(nullptr);
        if(depth<=z)depth++;
    }
    
    if(map[x][y][z] != nullptr) delete map[x][y][z];
    map[x][y][z] = tile;
    
    GridPosition newTileGridPosition;
    newTileGridPosition.x = x;
    newTileGridPosition.y = y;
    newTileGridPosition.z = z;
    
    updateLightLevel(newTileGridPosition);
    createAirBoundaries(newTileGridPosition);
}

Tile* Map::getTile(int x, int y, int z)
{
    if(x >= map.size() || x < 0) return nullptr;
    if(y >= map[x].size() || y < 0) return nullptr;
    if(z >= map[x][y].size() || z < 0) return nullptr;
    else return map[x][y][z];
}

void Map::updateLightLevel(GridPosition position)
{
    std::vector<GridPosition> tilesToUpdate;
    
    Tile* thisTile = getTile(position.x, position.y, position.z);
    Tile* targetTile = nullptr;
    
    TileProperties* thisTileProperties = thisTile->getTileProperties();
    TileProperties* targetTileProperties = nullptr;
    
    bool transparentAdjacentTile = false;
    
    thisTileProperties->isHidden = true;
    thisTileProperties->markedForLightUpdate = true;
    
    //Scan the adjacent tiles and make updates
    for(int y = position.y-1; y <= position.y+1; y++)
    {
        for (int x = position.x-1; x <= position.x+1; x++)
        {
            //Don't scan itself
            if(x == position.x && y == position.y) x++;
            targetTile = getTile(x, y, position.z);
            targetTileProperties = targetTile->getTileProperties();
            
            if(targetTile != nullptr)
            {
                if(thisTileProperties->isTransparent)
                {
                    targetTileProperties->isHidden = false;
                }
                else if(!thisTileProperties->isTransparent)
                {
                    if(targetTileProperties->isTransparent)
                    {
                        thisTileProperties->isHidden = false;
                        transparentAdjacentTile = true;
                    }
                    else if(!targetTileProperties->isTransparent)
                    {
                        if(!targetTileProperties->markedForLightUpdate && !targetTileProperties->isHidden)
                        {
                            targetTileProperties->markedForLightUpdate = true;
                            GridPosition nextTileGridPosition;
                            nextTileGridPosition.x = x;
                            nextTileGridPosition.y = y;
                            nextTileGridPosition.z = position.z;
                            tilesToUpdate.push_back(nextTileGridPosition);
                        }
                    }
                }
            }
        }
    }
    
    if(!transparentAdjacentTile)
    {
        thisTileProperties->isHidden = true;
    }
    
    while(tilesToUpdate.size() > 0)
    {
        updateLightLevel(tilesToUpdate.back());
        tilesToUpdate.pop_back();
        
        static int timesExecuted = 0;
        std::cout << timesExecuted << std::endl;
        timesExecuted++;
    }
    
    thisTileProperties->markedForLightUpdate = false;
}

void Map::createAirBoundaries(GridPosition position)
{
    Tile* thisTile = nullptr;
    Tile* tileAbove = nullptr;
    Tile* tileBelow = nullptr;
    
    thisTile = getTile(position.x, position.y, position.z);
    tileAbove = getTile(position.x, position.y, position.z+1);
    tileBelow = getTile(position.x, position.y, position.z-1);
    
    // If tile being placed is a solid or it's ascendable, make the above tile passable if it's not a solid
    if(tileAbove != nullptr && (thisTile->getTileProperties()->isSolid || thisTile->getTileProperties()->isAscendable) && !tileAbove->getTileProperties()->isSolid)
    {
        tileAbove->getTileProperties()->isPassable = true;
    }
    // Else if the tile being placed is a gas, and the tile below is a gas, make the current tile unpassable
    if(tileBelow != nullptr && thisTile->getTileProperties()->isGas && tileBelow->getTileProperties()->isGas)
    {
        thisTile->getTileProperties()->isPassable = false;
        if(tileAbove != nullptr)
        {
            tileAbove->getTileProperties()->isPassable = false;
        }
    }
}
