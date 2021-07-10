#include "MiniBoss.h"
#include "MiniBossRunningState.h"


MiniBoss::MiniBoss(Player *mPlayer, Camera *mCamera) 
{
    mAnimationStanding = new Animation("Resources/mario/standingright.png", 2, 1, 2, 0.8f);
    mAnimationJumping = new Animation("Resources/mario/jumpingright.png", 1, 1, 1, 0);
    mAnimationRunning = new Animation("Resources/mario/runningright.png", 6, 1, 6, 0.1f);
    mAnimationFlying = new Animation("Resources/mario/runningright.png", 6, 1, 6, 0.1f);
    this->mMiniBossData = new MiniBossData();
    this->mMiniBossData->miniBoss = this;
    this->vx = -10;
    this->vy = 0;
    this->mCamera = mCamera;
    mCurrentAnimation = mAnimationRunning;
    this->SetPosition(mCamera->GetPosition().x + mCamera->GetWidth(), mCamera->GetPosition().y);
    this->allowJump = true;
    this->allowMoveLeft = true;
}

MiniBoss::~MiniBoss()
{

}

void MiniBoss::Update(float dt)
{
    mCurrentAnimation->Update(dt);

    if (this->mMiniBossData->state)
    {
        this->mMiniBossData->state->Update(dt);
    }

    Entity::Update(dt);
}

void MiniBoss::SetReverse(bool flag)
{
    mCurrentReverse = flag;
}

void MiniBoss::SetAllowJump(bool _allowJump)
{
    this->allowJump = _allowJump;
}

//void MiniBoss::OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
//{
//    this->mMiniBossData->state->OnCollision(impactor, side, data);
//}

MiniBossData* MiniBoss::getMiniBossData()
{
    return this->mMiniBossData;
}

//void MiniBoss::OnNoCollisionWithBottom()
//{
//    //if (mCurrentState != PlayerState::Jumping && mCurrentState != PlayerState::Falling)
//    //{
//    //    this->SetState(new PlayerFallingState(this->mPlayerData));
//    //}
//}

void MiniBoss::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
    mCurrentAnimation->FlipVertical(mCurrentReverse);
    mCurrentAnimation->SetPosition(mCamera->tranform(posX, posY));
    D3DXVECTOR2 tran = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
        mCamera->GetHeight() / 2 - mCamera->GetPosition().y);
    mCurrentAnimation->Draw();
    //mCurrentAnimation->Draw(, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void MiniBoss::SetState(MiniBossState* newState)
{
    delete this->mMiniBossData->state;

    this->mMiniBossData->state = newState;

    this->changeAnimation(newState->GetState());

    mCurrentState = newState->GetState();
}

RECT MiniBoss::GetBound()
{
    RECT rect;
    int temp = mCurrentAnimation->GetWidth();
    rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
    rect.right = rect.left + mCurrentAnimation->GetWidth();
    rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
    rect.bottom = rect.top + mCurrentAnimation->GetHeight();

    return rect;
}

void MiniBoss::changeAnimation(MiniBossState::StateName state)
{
    switch (state)
    {
    case MiniBossState::Running:
        mCurrentAnimation = mAnimationRunning;
        break;

    case MiniBossState::Standing:
        mCurrentAnimation = mAnimationStanding;
        break;

    case MiniBossState::Falling:
        mCurrentAnimation = mAnimationJumping;
        break;

    case MiniBossState::Jumping:
        mCurrentAnimation = mAnimationJumping;
        break;
    case MiniBossState::Flying:
        mCurrentAnimation = mAnimationFlying;
        break;
    }

    this->width = mCurrentAnimation->GetWidth();
    this->height = mCurrentAnimation->GetHeight();
}

MiniBoss::MoveDirection MiniBoss::getMoveDirection()
{
    if (this->vx > 0)
    {
        return MoveDirection::MoveToRight;
    }
    else if (this->vx < 0)
    {
        return MoveDirection::MoveToLeft;
    }

    return MoveDirection::None;
}

MiniBossState::StateName MiniBoss::getState()
{
    return mCurrentState;
}

