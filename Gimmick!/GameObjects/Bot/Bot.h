#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../GameComponents/Animation.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameComponents/Camera.h"
#include "../Entity.h"
#include "BotData.h"
#include "BotState.h"
#include "BotRunningState.h"
class Bot : public Entity
{
public:
    Bot();
    ~Bot();


    enum MoveDirection
    {
        MoveToLeft, //chay tu phai sang trai
        MoveToRight, //chay tu trai sang phai
        None //dung im
    };

    void Update(float dt);

    void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

    void SetState(BotState* newState);

    MoveDirection getMoveDirection();

    RECT GetBound();

    BotState::StateName getState();

    //xu ly input
    //gom 256 key tuong ung true = dang dc nhan, false = khong dc nhan
    void HandleKeyboard(std::map<int, bool> keys);

    void OnKeyPressed(int key);

    void OnKeyUp(int key);

    //true thi se lat nguoc anh theo truc y
    void SetReverse(bool flag);

    void SetAllowJump(bool _allowJump);
    bool GetAllowJump() { return allowJump; }
    void setCamera(Camera *m) ;
    bool allowMoveLeft;
    bool allowMoveRight;
    void OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
    BotData* getBotData();

    void OnNoCollisionWithBottom();
protected:
    BotData* mBotData;

    Animation* mCurrentAnimation,
        * mAnimationStanding,
        * mAnimationRunning,
        * mAnimationJumping;

    void changeAnimation(BotState::StateName state);

    BotState::StateName mCurrentState;
    Camera * mCamera;
    //chi cho phep jump khi nhan nhim space, muon nhay lai phai tha phim space roi nhan lai
    bool allowJump, mCurrentReverse;
    
};

