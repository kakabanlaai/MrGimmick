#pragma once
#include "Brick.h"
#include <math.h>
class ramp : public Brick
{
private:
    enum sideramp
    {
        Left, //0
        Right, //1

    };
    sideramp side;
    D3DXVECTOR3 points[3];
    // float checkNum;

    void checkPolygon();
    D3DXVECTOR3 firstPoint;
    D3DXVECTOR3 secPoint;
    D3DXVECTOR3 mainPoint;
    //  float area(int af, int bf, int cf);

public:
    ~ramp();

    ramp(D3DXVECTOR3 position);
    float check(float xf, float yf);
    virtual const char* FileName();
    virtual int TotalFrame();
    virtual int Row();
    virtual int Column();
    virtual float SecondPerFrame();
    void setPolygon(int x, int y, int stt);
    virtual void OnCollision(Entity* impactor, CollisionReturn data, SideCollisions side);


};
