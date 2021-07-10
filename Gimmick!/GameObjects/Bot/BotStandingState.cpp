#include "BotStandingState.h"
#include "BotFallingState.h"
#include "BotJumpingState.h"
#include "Bot.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameComponents/GameLog.h"

BotStandingState::BotStandingState(BotData* botData)
{
    this->mBotData = botData;
    this->mBotData->bot->SetVx(0);
    this->mBotData->bot->SetVy(0);
}


BotStandingState::~BotStandingState()
{
}


void BotStandingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_SPACE] && this->mBotData->bot->GetAllowJump())
    {
        this->mBotData->bot->SetState(new BotJumpingState(this->mBotData));
        return;
    }
    if (keys[VK_LEFT] || keys[VK_RIGHT])
    {
        this->mBotData->bot->SetState(new BotRunningState(this->mBotData));
        return;
    }
}

BotState::StateName BotStandingState::GetState()
{
    return BotState::Standing;
}