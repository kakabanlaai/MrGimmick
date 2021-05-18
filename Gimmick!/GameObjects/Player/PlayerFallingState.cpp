#include "PlayerFallingState.h"
#include "PlayerStandingState.h"
#include "Player.h"
#include "../../GameDefines/GameDefine.h"

PlayerFallingState::PlayerFallingState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	acceleratorY = 30.0f;
	acceleratorX = 2.5f;
}


PlayerFallingState::~PlayerFallingState()
{
}

void PlayerFallingState::Update(float dt)
{
	this->mPlayerData->player->AddVy(acceleratorY);

	if (mPlayerData->player->GetVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
	{
		mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	}

	if (mPlayerData->player->GetPosition().y >= Define::GAME_SCREEN_HEIGHT / 2)
	{
		mPlayerData->player->SetVy(0);
		mPlayerData->player->SetState(new PlayerRunningState(mPlayerData));
		return;
	}
}

void PlayerFallingState::HandleKeyboard(std::map<int, bool> keys)
{

	if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(false);

		//di chuyen sang phai
		if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(acceleratorX);

			if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	else if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(true);

		//di chuyen sang trai
		if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(-acceleratorX);

			if (this->mPlayerData->player->GetVx() <= -Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	else
	{
		isLeftOrRightKeyPressed = false;
	}
}

PlayerState::StateName PlayerFallingState::GetState()
{
	return PlayerState::Falling;
}
