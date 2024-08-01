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

    defaultAim = LoadTexture("graphics/aim_p1.png");

    ObjectTexture = LoadTexture("graphics/aim_p1.png");    

    PlayerTexture = LoadTexture("graphics/testsprite.png");

    cameraPosFull = { 0 };
    cameraPosFull.target = (Vector2){P1.playerPos.x, P1.playerPos.y};
    cameraPosFull.offset = (Vector2){GetScreenWidth()/2, GetScreenHeight()/2};
    cameraPosFull.rotation = 0.0f;
    cameraPosFull.zoom = 0.4f;

    cameraposp1 = { 0 };
    cameraposp1.target = (Vector2){P1.playerPos.x, P1.playerPos.y};
    cameraposp1.offset = (Vector2){GetScreenWidth()/2, GetScreenHeight()/4};
//    cameraposp1.offset = (Vector2){GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    cameraposp1.rotation = 0.0f;
    cameraposp1.zoom = 0.4f;

    cameraposp2 = { 0 };
    cameraposp2.target = (Vector2) {P2.playerPos.x, P2.playerPos.y};
    cameraposp2.offset = (Vector2){GetScreenWidth()/2, GetScreenHeight()/4};
    cameraposp2.rotation = 0.0f;
    cameraposp2.zoom = 0.4f;

    CameraP1 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight()/2);
    CameraP2 = LoadRenderTexture(GetScreenWidth(), GetScreenHeight()/2);
    CameraP1fullscr = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    isGameDone = false;



    status = 1; // coroutine manager

    splitscreen = {0.0f, 0.0f, (float)CameraP1.texture.width, (float)-CameraP1.texture.height};
    fullscr = {0.0f, 0.0f, (float)CameraP1fullscr.texture.width, (float)-CameraP1fullscr.texture.height};

    GameMode = false; // gamemode 0 = um jogador, gamemode 1 = dois jogadores.

    // players.push_back({
    //                     0,            // player id
    //                     {0, 0},
    //                     150.f,
    //                     180.f,
    //                     LoadTexture("graphics/testsprite"),
    //                     {0, 0, 0, 0}, // source
    //                     {0, 0, 0, 0}, // dest
    //                     true,         // is alive?
    //                     false,        // is holding weapon?
    //                     false,        // is holding ranged?
    //                     false,        // has started firing?
    //                     false,        // is firing?
    //                     false,        // is aiming?
    //                     false,        // is running?
    //                     100,          // health
    //                     0,            // experience
    //                     1,            // level
    //                     0,            // location
    //                     0.f,          // altitude
    //                     0,            // is on vehicle?
    //                     {0, 0},       // direction
    //                     {0, 0},       // angle
    // });

    // players.push_back({
    //                     1,            // player id
    //                     {0, 0},
    //                     150.f,
    //                     180.f,
    //                     LoadTexture("graphics/testsprite"),
    //                     {0, 0, 0, 0}, // source
    //                     {0, 0, 0, 0}, // dest
    //                     true,         // is alive?
    //                     false,        // is holding weapon?
    //                     false,        // is holding ranged?
    //                     false,        // has started firing?
    //                     false,        // is firing?
    //                     false,        // is aiming?
    //                     false,        // is running?
    //                     100,          // health
    //                     0,            // experience
    //                     1,            // level
    //                     0,            // location
    //                     0.f,          // altitude
    //                     0,            // is on vehicle?
    //                     {0, 0},       // direction
    //                     {0, 0},       // angle
    // });

    P1 = (Player)
    {
        .playerPos = {0, 0},
        .playerVelocity = 150.0f,
        .velocityModifier = 180.0f,
        .player = LoadTexture("graphics/testsprite.png"),
        .collision = {P1.playerPos.x, P1.playerPos.y, PlayerTexture.width, PlayerTexture.height},
        .isAlive = true,
        .isHoldingWeapon = false,
        .isFiring = false,
        .isRunning = false,
        .Health = 100,
        .Experience = NULL, 
        .Level = 1,
        // .laser = {0, 0},
        .Dir = {0, 0},
        .state = IN_GAME,
        .weapon = WPN_PISTOL,
        .mode = ON_FOOT,
        .party = REBELLION,
    };

    P2 = (Player)
    {
        .playerPos = {200, 200},
        .playerVelocity = 150.0f,
        .velocityModifier = 180.0f,
        .player = LoadTexture("graphics/testsprite.png"),
        .isAlive = true,
        .isHoldingWeapon = false,
        .isFiring = false,
        .isRunning = false,
        .Health = 100,
        .Experience = NULL, 
        .Level = 1,
        // .laser = {0, 0},
        .Dir = {0, 0},
        .state = IN_GAME,
        .weapon = WPN_HANDS,
        .mode = ON_FOOT,
        .party = EMPIRE,
    };

    pistol = (Weapon)
    {
        .weapon = LoadTexture("graphics/testsprite.png"),
        .isAlive = true,
        .isActive = false,
        .isRanged = true,
        .weapontype = WPN_PISTOL,
    };

    // tilemap.hasRenderingBegan = true;

    FireSpeed = 0.5f;

    weaponPos = {(float)GetRandomValue(0, 256), (float)GetRandomValue(0, 256)};

    playerColl001 = {0, 0, 250, 213};
    pistolColl = {0, 0, (float)pistol.weapon.width, (float)pistol.weapon.height};



}

