#include "DemoScene.h"

using namespace Define;

DemoScene::DemoScene()
{
    LoadContent();
}

void DemoScene::LoadContent()
{
    mBackColor = 0x000000;

    RECT srcRectBlackBoard;
    srcRectBlackBoard.left = 0;
    srcRectBlackBoard.right = BLACK_BOARD_WIDTH;
    srcRectBlackBoard.top = 64;
    srcRectBlackBoard.bottom = 64 + BLACK_BOARD_HEIGHT;

    mBlackBoard = new Sprite(PATH_BLACKBOARD);
    mBlackBoard->SetHeight(BLACK_BOARD_HEIGHT);
    mBlackBoard->SetWidth(BLACK_BOARD_WIDTH);
    mBlackBoard->SetSourceRect(srcRectBlackBoard);

    mBlackBoard->SetPosition(D3DXVECTOR2(BLACK_BOARD_WIDTH / 2, GAME_SCREEN_HEIGHT + BLACK_BOARD_HEIGHT / 2));

    mMap = new GameMap(PATH_MAP1_TMX);

    //mCamera = Camera::GetInstance(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
    Camera::GetInstance(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT)->SetPosition(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2);

    //mMap->SetCamera(mCamera);

    mPlayer = new Player();
    mPlayer->SetPosition(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2);

}

void DemoScene::Update(float dt)
{
    mPlayer->HandleKeyboard(keys);
    mPlayer->Update(dt);
    mMap->Update(dt);
}

void DemoScene::Draw()
{
    mMap->Draw();
    mBlackBoard->Draw();
    mPlayer->Draw();
}

void DemoScene::OnKeyDown(int keyCode)
{
    //if (keyCode == VK_LEFT)
    //{
    //    Camera::GetInstance(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT)->SetPosition(Camera::GetInstance(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT)->GetPosition() + D3DXVECTOR3(-32, 0, 0));
    //}

    //if (keyCode == VK_RIGHT)
    //{
    //    Camera::GetInstance(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT)->SetPosition(Camera::GetInstance(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT)->GetPosition() + D3DXVECTOR3(32, 0, 0));
    //}

    //if (keyCode == VK_UP)
    //{
    //    Camera::GetInstance(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT)->SetPosition(Camera::GetInstance(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT)->GetPosition() + D3DXVECTOR3(0, -32, 0));
    //}

    //if (keyCode == VK_DOWN)
    //{
    //    Camera::GetInstance(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT)->SetPosition(Camera::GetInstance(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT)->GetPosition() + D3DXVECTOR3(0, 32, 0));
    //}

    keys[keyCode] = true;
    mPlayer->OnKeyPressed(keyCode);
}

void DemoScene::OnKeyUp(int keyCode)
{
    keys[keyCode] = false;
    mPlayer->OnKeyUp(keyCode);
}

void DemoScene::OnMouseDown(float x, float y)
{
}
