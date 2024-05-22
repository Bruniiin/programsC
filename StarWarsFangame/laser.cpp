#include <raylib.h>
#include <raymath.h>
#include "laser.hpp"
#include <math.h>
#include <iostream>

Laser::Laser()
{

}

Laser::Laser(Vector2 pPosition, Vector2 pDest, Vector2 pDest2, int pSpeed, Color pColor)
{

    this->pPosition = pPosition;
    // this->pPos = pPosition;
    this->pSpeed = pSpeed;
    this->pAiming = pAiming;
    this->pColor = pColor;
    this->pDest = pDest;
    this->pDest2 = pDest2;

    pLaser = LoadTexture("graphics/aim_p1.png");


	// angle = atan2(pPosition.y, pPosition.x) * 180 / PI;
	// if (pPosition.y <= 0) angle += 360;

    // currentRange = 0;


}

Laser::~Laser() {



}

void Laser::Init() {





}

void Laser::Draw() {

    // DrawRectangle
    // (pPosition.x, pPosition.y, 4, 15, BLUE);

    DrawTextureV
    (pLaser, pPosition, pColor);

}

void Laser::SetPos(Vector2 pos) {

    //this->pPosition = pPosition;

}

Vector2 Laser::Dir() {

    // Vector2 Dir = Vector2Subtract(GetMousePosition(), pPosition); // figure out the distance
    // Dir = Vector2Normalize(Dir);

    // Dir = Vector2Scale(Dir, pSpeed);
    // //pPosition = Vector2Add(pPosition, GetMousePosition());

}

void Laser::Update() {

        Vector2 changeVector = Vector2Scale(pDest, GetFrameTime());
        pPos = Vector2Add(pPos, changeVector);
        currentRange += Vector2Length(changeVector);
        
        pPosition.x += pDest2.x * pSpeed;
        pPosition.y -= pDest2.y * pSpeed;

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


