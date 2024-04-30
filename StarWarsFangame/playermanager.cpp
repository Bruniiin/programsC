#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "playermanager.hpp"
#include <math.h>

    using namespace std;

PlayerManager::PlayerManager() {

//    blank = LoadTexture("graphics/blank.png");
//    blankpos.x = (GetScreenWidth() - blank.width)/2; blankpos.y = GetScreenHeight() - blank.height - 100;

// Scene scenePlayer;

// player01.player = LoadTexture("graphics/testsprite.png");
// player01.playerVelocity = 2.0f;
// player01.playerPos = (Vector2){GetScreenWidth() /5, GetScreenHeight() /2};
// player01.blank.width = {GetScreenWidth() /4, GetScreenHeight() /4};

// player02.player = LoadTexture("graphics/testsprite.png");
// player02.playerVelocity = 2.0f;
// player02.playerPos = (Vector2){GetScreenWidth() /2, GetScreenHeight() /2};

///////////////

    velocityModifier =  4.0f;

    mouse = LoadTexture("graphics/aim_p1.png");

    cameraposp1 = { 0 };
    cameraposp1.target = (Vector2){player01.playerPos.x, player01.playerPos.y};
    cameraposp1.offset = (Vector2){GetScreenWidth()/2, GetScreenHeight()/4};
//    cameraposp1.offset = (Vector2){GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    cameraposp1.rotation = 0.0f;
    cameraposp1.zoom = 0.4f;

    cameraposp2 = { 0 };
    cameraposp2.target = (Vector2) {player02.playerPos.x, player02.playerPos.y};
    cameraposp2.offset = (Vector2){GetScreenWidth()/2, GetScreenHeight()/4};
    cameraposp2.rotation = 0.0f;
    cameraposp2.zoom = 0.4f;

    CameraP1 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight()/2);
    CameraP2 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight()/2);
    CameraP1fullscr = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    splitscreen = {0.0f, 0.0f, (float)CameraP1.texture.width, (float)-CameraP1.texture.height};
    fullscr = {0.0f, 0.0f, (float)CameraP1fullscr.texture.width, (float)-CameraP1fullscr.texture.height};

    GameMode = false; // gamemode 0 = um jogador, gamemode 1 = dois jogadores.

    player01 = (Player)
    {
        .playerPos = (Vector2){GetScreenWidth() /4, GetScreenHeight() /2},
        .playerVelocity = 2.0f,
        .player = LoadTexture("graphics/testsprite.png"),
        .isAlive = true,
        .isHoldingWeapon = false,
        .isFiringWeapon = false,
        .isRunning = false,
        .Health = 100,
        .Experience = NULL, 
        .Level = 1,
        .laser = {0, 0},
        .Dir = {0, 0},
        .type = JEDI,
        .weapon = WPN_HANDS,
        .mode = ON_FOOT,
    };

    player02 = (Player)
    {
        .playerPos = (Vector2){GetScreenWidth() /2, GetScreenHeight() /2},
        .playerVelocity = 2.0f,
        .player = LoadTexture("graphics/testsprite.png"),
        .isAlive = true,
        .isHoldingWeapon = false,
        .isFiringWeapon = false,
        .isRunning = false,
        .Health = 100,
        .Experience = NULL, 
        .Level = 1,
        .laser = {0, 0},
        .Dir = {0, 0},
        .type = SITH,
        .weapon = WPN_HANDS,
        .mode = ON_FOOT,
    };

    pistol = (Weapon)
    {
        .weapon = LoadTexture("graphics/testsprite.png"),
        .isAlive = true,
        .isActive = false,
        .weapontype = WPN_PISTOL,
    };



/////////////////////

    Map01 = LoadTexture("graphics/testmap.png");

}

PlayerManager::~PlayerManager() {


}

