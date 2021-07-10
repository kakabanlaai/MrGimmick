#include "BotRunningState.h"
#include "BotStandingState.h"
#include "BotFallingState.h"
#include "BotJumpingState.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameComponents/GameLog.h"

BotRunningState::BotRunningState(BotData* botData)
{
    this->mBotData = botData;

    acceleratorX = 5.0f;
}


BotRunningState::~BotRunningState()
{
}

void BotRunningState::Update(float dt)
{
    if (noPressed)
    {
        if (mBotData->bot->getMoveDirection() == Bot::MoveToLeft)
        {
            //bot dang di chuyen sang ben trai      
            if (mBotData->bot->GetVx() < 0)
            {
                this->mBotData->bot->AddVx(acceleratorX);

                if (mBotData->bot->GetVx() >= 0)
                {
                    mBotData->bot->SetState(new BotStandingState(this->mBotData));
                    return;
                }
            }
        }
        else if (mBotData->bot->getMoveDirection() == Bot::MoveToRight)
        {
            //bot dang di chuyen sang phai   
            if (mBotData->bot->GetVx() > 0)
            {
                this->mBotData->bot->AddVx(-acceleratorX);

                if (mBotData->bot->GetVx() <= 0)
                {
                    mBotData->bot->SetState(new BotStandingState(this->mBotData));
                    return;
                }
            }
        }

        if (mBotData->bot->GetVx() == 0)
        {
            mBotData->bot->SetState(new BotStandingState(this->mBotData));
            return;
        }
    }
}

void BotRunningState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_SPACE] && this->mBotData->bot->GetAllowJump())
    {
        this->mBotData->bot->SetState(new BotJumpingState(this->mBotData));
        return;
    }

    if (keys[VK_RIGHT])
    {
        if (this->mBotData->bot->GetVx() < 0)
        {
            this->mBotData->bot->SetVx(0);
        }

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
        if (this->mBotData->bot->GetVx() > 0)
        {
            this->mBotData->bot->SetVx(0);
        }

        mBotData->bot->SetReverse(true);

        //di chuyen sang trai
        if (this->mBotData->bot->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
        {
            this->mBotData->bot->AddVx(-acceleratorX);

            if (this->mBotData->bot->GetVx() <= -Define::PLAYER_MAX_RUNNING_SPEED)
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

    GAMELOG("x: %f, y: %f", this->mBotData->bot->GetPosition().x, this->mBotData->bot->GetPosition().y);
}

BotState::StateName BotRunningState::GetState()
{
    return BotState::Running;
}

void BotRunningState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
    //lay phia va cham so voi bot
    //GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mBotData->bot, data);
    if (impactor->Tag == Entity::EntityTypes::Ramp) return;

    switch (side)
    {
    case Entity::Left:
    {
        //va cham phia ben trai bot
        if (this->mBotData->bot->getMoveDirection() == Bot::MoveToLeft)
        {
            this->mBotData->bot->allowMoveLeft = false;

            //day Bot ra phia ben phai de cho bot khong bi xuyen qua object
            this->mBotData->bot->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);

            this->mBotData->bot->SetState(new BotStandingState(this->mBotData));
        }

        return;
    }

    case Entity::Right:
    {
        //va cham phia ben phai bot
        if (this->mBotData->bot->getMoveDirection() == Bot::MoveToRight)
        {
            this->mBotData->bot->allowMoveRight = false;
            this->mBotData->bot->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
            this->mBotData->bot->SetState(new BotStandingState(this->mBotData));
        }
        return;
    }

    case Entity::Top:
        break;

    case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
    {
        this->mBotData->bot->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

        this->mBotData->bot->SetVy(0);

        return;
    }
    }
}

