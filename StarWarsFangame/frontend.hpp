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

    private:
        Scene scene;
        Text3D textUtils;
        Game game;
        float CurrentTime;
        // bool OpeningScene;
        // bool Mode3D;
        // bool Mode2D;
        // bool MenuMode;
        // bool ModeSet;
        Texture2D background;
        Vector2 title;
        float offset;
        float screenWidth;
        float screenHeight;
        bool MainMenu;
        bool HasPressedTitle;
        float alpha;
        char Title2[128] = "Press any button.";


        typedef struct {
        char Title[128] = "Pressione qualquer botão.";
        } Dialog;
        Dialog dialog;

        bool OpeningScene;
        bool Mode2D;
        bool Mode3D;
        bool MenuMode;

//        bool* pMode2D = &mode.Mode2D;

};