#pragma once
#include "Bot.h"
#include "BotState.h"

class BotJumpingState : public BotState
{
public:
    BotJumpingState(BotData* botData);
    ~BotJumpingState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    void OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState();

protected:
    D3DXVECTOR3 standingPosition;
    float acceleratorY;
    float acceleratorX;
    bool noPressed;
    bool allowMoveRight, allowMoveLeft;
    bool allowJump = true;
};
