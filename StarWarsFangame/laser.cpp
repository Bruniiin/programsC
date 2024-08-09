#include <raylib.h>
#include <raymath.h>
#include "laser.hpp"
#include <math.h>
#include <iostream>

Laser::Laser()
{

    pLaser = LoadTexture("graphics/aim_p1.png");

}

Laser::Laser(Vector2 pPosition, Vector2 pDest, Vector2 pDest2, Rectangle rec, int pSpeed, Color pColor)
{

    // this->Position = pPosition;
    // this->pPos = pPosition;
    // this->pSpeed = pSpeed;
    this->pAiming = pAiming;
    // this->pColor = pColor;
    // this->pDest = pDest;
    this->pDest = pDest2;

    positions.push_back({pPosition.x, pPosition.y});


	// angle = atan2(pPosition.y, pPosition.x) * 180 / PI;
	// if (pPosition.y <= 0) angle += 360;

    // currentRange = 0;


}

Laser::~Laser() {



}

void Laser::Init(int pType, Vector2 pos, Vector2 dest, Vector2 dest2, int speed2, Color color2) {

    // switch(pType)
    // {
    //     case 0:
    //         lasers.push_back(Laser(pos, dest, dest2, (Rectangle){pos.x, pos.y, 50, 50}, 7, BLUE));
    //         // lasers2.push_back({pos, dest, speed2, color2}); 
    //         // positions.push_back({pPosition.x, pPosition.y});
    //     default:
    //     break;
    // }



}

void Laser::Render() {

    for (auto& lasers : lasers)
    {
        DrawTextureV(pLaser, lasers.pPosition, lasers.pColor);
    }

    // DrawRectangle
    // (pPosition.x, pPosition.y, 4, 15, BLUE);

    //for (int i = 0; i < positions.size(); i++)
    //{

    // for (auto& position : positions)
    // {
    //     DrawTextureV
    //     (pLaser, position, pColor);
    // }

}

// void Laser::SetPos(Vector2 pos) {

     //this->pPosition = pPosition;

// }

// void Laser::Test2()
// {

//     for(auto& laser: lasers) {
//         laser.Draw();
//     }

//     for(auto& laser: lasers) {
//         laser.Update();
//     }

// }

Vector2 Laser::Dir() {

    // Vector2 Dir = Vector2Subtract(GetMousePosition(), pPosition); // figure out the distance
    // Dir = Vector2Normalize(Dir);

    // Dir = Vector2Scale(Dir, pSpeed);
    // //pPosition = Vector2Add(pPosition, GetMousePosition());

}

void Laser::Update() {

    float dt = GetFrameTime();

    for(auto& lasers : lasers)
    {
        lasers.pPosition.x += lasers.pDest.x * lasers.pSpeed;
        lasers.pPosition.y -= lasers.pDest.y * lasers.pSpeed;

        lasers.pCurrentRange += 1.0f * dt;

        if(lasers.pCurrentRange >= lasers.pMaxRange)
        {
            lasers.isAlive = false;
        }
    }

    for(auto it = lasers.begin(); it != lasers.end(); )
    {
        if (!it->isAlive) {
        it = lasers.erase(it);
        }
        else {
            ++it;
        }
    }

    // Vector2 changeVector = Vector2Scale(pDest, GetFrameTime());
    // pPos = Vector2Add(pPos, changeVector);
    // currentRange += Vector2Length(changeVector);
    // for(auto& position : positions)
    // {
    //     position.x += pDest.x * pSpeed;
    //     position.y -= pDest.y * pSpeed;
    // }
	// pPosition.y *= -1;
	// angle = atan2(pPosition.y, pPosition.x) * 180 / PI;
	// if (pPosition.y <= 0) angle += 360;
    // Vector2 pPosition = Dir();
    // pPosition.y *= -1;
    // angle = atan2(pPosition.y, pPosition.x) * 180 / PI;
    // if (pPosition.y <= 0) angle += 360;
	// float angleSpread;
	// angleSpread = angle;
	// Vector2 direction = { cos(angleSpread * PI / 180), -sin(angleSpread * PI / 180) };
	// Vector2 pSpeed = Vector2Scale(pPosition, 7.f);

}


