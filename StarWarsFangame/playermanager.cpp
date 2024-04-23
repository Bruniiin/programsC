#include <raylib.h>
#include <raymath.h>
#include "playermanager.hpp"

PlayerManager::PlayerManager() {

//    blank = LoadTexture("graphics/blank.png");
//    blankpos.x = (GetScreenWidth() - blank.width)/2; blankpos.y = GetScreenHeight() - blank.height - 100;

typedef struct player0 {
    Vector2 blankpos;
    float blankSpeed;
    Texture2D blank;

} blankPlayer;

// Scene scenePlayer;

player0 player0;

player0.blank = LoadTexture("graphics/player01.png");
player0.blankSpeed = 1.0f;
player0.blankpos = (Vector2){GetScreenWidth() /2, GetScreenHeight() /2};



}

PlayerManager::~PlayerManager() {


}

void PlayerManager::Draw() {

    DrawTextureV(blank, blankpos, BLUE);

}