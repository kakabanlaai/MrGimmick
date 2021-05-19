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
#include "../QuadTree.h"
#include "../Brick.h"
#include "../BrickNormal.h"


class GameMap
{
public:
    GameMap(const char* filePath);
    ~GameMap();
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
    bool IsBoundLeft(); //kiem tra luc nay Camera o vi bien ben trai so voi WorldMap
    bool IsBoundRight(); // kiem tra xem co o vi tri bien ben phai worldmap khong
    bool IsBoundTop(); // kiem tra xem co o vi tri bien ben trai worldmap khong
    bool IsBoundBottom(); // kiem tra xem co o vi tri bien ben phai worldmap khong
    QuadTree* GetQuadTree();

private:
    void LoadMap(const char* filePath);

    bool isContain(RECT rect1, RECT rect2);

    Tmx::Map                        *mMap;
    std::map<int, Sprite*>          mListTileset;
    Camera                          *mCamera;
    std::map<int, Animation*> mListAnimation;
    QuadTree* mQuadTree;
    std::vector<Brick*>             mListBricks;
    long mapHeight;
};

#endif

