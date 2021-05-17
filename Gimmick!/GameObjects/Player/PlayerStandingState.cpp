#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "Player.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameComponents/GameLog.h"

PlayerStandingState::PlayerStandingState(PlayerData* playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
}


PlayerStandingState::~PlayerStandingState()
{
}

void PlayerStandingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_SPACE] && this->mPlayerData->player->GetAllowJump())
    {
        this->mPlayerData->player->SetState(new PlayerJumpingState(this->mPlayerData));
        return;
    }
    if (keys[VK_LEFT] || keys[VK_RIGHT])
    {
        this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
        return;
    }
}

PlayerState::StateName PlayerStandingState::GetState()
{
    return PlayerState::Standing;
}
