#include <raylib.h>
#include <iostream>
#include <rlgl.h>
#include <stddef.h>
#include "text3d.hpp"
#include <math.h>
#include <iostream>

using namespace std;

#define LETTER_BOUNDRY_SIZE 0.25f
#define TEXT_MAX_LAYERS 32
#define LETTER_BOUNDRY_COLOR VIOLET

bool SHOW_LETTER_BOUNDRY = false;
bool SHOW_TEXT_BOUNDRY = false;

static void DrawTextCodepoint3D(Font font, int codepoint, Vector3 position, float fontSize, bool backface, Color tint);

static void DrawText3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, Color tint);

static Vector3 MeasureText3D(Font font, const char *text, float fontSize, float fontSpacing, float lineSpacing);



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

Text3D::Text3D() {

    // pt-br: É um período crítico para as forças rebeldes. Embora a Estrela da Morte tenha sido destruída, tropas imperiais
    // conseguiram expulsar os rebeldes de sua base secreta e estão os perseguindo por toda a galáxia. 
    // O Imperador ouviu rumores de uma base secreta rebelde no remoto planeta remoto de Hoth e o IMPÉRIO GALÁTICO enviou todas as suas forças lideradas
    // por [PLAYER_EMPIRE] para encurralar os rebeldes.
    // Liderando os rebeldes, [PLAYER_REBELLION] prepara sua defesa em um confronto que pode mudar o rumo de toda a galáxia...

    // Em inglês pelas fontes não suportarem acentos ainda.

    Font font = GetFontDefault();

    fontf = LoadFontEx("utils/newsgothicbold.otf", 100, NULL, 0); // source: https://fontsinuse.com/uses/45329/star-wars-the-empire-strikes-back-opening-cra
    fontfTitle = LoadFontEx("utils/newsgothicboldextracondensed.ttf", 200, NULL, 0);

    float Time = 0.0f;
    int Size = 2 << 16; // 65536 caracteres

    position = {-2.f, 3.5f, 5.0f};
    positionTitle001 = {-2.f, 3.5f, 5.5f};
    positionTitle002 = {-2.f, 3.5f, 5.5f};

    alpha = 1.0f;

    textTitleYavin001 = "A NEW HOPE";
    textTitleHoth001 = "THE EMPIRE STRIKES BACK";

    // text needs to be carefully spaced so as to line up properly in the center of the screen.

    textHoth001 = "                    Episode V\n\n\n\n\n              BATTLE OF HOTH \nIt  is  a  dark  time for the Rebellion.\nAlthough  the DEATH STAR has been\ndestroyed,   Imperial    troops   have\ndriven  the  Rebel forces  from  their\nhidden   base   and   pursued   them\nacross the galaxy.\n\nTEST";
    textYavin001 = "                   Episode IV\n\n\n\n\n     \nIt   is  a  period  of  civil war. Rebel\nspaceships,  striking  from  a hidden\nbase,  have won their first victory\nagainst the evil Galactic Empire.\n\nTEST";


    P1 = "PLAYER1override";
    P2 = "PLAYER2override"; 

    AltColor = Color{202, 160, 0, 255};

    fontSize = 25.0f;
    fontSpacing = 0.5f;
    fontSpacingTitle = 0.1f;
    lineSpacing = -1.0f;
    fontSizeTitle = 112.0f;

// char text[64] = "A 3D Test \n TEST";
//     Vector3 tbox = {0};
//     int layers = 1;
//     int quads = 0;
//     float layerdistance = 0.01f;

}

Text3D::~Text3D() {

    
}

void Text3D::Draw() {

    CurrentTime += 0.01f;

    Vector3 tbox = {0};
    int layers = 2;
    int quads = 0;
    float layerdistance = 0.01f;

    position.z -= 0.1425f * GetFrameTime();
    positionTitle.z -= 0.1425f * GetFrameTime();

    Vector3 MeasureText001;
    Vector3 MeasureText002;
    MeasureText001 = MeasureText3D(fontf, textTitleHoth001, fontSizeTitle, fontSpacing, lineSpacing);
    MeasureText002 = MeasureText3D(fontf, textTitleYavin001, fontSizeTitle, fontSpacing, lineSpacing);

    rlPushMatrix();
    {
            rlRotatef(90.0f, 1.f, 0.f, 1.f);
            rlRotatef(90.0f, 0.f, 0.f, -1.f);

        if (CurrentTime > 0.f) 
        {
            for (int i = 0; i < layers; ++i)
            {
                switch(Campaign)
                {
                    case 1:
                        DrawText3D(fontf, TextFormat(textHoth001, P1), position, fontSize, fontSpacing, lineSpacing, true, Fade(AltColor, alpha)); //(Vector3){0.f, 1.f, -2.5f}
                        DrawText3D(fontfTitle, textTitleHoth001, positionTitle, fontSizeTitle, fontSpacingTitle, lineSpacing, true, Fade(AltColor, alpha));
                    break;
                    default:
                        DrawText3D(fontf, TextFormat(textYavin001, P1), position, fontSize, fontSpacing, lineSpacing, true, Fade(AltColor, alpha));
                        DrawText3D(fontfTitle, textTitleYavin001, positionTitle, fontSizeTitle, fontSpacingTitle, lineSpacing, true, Fade(AltColor, alpha));
                    break;
                }
            }
        }
    }
    rlPopMatrix();

    EndMode3D();

    if (CurrentTime > 82.f)
    {
        alpha -= 0.005f;
        // alpha -= GetTime() / 10;
    }

// Letterbox

    if(CurrentTime > 85.f)
    {
        RecSize001 -= 1;
        RecSize002 += 1;
    }

    DrawRectangle
    (0, 0, 1920, RecSize001, BLACK);
    DrawRectangle
    (0, RecSize002, 1920, 130, BLACK);

}

