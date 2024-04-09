#pragma once
#include <raylib.h>

class Scene {
    
    public:
        Scene();
        //~Scene();
        //void TextureDraw();
        //void DrawText();
        //void DrawBackground();
        //void ScrollText();
        //void Effects();
        void OpeningBegin();
    private:
        Texture2D logo;
        Texture2D background;
        Vector2 position;
        float alpha;

};
