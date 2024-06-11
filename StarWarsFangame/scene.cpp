#include <raylib.h>
#include <raymath.h>
#include "scene.hpp"
#include "rcamera.h"
#include "text3d.hpp"
#include <iostream>

    using namespace std;

Scene::Scene() {
    background = LoadTexture("graphics/backgroundalt.png");
    logo = LoadTexture("graphics/star-wars-logo.png");
    keyboard = LoadTexture("graphics/gdb-keyboard-key1.png");
    GenTextureMipmaps (&logo);

    openingm = LoadMusicStream("audio/Main Title.mp3");
    PlayMusicStream(openingm);

//    fontf = LoadFontEx("utils/newsgothicbold.otf", 100, NULL, 0);

//    screenWidth = 1920.0f;
//    screenHeight = 1080.0f;

    logo.width = 2400.0f;
    logo.height = 1028.0f;
    float currentTime = 0.0f;
    scroll.x = (500);
    scroll.y = (1080);

    this->background = background;
    this->logo = logo;
    SetTextureFilter(logo, TEXTURE_FILTER_TRILINEAR);


   cameraVector3 = { 0 };
//    cameraVector3.position = (Vector3){5.f, 2.f, 5.f};
//    cameraVector3.target = (Vector3){0.f, 2.f, 0.f};
   cameraVector3.position = (Vector3){5.f, 0.f, 5.f};
   cameraVector3.target = (Vector3){0.f, 2.5f, 0.f};
   cameraVector3.up = (Vector3){0.0f, 1.0f, 0.0f};
   cameraVector3.fovy = 60.0f;
   cameraVector3.projection = CAMERA_PERSPECTIVE;

   cameraVector2 = { 0 };
   cameraVector2.target = (Vector2){0.f, 2.f};
   cameraVector2.zoom = 1.f;

   int camera_mode = CAMERA_ORBITAL;

    position3 = {-10.f, 10.0f, -10.0f};

    debugMode = false;

    SceneSkipped = false;

    deconstructorCalled = false;

    logoSizeVector3 = 5.f;

//    target = LoadRenderTexture(800, 800);

//        BeginTextureMode(target);
//        ClearBackground(WHITE);
//            scroll.y -= 1.0f;
//        DrawTextEx(fontf, "    EPISODE V \n\n\n\n\n\n    AAAAAAAA LOL\n\n\n\n\n\nTHE EMPIRE STRIKES BACK\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT", scroll, 100, 10, YELLOW);
//        EndTextureMode();

////////////////

    // cameraVector2 = { 0 };
    // cameraVector2.target = (Vector2){0.f, 0.f};
    // cameraVector2.offset = (Vector2){0.f, 0.f};
    // cameraVector2.rotation = 0.0f;
    // cameraVector2.zoom = 1.0f;
    
//    camera.projection = CAMERA_PERSPECTIVE;

//    camera_mode = CAMERA_ORBITAL;
    
}

Scene::~Scene() {

    UnloadTexture(background);
    UnloadTexture(logo);
    UnloadRenderTexture(target);
    // UnloadMusicStream(openingm);

}

