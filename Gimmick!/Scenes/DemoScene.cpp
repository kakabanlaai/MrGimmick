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

    mCamera = new Camera(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
   
    mPlayer = new Player();
    mPlayer->setCamera(mCamera);
    mPlayer->SetPosition(300, 1000-16);
    
    mCamera->SetPosition(mPlayer->GetPosition() );
   
    mMap->SetCamera(mCamera);

  

}

void DemoScene::Update(float dt)
{
    checkCollision();
    mMap->Update(dt);
    mPlayer->HandleKeyboard(keys);
    mPlayer->Update(dt);
   
    //mCamera->SetPosition(mPlayer->GetPosition());
   
   
    
   //CheckCameraAndWorldMap();
}

void DemoScene::Draw()
{
    mMap->Draw();
    mBlackBoard->Draw();
    mPlayer->Draw();
}

void DemoScene::OnKeyDown(int keyCode)
{
   /* if (keyCode == VK_LEFT)
    {
        mCamera->SetPosition(mCamera->GetPosition() + D3DXVECTOR3(-32, 0, 0));
    }

    if (keyCode == VK_RIGHT)
    {
        mCamera->SetPosition(mCamera->GetPosition() + D3DXVECTOR3(32, 0, 0));
    }

    if (keyCode == VK_UP)
    {
        mCamera->SetPosition(mCamera->GetPosition() + D3DXVECTOR3(0, -32, 0));
    }

    if (keyCode == VK_DOWN)
    {
        mCamera->SetPosition(mCamera->GetPosition() + D3DXVECTOR3(0, 32, 0));
    }*/

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

void DemoScene::CheckCameraAndWorldMap()
{
    float x = int(mPlayer->GetPosition().x);
    float y = int(mPlayer->GetPosition().y);
    float z = int(mPlayer->GetPosition().z);
    D3DXVECTOR3 temp = D3DXVECTOR3(x + x,y ,z + z);
    mCamera->SetPosition(temp);

    if (mCamera->GetBound().left < 0)
    {
        //vi position cua camera ma chinh giua camera
        //luc nay o vi tri goc ben trai cua the gioi thuc
        mCamera->SetPosition(mCamera->GetWidth() / 2, mCamera->GetPosition().y);
    }

    if (mCamera->GetBound().right > mMap->GetWidth())
    {
        //luc nay cham goc ben phai cua the gioi thuc
        mCamera->SetPosition(mMap->GetWidth() - mCamera->GetWidth() / 2,
            mCamera->GetPosition().y);
    }

    if (mCamera->GetBound().top < 0)
    {
        //luc nay cham goc tren the gioi thuc
        mCamera->SetPosition(mCamera->GetPosition().x, mCamera->GetHeight() / 2);
    }

    if (mCamera->GetBound().bottom > mMap->GetHeight())
    {
        //luc nay cham day cua the gioi thuc
        mCamera->SetPosition(mCamera->GetPosition().x,
            mMap->GetHeight() - mCamera->GetHeight() / 2);
    }
}

void DemoScene::checkCollision()
{
    /*su dung de kiem tra xem khi nao mario khong dung tren 1 object hoac
    dung qua sat mep trai hoac phai cua object do thi se chuyen state la falling*/
    int widthBottom = 0;

    vector<Entity*> listCollision; 

    mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, mPlayer);
    int x = mMap->GetQuadTree()->getID();

    for (size_t i = 0; i < listCollision.size(); i++)
    {
        Entity::CollisionReturn r = GameCollision::RecteAndRect(mPlayer->GetBound(),
            listCollision.at(i)->GetBound());

        if (r.IsCollided)
        {
            //lay phia va cham cua Entity so voi Player
            Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, r);

            //lay phia va cham cua Player so voi Entity
            Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollision.at(i), r);

            //goi den ham xu ly collision cua Player va Entity
            mPlayer->OnCollision(listCollision.at(i), r, sidePlayer);
            listCollision.at(i)->OnCollision(mPlayer, r, sideImpactor);

            //kiem tra neu va cham voi phia duoi cua Player 
            if (sidePlayer == Entity::Bottom || sidePlayer == Entity::BottomLeft
                || sidePlayer == Entity::BottomRight)
            {
                //kiem cha do dai ma mario tiep xuc phia duoi day
                int bot = r.RegionCollision.right - r.RegionCollision.left;

                if (bot > widthBottom)
                    widthBottom = bot;
            }
        }
    }

    //Neu mario dung ngoai mep thi luc nay cho mario rot xuong duoi dat    
    if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING)
    {
        //mPlayer->OnNoCollisionWithBottom();
    }
}
