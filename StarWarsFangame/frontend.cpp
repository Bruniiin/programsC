#define RAYGUI_IMPLEMENTATION
#include <raylib.h>
#include "frontend.hpp"
#include <iostream>
#include <raygui.h>

    using namespace std;

Frontend::Frontend() {



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
    logo = LoadTexture("graphics/logotransparent2size.png");
    
//    this->background = background;

    MainMenu = false;
    HasPressedTitle = false;
    alphaTitle = 1.f;
    alphaMenu = 0.f;

    IsSettings = false;

    settings.VideoSettings = false;

    StartGame = false;

    CurrentTime = GetTime();

    Time = 0.0f;

}

Frontend::~Frontend() {

}

void Frontend::MainFrontend() {

    int centerOffset = 70;
    int verticalOffset = 40;

    Rectangle logoRectangle = (Rectangle){0, 0, logo.width, logo.height};
    Vector2 logoCenter = {logo.width/2, logo.height/2};
    Vector2 position {screenWidth /2, screenHeight /3};

    DrawTexture(background, 0, 0, WHITE);
//    DrawTextureEx(logo, (Vector2){screenWidth/2 - centerOffset, 50.f}, 0.f, 0.5f, WHITE);
    DrawTexturePro(logo, logoRectangle, (Rectangle){float(position.x), float(position.y), float(logoRectangle.width), float(logoRectangle.height)}, logoCenter, 0, WHITE);

    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, 50);                

//    if (GuiButton((Rectangle){25, 255, 125, 30}, GuiIconText(ICON_BOX, "TESTBUTTON")));

//    DrawFPS(10, 10);

    if(IsKeyPressed(KEY_ENTER))
    {
        HasPressedTitle = true;
    }

    if(HasPressedTitle)
    {
        alphaTitle -= 0.10f; //GetTime() / 50;
        
        if(alphaTitle < 0.0f)
        {  
            MainMenu = true;
            alphaMenu += 0.10f;
        }
    }

//  DrawRectanglePro(rec, (Vector2){, 0}, 0, Fade(WHITE, 0.5f));
//  Rectangle rec = {screenWidth/2, screenHeight/2, 100, 40};

    switch(MainMenu) 
    {
        case true:
            if (GuiButton((Rectangle){960 - centerOffset, 600, 125, 30}, "Novo Jogo")) OpeningScene = true, Mode3D = true, Mode2D = false; //x, y, width, height
            if (GuiButton((Rectangle){960 - centerOffset, 650, 125, 30}, "Configurações")) IsSettings = !IsSettings;
            if (GuiButton((Rectangle){960 - centerOffset, 700, 125, 30}, "Fechar Jogo")) CloseWindow();
            
            if (IsSettings)
            {
                DrawRectangle(GetScreenWidth() /2 - 300, GetScreenHeight() /2 - 40, 200, 300, Fade(WHITE, 0.5f));

                if (GuiTextBox((Rectangle){800 - centerOffset, 500, 125, 30}, type.Config0, 64, textBoxEditMode)) settings.VideoSettings = !settings.VideoSettings;
                if (GuiTextBox((Rectangle){800 - centerOffset, 500 + 40, 125, 30}, type.Config1, 64, textBoxEditMode)) settings.AudioSettings = !settings.AudioSettings;
                if (GuiTextBox((Rectangle){800 - centerOffset, 500 + 80, 125, 30}, type.Config2, 64, textBoxEditMode)) settings.InputSettings = !settings.InputSettings;
                if (GuiTextBox((Rectangle){800 - centerOffset, 500 + 120, 125, 30}, type.Config3, 64, textBoxEditMode)) settings.AccessSettings = !settings.AccessSettings;

                // método settings

                Settings();
            }

        break;
        case false:
            DrawTextEx(GetFontDefault(), dialog.Title, title, 10.f, 5.f, Fade(WHITE, alphaTitle));
            DrawText("TITLE SCREEN ON", 50, 50, 5.f, WHITE);
        break;
    }

}

void Frontend::mFrontend() {



//    float CurrentTime = GetTime();

    // if(!Mode3D && !Mode2D)
    // {
    //     Mode2D = true;
    // }

//    if(!MenuMode)
//    {
        if(OpeningScene) // && CurrentTime < 90.0f) 
        {
//        OpeningScene = true;
        Time += 0.01f;
        scene.OpeningBegin();
        textUtils.Draw();
        scene.SceneDebug();
            if(Time > 60.0f) // 60 segundos.
            {
                StartGame = true;
            }
        }
//    }

    if(StartGame)
    {
        Mode2D = true;
        Mode3D = false;
        OpeningScene = false;
        MenuMode = false;
    }

    if(Mode2D)
    {
//        Mode2D = false;

        switch(MenuMode)
        {
            case true:
            MainFrontend();
            break;    
            case false:   
            game.GameBegin();
            // game.TilemapManager();
            break;
        }

    }

        // scene.~Scene();
        // textUtils.~Text3D();

}

void Frontend::Settings() {

    if(settings.VideoSettings)
    {


    }

    if(settings.AudioSettings)
    {


    }

    if(settings.InputSettings)
    {


    }

}