PlayerManager::~PlayerManager() {


}

void PlayerManager::Update() {

//    DisableCursor();



    if(GameMode) 
    { 
        BeginTextureMode(CameraP1);
        ClearBackground(WHITE);
        BeginMode2D(cameraposp1);
    }
    else 
    {
        BeginTextureMode(CameraP1fullscr);
        ClearBackground(WHITE);
        BeginMode2D (cameraPosFull);
    }



    if(P1.isAlive)
    {

//      tilemap.hasRenderingBegan = true;

        coroutine.ResetStatus(status);

            switch(coroutine.CoroutineStatus)
            {
            case 1:
                RenderManager(); // método de renderização de entidades / entity rendering method
                PlayerUpdate();
                InputUpdate();
                //status = 0;
            break;
            default: // returns to calling function if value is 0.
            return;
        }

    }
    
        EndMode2D();
        EndTextureMode();

    if((GameMode && P2.isAlive) || (GameMode && P1.isAlive))
    {

        BeginTextureMode(CameraP2);

        ClearBackground(WHITE);
        BeginMode2D(cameraposp2);  

        coroutine.ResetStatus(status);

            switch(coroutine.CoroutineStatus)
            {
            case 1:
                RenderManager();
                PlayerUpdate();
                InputUpdate();
                //status = 0;
            break;
            default: 
            return;
            }



        EndMode2D();
        EndTextureMode();
    }


    cameraposp1.target = (Vector2){P1.playerPos.x, P1.playerPos.y};
    cameraposp2.target = (Vector2){P2.playerPos.x, P2.playerPos.y};
    cameraPosFull.target = (Vector2){P1.playerPos.x, P1.playerPos.y};

//        ClearBackground(WHITE);

    const char* WeaponChar[8] = { "Unarmed", "WEAPON2", "WEAPON3", "WEAPON4", "WEAPON5", "WEAPON6", "WEAPON7", "WEAPON8" };

    if(!GameMode)
    {
        DrawTextureRec(CameraP1fullscr.texture, fullscr, (Vector2){0, 0}, WHITE);
        // DrawText("HUD P1", 10, 10, 50, RED); // debug text
        // DrawText(TextFormat("Health: %d", P1.Health), 10, 128, 30, RED);
        // DrawText(TextFormat("Equipment: %s", WeaponChar[P1.weapon]), 10, 256, 30, RED);
        // DrawText(TextFormat("COLL: %d %d", playerColl001.x, playerColl001.y), 150, 150, 50, RED); // debug
        //return;
    }
    if(GameMode)
    {
        DrawTextureRec(CameraP1.texture, splitscreen, (Vector2){0, 0}, WHITE);
        DrawTextureRec(CameraP2.texture, splitscreen, (Vector2){0, GetScreenHeight()/2.0f}, WHITE);  
        // DrawText("HUD P2", 10, GetScreenHeight()/2 + 10, 50, RED);        
        // DrawText(TextFormat("Health: %d", P2.Health), 10, GetScreenHeight()/2 + 128, 30, RED);
        // DrawText(TextFormat("Equipment: %s", WeaponChar[P2.weapon]), 10, 256, 30, RED);
    }

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {

        if(gotDefaultMousePosition == false)
        {
            defaultMousePosX = GetMouseX();
            defaultMousePosY = GetMouseY();
            gotDefaultMousePosition = true;
        }

        Vector2 defaultMousePosition = {defaultMousePosX, defaultMousePosY};

        //Vector2 MousePos = Vector2Subtract(MousePosTest2, MousePosTest2);
        // mouseOffset = Vector2AddValue(mouseOffset, GetMouse);

        if(GetMousePosition().x >= defaultMousePosition.x)
            DrawRectangleV(defaultMousePosition, Vector2Subtract(GetMousePosition(), defaultMousePosition), Fade(BLUE, 0.5f));
        //else if(GetMousePosition().x <= defaultMousePosition.x)
        //DrawRectangleV(defaultMousePosition, {Vector2Subtract({GetMousePosition().x, -GetMousePosition().y}, defaultMousePosition)}, RED);

    }
    else gotDefaultMousePosition = false;

// DrawTextureRec(CameraP1.texture, splitScreen, (Vector2){0, 0}, WHITE);
// DrawTextureRec(CameraP1.texture, splitScreen, (Vector2){GetScreenWidth()/2.0f, 0}, WHITE);

}

