#define RAYGUI_IMPLEMENTATION
#include <raylib.h>
#include "frontend.hpp"
#include <iostream>
#include <raygui.h>
//#include <math.h>



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
    
    sEmpire = LoadTexture("graphics/Emblem_of_the_First_Galactic_Empire.png");
    sRebels = LoadTexture("graphics/Rebel_Alliance_logo.png");

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
    framerateSelected = 0;
    guiEditMode001 = false;
    guiEditMode002 = false;

    caseSet = false;
    resolutionSet = false;

    isCampaignSelected = 0;

    vDefaultResolution = false;

    Rec001 = {550, 350, 320, 320};
    Rec002 = {1050, 350, 320, 320};

    //game.Campaign = 0;

    SetMasterVolume(100);

    AudioVolume = 100.f;

    // SetMasterVolume(100.f);

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

    hasKeyBeenPressed = (GetKeyPressed()) 
    ? true 
    : false;
    hasKeyBeenPressed = (GetGamepadButtonPressed())
    ? false 
    : true;

    switch(MainMenu) 
    {
        case true:
            if (GuiButton((Rectangle){960 - centerOffset, 600, 125, 30}, option.Option0)) StartGame = !StartGame; //OpeningScene = true, Mode3D = true, Mode2D = false; //x, y, width, height
            if (GuiButton((Rectangle){960 - centerOffset, 650, 125, 30}, option.Option1)) IsSettings = !IsSettings;
            if (GuiButton((Rectangle){960 - centerOffset, 700, 125, 30}, option.Option2)) CloseWindow();
            DrawText("MAIN MENU SCREEN ON", 50, 50, 5.f, WHITE);            

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

    if(StartGame)
    {
        mouseCoordsX = GetMouseX();
        mouseCoordsY = GetMouseY();

        mousePos = {mouseCoordsX, mouseCoordsY};

        // DrawRectangle
        // (100 + 450, 100 + 250, 320, 320, Fade(WHITE, sAlpha));
        DrawRectangle
        (100, 100, GetScreenWidth() - 200, GetScreenHeight() - 200, BLACK);
        DrawRectangleRec
        (Rec001, Fade(WHITE, sAlpha));
        DrawRectangleRec
        (Rec002, Fade(WHITE, sAlpha));
        DrawText
        ("Escolha sua equipe:", GetScreenWidth()/2 - 128, GetScreenHeight()/2 + 256, 20, WHITE);
        DrawText
        ("Império", 800, 700, 20, WHITE);
        DrawText
        ("Rebeldes", 1000, 700, 20, WHITE);

        sAlpha = ((mouseCoordsX > Rec001.x && mouseCoordsX < Rec001.x + Rec001.width && mouseCoordsY > Rec001.y && mouseCoordsY < Rec001.y + Rec001.height) || (mouseCoordsX > Rec002.x && mouseCoordsX < Rec002.x + Rec002.width && mouseCoordsY > Rec002.y && mouseCoordsY < Rec002.y + Rec002.height)) 
        ? 0.5f 
        : 1.0f;

        DrawTextureRec
        (sEmpire, Rec001, (Vector2){Rec001.x, Rec001.y}, WHITE);
        DrawTextureRec
        (sRebels, Rec002, (Vector2){Rec002.x, Rec002.y}, WHITE);        

        Check001 = CheckCollisionPointRec(mousePos, Rec001);
        Check002 = CheckCollisionPointRec(mousePos, Rec002);



        if(Check001)
        { 
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
            {
                game.Empire.PLY = 0;
                isCampaignSelected = 1; // begin state machine!
            }
        }
        else if(Check002) // usando o famoso else if ;)
        {
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
            {
                game.Empire.PLY = 1;
                isCampaignSelected = 1;  
            }
        }

        switch(isCampaignSelected)
        {
            case 1:
                DrawRectangle
                (100, 100, GetScreenWidth() - 200, GetScreenHeight() - 200, BLACK);
                DrawText
                ("Quantidade de jogadores:", 840, 200, 20, WHITE);

                if(GuiButton((Rectangle){860, 500, 125, 125}, "1 Jogador")) game.Players = 1, isCampaignSelected = 2;
                if(GuiButton((Rectangle){985, 500, 125, 125}, "2 Jogador")) game.Players = 2, isCampaignSelected = 2;
                if(GuiButton((Rectangle){860, 500 + 125, 125, 125}, "3 Jogadores")) game.Players = 3, isCampaignSelected = 2;
                if(GuiButton((Rectangle){985, 500 + 125, 125, 125}, "4 Jogadores")) game.Players = 4, isCampaignSelected = 2;
            break;
            case 2:
                DrawRectangle
                (100, 100, GetScreenWidth() - 200, GetScreenHeight() - 200, BLACK);
                DrawText
                ("Escolha a campanha:", 840, 200, 20, WHITE);
                // DrawText
                // ();
                if(GuiButton((Rectangle){860, 500, 125, 30}, "Battle of Hoth")) game.Campaign = 1, isCampaignSelected = 3;
                if(GuiButton((Rectangle){860, 500 + 50, 125, 30}, "Battle of Yavin-4")) game.Campaign = 2, isCampaignSelected = 3;
                // if(GuiButton((Rectangle){860, 500 + 100, 125, 30}, "Battle of Bespin"));
            break;
            case 3:
                textUtils.Campaign = game.Campaign;
                DrawRectangle
                (100, 100, GetScreenWidth() - 200, GetScreenHeight() - 200, BLACK);
                if(IsGamepadAvailable(0) && hasKeyBeenPressed == false)
                {
                    DrawText
                    (TextFormat("Pressione %s para começar", ButtonStart), GetScreenWidth()/2, GetScreenHeight()/2, 20, WHITE);
                    if(IsGamepadButtonDown(0, GAMEPAD_BUTTON_MIDDLE_RIGHT))
                    {
                        Mode2D = false;
                        StartGame = false;
                        OpeningScene = true;
                    }
                }
                else
                {
                    DrawText
                    (TextFormat("Pressione %s para começar", KeyEnter), GetScreenWidth()/2, GetScreenHeight()/2, 20, WHITE);
                    if(IsKeyPressed(KEY_ENTER))
                    {
                        Mode2D = false;
                        StartGame = false;
                        OpeningScene = true;
                    }
                }
            break;
            default:
            break;
        };





        // if((mouseposx > 550 && mouseposx < 870) || (mouseposx > 1050 && mouseposx < 1370))
        // {
        //     sAlpha = 0.5f;
        // }
        // else
        // {
        //     sAlpha = 1.f;
        // }
        
    }

}

