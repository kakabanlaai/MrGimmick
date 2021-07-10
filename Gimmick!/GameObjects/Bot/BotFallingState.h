#pragma once
#include "BotState.h"


class BotFallingState : public BotState
{
public:
    BotFallingState(BotData* botData);
    ~BotFallingState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    void OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState();

protected:
    float acceleratorY;
    float acceleratorX;

    //neu nhu van toc ban dau = khong thi se khong cho giam toc do
    bool allowMoveX;

    bool isLeftOrRightKeyPressed;
};

