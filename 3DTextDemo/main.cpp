#include <raylib.h>
#include <iostream>
#include <rlgl.h>
#include <stddef.h>
#include <math.h>

 using namespace std;

#define LETTER_BOUNDRY_SIZE     0.25f
#define TEXT_MAX_LAYERS         32
#define LETTER_BOUNDRY_COLOR    VIOLET

bool SHOW_LETTER_BOUNDRY = false;
bool SHOW_TEXT_BOUNDRY = false;

static void DrawTextCodepoint3D(Font font, int codepoint, Vector3 position, float fontSize, bool backface, Color tint);

static void DrawText3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, Color tint);

static Vector3 MeasureText3D(Font font, const char *text, float fontSize, float fontSpacing, float lineSpacing);

    float fontSize = 8.0f;
    float fontSpacing = 0.5f;
    float lineSpacing = -1.0f;




static void DrawText3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, Color tint)
{
    int length = TextLength(text);

    float textOffsetX = 0.0f;
    float textOffsetY = 0.0f;

    float scale = fontSize/(float)font.baseSize;

    for (int i = 0; i < length;)
        {
            int codepointByteCount = 0;
            int codepoint = GetCodepoint(&text[i], &codepointByteCount);
            int index = GetGlyphIndex(font, codepoint);

            if (codepoint == 0x3f) codepointByteCount = 1;

            if (codepoint == '\n')
            {
                    textOffsetY += scale + lineSpacing/(float)font.baseSize*scale;
                    textOffsetX = 0.0f;
            }

            else
            {
                    if ((codepoint != ' ')  && (codepoint != '\t'))
                        {
                            DrawTextCodepoint3D(font, codepoint, (Vector3){ position.x + textOffsetX, position.y, position.z + textOffsetY}, fontSize, backface, tint);
                        }
                    if (font.glyphs[index].advanceX == 0) textOffsetX += (float)(font.recs[index].width + fontSpacing)/(float)font.baseSize*scale;
                    else textOffsetX += (float)(font.glyphs[index].advanceX + fontSpacing)/(float)font.baseSize*scale;
            }
            i += codepointByteCount;
        }

}

static void DrawTextCodepoint3D(Font font, int codepoint, Vector3 position, float fontSize, bool backface, Color tint) // COPIADO
{
    // Character index position in sprite font
    // NOTE: In case a codepoint is not available in the font, index returned points to '?'
    int index = GetGlyphIndex(font, codepoint);
    float scale = fontSize/(float)font.baseSize;

    // Character destination rectangle on screen
    // NOTE: We consider charsPadding on drawing
    position.x += (float)(font.glyphs[index].offsetX - font.glyphPadding)/(float)font.baseSize*scale;
    position.z += (float)(font.glyphs[index].offsetY - font.glyphPadding)/(float)font.baseSize*scale;

    // Character source rectangle from font texture atlas
    // NOTE: We consider chars padding when drawing, it could be required for outline/glow shader effects
    Rectangle srcRec = { font.recs[index].x - (float)font.glyphPadding, font.recs[index].y - (float)font.glyphPadding,
                         font.recs[index].width + 2.0f*font.glyphPadding, font.recs[index].height + 2.0f*font.glyphPadding };

    float width = (float)(font.recs[index].width + 2.0f*font.glyphPadding)/(float)font.baseSize*scale;
    float height = (float)(font.recs[index].height + 2.0f*font.glyphPadding)/(float)font.baseSize*scale;

    if (font.texture.id > 0)
    {
        const float x = 0.0f;
        const float y = 0.0f;
        const float z = 0.0f;

        // normalized texture coordinates of the glyph inside the font texture (0.0f -> 1.0f)
        const float tx = srcRec.x/font.texture.width;
        const float ty = srcRec.y/font.texture.height;
        const float tw = (srcRec.x+srcRec.width)/font.texture.width;
        const float th = (srcRec.y+srcRec.height)/font.texture.height;

        if (SHOW_LETTER_BOUNDRY) DrawCubeWiresV((Vector3){ position.x + width/2, position.y, position.z + height/2}, (Vector3){ width, LETTER_BOUNDRY_SIZE, height }, LETTER_BOUNDRY_COLOR);

        rlCheckRenderBatchLimit(4 + 4*backface);
        rlSetTexture(font.texture.id);

        rlPushMatrix();
            rlTranslatef(position.x, position.y, position.z);

            rlBegin(RL_QUADS);
                rlColor4ub(tint.r, tint.g, tint.b, tint.a);

                // Front Face
                rlNormal3f(0.0f, 1.0f, 0.0f);                                   // Normal Pointing Up
                rlTexCoord2f(tx, ty); rlVertex3f(x,         y, z);              // Top Left Of The Texture and Quad
                rlTexCoord2f(tx, th); rlVertex3f(x,         y, z + height);     // Bottom Left Of The Texture and Quad
                rlTexCoord2f(tw, th); rlVertex3f(x + width, y, z + height);     // Bottom Right Of The Texture and Quad
                rlTexCoord2f(tw, ty); rlVertex3f(x + width, y, z);              // Top Right Of The Texture and Quad

                if (backface)
                {
                    // Back Face
                    rlNormal3f(0.0f, -1.0f, 0.0f);                              // Normal Pointing Down
                    rlTexCoord2f(tx, ty); rlVertex3f(x,         y, z);          // Top Right Of The Texture and Quad
                    rlTexCoord2f(tw, ty); rlVertex3f(x + width, y, z);          // Top Left Of The Texture and Quad
                    rlTexCoord2f(tw, th); rlVertex3f(x + width, y, z + height); // Bottom Left Of The Texture and Quad
                    rlTexCoord2f(tx, th); rlVertex3f(x,         y, z + height); // Bottom Right Of The Texture and Quad
                }
            rlEnd();
        rlPopMatrix();

        rlSetTexture(0);
    }
}