void PlayerManager::PlayerRender(int pId, Texture2D pPlayer, Vector2 pPlayerPos, Rectangle pSource, Rectangle pDestination, bool pIsAlive, int pHealth, int pExperience, int pLevel, int pMode, int pType, int pParty) {

    if(pIsAlive)
        // DrawTexturePro(pPlayer, (Rectangle){0, 0, float(pPlayer.width), float(pPlayer.height)}, (Rectangle){pPlayerPos.x, pPlayerPos.y, pPlayer.width, pPlayer.height}, (Vector2){float(pPlayer.width)/2, float(pPlayer.height)/2}, 0, WHITE);
        DrawTexturePro(pPlayer, pSource, pDestination, (Vector2){float(pPlayer.width/2), float(pPlayer.height/2)}, 0, WHITE);

    //DrawTexturePro
            //(P1.player, playerColl001 = {0, 0, (float)P1.player.width, (float)P1.player.height}, playerColl001Dest = {P1.playerPos.x, P1.playerPos.y, playerColl001.width, playerColl001.height}, (Vector2){P1.player.width/2, P1.player.height/2}, 0, WHITE);

}

void PlayerManager::Object(int pId2, int pTypeId, int pObject, Vector2 pObjectPos, bool pIsAlive2, bool pCollision) {

    objects.push_back({ObjectTexture, pObjectPos});

    // switch(pObject)
    // {
    //     case OBJ_VEH1:
    //         if(pIsAlive2)
    //             DrawTextureV(Objects[pObject], pObjectPos, RED);
    //     break;
    //     case OBJ_VEH2:
    //     break;
    // }

}

void PlayerManager::AsyncUpdate() {

    PlayerAction();

    // tilemap.currentLevelP1 = P1.Location;
    // tilemap.currentLevelP2 = P2.Location;

    // DrawRectangleRec(PlayerDest(), RED);

}

void PlayerManager::ObjectRender() {



}

Rectangle PlayerManager::PlayerDest()
{
    // return P1.destination;
    return {P1.playerPos.x, P1.playerPos.y, P1.player.width, P1.player.height};
    // return Rectangle();
}

