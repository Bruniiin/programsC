#include <raylib.h>
#include <iostream>
#include "scene.hpp"

 using namespace std;

int main() {

    cout << "Zero page address!" << endl;

//    Color darkGreen = Color{20, 160, 133, 255};

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "My raylib game!");
    SetTargetFPS(60);
    
    Scene scene;

    while (!WindowShouldClose())
    {    
        if (IsKeyDown(KEY_ENTER) && (KEY_LEFT_ALT))
            ToggleBorderlessWindowed();

        // ClearBackground(WHITE);
        BeginDrawing();
        scene.OpeningBegin();
        DrawText("sample text", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
