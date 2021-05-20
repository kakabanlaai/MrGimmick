#pragma once
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "Player.h"
#include "../../GameComponents/GameTime.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameComponents/GameLog.h"

class PlayerRunningState : public PlayerState
{
public:
    PlayerRunningState(PlayerData* playerData);
    ~PlayerRunningState();

    void HandleKeyboard(std::map<int, bool> keys);

    void OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState();

protected:
    bool noPressed;
};

