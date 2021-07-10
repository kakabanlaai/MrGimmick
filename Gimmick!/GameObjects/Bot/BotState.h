#pragma once
#include "BotData.h"
#include "../Entity.h"
#include <map>

class BotState
{
public:
    enum StateName
    {
        Standing,
        Running,
        Falling,
        Jumping,
        Die
    };

    ~BotState();

    virtual void Update(float dt);

    virtual void HandleKeyboard(std::map<int, bool> keys);

    //ham thuan ao bat buoc phai ke thua
    virtual StateName GetState() = 0;

    virtual void OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
protected:
    BotState(BotData* playerData);
    BotState();

    BotData* mBotData;
};


