#include "BotState.h"


void BotState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

BotState::BotState(BotData* playerData)
{
    this->mBotData = playerData;
}

BotState::BotState()
{

}

BotState::~BotState()
{
}

void BotState::Update(float dt)
{

}

void BotState::HandleKeyboard(std::map<int, bool> keys)
{

}