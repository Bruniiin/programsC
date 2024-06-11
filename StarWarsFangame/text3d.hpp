#pragma once
#include <raylib.h>

class Text3D {

    public:
        Text3D();
        ~Text3D();
        void Draw();

    int Campaign;

    private:

    const char* P1;
    const char* P2;
    const char* P3;
    const char* P4;

    const char* textTitleHoth001;
    const char* textTitleYavin001;
    const char* textSandboxMode;

    const char* textHoth001;
    const char* textYavin001;

    int RecSize001 = 130;
    int RecSize002 = 950;

    float fontSize;
    float fontSpacing;
    float fontSpacingTitle;
    float lineSpacing;
    float fontSizeTitle;
    Font fontf;
    Font fontfTitle;
    Vector3 position;
    Vector3 positionTitle;
    Color AltColor;
    // char text[64] = "A 3D Test TEST";
    // Vector3 tbox = {0};
    // int layers = 1;
    // int quads = 0;
    // float layerdistance = 0.01f;
    double CurrentTime;
    float alpha;
    Color NewsGothicBold;

};