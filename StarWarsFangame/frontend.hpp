#pragma once
#include <raylib.h>
#include "scene.hpp"
#include "text3d.hpp"
#include "game.hpp"

class Frontend {

    public:
        Frontend();
        ~Frontend();
        void mFrontend();
        void MainFrontend();
        void Settings();

    private:
        Scene scene;
        Text3D textUtils;
        Game game;
        float CurrentTime;
        float Time;
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
        char TitleEng[128] = "    Press any button.";


        typedef struct {
        char Title[128] = "Pressione qualquer botão.";
        } Dialog;
        Dialog dialog;

        typedef struct {
            char Config0[32] = "Vídeo";
            char Config1[32] = "Áudio";
            char Config2[32] = "Controles";
            char Config3[32] = "Acessibilidade";
        } Config;
        Config type;

        typedef struct {
            char Config0[32] = "Video";
            char Config1[32] = "Audio";
            char Config2[32] = "Controls";
            char Config3[32] = "Accessibility";
        } ConfigEng;
        ConfigEng typeEng;

        typedef struct {
            bool VideoSettings;
            bool AudioSettings;
            bool InputSettings;
            bool AccessSettings;
        } SettingsWindow;
        SettingsWindow settings;

        bool OpeningScene;
        bool Mode2D;
        bool Mode3D;
        bool MenuMode;

//        bool* pMode2D = &mode.Mode2D;

};