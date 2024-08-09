#pragma once
#include <raylib.h>
#include <vector>
#include <math.h>

class Laser {

    public:
        Laser();
        Laser(Vector2 pPosition, Vector2 pDest, Vector2 pDest2, Rectangle pRectangle, int pSpeed, Color color);
        ~Laser();
        void Render();
        void Update();
        void Init(int pType, Vector2 pos, Vector2 dest, Vector2 dest2, int speed2, Color color2);
        void Projectile(Vector2 pPosition, int pSpeed, Color color);
        void SetPos(Vector2 pos);
        void Test2();
        Vector2 Dir();
        Vector2 pPos;
        float currentRange;

        typedef struct {
            Vector2 pPosition;
            Vector2 pDest;
            int pSpeed;
            int pCurrentRange;
            int pMaxRange;
            bool isAlive;
            Color pColor;
        } sLaser;

        float angle;

        std::vector<float> angles;

        // std::vector<Laser> lasers;
        std::vector<sLaser> lasers;

        std::vector<Vector2>positions;

        Vector2 Position;
        Vector2 pDest;
        Vector2 pDest2;

    private:

        int pSpeed;
        Texture2D pLaser;
        bool pAiming;
        Color pColor;
        float pMouseX;
        float pMouseY;
        float pDirectionX;
        float pDirectionY;

};