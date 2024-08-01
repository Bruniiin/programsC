#define RAYGUI_IMPLEMENTATION
#include <raylib.h>
#include "frontend.hpp"
#include <iostream>
#include <raygui.hpp>
#include <math.h>

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

using namespace std;

Frontend::Frontend()
{

    OpeningScene = false;
    MenuMode = true;
    Mode2D = true;
    Mode3D = false;

    offset = 65.f;

    title = {(float)GetScreenWidth() / 2 - offset, (float)GetScreenHeight() / 2};

    Image Background001 = LoadImage("graphics/wallpaperalt.png");
    Image Background002 = LoadImage("graphics/HothAlt.png");
    Image Logo001 = LoadImage("graphics/star-wars-logo-png-transparent.png");
    Image Empire = LoadImage("graphics/Emblem_of_the_First_Galactic_Empire.png");
    Image Rebels = LoadImage("graphics/Rebel_Alliance_logo.png");

    ImageBlurGaussian(&Background001, 4);
    ImageBlurGaussian(&Background002, 8);
    ImageResize(&Logo001, 200, 200);
    ImageResize(&Empire, 320, 320);    

    Background = LoadTextureFromImage(Background001);
    BackgroundAlternate = LoadTextureFromImage(Background002);
    Logo = LoadTextureFromImage(Logo001);
    sEmpire = LoadTextureFromImage(Empire);
    sRebels = LoadTextureFromImage(Rebels);

    Font001 = LoadFontEx("utils/Franklin Gothic Book Regular.ttf", 40, NULL, 512);

    Font Font002 = LoadFontEx("utils/Franklin Gothic Book Regular.ttf", 10, NULL, 512);
    GuiSetFont(Font002);

    //screenWidth = GetScreenWidth();
    //screenHeight = GetScreenHeight();
    //    ModeSet = true;

    // Image *Background001 = &Background001;
    // background = LoadTexture("graphics/backgroundmenu.png");
    // logo = LoadTexture("graphics/logotransparent2size.png");
    // sEmpire = LoadTexture("graphics/Emblem_of_the_First_Galactic_Empire.png");
    // sRebels = LoadTexture("graphics/Rebel_Alliance_logo.png");

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

    StartState = 0;

    vDefaultResolution = false;

    Rec001 = {550, 350, 320, 320};
    Rec002 = {1050, 350, 320, 320};

    screenWidth = 1920;
    screenHeight = 1080;

    // game.Campaign = 0;

    SetMasterVolume(100);

    AudioVolume = 100.f;

    frontendScaler = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(frontendScaler.texture, TEXTURE_FILTER_BILINEAR);
    RenderRec = {0.0f, 0.0f, (float)frontendScaler.texture.width, (float)-frontendScaler.texture.height};

    Alpha001 = 1.0f;

    AwakeState = 0;

    // SetMasterVolume(100.f);
}

Frontend::~Frontend()
{

}

