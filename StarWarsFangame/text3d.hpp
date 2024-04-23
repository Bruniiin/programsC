#pragma once
#include <raylib.h>

class Text3D {

    public:
        Text3D();
        ~Text3D();
        void Draw();
    private:

    float fontSize;
    float fontSpacing;
    float lineSpacing;
    float fontSizeTitle;
    Font fontf;
    Vector3 position;
    Vector3 positionTitle;
    // char text[64] = "A 3D Test TEST";
    // Vector3 tbox = {0};
    // int layers = 1;
    // int quads = 0;
    // float layerdistance = 0.01f;
    float CurrentTime;
    float alpha;
    Color NewsGothicBold;

};