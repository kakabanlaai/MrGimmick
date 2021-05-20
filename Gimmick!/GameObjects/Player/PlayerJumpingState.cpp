#include "PlayerJumpingState.h"

using namespace Define;

PlayerJumpingState::PlayerJumpingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);

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
                this->mPlayerData->player->AddVx(PLAYER_DECREASE_JUMP_ACCELERATOR_X);

                if (mPlayerData->player->GetVx() > 0)
                    this->mPlayerData->player->SetVx(0);
            }
        }
        else if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
        {
            //player dang di chuyen sang phai   
            if (mPlayerData->player->GetVx() > 0)
            {
                this->mPlayerData->player->AddVx(-PLAYER_DECREASE_JUMP_ACCELERATOR_X);

                if (mPlayerData->player->GetVx() < 0)
                    this->mPlayerData->player->SetVx(0);
            }
        }
    }
}

void PlayerJumpingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_SPACE])
    {
        if (this->standingPosition.y - this->mPlayerData->player->GetPosition().y > 70)
        {
            mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
            return;
        }
    }
    else
    {
        mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
        return;
    }

    if (keys[VK_RIGHT])
    {
        mPlayerData->player->SetReverse(false);

        //di chuyen sang phai
        if (this->mPlayerData->player->GetVx() < PLAYER_MAX_RUNNING_SPEED)
        {
            this->mPlayerData->player->AddVx(PLAYER_JUMP_ACCELERATOR_X);

            if (this->mPlayerData->player->GetVx() >= PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(PLAYER_MAX_RUNNING_SPEED);
            }
        }

        noPressed = false;
    }
    else if (keys[VK_LEFT])
    {
        mPlayerData->player->SetReverse(true);

        //di chuyen sang trai
        if (this->mPlayerData->player->GetVx() > -PLAYER_MAX_RUNNING_SPEED)
        {
            this->mPlayerData->player->AddVx(-PLAYER_JUMP_ACCELERATOR_X);

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
        this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
        this->mPlayerData->player->SetVx(0);
        break;
    }

    case Entity::Right:
    {
        this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
        this->mPlayerData->player->SetVx(0);
        break;
    }

    case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
    {
        this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
        this->mPlayerData->player->SetVy(0);
        break;
    }

    case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
    {
        this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
    }

    default:
        break;
    }
}

