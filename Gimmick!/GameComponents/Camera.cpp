#include "Camera.h"


Camera::Camera(int width, int height)
{
    mWidth = width ;
    mHeight = height ;

    mPosition = D3DXVECTOR3(0, 0, 0);
}


Camera::~Camera()
{

}

D3DXVECTOR3  Camera::tranform(float x, float y) {
    D3DXMATRIX matrix;
    D3DXMatrixIdentity(&matrix);
    matrix._22 = -1;
    matrix._41 = -mPosition.x+this->mWidth/2;
    matrix._42 =  mPosition.y+this->mHeight/2;
    D3DXVECTOR3 Pos3(x, y,1);
    D3DXVECTOR4 Pos4;
      D3DXVec3Transform(&Pos4, &Pos3, &matrix);
      D3DXVECTOR3 result = D3DXVECTOR3(Pos4.x, Pos4.y,0.0);
      return result;

}

void Camera::SetPosition(float x, float y)
{
    SetPosition(D3DXVECTOR3(x, y, 0));
}

void Camera::SetPosition(D3DXVECTOR3 pos)
{
    mPosition = pos;
}

D3DXVECTOR3 Camera::GetPosition()
{
    return mPosition;
}

RECT Camera::GetBound()
{
    RECT bound; 

    bound.left = mPosition.x - mWidth / 2;
    bound.right = bound.left + mWidth;;
    bound.top = mPosition.y - mHeight / 2;
    bound.bottom = bound.top + mHeight;

    return bound;
}

int Camera::GetWidth()
{
    return mWidth;
}

int Camera::GetHeight()
{
    return mHeight;
}