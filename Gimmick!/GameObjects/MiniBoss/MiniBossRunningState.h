#pragma once
#include "MiniBossState.h"

class MiniBossRunningState : public MiniBossState
{
public:
	MiniBossRunningState(MiniBossData* miniBossData);
	~MiniBossRunningState();

	void Update(float dt);

	//void HandleKeyboard(std::map<int, bool> keys);

	void OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

protected:
	float acceleratorX;
	bool noPressed;

};

