#pragma once
#ifndef __GAME_MAP__
#define __GAME_MAP__

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "Sprite.h"
#include "Animation.h"
#include "../MapReader/Tmx.h.in"
#include "GameGlobal.h"
#include "../GameComponents/Camera.h"
#include "../GameDefines/GameDefine.h"
<<<<<<< Updated upstream
=======
#include "../QuadTree.h"
#include "../Brick.h"
#include "../BrickNormal.h"
#include "../ramp.h"
>>>>>>> Stashed changes

class GameMap
{
public:
    GameMap(const char* filePath);

    Tmx::Map* GetMap();

    int GetWidth();
    int GetHeight();
    int GetTileWidth();
    int GetTileHeight();

    void LoadMap1Animation();
    void DrawAnimation(const Tmx::TileLayer *layer, D3DXVECTOR2 trans);

    void SetCamera(Camera *camera);

    void Update(float dt);

    void Draw();    

    ~GameMap();

private:
    void LoadMap(const char* filePath);

    bool isContain(RECT rect1, RECT rect2);

    Tmx::Map                        *mMap;
    std::map<int, Sprite*>          mListTileset;
    Camera *mCamera;
    std::map<int, Animation*> mListAnimation;
};

#endif

