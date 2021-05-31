#include "PlayerRunningState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameComponents/GameLog.h"

PlayerRunningState::PlayerRunningState(PlayerData* playerData)
{
    this->mPlayerData = playerData;

    acceleratorX = 5.0f;
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
                this->mPlayerData->player->AddVx(acceleratorX);

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
                this->mPlayerData->player->AddVx(-acceleratorX);

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
        if (this->mPlayerData->player->GetVx() > 0)
        {
            this->mPlayerData->player->SetVx(0);
        }

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
        noPressed = false;
    }
    else
    {
        noPressed = true;
    }

    GAMELOG("x: %f, y: %f", this->mPlayerData->player->GetPosition().x, this->mPlayerData->player->GetPosition().y);
}

PlayerState::StateName PlayerRunningState::GetState()
{
    return PlayerState::Running;
}

void PlayerRunningState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
    //lay phia va cham so voi player
    //GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
    if (impactor->Tag == Entity::EntityTypes::Ramp) return;
    switch (side)
    {
    case Entity::Left:
    {
        //va cham phia ben trai player
        if (this->mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
        {
            this->mPlayerData->player->allowMoveLeft = false;

            //day Player ra phia ben phai de cho player khong bi xuyen qua object
            this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);

            this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
        }

        return;
    }

    case Entity::Right:
    {
        //va cham phia ben phai player
        if (this->mPlayerData->player->getMoveDirection() == Player::MoveToRight)
        {
            this->mPlayerData->player->allowMoveRight = false;
            this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
            this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
        }
        return;
    }

    case Entity::Top:
        break;

    case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
    {
        this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

        this->mPlayerData->player->SetVy(0);

        return;
    }
    }
}

