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
    private:
        Texture2D logo;
        Texture2D background;
        Vector2 position;
        float alpha;
        float currentTime;
        float screenWidth;
        float screenHeight;
        Font fontf;
        Vector2 scroll;
        Music openingm;
        Camera3D camera;
        Camera2D cameraVector2;
        int camera_mode;
        Shader textshader;
        RenderTexture2D target;

};