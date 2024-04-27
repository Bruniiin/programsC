#pragma once
#include <raylib.h>
#include "tilemapmanager.hpp"

class PlayerManager {

    public:
        PlayerManager();
        ~PlayerManager();
        void Draw();
        void Move();
        void Action();
        void Update();
        void RenderManager();
        Texture2D blank;
        Texture2D Map01;

        typedef struct {
            Vector2 blankpos;
            float blankSpeed;
            Texture2D blank;
        } Player0;
        Player0 player01;

        typedef struct {
            Vector2 blankpos;
            float blankSpeed;
            Texture2D blank;
        } Player1;
         Player1 player02;

    private:
        Vector2 p1pos;
        Vector2 p2pos;
//        Vector2 blankpos;
//        float blankspeed;
//        Texture2D blank;


        float playerSpeed;
        Camera2D cameraposp1;
        Camera2D cameraposp2;

        RenderTexture CameraP1;
        RenderTexture CameraP2;
        Rectangle splitScreen;
        TilemapManager tileManager;

};