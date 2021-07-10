#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../GameComponents/Animation.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameComponents/Camera.h"
#include "../Entity.h"
#include "MiniBossData.h"
#include "MiniBossState.h"
#include "../Player/Player.h"
//#include "PlayerRunningState.h"

class MiniBoss : public Entity
{
public:
    MiniBoss(Player *mPlayer, Camera *mCamera);
    ~MiniBoss();
    enum MoveDirection
    {
        MoveToLeft, //chay tu phai sang trai
        MoveToRight, //chay tu trai sang phai
        None //dung im
    };

    void Update(float dt);

    void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

    void SetState(MiniBossState* newState);

    MoveDirection getMoveDirection();

    RECT GetBound();

    MiniBossState::StateName getState();


    //true thi se lat nguoc anh theo truc y
    void SetReverse(bool flag);

    void SetAllowJump(bool _allowJump);
    bool GetAllowJump() { return allowJump; }
    bool allowMoveLeft;
    bool allowMoveRight;
    MiniBossData* getMiniBossData();

protected:
    MiniBossData* mMiniBossData;

    Animation* mCurrentAnimation,
        * mAnimationStanding,
        * mAnimationRunning,
        * mAnimationJumping,
        * mAnimationFlying;

    Camera* mCamera;
    void changeAnimation(MiniBossState::StateName state);

    MiniBossState::StateName mCurrentState;
    //chi cho phep jump khi nhan nhim space, muon nhay lai phai tha phim space roi nhan lai
    bool allowJump, 
        mCurrentReverse = true;

};