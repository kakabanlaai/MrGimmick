#include "DynamicObject.h"
#include "../../GameComponents/GameGlobal.h"


DynamicObject::DynamicObject()
{
    
}

DynamicObject::~DynamicObject()
{

}

bool DynamicObject::init(D3DXVECTOR3 position)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());

    SetPosition(position);

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    return true;
}

void DynamicObject::OnSetPosition(D3DXVECTOR3 pos)
{
    mAnimation->SetPosition(pos);
}

void DynamicObject::Update(float dt)
{
    mAnimation->Update(dt);
}

void DynamicObject::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
    mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void DynamicObject::Draw(D3DXVECTOR2 transform)
{
    mAnimation->Draw(D3DXVECTOR2(transform));
}