void PlayerManager::RenderManager() { // paint.net me ajudou com as coordenadas

    // cenário

    // tilemap.Render();

    int pId; 

    // charactermanager.Update();

    Object(0, WPN_PISTOL, 0, (Vector2){120, 120}, 1, true);
    Object(1, WPN_PISTOL, 0, (Vector2){150, 150}, 1, true);

    // for (auto& object : objects)
    // {
    //     ObjectRender();
    // }

    //laser.Test2();






       // instâncias

        // cordenadas dos objetos são relativos ao mapa, que começa em 0, 0. // object coordinates are relative to the map which starts at 0,0.

        // DrawTextureV(pistol.weapon, (Vector2){10, -5}, WHITE); 
        // DrawTextureRec(pistol.weapon, pistolColl = {pistolColl.x = 100, pistolColl.y = 100, pistolColl.width = pistol.weapon.width, pistolColl.height = pistol.weapon.height}, (Vector2){100, 100}, WHITE);

        //DrawTexturePro
        //(pistol.weapon, pistolColl = {0, 0, (float)pistol.weapon.width, (float)pistol.weapon.height}, pistolCollDest = {pistol.weaponPos.x, pistol.weaponPos.y, pistolColl.width, pistolColl.height}, (Vector2){0, 0}, 0, WHITE);
    
        // DrawTextureRec(pistol.weapon, pistolColl, (Vector2){ 400, 400 }, WHITE);

        // void IsFiring();
        // {
        //     DrawRectangle
        //     (50, 50, 4*2, 15*2, BLUE);
        // }

}

