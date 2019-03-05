//
//  Settings.h
//  Game
//
//  Created by Cai Smaldon on 08/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef Settings_h
#define Settings_h

const int WINDOW_FPS = 60;
const float WINDOW_FRAME_DURATION = 1000.0f / WINDOW_FPS;

const int WINDOW_W = 800;
const int WINDOW_H = 640;

const int MAP_WIDTH = 32;
const int MAP_HEIGHT = 24;

const int TILE_SIZE = 96;
const float TILE_SIZE_MULTIPLIER = 1.0/TILE_SIZE;

const float BASE_SPEED = 4;

const int COLLISION_RUMBLE = 6; // 6 = No collision rumble, >7 Collision rumble
const float COLLISION_POSITION_ADJUSTMENT = TILE_SIZE_MULTIPLIER * COLLISION_RUMBLE * -1.0;

enum
{
    TILE_VOID = 1, TILE_GRASS, TILE_SLATE, TILE_SLATE_SURFACE, TILE_WALL, TILE_AIR, TILE_STAIRS, TILE_DIRT, TILE_WATER, ENTITY_PLAYER, PROJECTILE_GENERIC
};

enum
{
    DIRECTION_NORTH, DIRECTION_SOUTH, DIRECTION_WEST, DIRECTION_EAST, DIRECTION_UP, DIRECTION_DOWN, PLANE_NS, PLANE_EW, DIRECTION_ANY
};

enum
{
   BORDER_NORTH, BORDER_SOUTH, BORDER_WEST, BORDER_EAST
};

enum
{
    ACTION_TRIGGER_NONE, ACTION_TRIGGER_GRIDPOSITIONCHANGED, ACTION_MOVE, ACTION_HALT, ACTION_UPDOWN
};

enum
{
    EVENT_NONE, EVENT_COLLISION, EVENT_ENTER
};

struct Action
{
    int type;
    int subType;
    int quality;
    int state;
};

struct PhysicalPosition // Turn this into a position manager class
{
    float x;
    float y;
    float z;
};

struct GridPosition
{
    int x;
    int y;
    int z;
};

struct Borders
{
    int north;
    int south;
    int west;
    int east;
};

struct TileProperties
{
    int transparency;
    int lightLevel;
    bool isHidden;
    
    bool isSolid;
    bool isGas;
    bool isPassable;
    bool isAscendable;
    bool isTransparent;
    
    bool isInUse;
    bool markedForLightUpdate;
};

struct TextureTag
{
    int primary;
    int orientation;
    
};

#endif /* Settings_h */
