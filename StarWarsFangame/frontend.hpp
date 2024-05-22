#pragma once
#include <raylib.h>
#include "scene.hpp"
#include "text3d.hpp"
#include "game.hpp"
#include "playermanager.hpp"

class Frontend {

    public:
        Frontend();
        ~Frontend();
        void DefaultFrontend();
        void MainFrontend();
        void Settings();

    private:
        Scene scene;
        Text3D textUtils;
        Game game;
        float CurrentTime;
        double Time;
        // bool OpeningScene;
        // bool Mode3D;
        // bool Mode2D;
        // bool MenuMode;
        // bool ModeSet;
        Texture2D background;
        Texture2D logo;
        Texture2D icon;
        Vector2 title;
        float offset;
        float screenWidth;
        float screenHeight;
        bool MainMenu;
        bool HasPressedTitle;
        bool IsSettings;
        float alphaTitle;
        float alphaMenu;
        bool textBoxEditMode = false;
        Rectangle Gui;
        bool StartGame;
        bool hasKeyBeenPressed;


        typedef struct {
            char Title[128] = "Pressione qualquer botão.";
            char Type0[32] = "Vídeo";
            char Type1[32] = "Áudio";
            char Type2[32] = "Controles";
            char Type3[32] = "Acessibilidade";
            char Option0[32] = "Novo Jogo";
            char Option1[32] = "Configurações de Jogo";
            char Option2[32] = "Fechar Jogo";
            char Video1[32] = "Sincronização Vertical";
            char Video2[32] = "Janela sem Borda";
            char Video3[32] = "Limite de Quadros";
        } Dialog;
        Dialog dialog;

        typedef struct {
            char TitleEng[128] = "Press any button.";
            char Type0[32] = "Video";
            char Type1[32] = "Audio";
            char Type2[32] = "Controls";
            char Type3[32] = "Accessibility";
            char Option0[32] = "New Game";
            char Option1[32] = "Options";
            char Option2[32] = "Exit Game";
            char Video1[32] = "Vertical Sync";
            char Video2[32] = "Borderless Fullscreen";
            char Video3[32] = "Framerate Limit";
        } DialogEng;
        DialogEng dialogEng;

        typedef struct {
            char Type0[32] = "Vídeo";
            char Type1[32] = "Áudio";
            char Type2[32] = "Controles";
            char Type3[32] = "Acessibilidade";
        } Config;
        Config type;

        typedef struct {
            char Type0[32] = "Video";
            char Type1[32] = "Audio";
            char Type2[32] = "Controls";
            char Type3[32] = "Accessibility";
        } ConfigEng;
        ConfigEng typeEng;

        typedef struct {
            char Option0[32] = "Novo Jogo";
            char Option1[32] = "Configurações de Jogo";
            char Option2[32] = "Fechar Jogo";
        } Option;
        Option option;

        typedef struct {
            char Option0[32] = "New Game";
            char Option1[32] = "Options";
            char Option2[32] = "Exit Game";
        } OptionEng;
        OptionEng optionEng;

        typedef struct {
            char Video1[32] = "Sincronização Vertical";
            char Video2[32] = "Janela sem Borda";
            char Video3[32] = "Limite de Quadros";
            // char Video4[32] = 
            // char Video5[32] = 
            // char Video6[32] = 
        } Video;
        Video video;

        typedef struct {
            char Video1[32] = "Vertical Sync";
            char Video2[32] = "Borderless Fullscreen";
            char Video3[32] = "Framerate Limit";
            // char Video4[32] = 
            // char Video5[32] = 
            // char Video6[32] = 
        } VideoEng;
        VideoEng videoEng;

        typedef struct {
            bool VideoSettings;
            bool AudioSettings;
            bool InputSettings;
            bool AccessSettings;
        } SettingsWindow;
        SettingsWindow settings;

        typedef struct {
        } sFrontend;

        bool OpeningScene;
        bool Mode2D;
        bool Mode3D;
        bool MenuMode;

        bool isOnVsync;
        bool isOnBorderless;
        bool isBorderlessChecked;

        int setAudioVolume;

        float AudioVolume;

        bool guiEditMode001;
        bool guiEditMode002;

        int resolutionSelected;
        int framerateSelected;
        int defaultResWidth;
        int defaultResHeight;

        bool vDefaultResolution;
        bool resolutionSet;
        bool caseSet;
        
        int monitor = 0;

        float sAlpha = 0.5f;

        Rectangle Rec001;
        Rectangle Rec002;

        bool Coll001;

        bool Check001;
        bool Check002;

        Vector2 mousePos;

        float mouseCoordsX;
        float mouseCoordsY;

        char KeyEnter[16] = "Enter";
        char ButtonStart[16] = "Start";

        int isCampaignSelected;
        
        PlayerManager player;

        Texture2D sEmpire;
        Texture2D sRebels;

//        bool* pMode2D = &mode.Mode2D;

};