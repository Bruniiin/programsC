#define RAYGUI_IMPLEMENTATION
#include <raylib.h>
#include "frontend.hpp"
#include <iostream>
#include <raygui.h>

    using namespace std;

Frontend::Frontend() {

    CurrentTime = GetTime();

         OpeningScene = false;
         Mode2D = true;
         Mode3D = false;
         MenuMode = true;

        offset = 150.f;

    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    title = {screenWidth/2 - offset, screenHeight/2};

//    ModeSet = true;

    background = LoadTexture("graphics/backgroundmenu.png");
    
//    this->background = background;

    MainMenu = false;
    HasPressedTitle = false;
    alpha = 1.f;

}

Frontend::~Frontend() {

}

void Frontend::MainFrontend() {



    DrawTexture(background, 0, 0, WHITE);

    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, 50);                

    if (GuiButton((Rectangle){25, 255, 125, 30}, GuiIconText(ICON_BOX, "TESTBUTTON")));

    DrawFPS(10, 10);

    if(!MainMenu) // title
    {
    DrawTextEx(GetFontDefault(), Title2, title, 10.f, 5.f, Fade(WHITE, alpha));

    }

    if(IsKeyPressed(KEY_ENTER))
    {
        HasPressedTitle = true;
    }

    if(HasPressedTitle)
    {
        alpha -= 0.10f; //GetTime() / 50;
        
        if(alpha == 0.0f)
        {  
            MainMenu = true;
        }


    }

}

void Frontend::mFrontend() {

    float CurrentTime = GetTime();

    // if(!Mode3D && !Mode2D)
    // {
    //     Mode2D = true;
    // }

    if(OpeningScene) // && CurrentTime < 90.0f) 
    {
    scene.OpeningBegin();
    textUtils.Draw();
    scene.SceneDebug();
        if(CurrentTime > 90.0f)
        {
            OpeningScene = false;
            Mode3D = false;
        }
    }

    if(Mode2D)
    {
//        Mode2D = false;

        if (MenuMode)
        {
            MainFrontend();
        }
        if (!MenuMode)
        {
            game.GameBegin();
        }

    }

        // scene.~Scene();
        // textUtils.~Text3D();

}