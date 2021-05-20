#include "PlayerRunningState.h"

using namespace Define;

PlayerRunningState::PlayerRunningState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
}


PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::Update(float dt)
{
    if (noPressed)
    {
        if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
        {
            //player dang di chuyen sang ben trai      
            if (mPlayerData->player->GetVx() < 0)
            {
                this->mPlayerData->player->AddVx(PLAYER_RUN_ACCELERATOR);

                if (mPlayerData->player->GetVx() >= 0)
                {
                    mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
                    return;
                }
            }
        }
        else if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
        {
            //player dang di chuyen sang phai   
            if (mPlayerData->player->GetVx() > 0)
            {
                this->mPlayerData->player->AddVx(-PLAYER_RUN_ACCELERATOR);

                if (mPlayerData->player->GetVx() <= 0)
                {
                    mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
                    return;
                }
            }
        }

        if (mPlayerData->player->GetVx() == 0)
        {
            mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
            return;
        }
    }
}

void PlayerRunningState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_SPACE] && this->mPlayerData->player->GetAllowJump())
    {
        this->mPlayerData->player->SetState(new PlayerJumpingState(this->mPlayerData));
        return;
    }

    if (keys[VK_RIGHT])
    {
        if (this->mPlayerData->player->GetVx() < 0) 
        {
            this->mPlayerData->player->SetVx(0);
        }

        mPlayerData->player->SetReverse(false);

        //di chuyen sang phai
        if (this->mPlayerData->player->GetVx() < PLAYER_MAX_RUNNING_SPEED)
        {
            this->mPlayerData->player->AddVx(PLAYER_RUN_ACCELERATOR);

            if (this->mPlayerData->player->GetVx() >= PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(PLAYER_MAX_RUNNING_SPEED);
            }
        }
        noPressed = false;
    }
    else if (keys[VK_LEFT])
    {
        if (this->mPlayerData->player->GetVx() > 0)
        {
            this->mPlayerData->player->SetVx(0);
        }

        mPlayerData->player->SetReverse(true);

        //di chuyen sang trai
        if (this->mPlayerData->player->GetVx() > -PLAYER_MAX_RUNNING_SPEED)
        {
            this->mPlayerData->player->AddVx(-PLAYER_RUN_ACCELERATOR);

            if (this->mPlayerData->player->GetVx() < -PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(-PLAYER_MAX_RUNNING_SPEED);
            }
        }
        noPressed = false;
    }
    else
    {
        noPressed = true;
    }
}

PlayerState::StateName PlayerRunningState::GetState()
{
    return PlayerState::Running;
}
