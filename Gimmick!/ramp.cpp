#include "ramp.h"

ramp::ramp(D3DXVECTOR3 position)
{
    ramp::mainPoint = position;

}

ramp::~ramp()
{
}


const char* ramp::FileName()
{
    return "Resources/normalbrick.png";
}

int ramp::TotalFrame()
{
    return 1;
}

int ramp::Row()
{
    return 1;
}

int ramp::Column()
{
    return 1;
}

float ramp::SecondPerFrame()
{
    return 1.0f;
}
void ramp::setPolygon(int x, int y, int stt) {
    ramp::points[stt] = D3DXVECTOR3(x, y, 3);
    if (stt == 2)
        ramp::checkPolygon();



}
void ramp::OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side) {


    if (impactor->GetVy() > 0) return;
    
   
       
    // if (data.RegionCollision.right - data.RegionCollision.left < impactor->GetWidth() / 2) return;

    // float temp = temp = ramp::GetBound().top;

    //     if (ramp::side == ramp::sideramp::Right)
    //     {

    //          temp = ramp::GetBound().top + ramp::check(impactor->GetBound().right, impactor->GetPosition().y - impactor->GetHeight() / 2);
    //         this;
    //         if (temp > ramp::GetBound().bottom) temp = ramp::GetBound().bottom;



    //     }
    //     else {
    //          temp = ramp::GetBound().top + ramp::check(impactor->GetBound().left, impactor->GetBound().bottom);
    //         if (temp > ramp::GetBound().bottom)
    //             temp = ramp::GetBound().bottom;


    //     }
    //if ( data.RegionCollision.right-data.RegionCollision.left<ramp::GetWidth()/2 &&temp != ramp::GetBound().bottom)
    //{
    //    temp = ramp::GetBound().top;
    //}

    //     impactor->SetPosition(impactor->GetPosition().x, temp + impactor->GetHeight() / 2);
         //----------------------------------------------------------------------------------------------------------//

    
    
   
    float temp = ramp::GetBound().top;
    //if (impactor->GetVy() < 0 &&impactor->GetBound().bottom>) return;
    
    if (ramp::side == ramp::sideramp::Left)

    {
        switch (side)
        {
            if (data.RegionCollision.right - data.RegionCollision.left < impactor->GetWidth() / 2) 
                return;
        case Entity::Left:
        {

        }


        case Entity::TopRight: case Entity::Top:
        {     if (data.RegionCollision.right - data.RegionCollision.left < impactor->GetWidth() / 2) return;
        temp = ramp::GetBound().top + ramp::check(impactor->GetBound().left, impactor->GetPosition().y - impactor->GetHeight() / 2);
        if (impactor->GetBound().top < temp && impactor->GetVy() < 0) {
           /* impactor->SetVy(0);*/
            if (temp > ramp::GetBound().bottom)
                temp = ramp::GetBound().bottom;
            impactor->SetPosition(impactor->GetPosition().x, temp + impactor->GetHeight() / 2);

        }

        }
        case Entity::TopLeft:
        {

            temp = ramp::GetBound().top + ramp::check(impactor->GetBound().left, impactor->GetPosition().y - impactor->GetHeight() / 2);
          
            if (impactor->GetVy() < 0) {
               /* if (impactor->GetBound().top < temp)
                    impactor->SetVy(0);*/
                if (temp > ramp::GetBound().bottom)
                    temp = ramp::GetBound().bottom;
                impactor->SetPosition(impactor->GetPosition().x, temp + impactor->GetHeight() / 2);
            }
            if (impactor->GetVy() == 0) {

                if (temp > ramp::GetBound().bottom)
                    temp = ramp::GetBound().bottom;
                impactor->SetPosition(impactor->GetPosition().x, temp + impactor->GetHeight() / 2);


            }

        case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
        {

           // impactor->SetPosition(impactor->GetPosition().x, temp + impactor->GetHeight() / 2);
        }

        default:
            break;
        }
        case Entity::Right:
        {
            /*  if (data.RegionCollision.right - data.RegionCollision.left < impactor->GetWidth() / 2&& impactor->GetVx()<0) {
              }*/
            if (data.RegionCollision.right - data.RegionCollision.left < impactor->GetWidth() / 2 && impactor->GetVx() && impactor->GetVx() < 0) return;
            if (data.RegionCollision.right - data.RegionCollision.left < impactor->GetWidth() / 2 && impactor->GetVx() && impactor->GetVx() >0) {
                impactor->SetPosition(impactor->GetPosition().x, ramp::GetBound().top + impactor->GetHeight() / 2);
                return;
            }
            if (data.RegionCollision.right - data.RegionCollision.left > impactor->GetWidth() / 2) {
                if (ramp::check(impactor->GetBound().left, impactor->GetPosition().y - impactor->GetHeight() / 2) >= 0.0);
                temp = temp + ramp::check(impactor->GetBound().left, impactor->GetPosition().y - impactor->GetHeight() / 2);

                impactor->SetPosition(impactor->GetPosition().x, temp + impactor->GetHeight() / 2);
              /*  if (impactor->GetVy() < 0)
                    impactor->SetVy(0);*/

            }

        }

        }

    }


    if (ramp::side == ramp::sideramp::Right)

    {
        switch (side)
        {

        case Entity::Left:
        {
            if (data.RegionCollision.right - data.RegionCollision.left < impactor->GetWidth() / 2 && impactor->GetVx() && impactor->GetVx() > 0) return;
            if (data.RegionCollision.right - data.RegionCollision.left < impactor->GetWidth() / 2 && impactor->GetVx() && impactor->GetVx() < 0) {
                impactor->SetPosition(impactor->GetPosition().x, ramp::GetBound().top + impactor->GetHeight() / 2);
                return;
            }
            if (data.RegionCollision.right - data.RegionCollision.left > impactor->GetWidth() / 2) {
                if (ramp::check(impactor->GetBound().right, impactor->GetPosition().y - impactor->GetHeight() / 2) >= 0.0);
                temp = temp + ramp::check(impactor->GetBound().right, impactor->GetPosition().y - impactor->GetHeight() / 2);
                this;
                impactor->SetPosition(impactor->GetPosition().x, temp + impactor->GetHeight() / 2);
               /* if (impactor->GetVy() < 0)
                    impactor->SetVy(0);*/

            }

        }

        case Entity::Right:
        {
            //this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);

        }

        case Entity::TopLeft: case Entity::Top:
        {
            if (data.RegionCollision.right - data.RegionCollision.left < impactor->GetWidth() / 2) return;
            temp = ramp::GetBound().top + ramp::check(impactor->GetBound().right, impactor->GetPosition().y - impactor->GetHeight() / 2);
            if (impactor->GetBound().top < temp && impactor->GetVy() < 0) {
               /* impactor->SetVy(0);*/
                if (temp > ramp::GetBound().bottom)
                    temp = ramp::GetBound().bottom;
                impactor->SetPosition(impactor->GetPosition().x, temp + impactor->GetHeight() / 2);

            }

        }
        case Entity::TopRight:
        {
            temp = ramp::GetBound().top + ramp::check(impactor->GetBound().right, impactor->GetPosition().y - impactor->GetHeight() / 2);
            if (impactor->GetVy() < 0) {
                /*if (impactor->GetBound().top < temp)
                    impactor->SetVy(0);*/
                if (temp > ramp::GetBound().bottom)
                    temp = ramp::GetBound().bottom;
                impactor->SetPosition(impactor->GetPosition().x, temp + impactor->GetHeight() / 2);
            }
            if (impactor->GetVy() == 0) {

                if (temp > ramp::GetBound().bottom)
                    temp = ramp::GetBound().bottom;
                impactor->SetPosition(impactor->GetPosition().x, temp + impactor->GetHeight() / 2);

            }

      

        default:
            break;
        }

        }
    }
   


}
float ramp::check(float  x, float  y) {

    x = x - (ramp::GetBound().left);
    y = y - (ramp::GetBound().top);
    float temp = ramp::firstPoint.y + (x - ramp::firstPoint.x) * (ramp::firstPoint.y - ramp::secPoint.y) / (ramp::firstPoint.x - ramp::secPoint.x);
    temp = temp + mainPoint.y - ramp::GetBound().top;
    return temp;
}
void ramp::checkPolygon() {
    // if(ramp::points[0].x== ramp::points[1].x) mainPoint=
    if (ramp::points[0].x == ramp::points[1].x) ramp::firstPoint = ramp::points[2];
    else if (ramp::points[2].x == ramp::points[0].x) ramp::firstPoint = ramp::points[1];
    else firstPoint = ramp::points[0];
    for (auto item : ramp::points) {
        if (item.y != ramp::firstPoint.y) ramp::secPoint = item;

    }
    if (ramp::firstPoint.x > ramp::secPoint.x) ramp::side = ramp::sideramp::Left;
    else ramp::side = ramp::sideramp::Right;
    ramp::width = abs(ramp::secPoint.x - ramp::firstPoint.x);
    ramp::height = abs(ramp::secPoint.y - ramp::firstPoint.y);
    init(D3DXVECTOR3((ramp::secPoint.x + ramp::firstPoint.x + 2 * ramp::mainPoint.x) / 2, (ramp::secPoint.y + ramp::firstPoint.y + 2 * ramp::mainPoint.y) / 2, 0));



}