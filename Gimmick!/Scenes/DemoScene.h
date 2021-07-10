#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>

#include "../GameComponents/Scene.h"
#include "../GameComponents/Sprite.h"
#include "../GameComponents/Animation.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameDefines/GameDefine.h"
#include "../GameObjects/Player/Player.h"
#include "../GameObjects/MiniBoss/MiniBoss.h"
#include "../GameObjects/Bot/Bot.h"

class DemoScene : public Scene
{
public:
    DemoScene();

    void Update(float dt);
    void LoadContent();
    void Draw();

    void OnKeyDown(int keyCode);
    void OnKeyUp(int keyCode);
    void OnMouseDown(float x, float y);
    void CheckCameraAndWorldMap();
    void checkCollision();
protected:
    GameMap* mMap;
    Camera* mCamera;
    Sprite* mBlackBoard;
    Player* mPlayer;
    Bot* mBot;
    //Bot** bot;
    MiniBoss* mMiniBoss;

    float mTimeCounter;

    std::map<int, bool> keys;
};