static Vector3 MeasureText3D(Font font, const char* text, float fontSize, float fontSpacing, float lineSpacing) // COPIADO
{
    int len = TextLength(text);
    int tempLen = 0;                // Used to count longer text line num chars
    int lenCounter = 0;

    float tempTextWidth = 0.0f;     // Used to count longer text line width

    float scale = fontSize/(float)font.baseSize;
    float textHeight = scale;
    float textWidth = 0.0f;

    int letter = 0;                 // Current character
    int index = 0;                  // Index position in sprite font

    for (int i = 0; i < len; i++)
    {
        lenCounter++;

        int next = 0;
        letter = GetCodepoint(&text[i], &next);
        index = GetGlyphIndex(font, letter);

        // NOTE: normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol so to not skip any we set next = 1
        if (letter == 0x3f) next = 1;
        i += next - 1;

        if (letter != '\n')
        {
            if (font.glyphs[index].advanceX != 0) textWidth += (font.glyphs[index].advanceX+fontSpacing)/(float)font.baseSize*scale;
            else textWidth += (font.recs[index].width + font.glyphs[index].offsetX)/(float)font.baseSize*scale;
        }
        else
        {
            if (tempTextWidth < textWidth) tempTextWidth = textWidth;
            lenCounter = 0;
            textWidth = 0.0f;
            textHeight += scale + lineSpacing/(float)font.baseSize*scale;
        }

        if (tempLen < lenCounter) tempLen = lenCounter;
    }

    if (tempTextWidth < textWidth) tempTextWidth = textWidth;

    Vector3 vec = { 0 };
    vec.x = tempTextWidth + (float)((tempLen - 1)*fontSpacing/(float)font.baseSize*scale); // Adds chars spacing to measure
    vec.y = 0.25f;
    vec.z = textHeight;

    return vec;
}




int main() {

    float screenSizeWidth = GetScreenWidth();
    float screenSizeHeight = GetScreenHeight();

    InitWindow((screenSizeWidth / 2), (screenSizeHeight / 2), "My raylib game!");
    InitAudioDevice();
    SetConfigFlags(FLAG_VSYNC_HINT && FLAG_MSAA_4X_HINT);
    SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
    SetTargetFPS(165);

///////////////////

    Camera3D camera = { 0 };
    camera.position = (Vector3){-10.f, 15.f, -10.f};
    camera.target = (Vector3){0.f, 0.f, 0.f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 cubePosition = {0.0f, 1.0f, 0.0f};
    Vector3 cubeSize = {2.0f, 2.0f, 2.0f};

    Font font = GetFontDefault();

    // typedef struct fontDefault {
    //     float fontSize = 8.0f;
    //     float fontSpacing = 0.5f;
    //     float lineSpacing = -1.0f;  
    // } fontDefault;

    // fontDefault fontMain;  

    char text[64] = "A 3D Test \n TEST";
        Vector3 tbox = {0};
        int layers = 1;
        int quads = 0;
        float layerdistance = 0.01f;

    // WaveTextConfig wcfg;

    float Time = 0.0f;

    DisableCursor();

//    int camera_mode = CAMERA_ORBITAL;

//////////////////////////

    while (!WindowShouldClose())
    {   

        UpdateCamera(&camera, CAMERA_ORBITAL);

        Time += GetFrameTime();
        quads = 0;



        if (IsKeyDown(KEY_ENTER) && (KEY_LEFT_ALT))
            ToggleBorderlessWindowed();

        BeginDrawing();

            ClearBackground(WHITE);

            BeginMode3D(camera);
                DrawGrid(10, 2.0f);
                DrawCubeV(cubePosition, cubeSize, BLUE);
                DrawCubeWires(cubePosition, 2.1f, 2.1f, 2.1f, WHITE);

                rlPushMatrix();
                    rlRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                    rlRotatef(90.0f, 0.0f, 0.0f, -1.0f);
                
                for (int i = 0; i < layers; ++i)
                {
            DrawText3D(GetFontDefault(), text, (Vector3){ 0.0f, 0.0f, -4.5f + tbox.z/2}, fontSize, fontSpacing, lineSpacing, true, DARKBLUE);
                }

                rlPopMatrix();


///////////////

            // rlPushMatrix();
            //     rlRotatef(180.f, 0.f, 1.f, 0.f);
            //     char *opt = (char *)TextFormat("Test", fontMain.fontSize);
            //     quads+= TextLength(opt);
            //     Vector3 m = MeasureText3D(GetFontDefault(), opt, 8.f, 1.f, 0.f);
            //     Vector3 pos = { -m.x/2.0f, 0.01f, 2.f};
            //     DrawText3D(GetFontDefault(), opt, pos, 8.f, 1.f, 0.f, false, BLUE);
            //     pos.z += 0.5f + m.z;
            // rlPopMatrix();

            char* textvector = "ANOTHER TEST";

            Vector3 m = MeasureText3D(GetFontDefault(), text, 8.0f, 1.0f, 1.0f);
            Vector3 pos = {5.0f, 0.01f, -5.0f};
            quads += 36;
            m = MeasureText3D(GetFontDefault(), text, 10.0f, 0.5f, 0.0f);
            // pos = (Vector3){2.f, 1.01f, 2.f};
            DrawText3D(GetFontDefault(), textvector, pos, 10.0f, 0.5f, 0.0f, true, DARKBLUE);
            // pos.z += 1.5f + m.z;


/////////////////////

            EndMode3D();
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}