#include <raylib.h>
#include <iostream>
#include "scene.hpp"
#include "playermanager.hpp"
#include "text3d.hpp"
#include "cameram.hpp"
#include "frontend.hpp"
#include "laser.hpp"

 using namespace std;

 static void DrawTextCodepoint3D(Font font, int codepoint, Vector3 position, float fontSize, bool backface, Color tint);

 static void DrawText3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, Color tint);

 static Vector3 MeasureText3D(Font font, const char *text, float fontSize, float fontSpacing, float lineSpacing);



int main() {

//    cout << "Zero page address!" << endl;

//    Color TEST = Color{20, 160, 133, 255};

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    float MousePosX;
    float MousePosY;

    bool debugMode = false;

    InitWindow(GetScreenWidth(), GetScreenHeight(), "My raylib game!");
    InitAudioDevice();
    SetConfigFlags(FLAG_VSYNC_HINT);
//    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
    SetTargetFPS(120);

///////////////////

//    Camera3D camerat = { 0 };
//    camerat.position = (Vector3){10.f, 15.f, 10.f};
//    camerat.target = (Vector3){0.f, 0.f, 0.f};
//    camerat.up = (Vector3){0.0f, 1.0f, 2.0f};
//    camerat.fovy = 45.0f;
//    camerat.projection = CAMERA_PERSPECTIVE;

//    int camera_mode = CAMERA_ORBITAL;

//////////////////////////

//    float screenWidth;
//    float screenHeight;

    Scene scene;
    PlayerManager player;
//    CameraM camera;
    Text3D sceneUtils;
    Frontend frontend;

    // Laser laser = Laser({200, 200}, 7);


    


    bool CurrentTime = GetTime();

    while (!WindowShouldClose())
    {   

        if (IsKeyPressed(KEY_ENTER) && IsKeyDown(KEY_LEFT_ALT))
            ToggleBorderlessWindowed();

    MousePosX = GetMouseX();
    MousePosY = GetMouseY();


//        if (IsKeyPressed(KEY_F1))
//            debugMode = true;

        bool* pDebugMode = &debugMode;

        ClearBackground(WHITE);

//////////////////////////

        BeginDrawing();
        frontend.DefaultFrontend();

                // laser.Update();
                // laser.Draw();


    if(IsKeyDown(KEY_F2)) // visualização de coordenadas / coordinate viewer
    {
        DrawText(TextFormat("Position: %06.3f, %06.3f", MousePosX, MousePosY), 128, 128, 10, RED);
    }

    

//        camera.InitCamera();
//        scene.OpeningBegin(); // precisa de scene manager
//        scene.TextBegin();

//        sceneUtils.Draw();
        
//        player.Draw();
        // DrawText("sample text", 190, 200, 20, LIGHTGRAY);
//        camera.DeInitCamera();
        EndMode2D();

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}