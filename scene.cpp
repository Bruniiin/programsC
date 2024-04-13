#include <raylib.h>
#include <raymath.h>
#include "scene.hpp"

Scene::Scene() {
    Texture2D background = LoadTexture("graphics/background.png");
    Texture2D logo = LoadTexture("graphics/star-wars-logo.png");
    GenTextureMipmaps (&logo);

    openingm = LoadMusicStream("audio/maintitle.mp3");
    PlayMusicStream(openingm);

    screenWidth = 1920.0f;
    screenHeight = 1080.0f;

    logo.width = 2400.0f;
    logo.height = 1028.0f;
    float currentTime = 0.0f;
    scroll.x = (500);
    scroll.y = (1080);

    this->background = background;
    this->logo = logo;
    SetTextureFilter(logo, TEXTURE_FILTER_TRILINEAR);
    fontf = LoadFontEx("utils/newsgothicbold.otf", 100, NULL, 0);

//    target = LoadRenderTexture(800, 800);

//        BeginTextureMode(target);
//        ClearBackground(WHITE);
//            scroll.y -= 1.0f;
//        DrawTextEx(fontf, "    EPISODE V \n\n\n\n\n\n    AAAAAAAA LOL\n\n\n\n\n\nTHE EMPIRE STRIKES BACK\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT", scroll, 100, 10, YELLOW);
//        EndTextureMode();

////////////////

    camera = { 0 };
    camera.position = (Vector3){0.f, 0.f, 0.f};
    camera.target = (Vector3){0.f, 0.f, 0.f};
    camera.up = (Vector3){0.0f, 1.0f, 2.0f};
    camera.projection = CAMERA_PERSPECTIVE;

    camera_mode = CAMERA_ORBITAL;
    
}

Scene::~Scene() {

    UnloadTexture(background);
    UnloadTexture(logo);
    UnloadRenderTexture(target);
    UnloadMusicStream(openingm);

}

void Scene::OpeningBegin() {

//    UpdateCamera(&camera, camera_mode);

    UpdateMusicStream(openingm);

    float alpha = 1.0f;
    
    int x;
    int y;

    currentTime += GetTime();

    float alphaSpeed;

    alphaSpeed = GetTime() / 20;

    float unloadTime;

    unloadTime -= GetTime() / 30;



    if(currentTime > 1.0f) 
    { 
        alpha -= GetTime() / 25;
    }

    float unloadTexture = 1800.0f;

    Vector2 position {screenWidth/2, screenHeight/2};

    Rectangle logoRectangle = (Rectangle){0, 0, logo.width, logo.height};
    Vector2 logoCenter = {logo.width/2 / GetTime(), logo.height/2 / GetTime()};

    DrawTexture(this->background, 0, 0, LIGHTGRAY);
    DrawTexturePro(this->logo, logoRectangle, (Rectangle){float(position.x), float(position.y), float(logoRectangle.width) / GetTime(), float(logoRectangle.height) / GetTime()}, logoCenter, 0, Fade(WHITE, alpha)); // position = posição, logorectangle = tamanho



}

    void Scene::TextBegin() { // texto 3D a fazer, por enquanto, texto 2D. Também preciso criar um método para modificar o texto dependendo das decisões dos jogadores.

        int offset = 50;

        if(currentTime > 2500.0f) 
        {
            // DrawTextureRec(target.texture, (Rectangle) {200, 200, (float)target.texture.width, (float)-target.texture.height}, Vector2{0, 0}, WHITE);
            scroll.y -= 1.0f;
            DrawTextEx(fontf, "    EPISODE V \n\n\n\n\n\n    AAAAAAAA LOL\n\n\n\n\n\nTHE EMPIRE STRIKES BACK\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT", scroll, 100, 10, YELLOW);
        }

// (Vector2){500, 500}

}

    void Scene::TextToTexture() {


    
}


// Funções obsoletas //


//        for (x = 0, y = 10; x < y; x++) 
//        { 
//            alpha -= 0.01f; 
//        }
 // { logo.width = 0; logo.height = 0; UnloadTexture(logo);} 

//    if (logo.width < 3000) {
//    UnloadTexture(logo);
//    EndDrawing();
//   }

//    position.x = 500;
//    position.y = 500;

//    float scalef = 0.5f;
//    float rotationf = 0.f;
//    float scalefdec = 0.001f;
//    float scaleFactor = 0.999f;
    
//    number1 = 000.5f;


//    while(scalef < 0.01f) { 
//        scalef = scalef -= scalefdec; // GetFrameTime();
//         if (scalef < 0.1f) { scalef = 0.1f; break; }
//        }




//    Rectangle RectangleDest = (Rectangle){screenWidth/2, screenHeight/2, logo.width * 2, logo.height * 2};
//    Rectangle logoSize = (Rectangle){logo.width * 10, logo.height * 10};

//    DrawTextureEx(logo, position, rotationf, scalef / GetTime(), LIGHTGRAY);