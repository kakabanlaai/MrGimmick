#include "Bot.h"
#include "BotStandingState.h"
#include "BotJumpingState.h"
#include "BotFallingState.h"
Bot::Bot()
{
    mAnimationStanding = new Animation("Resources/mario/standingright.png", 2, 1, 2, 0.8f);
    mAnimationJumping = new Animation("Resources/mario/jumpingright.png", 1, 1, 1, 0);
    mAnimationRunning = new Animation("Resources/mario/runningright.png", 6, 1, 6, 0.1f);

    this->mBotData = new BotData();
    this->mBotData->bot = this;
    this->vx = 0;
    this->vy = 0;
    this->SetState(new BotFallingState(this->mBotData));

    allowJump = true;
}

Bot::~Bot()
{
}

void Bot::Update(float dt)
{   
    mCurrentAnimation->Update(dt);

    if (this->mBotData->state)
    {
        this->mBotData->state->Update(dt);
    }

    Entity::Update(dt);
}

void Bot::HandleKeyboard(std::map<int, bool> keys)
{
    if (this->mBotData->state)
    {
        this->mBotData->state->HandleKeyboard(keys);
    }
}

void Bot::OnKeyPressed(int key)
{

}

void Bot::OnKeyUp(int key)
{
    if (key == VK_SPACE)
        allowJump = true;
}

void Bot::SetReverse(bool flag)
{
    mCurrentReverse = flag;
}

void Bot::SetAllowJump(bool _allowJump)
{
    this->allowJump = _allowJump;
}

void Bot::OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
    this->mBotData->state->OnCollision(impactor, side, data);
 }

BotData* Bot::getBotData()
{
    return this->mBotData;
}

void Bot::OnNoCollisionWithBottom()
{
    if (mCurrentState != BotState::Jumping && mCurrentState != BotState::Falling)
    {
        this->SetState(new BotFallingState(this->mBotData));
    }
}


void Bot::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
    mCurrentAnimation->FlipVertical(mCurrentReverse);
    mCurrentAnimation->SetPosition(mCamera->tranform(posX, posY));
    D3DXVECTOR2 tran = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
        mCamera->GetHeight() / 2 - mCamera->GetPosition().y);
    mCurrentAnimation->Draw();
    //mCurrentAnimation->Draw(, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Bot::SetState(BotState* newState)
{
    delete this->mBotData->state;

    this->mBotData->state = newState;

    this->changeAnimation(newState->GetState());

    mCurrentState = newState->GetState();
}

RECT Bot::GetBound()
{
    RECT rect;
    int temp = mCurrentAnimation->GetWidth();
    rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
    rect.right = rect.left + mCurrentAnimation->GetWidth();
    rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
    rect.bottom = rect.top + mCurrentAnimation->GetHeight();

    return rect;
}

void Bot::changeAnimation(BotState::StateName state)
{
    switch (state)
    {
    case BotState::Running:
        mCurrentAnimation = mAnimationRunning;
        break;

    case BotState::Standing:
        mCurrentAnimation = mAnimationStanding;
        break;

    case BotState::Falling:
        mCurrentAnimation = mAnimationJumping;
        break;

    case BotState::Jumping:
        mCurrentAnimation = mAnimationJumping;
        break;
    }

    this->width = mCurrentAnimation->GetWidth();
    this->height = mCurrentAnimation->GetHeight();
}

Bot::MoveDirection Bot::getMoveDirection()
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

BotState::StateName Bot::getState()
{
    return mCurrentState;
}

void Bot::setCamera(Camera* m) {
    Bot::mCamera = m;
}