void Frontend::DefaultFrontend() {

//    float CurrentTime = GetTime();

    // if(!Mode3D && !Mode2D)
    // {
    //     Mode2D = true;
    // }

        if(OpeningScene) // && CurrentTime < 90.0f) 
        {
        // OpeningScene = true;
        // StartGame = false;
        // DisableCursor();
        Time += 0.01f;
        scene.OpeningBegin();
        textUtils.Draw();
        scene.SceneDebug();


            if((Time > 80.0f) || (scene.SceneSkipped == true)) // 80 segundos.
            {
                OpeningScene = false;
                MenuMode = false;
                Mode2D = true;

                // EnableCursor();
            }
        }
//    }

    if(Mode2D)
    {

        switch(MenuMode)
        {
            case true:
            MainFrontend();
            break;    
            case false:   
            game.GameRun();
            // game.TilemapManager();
            // MenuMode = (player.isGameDone) ? true : false;
            break;
        }

    }

        // scene.~Scene();
        // textUtils.~Text3D();

}

void Frontend::Settings() { 

    int widthOffset = 2 << 8;

    char* resolution = {"Atual: %dx%d;1280x720;1366x768;1920x1080;2560x1440;3840x2160"}; //resoluções comuns/common resolutions
    char* framerate = {"Atual: %d FPS;60 FPS;120 FPS; 144 FPS; 240 FPS"};

    DrawText(TextFormat("Resolution: %dx%d", GetScreenWidth(), GetScreenHeight()), 50, 50, 30, WHITE); //debug
    //    DrawText(TextFormat(resolution, GetScreenHeight()), 50, 100, 30, WHITE); //debug

    if(settings.VideoSettings)
    {
        if(guiEditMode001 || guiEditMode002) GuiLock();

        if(!vDefaultResolution)
        {
        defaultResWidth = GetMonitorWidth(monitor);
        defaultResHeight = GetMonitorHeight(monitor);
        vDefaultResolution = true;        
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
                caseSet = false;
            break;
            case 1:
                SetWindowSize(1280, 720);
                if(caseSet == false)
                {
                    if(defaultResWidth < 1280 && defaultResHeight < 720) 
                    { 
                        SetWindowSize(defaultResWidth, defaultResHeight); 
                        caseSet = true;
                    }
                }
                if(caseSet == true)
                {
                    resolutionSelected = 0;
                }
            break;
            case 2:
                SetWindowSize(1366, 768);
                if(caseSet == false)
                {
                    if(defaultResWidth < 1366 && defaultResHeight < 768) 
                    { 
                        SetWindowSize(defaultResWidth, defaultResHeight);
                        caseSet = true;
                    }
                }
                if(caseSet == true)
                {
                    resolutionSelected = 0;
                }
            break;
            case 3:
                SetWindowSize(1920, 1080);
                if(caseSet == false)
                {
                    if(defaultResWidth < 1920 && defaultResHeight < 1080) 
                    { 
                        SetWindowSize(defaultResWidth, defaultResHeight);
                        caseSet = true;
                    }
                }
                if(caseSet == true)
                {
                    resolutionSelected = 0;
                }
            break;
            case 4:
                SetWindowSize(2560, 1440);
                if(caseSet == false)
                {
                    if(defaultResWidth < 2560 && defaultResHeight < 1440) 
                    {
                        SetWindowSize(defaultResWidth, defaultResHeight); 
                        caseSet = true;
                    }
                }
                if(caseSet == true)
                {
                    resolutionSelected = 0;
                }
            break;
            case 5:
                SetWindowSize(3840, 2160);
                if(caseSet == false)
                {
                    if(defaultResWidth < 3840 && defaultResHeight < 2160) 
                    { 
                        SetWindowSize(defaultResWidth, defaultResHeight);
                        caseSet = true; 
                    }
                }
                if(caseSet == true)
                {
                    resolutionSelected = 0;
                }
            break;
        }
    
        switch(framerateSelected)
        {
            case 1:
                SetTargetFPS(60);
            break;
            case 2:
                SetTargetFPS(120);
            break;
            case 3:
                SetTargetFPS(144);
            break;
            case 4:
                SetTargetFPS(240);
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
        else 
        { 
            SetWindowState(FLAG_VSYNC_HINT);
        }
    
    }



    if(settings.AudioSettings)
    {
        SetMasterVolume
        (AudioVolume);
        DrawRectangle
        (widthOffset, GetScreenHeight() /4, 200, 300, Fade(WHITE, 0.5f));
        // GuiToggleSlider((Rectangle){512, 256, 120, 30}, "Áudio", &setAudioVolume);
        GuiSliderBar
        ((Rectangle){512, 256, 120, 30}, "Áudio Geral", TextFormat("%2.2f", &AudioVolume), &AudioVolume, 0, 100);
    }

    if(settings.InputSettings)
    {
        DrawRectangle
        (widthOffset, GetScreenHeight() /5, 200, 300, Fade(WHITE, 0.5f));
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