void PlayerManager::InputUpdate() {

    int Player02AxisX = GetGamepadAxisMovement(GamepadP2, GAMEPAD_AXIS_LEFT_X); //Não faço muita ideia como usa getgamepadaxismovement ainda /Still not much clue how to use getgamepadaxismovement.
    int Player02AxisY = GetGamepadAxisMovement(GamepadP2, GAMEPAD_AXIS_LEFT_Y);

        mousePosX = GetMouseX();
        mousePosY = GetMouseY();

        P1dirX = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
        P1dirY = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);
        P2dirX = GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_X);
        P2dirY = GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_Y);

        P1GamepadDir = {P1dirX, P1dirY};
        P2GamepadDir = {P2dirX, P2dirY};

        mousePos = {(float)GetMouseX(), (float)GetMouseY()};



    if(P1.isAlive)
    {
        if(IsKeyDown(KEY_W))
        {
            P1.playerPos.y -= P1.playerVelocity * P1.velocityModifier * GetFrameTime();
            //P1.Angle = (Vector2){0, 1};
        }
        if(IsKeyDown(KEY_A))
        {
            P1.playerPos.x -= P1.playerVelocity * P1.velocityModifier * GetFrameTime();
            //P1.Angle = (Vector2){-1, 0};
        }
        if(IsKeyDown(KEY_S))
        {
            P1.playerPos.y += P1.playerVelocity * P1.velocityModifier * GetFrameTime();
            //P1.Angle = (Vector2){0, -1};
        }
        if(IsKeyDown(KEY_D))
        {
            P1.playerPos.x += P1.playerVelocity * P1.velocityModifier * GetFrameTime();
            //P1.Angle = (Vector2){1, 0};
        }

                Rectangle CenterVer = {GetScreenWidth()/2, GetScreenHeight()/2 - 200, 400, 400};
                Rectangle CenterHor = {GetScreenWidth()/2 - 400, GetScreenHeight()/2, 800, 400};
                Rectangle CenterVer2 = {0, GetScreenHeight()/2 - 200, 400, 400};
                Rectangle CenterHor2 = {GetScreenWidth()/2 - 400, 0, 800, 400};

                bool Coll001Angle = CheckCollisionPointRec(mousePos, CenterVer);
                bool Coll002Angle = CheckCollisionPointRec(mousePos, CenterHor);
                bool Coll003Angle = CheckCollisionPointRec(mousePos, CenterVer2);
                bool Coll004Angle = CheckCollisionPointRec(mousePos, CenterHor2);

                bool CollAngle[4] = {Coll001Angle, Coll002Angle, Coll003Angle, Coll004Angle};

                if(Coll001Angle) P1.Angle.x = 1; 
                else P1.Angle.x = 0;
                if(Coll002Angle) P1.Angle.y = -1; 
                else P1.Angle.y = 0;
                if(Coll003Angle) P1.Angle.x = -1;
                if(Coll004Angle) P1.Angle.y = 1; 

                // P1.Angle.x = (Coll001) ? 1 : 0;
                // P1.Angle.y = (Coll002) ? -1 : 0;
                // P1.Angle.x = (Coll003) ? -1 : 0;
                // P1.Angle.y = (Coll004) ? 1 : 0;

    P1.isFiring 
    = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    P1.isAiming 
    = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
    P1.isRunning 
    = IsKeyDown(KEY_LEFT_SHIFT);
    bool isCrouching = IsKeyPressed(KEY_LEFT_ALT);
    bool isProne = IsKeyPressed(KEY_LEFT_CONTROL);

    int ItemsArray[8];

    // ItemsArray[1] = IsKeyPressed(KEY_KP_1);
    // ItemsArray[2] = IsKeyPressed(KEY_KP_2);
    // ItemsArray[3] = IsKeyPressed(KEY_KP_3);
    // ItemsArray[4] = IsKeyPressed(KEY_KP_4);
    // ItemsArray[5] = IsKeyPressed(KEY_KP_5);
    // ItemsArray[6] = IsKeyPressed(KEY_KP_6);
    // ItemsArray[7] = IsKeyPressed(KEY_KP_7);
    // ItemsArray[8] = IsKeyPressed(KEY_KP_8);

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




    if(IsGamepadAvailable && P2.isAlive)
    {
            if(IsGamepadButtonDown(GamepadP2, GAMEPAD_BUTTON_LEFT_FACE_UP))
            {
                P2.playerPos.y -= P2.playerVelocity * P2.velocityModifier * GetFrameTime();
                P2.Angle = (Vector2){P2.Angle.x, 1};
            }
            if(IsGamepadButtonDown(GamepadP2, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
            {
                P2.playerPos.x -= P2.playerVelocity * P2.velocityModifier * GetFrameTime();
                P2.Angle = (Vector2){-1, P2.Angle.y};
            }
            if(IsGamepadButtonDown(GamepadP2, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
            {
                P2.playerPos.y += P2.playerVelocity * P2.velocityModifier * GetFrameTime();
                P2.Angle = (Vector2){P2.Angle.x, -1};
            }
            if(IsGamepadButtonDown(GamepadP2, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
            {
                P2.playerPos.x += P2.playerVelocity * P2.velocityModifier * GetFrameTime();
                P2.Angle = (Vector2){1, P2.Angle.y};
            }


            P2.isFiring 
            = IsGamepadButtonDown(GamepadP2, GAMEPAD_BUTTON_RIGHT_TRIGGER_1);
            P2.isAiming 
            = IsGamepadButtonDown(GamepadP2, GAMEPAD_BUTTON_LEFT_TRIGGER_2);
            P2.isRunning 
            = IsGamepadButtonDown(GamepadP2, GAMEPAD_BUTTON_RIGHT_FACE_LEFT);

    }

        // player02.blankpos.x += Player1AxisX * playerSpeed;
        // player02.blankpos.y += Player1AxisY * playerSpeed;  

    




}



void PlayerManager::PlayerUpdate() { // não otimizado ainda, checa um player de cada vez. precisa de iteração para checar todos os players, que vi que é feito usando vectors. /not optimized.



    if(P1.playerVelocity == 0)
    {
        P1.velocityModifier = 0.f;
    }
    if(P2.playerVelocity == 0)
    {
        P2.velocityModifier = 0.f;
    }

    if((P1.state == GAME_SET) || (P2.state == GAME_SET))
    {
        isGameDone = true;
        return;
    }

    if(P1.Health < 0)
    {
        P1.playerPos = {0, 0};
        if(P1.state == GAME_SET) 
            return;
        P1.playerVelocity = 0.f;
        P1.isAlive = false;
        P2.state = GAME_SET;
        if(P2.Health > 0)
            return;
    }

    if(P2.Health < 0)
    {
        P2.playerPos = {0, 0};
        if(P2.state == GAME_SET) 
            return;
        P2.isAlive = false;
        P1.state = GAME_SET;
        return;
    }

    P1.source = {0, 0, (float)P1.player.width, (float)P1.player.height};
    P1.destination = {P1.playerPos.x, P1.playerPos.y, (float)P1.player.width, (float)P1.player.height};
    P1.collision = {P1.playerPos.x, P1.playerPos.y, (float)PlayerTexture.width, (float)PlayerTexture.height};



}

void PlayerManager::Render() {


    if(!GameMode)
    {
        if(P1.isAlive)
        { // finalmente aprendi as colisões. fiquei quase 2 horas tentando advinhar as colisões e retângulos porque o mapa ficava sumindo, depois notei que o problema era o tilemap manager. Depois teve outro problema com colisão e e eu tinha botado o retângulo errado. // after 2 hours I finally learned how collisions work.
            PlayerRender(0, P1.player, P1.playerPos, P1.source, P1.destination, P1.isAlive, P1.Health, P1.Experience, P1.Level, P1.mode, P1.type, P1.party);

            //DrawTexturePro
            //(P1.player, playerColl001 = {0, 0, (float)P1.player.width, (float)P1.player.height}, playerColl001Dest = {P1.playerPos.x, P1.playerPos.y, playerColl001.width, playerColl001.height}, (Vector2){P1.player.width/2, P1.player.height/2}, 0, WHITE);
            //DrawTextureRec(P1.player, playerColl001, P1.playerPos, WHITE);
        } 
    }
    if(GameMode)
    {
        if(P1.isAlive)
        {
            PlayerRender(0, P1.player, P1.playerPos, P1.source, P1.destination, P1.isAlive, P1.Health, P1.Experience, P1.Level, P1.mode, P1.type, P1.party);
        }
        if(P2.isAlive)
        {
            PlayerRender(1, P2.player, P2.playerPos, P2.source, P2.destination, P2.isAlive, P2.Health, P2.Experience, P2.Level, P1.mode, P2.type, P2.party);
            //DrawTexturePro
            //(P2.player, playerColl002, playerColl002Dest = {P1.playerPos.x, P1.playerPos.y, playerColl001.width, playerColl001.height}, (Vector2){P2.player.width/2, P2.player.height/2}, 0, WHITE);
        }
    }

}




    // DrawTextureRec(P1.player, playerColl001, P1.playerPos, WHITE);

    // switch(player01.isAlive) // switch case obsoleto, vou substituir depois mas não precisa agora.
    // {
    //     case true:
    //         DrawTextureV(player01.player, player01.playerPos, WHITE);
    //     break;
    //     case false:
    //     break;

    // }

    // switch(player02.isAlive)
    // {
    //     case true:
    //         DrawTextureV(player02.player, player02.playerPos, WHITE);
    //     break;
    //     case false:
    //     break;

    // }


    void PlayerManager::PlayerAction() {



        P1.hasStartedFiring = P1.isFiring && P1.isAiming && FireDelay >= FireSpeed;
        P2.hasStartedFiring = P2.isFiring && P2.isAiming && FireDelay >= FireSpeed;

        if((P1.isFiring || P1.hasStartedFiring) || (P2.isFiring || P2.hasStartedFiring))
        {
            HandleShooting();
        }

        // if(P1.isFiring)
        // {
        //     P1.hasStartedFiring = P1.isAiming;
        //     // else
        //     // {
        //     //     // return;
        //     // } 
        // }

        if(P1.isAiming)
        {
            HideCursor();

            if(IsCursorHidden())
            {
                DrawTexturePro
                (defaultAim, (Rectangle){0, 0, 16, 16}, (Rectangle){mousePosX, mousePosY, 16, 16}, (Vector2){8, 8}, 0, GRAY);

                if(IsGamepadAvailable(GamepadP1))
                {
                    DrawTexturePro
                    (defaultAim, (Rectangle){0, 0, 16, 16}, (Rectangle){P1dirX, P1dirY, 16, 16}, (Vector2){8, 8}, 0, GRAY);
                }
            }
            // else{
            //     DrawTexture(mouse, mouseposX, mouseposY, WHITE);
            // }
        }

        if(IsCursorHidden())
            ShowCursor();

        // P1.Dir = 
        // {P1dirX, P1dirY};
        // P2.Dir = 
        // {P2dirX, P2dirY};

        if(P1.isRunning)
        {
            P1.velocityModifier = 10.f;
        }
        if(!P1.isRunning)
        {
            P1.velocityModifier = 4.0f;
        }

        if(P2.isAiming)
        {

            if(IsGamepadAvailable(GamepadP2))
            {
                    DrawTexturePro
                    (defaultAim, (Rectangle){0, 0, 16, 16}, (Rectangle){P2dirX, P2dirY, 16, 16}, (Vector2){8, 8}, 0, GRAY);  
            }

        }

        if(P2.isRunning)
        {
            P2.velocityModifier = 10.f;
        }
        if(!P2.isRunning)
        {
            P2.velocityModifier =  4.0f;
        }


}

    void PlayerManager::LoadCollision() {

    static int staticSize = 1 << 16;

    bool collisionsObject[staticSize] = {Coll001, Coll002, Coll003, Coll004};
    bool collisionsMove[staticSize] = {Coll006, Coll007, Coll008, Coll009};

    Coll001 = CheckCollisionRecs(playerColl001Dest, pistolColl); Coll002 = CheckCollisionRecs(playerColl002Dest, pistolColl);

    if(*collisionsObject) // otimizar em arrays/vectors é obrigatório nesse caso, ou terei que criar uma condição para cada objeto no mapa
    {
        DrawText("COLLISION CHECKED", 50, 50, 30, RED);
    }

}



    Vector2 PlayerManager::DirCalculate() {

        Vector2 Dir = Vector2Normalize(Vector2Subtract(GetMousePosition(), P1.playerPos));
        return Dir;

        // if(IsGamepadAvailable(GamepadP2))
        // {
        //     Vector2 Dir2 = Vector2Normalize(Vector2Subtract(P2GamepadDir, P2.playerPos));
        //     return Dir2;
        // }

}

    void PlayerManager::HandleShooting() { // credits to WaiLimChan for figuring out the math, a lot of this is copied from him/her!

        float dt = GetFrameTime();
        // FireDelay += 1.f * dt;
        // if(FireDelay > FireSpeed)
        // {
        //     FireDelay = FireSpeed;
        // }

            switch(P1.weapon)
            {
                case WPN_LIGHTSABER:
                case WPN_HANDS:
                    P1.isHoldingRangedWeapon = 0;
                break;
                case WPN_PISTOL:           
                case WPN_RIFLE:
                    P1.isHoldingRangedWeapon = 1;
                break;
                default:
                break;
            }

        if(P1.isFiring) // i wanted to try a nested if statement!
        {
            if(P1.isAiming)
            {
                if(P1.hasStartedFiring) 
                {
                    if(P1.isHoldingRangedWeapon)
                    {
                        // first it calculates the direction, then the angle from the direction, then the angle is added to the new direction product.

                        P1.Dir = DirCalculate();

                        P1.Dir.y *= -1;
                        angle = atan2(P1.Dir.y, P1.Dir.x) * 180 / PI;
                        if (P1.Dir.y <= 0) angle += 360;

                        float angleSpread;
                        if ((int) bulletSpread == 0) angleSpread = angle;
                        else angleSpread = angle + (rand() % (int)bulletSpread - bulletSpread / 2);

                        Vector2 Dir = { cos(angleSpread * PI / 180), -sin(angleSpread * PI / 180)};
                        laserDest = Vector2Scale(Dir, 64); // dir final product x 64 (velocity)
                        
                        laser.Init(0, P1.playerPos, {0}, laserDest, 7, BLUE);
                    }
                }
            }
        }
    
        // if(P1.isFiring) // && FireSpeed >= FireDelay && !P1.hasStartedFiring)
        // {       

        //     laserDest = {P1.Angle.x, P1.Angle.y};
        //     //lasers.push_back(Laser(P1.playerPos, {0}, laserDest, 7, BLUE));
        //     laser.lasers.push_back({P1.playerPos, laserDest, 7, BLUE});

        // }

        switch(P2.weapon)
        {
            case WPN_LIGHTSABER:
            case WPN_HANDS:
                P1.isHoldingRangedWeapon = 0;
            break;
            case WPN_PISTOL:           
            case WPN_RIFLE:
                P1.isHoldingRangedWeapon = 1;
            break;
            default:
            break;
        }

        if(P2.hasStartedFiring && P2.isHoldingRangedWeapon)
        {

            P2.Dir = DirCalculate();

        }
        
        if(P2.isFiring && !P2.hasStartedFiring)
        {

        }

}


