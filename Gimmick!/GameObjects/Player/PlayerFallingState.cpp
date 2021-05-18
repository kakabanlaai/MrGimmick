#include "PlayerFallingState.h"
#include "PlayerStandingState.h"
#include "Player.h"
#include "../../GameDefines/GameDefine.h"

PlayerFallingState::PlayerFallingState(PlayerData* playerData)
{
    this->mPlayerData = playerData;
    acceleratorY = 15.0f;
    acceleratorX = 8.0f;

    if (this->mPlayerData->player->GetVx() == 0)
    {
        allowMoveX = false;
    }
    else
    {
        allowMoveX = true;
    }
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
}

void PlayerFallingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_RIGHT])
    {
        mPlayerData->player->SetReverse(false);

        isLeftOrRightKeyPressed = true;
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

        isLeftOrRightKeyPressed = true;
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

void PlayerFallingState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
    //lay phia va cham so voi player
    //GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);

    switch (side)
    {
    case Entity::Left:
        if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
        {
            this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
            this->mPlayerData->player->SetVx(0);
            this->mPlayerData->player->SetVy(10);
        }
        break;

    case Entity::Right:
        if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
        {
            this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
            this->mPlayerData->player->SetVx(0);
            this->mPlayerData->player->SetVy(10);
        }
        break;

    case Entity::Top:
        this->mPlayerData->player->SetVy(50);
        break;

    case Entity::Bottom:

    case Entity::BottomRight:
    case Entity::BottomLeft:
        this->mPlayerData->player->SetVy(0);
        if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
        {
            this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

            if (isLeftOrRightKeyPressed)
            {
                this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
            }
            else
            {
                this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
            }
        }
        return;

    default:
        this->mPlayerData->player->SetVy(10);
        break;
    }
}

PlayerState::StateName PlayerFallingState::GetState()
{
    return PlayerState::Falling;
}