void Frontend::MainFrontend()
{
    // ClearBackground(BLACK);



    int centerOffset = 65;
    // int verticalOffset = 40;

    Rectangle logoRectangle = (Rectangle){0, 0, Logo.width, Logo.height};
    Vector2 logoCenter = {Logo.width / 2, Logo.height / 2};
    Vector2 position{screenWidth / 2, screenHeight / 3};

    DrawTexture(Background, 0, 0, WHITE);
    DrawTexture(BackgroundAlternate, 0, 0, Fade(WHITE, Alpha001));
    // DrawTextureEx(logo, (Vector2){screenWidth/2 - centerOffset, 50.f}, 0.f, 0.5f, WHITE);
    DrawTexturePro(Logo, logoRectangle, (Rectangle){float(position.x), float(position.y), float(logoRectangle.width), float(logoRectangle.height)}, logoCenter, 0, Fade(WHITE, alphaMenu));

    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, 50);

    //    if (GuiButton((Rectangle){25, 255, 125, 30}, GuiIconText(ICON_BOX, "TESTBUTTON")));

    //    DrawFPS(10, 10);

    if (IsKeyPressed(KEY_ENTER) && AwakeState == 1)
    {
        HasPressedTitle = true;
    }

    if (HasPressedTitle)
    {
        alphaTitle -= 1.f * GetFrameTime(); // GetTime() / 50;

        if (alphaTitle < 0.0f)
        {
            MainMenu = true;
            alphaMenu += 1.f * GetFrameTime();
        }
    }

    hasKeyBeenPressed = (GetKeyPressed())
                            ? true
                            : false;
    hasKeyBeenPressed = (GetGamepadButtonPressed())
                            ? false
                            : true;

    // if(GetKeyPressed)
    // {
    //     hasKeyBeenPressed = true;
    // }
    // if(GetGamepadButtonPressed)
    // {
    //     hasKeyBeenPressed = false;
    // }

    //  DrawRectanglePro(rec, (Vector2){, 0}, 0, Fade(WHITE, 0.5f));
    //  Rectangle rec = {screenWidth/2, screenHeight/2, 100, 40};

    switch (MainMenu)
    {
    case true:
        Alpha001 -= 1.5f * GetFrameTime();
        if (GuiButton((Rectangle){960 - centerOffset, 600, 130, 30}, Option0))
            StartGame = !StartGame; // OpeningScene = true, Mode3D = true, Mode2D = false; //x, y, width, height
        if (GuiButton((Rectangle){960 - centerOffset, 650, 130, 30}, Option1))
            IsSettings = !IsSettings;
        if (GuiButton((Rectangle){960 - centerOffset, 700, 130, 30}, Option2))
            CloseWindow();
        // DrawText("MAIN MENU SCREEN ON", 50, 50, 5.f, WHITE);

        if (IsSettings)
        {
            DrawRectangle(GetScreenWidth() / 2 - 300, GetScreenHeight() / 2 - 40, 200, 300, Fade(WHITE, 0.5f));

            if (GuiTextBox((Rectangle){960 - centerOffset, 500, 130, 30}, Type0, 64, textBoxEditMode))
                settings.VideoSettings = !settings.VideoSettings;
            if (GuiTextBox((Rectangle){960 - centerOffset, 500 + 40, 130, 30}, Type1, 64, textBoxEditMode))
                settings.AudioSettings = !settings.AudioSettings;
            if (GuiTextBox((Rectangle){960 - centerOffset, 500 + 80, 130, 30}, Type2, 64, textBoxEditMode))
                settings.InputSettings = !settings.InputSettings;
            if (GuiTextBox((Rectangle){960 - centerOffset, 500 + 120, 130, 30}, Type3, 64, textBoxEditMode))
                settings.AccessSettings = !settings.AccessSettings;

            // método settings

            Settings();
        }

        break;
    case false:
        switch (AwakeState)
            {
                case 0:
                    DrawRectangle(400, 400, GetScreenWidth() - 600, GetScreenHeight() - 600, Fade(WHITE, 0.6f));
                    DrawTextEx(Font001, "Select your language:", (Vector2){850, 450}, 40, 10, BLACK);
                    if (GuiButton((Rectangle){960 - centerOffset, 500, 130, 30}, "English"))
                    {
                        LanguageSelection = 0; 
                        AwakeState = 1;
                    }
                    if (GuiButton((Rectangle){960 - centerOffset, 500 + 40, 130, 30}, "Espanõl"))
                    {
                        LanguageSelection = 1; 
                        AwakeState = 1;
                    }
                    // if (GuiButton((Rectangle){800, 500, 125 + 80, 30}, "Português", 64, languageSelectionEditMode))
                    if (GuiButton((Rectangle){960 - centerOffset, 500 + 80, 130, 30}, "Português"))
                    {
                        LanguageSelection = 2; 
                        AwakeState = 1;
                    }             
                    break;
                case 1:
                    LoadTextData();

                    // DrawTextEx(Font001, dialogEng.Title, title, 10.f, 5.f, Fade(WHITE, alphaTitle));
                    // DrawText("TITLE SCREEN ON", 50, 50, 5.f, WHITE);
                    break;
            }
    }

    if (StartGame)
    {
        mouseCoordsX = GetMouseX();
        mouseCoordsY = GetMouseY();

        mousePos = {mouseCoordsX, mouseCoordsY};

        if(TestState)
        {
        // DrawRectangle
        // (100 + 450, 100 + 250, 320, 320, Fade(WHITE, sAlpha));
        DrawRectangle(100, 100, GetScreenWidth() - 200, GetScreenHeight() - 200, Fade(WHITE, 0.6f));
        DrawRectangleRec(Rec001, Fade(WHITE, sAlpha));
        DrawRectangleRec(Rec002, Fade(WHITE, sAlpha));
        DrawText(PartySelection, GetScreenWidth() / 2 - 128, GetScreenHeight() / 2 + 256, 20, WHITE);
        DrawText(Party0, 800, 700, 20, WHITE);
        DrawText(Party1, 1000, 700, 20, WHITE);

        sAlpha = ((mouseCoordsX > Rec001.x && mouseCoordsX < Rec001.x + Rec001.width && mouseCoordsY > Rec001.y && mouseCoordsY < Rec001.y + Rec001.height) || (mouseCoordsX > Rec002.x && mouseCoordsX < Rec002.x + Rec002.width && mouseCoordsY > Rec002.y && mouseCoordsY < Rec002.y + Rec002.height))
                     ? 0.5f
                     : 1.0f;

        DrawTexturePro(sEmpire, (Rectangle){0, 0, 320, 320}, (Rectangle){Rec001.x, Rec001.y, sEmpire.width, sEmpire.height}, {0}, 0, WHITE);
        DrawTextureRec(sRebels, (Rectangle){0, 0, 320, 320}, (Vector2){Rec002.x, Rec002.y}, WHITE);

        Check001 = CheckCollisionPointRec(mousePos, Rec001);
        Check002 = CheckCollisionPointRec(mousePos, Rec002);

        if (Check001)
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                game.Empire.PLY = 0;
                StartState = 1; // begin state machine!
                TestState = 0;
            }
        }
        else if (Check002)
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                game.Empire.PLY = 1;
                StartState = 1;
                TestState = 0;
            }
        }
        }

        switch (StartState)
        {
        case 1:
            DrawRectangle(100, 100, GetScreenWidth() - 200, GetScreenHeight() - 200, Fade(WHITE, 0.6f));
            DrawText(PlayerSelection, 840, 200, 20, WHITE);

            if (GuiButton((Rectangle){960 - 65, 500, 130, 130}, Players1))
                game.Players = 1, StartState = 2;
            if (GuiButton((Rectangle){960 - 65 + 130, 500, 130, 130}, Players2))
                game.Players = 2, StartState = 2;
            if (GuiButton((Rectangle){960 - 65, 500 + 130, 130, 130}, Players3))
                game.Players = 3, StartState = 2;
            if (GuiButton((Rectangle){960 - 65 + 130, 500 + 130, 130, 130}, Players4))
                game.Players = 4, StartState = 2;
            break;
        case 2:
            DrawRectangle(100, 100, GetScreenWidth() - 200, GetScreenHeight() - 200, Fade(WHITE, 0.6f));
            DrawText(GameSelection, 840, 200, 20, WHITE);
            // DrawText
            // ();
            if (GuiButton((Rectangle){960 - 65, 500, 130, 30}, Game_Hoth))
                game.Campaign = 1, StartState = 3;
            // if (GuiButton((Rectangle){960 - 65, 500 + 50, 130, 30}, "Battle of Yavin-4"))
            //     game.Campaign = 2, StartState = 3;
            if (GuiButton((Rectangle){960 - 65, 500 + 50, 130, 30}, Game_Sandbox))
                game.Campaign = 2, StartState = 3;
            // if(GuiButton((Rectangle){860, 500 + 100, 125, 30}, "Battle of Bespin"));
            break;
        case 3:
            textUtils.Campaign = game.Campaign;
            DrawRectangle(100, 100, GetScreenWidth() - 200, GetScreenHeight() - 200, Fade(WHITE, 0.6f));
            if (IsGamepadAvailable(0) && hasKeyBeenPressed == false)
            {
                DrawText(TextFormat(PressToStart, ButtonStart), GetScreenWidth() / 2, GetScreenHeight() / 2, 20, WHITE);
                if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_MIDDLE_RIGHT))
                {
                    Mode2D = false;
                    StartGame = false;
                    OpeningScene = true;
                }
            }
            else
            {
                DrawText(TextFormat("Pressione %s para começar", KeyEnter), GetScreenWidth() / 2, GetScreenHeight() / 2, 20, WHITE);
                if (IsKeyPressed(KEY_ENTER))
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

void Frontend::DefaultFrontend()
{

    if(MenuMode && GetScreenWidth() != screenWidth && GetScreenHeight() != screenHeight)
    {
        BeginTextureMode(frontendScaler);
        ClearBackground(WHITE);
    }

    float scale = MIN((float)GetScreenWidth()/screenWidth, (float)GetScreenHeight()/screenHeight);

    if (OpeningScene) // && CurrentTime < 90.0f)
    {
        // OpeningScene = true;
        // StartGame = false;
        // DisableCursor();
        Time += 1.f * GetFrameTime();

        scene.OpeningBegin();
        textUtils.Draw();
        scene.SceneDebug();

        if ((Time > 106.0f) || (scene.SceneSkipped == true))
        {
            OpeningScene = false;
            MenuMode = false;
            Mode2D = true;

            // EnableCursor();
        }
    }

    if (Mode2D)
    {

        switch (MenuMode)
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

    ui.Update();

    if(MenuMode && GetScreenWidth() != screenWidth && GetScreenHeight() != screenHeight)
    {
        EndTextureMode();
        DrawTexturePro(frontendScaler.texture, (Rectangle){ 0.0f, 0.0f, (float)frontendScaler.texture.width, (float)-frontendScaler.texture.height },
                                    (Rectangle){ (GetScreenWidth() - ((float)screenWidth*scale))*0.5f, (GetScreenHeight() - ((float)screenHeight*scale))*0.5f,
                                    (float)screenWidth*scale, (float)screenHeight*scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);
    }

    // scene.~Scene();
    // textUtils.~Text3D();
}

void Frontend::Settings()
{

    int widthOffset = 2 << 8;

    char *resolution = {"Atual: %dx%d;1280x720;1366x768;1920x1080;2560x1440;3840x2160"};
    char *framerate = {"Atual: %d FPS;60 FPS;120 FPS; 144 FPS; 240 FPS"};

    DrawText(TextFormat("Resolution: %dx%d", GetScreenWidth(), GetScreenHeight()), 50, 50, 30, WHITE); // debug
    //    DrawText(TextFormat(resolution, GetScreenHeight()), 50, 100, 30, WHITE); //debug

    if (settings.VideoSettings)
    {
        if (guiEditMode001 || guiEditMode002)
            GuiLock();

        if (!vDefaultResolution)
        {
            defaultResWidth = GetMonitorWidth(monitor);
            defaultResHeight = GetMonitorHeight(monitor);
            vDefaultResolution = true;
        }

        DrawText(TextFormat("WINDOW: %d", isOnBorderless), 10, 10, 30, WHITE); // debug
        DrawRectangle(widthOffset, GetScreenHeight() / 3, 200, 300, Fade(WHITE, 0.5f));
        GuiCheckBox((Rectangle){widthOffset, GetScreenHeight() / 3, 30, 30}, Video1, &isOnVsync);
        GuiCheckBox((Rectangle){widthOffset, GetScreenHeight() / 3 + 40, 30, 30}, Video2, &isOnBorderless);

        GuiUnlock();
        if (GuiDropdownBox((Rectangle){widthOffset, GetScreenHeight() / 3 + 120, 120, 30}, TextFormat(resolution, GetScreenWidth(), GetScreenHeight()), &resolutionSelected, guiEditMode001))
            guiEditMode001 = !guiEditMode001;
        if (GuiDropdownBox((Rectangle){widthOffset, GetScreenHeight() / 3 + 80, 120, 30}, TextFormat(framerate, GetFPS()), &framerateSelected, guiEditMode002))
            guiEditMode002 = !guiEditMode002;

        switch (resolutionSelected) // my solution to choosing multiple resolutions, not sure if its good or optimized but it works. // minha solução pra escolher as resoluções, pode estar mal otimizado.
        {
        case 0:
            SetWindowSize(GetScreenWidth(), GetScreenHeight());
            caseSet = false;
            break;
        case 1:
            SetWindowSize(1280, 720);
            if (caseSet == false)
            {
                if (defaultResWidth < 1280 && defaultResHeight < 720)
                {
                    SetWindowSize(defaultResWidth, defaultResHeight);
                    caseSet = true;
                }
            }
            if (caseSet == true)
            {
                resolutionSelected = 0;
            }
            break;
        case 2:
            SetWindowSize(1366, 768);
            if (caseSet == false)
            {
                if (defaultResWidth < 1366 && defaultResHeight < 768)
                {
                    SetWindowSize(defaultResWidth, defaultResHeight);
                    caseSet = true;
                }
            }
            if (caseSet == true)
            {
                resolutionSelected = 0;
            }
            break;
        case 3:
            SetWindowSize(1920, 1080);
            if (caseSet == false)
            {
                if (defaultResWidth < 1920 && defaultResHeight < 1080)
                {
                    SetWindowSize(defaultResWidth, defaultResHeight);
                    caseSet = true;
                }
            }
            if (caseSet == true)
            {
                resolutionSelected = 0;
            }
            break;
        case 4:
            SetWindowSize(2560, 1440);
            if (caseSet == false)
            {
                if (defaultResWidth < 2560 && defaultResHeight < 1440)
                {
                    SetWindowSize(defaultResWidth, defaultResHeight);
                    caseSet = true;
                }
            }
            if (caseSet == true)
            {
                resolutionSelected = 0;
            }
            break;
        case 5:
            SetWindowSize(3840, 2160);
            if (caseSet == false)
            {
                if (defaultResWidth < 3840 && defaultResHeight < 2160)
                {
                    SetWindowSize(defaultResWidth, defaultResHeight);
                    caseSet = true;
                }
            }
            if (caseSet == true)
            {
                resolutionSelected = 0;
            }
            break;
        }

        switch (framerateSelected)
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

        if (isOnBorderless && !isBorderlessChecked)
        {
            ToggleBorderlessWindowed();
            isBorderlessChecked = true;
        }
        if (!isOnBorderless && isBorderlessChecked)
        {
            ToggleBorderlessWindowed();
            isBorderlessChecked = false;
        }

        if (!isOnVsync)
        {
            if (IsWindowState(FLAG_VSYNC_HINT))
                ClearWindowState(FLAG_VSYNC_HINT);
        }
        else
        {
            SetWindowState(FLAG_VSYNC_HINT);
        }
    }

    if (settings.AudioSettings)
    {
        SetMasterVolume(AudioVolume);
        DrawRectangle(widthOffset, GetScreenHeight() / 4, 200, 300, Fade(WHITE, 0.5f));
        // GuiToggleSlider((Rectangle){512, 256, 120, 30}, "Áudio", &setAudioVolume);
        GuiSliderBar((Rectangle){512, 256, 120, 30}, "Áudio Geral", TextFormat("%2.2f", &AudioVolume), &AudioVolume, 0, 100);
    }

    if (settings.InputSettings)
    {
        DrawRectangle(widthOffset, GetScreenHeight() / 5, 200, 300, Fade(WHITE, 0.5f));
    }

    // if(isOnVsync)
    // {
    //     SetConfigFlags(FLAG_VSYNC_HINT);
    // }

    // else
    // {
    //     SetWindowState(FLAG_WINDOW_RESIZABLE);
    // }

    //    float CurrentTime = GetTime();

    // if(!Mode3D && !Mode2D)
    // {
    //     Mode2D = true;
    // }

}

void Frontend::LoadTextData()
{
    switch(LanguageSelection)
    {
        case 0:
            Title = "Press any button.";Type0 = "Video";Type1 = "Audio";Type2 = "Controls";Type3 = "Accessibility";Option0 = "New Game";Option1 = "Options";Option2 = "Exit Game";Video1 = "Vertical Sync";Video2 = "Borderless Fullscreen";Video3 = "Framerate Limit";PartySelection = "Choose your team:";Party0 = "Rebellion";Party1 = "Galactic Empire";PlayerSelection = "How many players:"; 
            Players1 = "1 Player";Players2 = "2 Players";Players3 = "3 Players";Players4 = "4 Players";GameSelection = "Select your campaign:";Game_Hoth = "Battle of Hoth";Game_Sandbox = "Sandbox Mode";PressToStart = "Press %s to start";

        break;
        case 1:
            Title = "Presione cualquier botón.";Type0 = "Video";Type1 = "Audio";Type2 = "Controles";Type3 = "Accesibilidad";Option0 = "Nuevo Juego";Option1 = "Opciones";Option2 = "Salir del Juego";Video1 = "Sincronización Vertical";Video2 = "Pantalla Completa";Video3 = "Quadros por Segundo";
        break;
        case 2:
            Title = "     Pressione qualquer botão.     ";Type0 = "Vídeo";Type1 = "Áudio";Type2 = "Controles";Type3 = "Acessibilidade";Option0 = "Novo Jogo";Option1 = "Configurações de Jogo";Option2 = "Fechar Jogo";Video1 = "Sincronização Vertical";Video2 = "Janela sem Borda";Video3 = "Limite de Quadros";PartySelection = "Escolha sua equipe:";Party0 = "Rebelião";Party1 = "Império Galáctico";PlayerSelection = "Quantidade de jogadores:"; 
            Players1 = "1 Jogador";Players2 = "2 Jogadores";Players3 = "3 PlaJogadoresyers";Players4 = "4 Jogadores";GameSelection = "Selecione sua campanha::";Game_Hoth = "Batalha de Hoth";Game_Sandbox = "Modo Sandbox";PressToStart = "Pressione %s para começar";
        break;
        default:
        break;
    }

}
