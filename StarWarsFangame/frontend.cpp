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
    settings.AudioSettings = false;
    settings.InputSettings = false;

    StartGame = false;

    CurrentTime = GetTime();

    Time = 0.0f;

    isOnVsync = true;
    isOnBorderless = true;
    isBorderlessChecked = true;

    resolutionSelected = 0;
    guiEditMode001 = false;
    guiEditMode002 = false;

    gotDefaultResolution = false;

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
            if (GuiButton((Rectangle){960 - centerOffset, 600, 125, 30}, option.Option0)) OpeningScene = true, Mode3D = true, Mode2D = false; //x, y, width, height
            if (GuiButton((Rectangle){960 - centerOffset, 650, 125, 30}, option.Option1)) IsSettings = !IsSettings;
            if (GuiButton((Rectangle){960 - centerOffset, 700, 125, 30}, option.Option2)) CloseWindow();
            
            if (IsSettings)
            {
                DrawRectangle(GetScreenWidth() /2 - 300, GetScreenHeight() /2 - 40, 200, 300, Fade(WHITE, 0.5f));

                if (GuiTextBox((Rectangle){800 - centerOffset, 500, 125, 30}, type.Type0, 64, textBoxEditMode)) settings.VideoSettings = !settings.VideoSettings;
                if (GuiTextBox((Rectangle){800 - centerOffset, 500 + 40, 125, 30}, type.Type1, 64, textBoxEditMode)) settings.AudioSettings = !settings.AudioSettings;
                if (GuiTextBox((Rectangle){800 - centerOffset, 500 + 80, 125, 30}, type.Type2, 64, textBoxEditMode)) settings.InputSettings = !settings.InputSettings;
                if (GuiTextBox((Rectangle){800 - centerOffset, 500 + 120, 125, 30}, type.Type3, 64, textBoxEditMode)) settings.AccessSettings = !settings.AccessSettings;

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
        DisableCursor();
        Time += 0.01f;
        scene.OpeningBegin();
        textUtils.Draw();
        scene.SceneDebug();

            if(Time > 0.0f) // 60 segundos.
            {
                StartGame = true;
                EnableCursor();
            }
        }
//    }

    if(StartGame)
    {
        Mode2D = true;
        Mode3D = false;
        OpeningScene = false;
        MenuMode = false;
        StartGame = false;
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

    int widthOffset = 2 << 8;

    char *resolution = {"Atual: %dx%d;1280x720;1366x768;1920x1080;2560x1440;3840x2160"}; //resoluções comuns/common resolutions
    char *framerate = {"Atual: %d FPS;60 FPS;120 FPS; 240 FPS"};

    DrawText(TextFormat("Resolution: %dx%d", GetScreenWidth(), GetScreenHeight()), 50, 50, 30, WHITE); //debug
    //    DrawText(TextFormat(resolution, GetScreenHeight()), 50, 100, 30, WHITE); //debug

    if(settings.VideoSettings)
    {
        if(guiEditMode001 || guiEditMode002) GuiLock();

        if(!gotDefaultResolution)
        {
        defaultResWidth = GetMonitorWidth(monitor);
        defaultResHeight = GetMonitorHeight(monitor);
        gotDefaultResolution = true;        
        }

        DrawText(TextFormat("WINDOW: %d", isOnBorderless), 10, 10, 30, WHITE); // debug
        DrawRectangle(widthOffset, GetScreenHeight() /3, 200, 300, Fade(WHITE, 0.5f));
        GuiCheckBox((Rectangle){widthOffset, GetScreenHeight()/3, 30, 30}, video.Video1, &isOnVsync);
        GuiCheckBox((Rectangle){widthOffset, GetScreenHeight()/3 + 40, 30, 30}, video.Video2, &isOnBorderless);     

        GuiUnlock();
        if (GuiDropdownBox((Rectangle){widthOffset, GetScreenHeight()/3 + 120, 120, 30}, TextFormat(resolution, GetScreenWidth(), GetScreenHeight()), &resolutionSelected, guiEditMode001)) guiEditMode001 = !guiEditMode001;
        if (GuiDropdownBox((Rectangle){widthOffset, GetScreenHeight()/3 + 80, 120, 30}, TextFormat(framerate, GetFPS()), &framerateSelected, guiEditMode002)) guiEditMode002 = !guiEditMode002;


        switch(resolutionSelected) // my solution to choosing multiple resolutions, not sure if its good or optimized but it works. // minha solução pra escolher as resoluções, pode estar mal otimizado.
        {
            case 0:
                SetWindowSize(GetScreenWidth(), GetScreenHeight());
            break;
            case 1:
                caseSet = false; if(caseSet == false) { resolutionSet = false; }
                SetWindowSize(1280, 720);
                    if(defaultResWidth < 1280 && defaultResHeight < 720) { if(!resolutionSet) { SetWindowSize(defaultResWidth, defaultResHeight); resolutionSet = true; } }
                caseSet = true;
            break;
            case 2:
                caseSet = false; if(caseSet == false) { resolutionSet = false; }
                SetWindowSize(1366, 768);
                    if(defaultResWidth < 1366 && defaultResHeight < 768) { if(!resolutionSet) { SetWindowSize(defaultResWidth, defaultResHeight); resolutionSet = true; } }
                caseSet = true;
            break;
            case 3:
                caseSet = false; if(caseSet == false) { resolutionSet = false; }
                SetWindowSize(1920, 1080);
                    if(defaultResWidth < 1920 && defaultResHeight < 1080) { if(!resolutionSet) { SetWindowSize(defaultResWidth, defaultResHeight); resolutionSet = true; } }
                caseSet = true;
            break;
            case 4:
                caseSet = false; if(caseSet == false) { resolutionSet = false; }
                SetWindowSize(2560, 1440);
                    if(defaultResWidth < 2560 && defaultResHeight < 1440) { if(!resolutionSet) { SetWindowSize(defaultResWidth, defaultResHeight); resolutionSet = true; } }
                caseSet = true;
            break;
            case 5:
                caseSet = false; if(caseSet == false) { resolutionSet = false; }
                SetWindowSize(3840, 2160);
                    if(defaultResWidth < 3840 && defaultResHeight < 2160) { if(!resolutionSet) { SetWindowSize(defaultResWidth, defaultResHeight); resolutionSet = true; } }
                 = true;
            break;
        }
    
        if(isOnBorderless && !isBorderlessChecked)
        {
            ToggleBorderlessWindowed();
            isBorderlessChecked = true;
        }
        if(!isOnBorderless && isBorderlessChecked)
        {
            ToggleBorderlessWindowed();
            isBorderlessChecked = false;
        }

        if(!isOnVsync) 
        {
            if(IsWindowState(FLAG_VSYNC_HINT)) ClearWindowState(FLAG_VSYNC_HINT);
        }
        else { SetWindowState(FLAG_VSYNC_HINT); }
    
    }

    if(settings.AudioSettings)
    {
        DrawRectangle(widthOffset, GetScreenHeight() /4, 200, 300, Fade(WHITE, 0.5f));

    }

    if(settings.InputSettings)
    {
        DrawRectangle(widthOffset, GetScreenHeight() /5, 200, 300, Fade(WHITE, 0.5f));

    }

    // if(isOnVsync)
    // {
    //     SetConfigFlags(FLAG_VSYNC_HINT);
    // }

    // else
    // {
    //     SetWindowState(FLAG_WINDOW_RESIZABLE);
    // }
}