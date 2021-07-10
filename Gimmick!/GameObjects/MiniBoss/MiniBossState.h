#pragma once
#include "MiniBossData.h"
#include "../Entity.h"
#include <map>

class MiniBossState
{
public:
    enum StateName
    {
        Standing,
        Running,
        Falling,
        Jumping,
        Flying,
        Die
    };
    ~MiniBossState();

    virtual void Update(float dt);

    //ham thuan ao bat buoc phai ke thua
    virtual StateName GetState() = 0;

    virtual void OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
protected:
    MiniBossState(MiniBossData* miniBossData);
    MiniBossState();

    MiniBossData* mMiniBossData;

};

