#include "BotJumpingState.h"
#include "BotStandingState.h"
#include "BotFallingState.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameComponents/GameLog.h"

BotJumpingState::BotJumpingState(BotData* botData)
{
    this->mBotData = botData;
    this->mBotData->bot->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);

    acceleratorY = -3.0f;
    acceleratorX = 2.5f;

    noPressed = false;
    this->mBotData->bot->SetAllowJump(false);
    this->standingPosition = this->mBotData->bot->GetPosition();
}


BotJumpingState::~BotJumpingState()
{

}

void BotJumpingState::Update(float dt)
{
    if (noPressed)
    {
        if (mBotData->bot->getMoveDirection() == Bot::MoveToLeft)
        {
            //bot dang di chuyen sang ben trai      
            if (mBotData->bot->GetVx() < 0)
            {
                this->mBotData->bot->AddVx(acceleratorX);

                if (mBotData->bot->GetVx() > 0)
                    this->mBotData->bot->SetVx(0);
            }
        }
        else if (mBotData->bot->getMoveDirection() == Bot::MoveToRight)
        {
            //bot dang di chuyen sang phai   
            if (mBotData->bot->GetVx() > 0)
            {
                this->mBotData->bot->AddVx(-acceleratorX);

                if (mBotData->bot->GetVx() < 0)
                    this->mBotData->bot->SetVx(0);
            }
        }
    }
}

void BotJumpingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_SPACE] && this->allowJump)
    {
        if (this->mBotData->bot->GetPosition().y - this->standingPosition.y > 100)
        {
            mBotData->bot->SetState(new BotFallingState(this->mBotData));
            this->allowJump = false;
            return;
        }
    }
    else
    {
        mBotData->bot->SetState(new BotFallingState(this->mBotData)); 
        this->allowJump = true;
        return;
    }

    if (keys[VK_RIGHT])
    {
        mBotData->bot->SetReverse(false);

        //di chuyen sang phai
        if (this->mBotData->bot->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
        {
            this->mBotData->bot->AddVx(acceleratorX);

            if (this->mBotData->bot->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mBotData->bot->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }

        noPressed = false;
    }
    else if (keys[VK_LEFT])
    {
        mBotData->bot->SetReverse(true);

        //di chuyen sang trai
        if (this->mBotData->bot->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
        {
            this->mBotData->bot->AddVx(-acceleratorX);

            if (this->mBotData->bot->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mBotData->bot->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }

        noPressed = false;
    }
    else
    {
        noPressed = true;
    }
}

BotState::StateName BotJumpingState::GetState()
{
    return BotState::Jumping;
}


void BotJumpingState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
    if (impactor->Tag = Entity::EntityTypes::Ramp) return;
    switch (side)
    {
    case Entity::Left:
    {
        //this->mBotData->bot->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
        this->mBotData->bot->SetVx(0);
        break;
    }

    case Entity::Right:
    {
        //this->mBotData->bot->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
        this->mBotData->bot->SetVx(0);
        break;
    }

    case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
    {
        //this->mBotData->bot->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
        this->mBotData->bot->SetVy(-this->mBotData->bot->GetVy());
        break;
    }

    case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
    {
        this->mBotData->bot->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top -5.0f));
        
    }

    default:
        break;
    }
}