void Scene::OpeningBegin() {



//    BeginMode3D(cameraVector3);

        // UpdateCameraPro(&cameraVector3,
        //     (Vector3){
        //         (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))*0.1f -  
        //         (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))*0.1f,    
        //         (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))*0.1f -
        //         (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))*0.1f,
        //         0.0f                                      
        //     },
        //     (Vector3){
        //         GetMouseDelta().x*0.05f,                        
        //         GetMouseDelta().y*0.05f,                       
        //         0.0f                                           
        //     },
        //     GetMouseWheelMove()*2.0f);

            
//    DrawGrid(10, 1.0f);

//    UpdateCamera(&camerat, CAMERA_ORBITAL);

    UpdateMusicStream(openingm);

    float alpha = 1.0f;
    
    int x;
    int y;

    currentTime = GetTime();

    float alphaSpeed;

    alphaSpeed = GetTime() / 20;

    float unloadTime;

    unloadTime -= GetTime() / 30;



    if(currentTime > 1.0f) 
    { 
        alpha -= Time / 20;
    }

    Time += GetFrameTime();
    Time2 += 0.01f;

    float unloadTexture = 1800.0f;

    Vector2 position {GetScreenWidth() /2, GetScreenHeight() /2};

    Vector3 position3logo {0.f, 0.f, 0.f};

    Vector3 position3up {0.f, 1.f, 0.f};

    Rectangle logoRectangleVector3 = {0, 0, logo.width, logo.height - 10};

    Rectangle logoRectangle = (Rectangle){0, 0, logo.width, logo.height};
    Vector2 logoCenter = {logo.width/2 / Time, logo.height/2 / Time};
    // / GetTime();

    float delta = GetFrameTime();

    logoSizeVector3 -= 0.75f * GetFrameTime();

    if (logoSizeVector3 < 0.f)
    {
        logoSizeVector3 = 0.f;
    }

//    DrawBillboard(cameraVector3, background, position3, 30.0f, WHITE);
//    DrawBillboard(cameraVector3, logo, Vector3{cameraVector3.target.x, cameraVector3.target.y, cameraVector3.target.z}, logoSizeVector3, Fade(WHITE, 0.f));    
//    DrawBillboardPro(cameraVector3, logo, logoRectangleVector3, position3logo, position3up, (Vector2){5.0f, 5.0f}, (Vector2){logo.width/2, logo.height/2}, 0.f, Fade(WHITE, alpha)); //5.f 5.f is size, 0.f is origin and the last 0.f is rotation.
//    DrawBillboardRec(cameraVector3, logo, logoRectangleVector3, position3logo, (Vector2){5.f, 5.f}, WHITE);

//    EndMode3D();

    BeginMode2D(cameraVector2); // 2D elements drawn after 3D elements are drawn.

    DrawTexture(this->background, 0, 0, WHITE);
    //DrawTexture(this->background, 0, 1920, WHITE);
    DrawTexturePro(this->logo, logoRectangle, (Rectangle){float(position.x), float(position.y), float(logoRectangle.width) / Time, float(logoRectangle.height) / Time}, logoCenter, 0, Fade(WHITE, alpha)); // position = posição, logorectangle = tamanho    

    // logoCenter.x -= 10.75f * GetFrameTime();
    // logoCenter.y -= 10.75f * GetFrameTime();    
    // logoRectangle.width -= 10.75f * GetFrameTime();    
    // logoRectangle.height -= 10.75f * GetFrameTime(); 

    if(Time2 > 0.f)
    {
        DrawTexture
        (this->keyboard, 1780, 600, WHITE);
        DrawText
        ("Pular \nIntrodução", 1800, 630, 20, WHITE);
            if(IsKeyPressed(KEY_ENTER))
            {
                SceneSkipped = true;
            }
    }

    if(Time2 > 86.f && Time2 < 94.f)
    {
        cameraVector2.target.y += 1;
    }

//    EndMode2D();

    BeginMode3D(cameraVector3);

// Mesma coisa só que 2D

//    DrawTexture(this->background, 0, 0, LIGHTGRAY);
//    DrawTexturePro(this->logo, logoRectangle, (Rectangle){float(position.x), float(position.y), float(logoRectangle.width) / GetTime(), float(logoRectangle.height) / GetTime()}, logoCenter, 0, Fade(WHITE, alpha)); // position = posição, logorectangle = tamanho

    if(currentTime > 90.0f && !deconstructorCalled)
    {
        Scene::~Scene();
        deconstructorCalled = true;
    }

}

//     void Scene::TextBegin() { // texto 3D a fazer, por enquanto, texto 2D. Também preciso criar um método para modificar o texto dependendo das decisões dos jogadores.

//         int offset = 50;

//         if(currentTime > 10.0f)
//         {
//             // DrawTextureRec(target.texture, (Rectangle) {200, 200, (float)target.texture.width, (float)-target.texture.height}, Vector2{0, 0}, WHITE);
//             scroll.y -= 1.0f;
//             // DrawTextEx(fontf, "    EPISODE V \n\n\n\n\n\n    AAAAAAAA LOL\n\n\n\n\n\nTHE EMPIRE STRIKES BACK\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT\n\n\n\n\n\nTEXT", scroll, 100, 10, YELLOW);
//                 if (scroll.y < -1080) 
//                 { 
//                     CloseWindow();

//                 }
//         }
// }

void Scene::SceneDebug() {

    if (IsKeyPressed(KEY_F1))
    {
        // if(debugMode == false)
        // debugMode = true;
        // else(debugMode == true)
        // debugMode = false;
        debugMode = !debugMode;

        if (debugMode)
        {
        cout << "Debug Mode On" << endl;
        }
    }


    if (debugMode == true)
    {
        DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", cameraVector3.position.x, cameraVector3.position.y, cameraVector3.position.z), 610, 60, 10, RED);
        DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", cameraVector3.target.x, cameraVector3.target.y, cameraVector3.target.z), 610, 75, 10, RED);
        DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", cameraVector3.up.x, cameraVector3.up.y, cameraVector3.up.z), 610, 90, 10, RED);

                UpdateCameraPro(&cameraVector3,
        (Vector3){
            (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))*0.1f -  
            (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))*0.1f,    
            (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))*0.1f -
            (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))*0.1f,
            0.0f                                      
        },
        (Vector3){
            GetMouseDelta().x*0.05f,                        
            GetMouseDelta().y*0.05f,                       
            0.0f                                           
        },
        GetMouseWheelMove()*2.0f);
    }

}


// Obsolete functions //


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