#pragma once
#include "BotState.h"
#include "Bot.h"
#include "../../GameComponents/GameTime.h"

class BotRunningState : public BotState
{
public:
    BotRunningState(BotData* botData);
    ~BotRunningState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    void OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState();

protected:
    float acceleratorX;
    bool noPressed;
};

