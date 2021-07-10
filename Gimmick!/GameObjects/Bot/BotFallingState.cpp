#include "BotFallingState.h"
#include "BotStandingState.h"
#include "Bot.h"
#include "../../GameDefines/GameDefine.h"

BotFallingState::BotFallingState(BotData* botData)
{
	this->mBotData = botData;
	acceleratorY = -30.0f;
	acceleratorX = 2.5f;
}


BotFallingState::~BotFallingState()
{
}

void BotFallingState::Update(float dt)
{
	this->mBotData->bot->AddVy(acceleratorY);

	if (mBotData->bot->GetVy() < Define::PLAYER_MAX_JUMP_VELOCITY)
	{
		mBotData->bot->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	}
}

void BotFallingState::HandleKeyboard(std::map<int, bool> keys)
{

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
	}
	else if (keys[VK_LEFT])
	{
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
	}
	else
	{
		isLeftOrRightKeyPressed = false;
	}
}

BotState::StateName BotFallingState::GetState()
{
	return BotState::Falling;
}

void BotFallingState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{	


	if (impactor->Tag == Entity::EntityTypes::Ramp) {

		switch (side)
		{
		case Entity::Left:
			if (mBotData->bot->getMoveDirection() == Bot::MoveToLeft)
			{
				this->mBotData->bot->AddPosition((data.RegionCollision.right - data.RegionCollision.left), 0);
				this->mBotData->bot->SetVx(0);
			}
			break;

		case Entity::Right:
			if (mBotData->bot->getMoveDirection() == Bot::MoveToRight)
			{
				this->mBotData->bot->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				this->mBotData->bot->SetVx(0);
			}
			break;

		case Entity::Top:
		//	this->mBotData->bot->SetVy(0);
			break;

		case Entity::Bottom:
		case Entity::BottomRight:
		case Entity::BottomLeft:
			if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
			{
				this->mBotData->bot->AddPosition(0, (data.RegionCollision.bottom - data.RegionCollision.top - 5.0f));

				if (isLeftOrRightKeyPressed)
				{
					this->mBotData->bot->SetState(new BotRunningState(this->mBotData));
				}
				else
				{
					this->mBotData->bot->SetState(new BotStandingState(this->mBotData));
				}
			}
			return;

		default:
			break;
		}
	}
	
	
	

	if (impactor->Tag == Entity::EntityTypes::Static) {
		switch (side)
		{
		case Entity::Left:
			if (mBotData->bot->getMoveDirection() == Bot::MoveToLeft)
			{
				this->mBotData->bot->AddPosition((data.RegionCollision.right - data.RegionCollision.left), 0);
				this->mBotData->bot->SetVx(0);
			}
			break;

		case Entity::Right:
			if (mBotData->bot->getMoveDirection() == Bot::MoveToRight)
			{
				this->mBotData->bot->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				this->mBotData->bot->SetVx(0);
			}
			break;

		case Entity::Top:
			this->mBotData->bot->SetVy(0);
			break;

		case Entity::Bottom:
		case Entity::BottomRight:
		case Entity::BottomLeft:
			if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
			{
				this->mBotData->bot->AddPosition(0, (data.RegionCollision.bottom - data.RegionCollision.top - 5.0f));

				if (isLeftOrRightKeyPressed)
				{
					this->mBotData->bot->SetState(new BotRunningState(this->mBotData));
				}
				else
				{
					this->mBotData->bot->SetState(new BotStandingState(this->mBotData));
				}
			}
			return;

		default:
			break;
		}
	}
}


