//
//  Camera.hpp
//  Game
//
//  Created by Cai Smaldon on 14/08/2018.
//  Copyright © 2018 Cai Smaldon. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "Includes.h"
#include "Player.h"

class Camera
{
public:
    void attachToPlayer(Player* entity);
private:
    Player* player;
};

#endif /* Camera_hpp */
