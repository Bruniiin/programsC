#pragma once
#include <raylib.h>

class Scene {
    
    public:
        Scene();
        ~Scene();
        //void TextureDraw();
        //void DrawText();
        //void DrawBackground();
        //void ScrollText();
        //void Effects();
        void OpeningBegin();
        void TextBegin();
        void TextToTexture();
        void SceneDebug();

        Font fontf;
        bool SceneSkipped;

    private:
        Texture2D logo;
        Texture2D background;
        Texture2D keyboard;
        Texture2D gamepad;
        float alpha;
        float currentTime;
        double Time;
        double Time2;

    typedef struct {
        char* Dialog001 = "Pular Introdução";
        char* Dialog002 = "Skip Intro";
    } Dialog;

//        Vector2 position;
        Rectangle logoRectangle;
        Vector2 logoCenter;
        Vector2 scroll;
        Music openingm;
        Camera3D cameraVector3;
        Camera2D cameraVector2;
        int camera_mode;
        Shader textshader;
        RenderTexture2D target;
        Vector2 position;
        Vector3 position3;
        bool objDeclared;
        bool debugMode;
        bool deconstructorCalled;
        float logoSizeVector3;

};

