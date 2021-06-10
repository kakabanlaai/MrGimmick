#include "Slider.h"
Slider::Slider()
{

}

Slider::~Slider() 
{

}

void Slider::OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side) 
{
    if (Slider::side == Slider::SideSiler::LeftToRight)
    {
        if (impactor->GetVx() > 0)
            impactor->AddVx(50.0f);
        else if (impactor->GetVx() < 0)
            impactor->AddVx(-50.0f);
        else impactor->SetVx(50.0f);
    }
    else if (Slider::side == Slider::SideSiler::RightToLeft)
    {
        if (impactor->GetVx() > 0)
            impactor->AddVx(-50.0f);
        else if (impactor->GetVx() < 0)
            impactor->AddVx(50.0f);
        else impactor->SetVx(-50.0f);
    }
}
