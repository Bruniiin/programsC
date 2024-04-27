#include <raylib.h>
#include <raymath.h>
#include "playermanager.hpp"

using namespace std;

PlayerManager::PlayerManager() {

//    blank = LoadTexture("graphics/blank.png");
//    blankpos.x = (GetScreenWidth() - blank.width)/2; blankpos.y = GetScreenHeight() - blank.height - 100;

// Scene scenePlayer;

player01.blank = LoadTexture("graphics/testsprite.png");
player01.blankSpeed = 2.0f;
player01.blankpos = (Vector2){GetScreenWidth() /5, GetScreenHeight() /2};
// player01.blank.width = {GetScreenWidth() /4, GetScreenHeight() /4};

player02.blank = LoadTexture("graphics/testsprite.png");
player02.blankSpeed = 2.0f;
player02.blankpos = (Vector2){GetScreenWidth() /2, GetScreenHeight() /2};


    playerSpeed = 5.0f;

///////////////

    cameraposp1 = { 0 };
    cameraposp1.target = (Vector2){ player01.blankpos.x, player01.blankpos.y};
    cameraposp1.offset = (Vector2){GetScreenWidth()/2, GetScreenHeight()/4};
//    cameraposp1.offset = (Vector2){GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    cameraposp1.rotation = 0.0f;
    cameraposp1.zoom = 0.4f;

    cameraposp2 = { 0 };
    cameraposp2.target = (Vector2) {player02.blankpos.x, player02.blankpos.y};
    cameraposp2.offset = (Vector2){GetScreenWidth()/2, GetScreenHeight()/4};
    cameraposp2.rotation = 0.0f;
    cameraposp2.zoom = 0.4f;

    CameraP1 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight()/2);
    CameraP2 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight()/2);  

    splitScreen = {0.0f, 0.0f, (float)CameraP1.texture.width, (float)-CameraP1.texture.height};

/////////////////////

    Map01 = LoadTexture("graphics/testmap.png");

}

PlayerManager::~PlayerManager() {


}

void PlayerManager::Draw() {

    DisableCursor();

    BeginTextureMode(CameraP1);

        ClearBackground(WHITE);
        BeginMode2D(cameraposp1);
        DrawText("TEST", 10, 10, 5, WHITE);

        RenderManager(); // método de renderização

//        DrawRectangle(0, GetScreenHeight() + 130, GetScreenWidth() * 4, 10, RED);   

        EndMode2D();
        EndTextureMode();

    BeginTextureMode(CameraP2);

        ClearBackground(WHITE);
        BeginMode2D(cameraposp2);  

        RenderManager();

        EndMode2D();
        EndTextureMode();



//        ClearBackground(WHITE);

        DrawTextureRec(CameraP1.texture, splitScreen, (Vector2){0, 0}, WHITE);
        DrawTextureRec(CameraP2.texture, splitScreen, (Vector2){0, GetScreenHeight()/2.0f}, WHITE);  

        BeginMode2D(cameraposp1);

//        DrawRectangle(0, GetScreenHeight() + 130, GetScreenWidth() * 4, 10, RED);   

        EndMode2D();

        // Splitscreen vertical

        // DrawTextureRec(CameraP1.texture, splitScreen, (Vector2){0, 0}, WHITE);
        // DrawTextureRec(CameraP1.texture, splitScreen, (Vector2){GetScreenWidth()/2.0f, 0}, WHITE);    

}

void PlayerManager::Update() {

  

    if(IsKeyDown(KEY_W))
    {
        player01.blankpos.y -= player01.blankSpeed * playerSpeed;
    }
    if(IsKeyDown(KEY_A))
    {
        player01.blankpos.x -= player01.blankSpeed * playerSpeed;
    }
    if(IsKeyDown(KEY_S))
    {
        player01.blankpos.y += player01.blankSpeed * playerSpeed;
    }
    if(IsKeyDown(KEY_D))
    {
        player01.blankpos.x += player01.blankSpeed * playerSpeed;
    }



    if(IsKeyDown(KEY_UP))
    {
        player02.blankpos.y -= player02.blankSpeed * playerSpeed;
    }
    if(IsKeyDown(KEY_LEFT))
    {
        player02.blankpos.x -= player02.blankSpeed * playerSpeed;
    }
    if(IsKeyDown(KEY_DOWN))
    {
        player02.blankpos.y += player02.blankSpeed * playerSpeed;
    }
    if(IsKeyDown(KEY_RIGHT))
    {
        player02.blankpos.x += player02.blankSpeed * playerSpeed;
    }

    cameraposp1.target = (Vector2){ player01.blankpos.x, player01.blankpos.y};
    cameraposp2.target = (Vector2){ player02.blankpos.x, player02.blankpos.y};

}

void PlayerManager::RenderManager() {

        DrawTexture(Map01, 0, 0, WHITE);
        DrawTextureV(player01.blank, player01.blankpos, WHITE);
        DrawTextureV(player02.blank, player02.blankpos, WHITE);

}