#include "MiniBossState.h"

void MiniBossState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

MiniBossState::MiniBossState(MiniBossData* miniBossData)
{
    this->mMiniBossData = miniBossData;
}

MiniBossState::MiniBossState()
{

}

MiniBossState::~MiniBossState()
{
}

void MiniBossState::Update(float dt)
{

}