void PlayerManager::Draw() {

//    DisableCursor();

    if(GameMode) { BeginTextureMode(CameraP1); }
//    else { BeginTextureMode(CameraP1fullscr); }

        ClearBackground(WHITE);
        BeginMode2D(cameraposp1);

    if(player01.isAlive)
    {
        RenderManager(); // método de renderização
        PlayerUpdate();
        InputUpdate();
    }

//        DrawRectangle(0, GetScreenHeight() + 130, GetScreenWidth() * 4, 10, RED);   

        EndMode2D();
        EndTextureMode();

    if(GameMode && player02.isAlive)
    {
        BeginTextureMode(CameraP2);

            ClearBackground(WHITE);
            BeginMode2D(cameraposp2);  

            RenderManager();
            PlayerUpdate();
            InputUpdate();


            EndMode2D();
            EndTextureMode();
    }


    cameraposp1.target = (Vector2){player01.playerPos.x, player01.playerPos.y};
    cameraposp2.target = (Vector2){player02.playerPos.x, player02.playerPos.y};

//        ClearBackground(WHITE);

        const char *WeaponChar[16] = { "WEAPON1", "WEAPON2", "WEAPON3", "WEAPON4" };

    if(!GameMode)
    {
        DrawTextureRec(CameraP1fullscr.texture, fullscr, (Vector2){0, 0}, WHITE);
        DrawText("HUD P1", 10, 10, 50, RED); // debug text
        DrawText(TextFormat("Health: %d", player01.Health), 10, 128, 30, RED);
        DrawText(TextFormat("Weapon: %s", WeaponChar[player01.weapon]), 10, 256, 30, RED);
    }

    if(GameMode)
    {
        DrawTextureRec(CameraP1.texture, splitscreen, (Vector2){0, 0}, WHITE);
        DrawTextureRec(CameraP2.texture, splitscreen, (Vector2){0, GetScreenHeight()/2.0f}, WHITE);  
        DrawText("HUD P2", 10, 10, 50, RED);        
        DrawText(TextFormat("Health: %d", player02.Health), 10, GetScreenHeight()/2 + 128, 30, RED);
        DrawText(TextFormat("Weapon: %s", WeaponChar[player02.weapon]), 10, 256, 30, RED);
    }
    
//        DrawText("HUD P2", 10, GetScreenHeight()/2 + 10, 50, RED);


//        BeginMode2D(cameraposp1);

//        DrawRectangle(0, GetScreenHeight() + 130, GetScreenWidth() * 4, 10, RED);   

//        EndMode2D();

        // DrawTextureRec(CameraP1.texture, splitScreen, (Vector2){0, 0}, WHITE);
        // DrawTextureRec(CameraP1.texture, splitScreen, (Vector2){GetScreenWidth()/2.0f, 0}, WHITE);

}




void PlayerManager::RenderManager() { // paint.net me ajudou com as coordenadas

        // cenário

        DrawTexture(Map01, 0, 0, WHITE);

        // instâncias

        DrawTextureV(pistol.weapon, (Vector2){10, -5}, WHITE); // cordenadas dos objetos são relativos ao mapa, que começa em 0, 0. // object coordinates are relative to the map which starts at 0,0.
        DrawTextureV(pistol.weapon, (Vector2){pow(2, 8), 0}, WHITE);

        // DrawTextureV(player01.player, player01.playerPos, WHITE);
        // DrawTextureV(player02.player, player02.playerPos, WHITE);


}




