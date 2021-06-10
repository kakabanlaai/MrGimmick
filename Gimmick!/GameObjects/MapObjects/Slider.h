#pragma once
#include "Brick.h"
#include <math.h>

class Slider:public Brick
{
private:
	enum SideSiler
	{
		LeftToRight,
		RightToLeft
	};
	SideSiler side;
public:
	Slider();
	~Slider();

	virtual void OnCollision(Entity* impactor, CollisionReturn data, SideCollisions side);

};

