#pragma once
#include <raylib.h>
#include <vector>
#include <math.h>

class Laser {

    public:
        Laser();
        Laser(Vector2 pPosition, Vector2 pDest, Vector2 pDest2, int pSpeed, Color color);
        ~Laser();
        void Draw();
        void Update();
        void Init();
        void Projectile(Vector2 pPosition, int pSpeed, Color color);
        void SetPos(Vector2 pos);
        Vector2 Dir();
        Vector2 pPos;
        float currentRange;

        float angle;

        std::vector<float> angles;

        std::vector<Laser> lasers;


    private:
        Vector2 pPosition;
        Vector2 pDest;
        Vector2 pDest2;
        int pSpeed;
        Texture2D pLaser;
        bool pAiming;
        Color pColor;
        float pMouseX;
        float pMouseY;
        float pDirectionX;
        float pDirectionY;

};