void PlayerManager::InputUpdate() {

    int Player02AxisX = GetGamepadAxisMovement(GamepadP2, GAMEPAD_AXIS_LEFT_X); //Não faço muita ideia como usa getgamepadaxismovement ainda /Still not much clue how to use getgamepadaxismovement.
    int Player02AxisY = GetGamepadAxisMovement(GamepadP2, GAMEPAD_AXIS_LEFT_Y);

if(player01.isAlive)
{
    if(IsKeyDown(KEY_W))
    {
        player01.playerPos.y -= player01.playerVelocity * velocityModifier;
    }
    if(IsKeyDown(KEY_A))
    {
        player01.playerPos.x -= player01.playerVelocity * velocityModifier;
    }
    if(IsKeyDown(KEY_S))
    {
        player01.playerPos.y += player01.playerVelocity * velocityModifier;
    }
    if(IsKeyDown(KEY_D))
    {
        player01.playerPos.x += player01.playerVelocity * velocityModifier;
    }

    player01.isFiringWeapon = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    player01.isAiming = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
    player01.isRunning = IsKeyDown(KEY_LEFT_SHIFT);

    // if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    // {
    //     player01.isFiringWeapon = true;
    // }
    // else player01.isFiringWeapon = false;

    // if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    // {
    //     player01.isAiming = true;
    // }
    // if(IsKeyPressed(KEY_E))
    // {
    // }


}




    if(IsGamepadAvailable && player02.isAlive)
    {
            if(IsGamepadButtonDown(GamepadP2, GAMEPAD_BUTTON_LEFT_FACE_UP))
            {
                player02.playerPos.y -= player02.playerVelocity * velocityModifier;
            }
            if(IsGamepadButtonDown(GamepadP2, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
            {
                player02.playerPos.x -= player02.playerVelocity * velocityModifier;
            }
            if(IsGamepadButtonDown(GamepadP2, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
            {
                player02.playerPos.y += player02.playerVelocity * velocityModifier;         
            }
            if(IsGamepadButtonDown(GamepadP2, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
            {
                player02.playerPos.x += player02.playerVelocity * velocityModifier;        
            }
            
            player02.isFiringWeapon = IsGamepadButtonDown(GamepadP2, GAMEPAD_BUTTON_RIGHT_TRIGGER_1);
            player02.isAiming = IsGamepadButtonDown(GamepadP2, GAMEPAD_BUTTON_LEFT_TRIGGER_2);
            player02.isRunning = IsGamepadButtonDown(GamepadP2, GAMEPAD_BUTTON_RIGHT_FACE_LEFT);

    }

        // player02.blankpos.x += Player1AxisX * playerSpeed;
        // player02.blankpos.y += Player1AxisY * playerSpeed;  

    




}



void PlayerManager::PlayerUpdate() { // não otimizado ainda, checa um player de cada vez. precisa de iteração para checar todos os players, que vi que é feito usando vectors. /not optimized.



    // if(player01.Health < 1) player01.isAlive = 0;

    // if(player02.Health < 1) player02.isAlive = 0;

    switch(player01.isAlive) // switch case obsoleto, vou substituir depois mas não precisa agora.
    {
        case true:
            DrawTextureV(player01.player, player01.playerPos, WHITE);
        break;
        case false:
        break;

    }

    switch(player02.isAlive)
    {
        case true:
            DrawTextureV(player02.player, player02.playerPos, WHITE);
        break;
        case false:
        break;

    }

}

    void PlayerManager::Action() {

        float mouseposP1_x = GetMouseX();
        float mouseposP1_y = GetMouseY();

        float playerDirP1_x = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
        float playerDirP1_y = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);
        float playerDirP2_x = GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_X);
        float playerDirP2_y = GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_X);

        if(player01.isFiringWeapon)
        {
            DrawText("CONDITION TRUE", 100, 100, 5, RED);
        }

        if(player01.isAiming)
        {
            DrawText("CONDITION TRUE", 100, 100, 5, RED);
            if(IsGamepadAvailable)
            {
                DrawTexture(mouse, playerDirP1_x, playerDirP1_y, WHITE);                
            }
            // else{
            //     DrawTexture(mouse, mouseposX, mouseposY, WHITE);
            // }
        }

        if(player01.isRunning)
        {
            DrawText("CONDITION TRUE", 100, 100, 5, RED);
            velocityModifier = 10.f;
        }
        if(!player01.isRunning)
        {
            velocityModifier =  4.0f;
        }



        if(player02.isFiringWeapon)
        {
            DrawText("CONDITION TRUE", 100, GetScreenHeight()/2 + 100, 5, RED);
        }

        if(player02.isAiming)
        {
            DrawText("CONDITION TRUE", 100, GetScreenHeight()/2 + 100, 5, RED);

            if(IsGamepadAvailable)
            {
                DrawTexture(mouse, playerDirP2_x, playerDirP2_y, WHITE);                
            }

        }

        if(player02.isRunning)
        {
            DrawText("CONDITION TRUE", 100, 100, 5, RED);
            velocityModifier = 10.f;
        }
        if(!player02.isRunning)
        {
            velocityModifier =  4.0f;
        }


    }