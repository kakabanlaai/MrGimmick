#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameComponents/GameLog.h"

PlayerJumpingState::PlayerJumpingState(PlayerData* playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);

    acceleratorY = -3.0f;
    acceleratorX = 2.5f;

    noPressed = false;
    this->mPlayerData->player->SetAllowJump(false);
    this->standingPosition = this->mPlayerData->player->GetPosition();
}


PlayerJumpingState::~PlayerJumpingState()
{

}

void PlayerJumpingState::Update(float dt)
{
    if (noPressed)
    {
        if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
        {
            //player dang di chuyen sang ben trai      
            if (mPlayerData->player->GetVx() < 0)
            {
                this->mPlayerData->player->AddVx(acceleratorX);

                if (mPlayerData->player->GetVx() > 0)
                    this->mPlayerData->player->SetVx(0);
            }
        }
        else if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
        {
            //player dang di chuyen sang phai   
            if (mPlayerData->player->GetVx() > 0)
            {
                this->mPlayerData->player->AddVx(-acceleratorX);

                if (mPlayerData->player->GetVx() < 0)
                    this->mPlayerData->player->SetVx(0);
            }
        }
    }
}

void PlayerJumpingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_SPACE] && this->allowJump)
    {
        if (this->mPlayerData->player->GetPosition().y - this->standingPosition.y > 100)
        {
            mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
            this->allowJump = false;
            return;
        }
    }
    else
    {
        mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData)); 
        this->allowJump = true;
        return;
    }

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

        noPressed = false;
    }
    else if (keys[VK_LEFT])
    {
        mPlayerData->player->SetReverse(true);

        //di chuyen sang trai
        if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
        {
            this->mPlayerData->player->AddVx(-acceleratorX);

            if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }

        noPressed = false;
    }
    else
    {
        noPressed = true;
    }
}

PlayerState::StateName PlayerJumpingState::GetState()
{
    return PlayerState::Jumping;
}


void PlayerJumpingState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
    switch (side)
    {
    case Entity::Left:
    {
        //this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
        this->mPlayerData->player->SetVx(0);
        break;
    }

    case Entity::Right:
    {
        //this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
        this->mPlayerData->player->SetVx(0);
        break;
    }

    case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
    {
        //this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
        this->mPlayerData->player->SetVy(-this->mPlayerData->player->GetVy());
        break;
    }

    case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
    {
        this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top -5.0f));
        
    }

    default:
        break;
    }
}

