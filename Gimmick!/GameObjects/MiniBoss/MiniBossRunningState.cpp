#include "MiniBossRunningState.h"
#include "../../GameDefines/GameDefine.h"
#include "../../GameComponents/GameLog.h"

MiniBossRunningState::MiniBossRunningState(MiniBossData* playerData)
{
    this->mMiniBossData = playerData;

    acceleratorX = 5.0f;
}


MiniBossRunningState::~MiniBossRunningState()
{
}

void MiniBossRunningState::Update(float dt)
{
}


MiniBossState::StateName MiniBossRunningState::GetState()
{
    return MiniBossState::Running;
}

void MiniBossRunningState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
    //lay phia va cham so voi player
    //GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
    if (impactor->Tag == Entity::EntityTypes::Ramp) return;

    switch (side)
    {
    case Entity::Left:
        break;
    case Entity::Right:
        break;
    case Entity::Top:
        break;
    case Entity::Bottom:
        break;
    case Entity::TopLeft:
        break;
    case Entity::TopRight:
        break;
    case Entity::BottomLeft:
        break;
    case Entity::BottomRight:
        break;
    case Entity::NotKnow:
        break;
    default:
        break;
    }
}

