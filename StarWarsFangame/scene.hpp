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

    private:
        Texture2D logo;
        Texture2D background;
        float alpha;
        float currentTime;

        Vector2 scroll;
        Music openingm;
        Camera3D cameraVector3;
//        Camera2D cameraVector2;
        int camera_mode;
        Shader textshader;
        RenderTexture2D target;
        Vector2 position;
        Vector3 position3;
        bool objDeclared;
        bool debugMode;
        bool deconstructorCalled;

};

