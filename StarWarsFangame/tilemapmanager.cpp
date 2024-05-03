#include <raylib.h>
#include "tilemapmanager.hpp"
#include <iostream>

// https://github.com/mapeditor/tiled

TilemapManager::TilemapManager() {

    hasLevelChanged = true;
    *currentLevel = { 1 };
    
}

TilemapManager::~TilemapManager() {


}

void TilemapManager::DrawTile(int posX, int posY, int indexTextureX, int indexTextureY) {

    // Rectangle tSource;
    // Rectangle tDest;
    // Vector2 tOrigin;
    // DrawTexturePro(tileset[TILEMAP_GENERAL]);

}

void TilemapManager::Check() {

    switch(*currentLevel)
    {
    case 0:
        ChangeLevel();
    break;
    case 1:
        Image Tilemap001 = LoadImage("graphics/tilemap_all.png");
        dTileset[TILEMAP_HOTH] = LoadTextureFromImage(Tilemap001);
        UnloadImage(Tilemap001);
    break;
    }

    hasLevelChanged = false;






}

void TilemapManager::Render() {

    if(hasLevelChanged)
    {
    Check();
    }

    DrawTextureEx(dTileset[TILEMAP_HOTH], (Vector2){0, 0}, 0, 5, WHITE);

    // UnloadImage(Tilemap001);

    // for (int i = 0; i < WORLD_WIDTH; i++) {
    //     for (int j = 0; j < WORLD_HEIGHT; j++) {
    //         LEVEL1[i][j] = (Tileset)
    //         {
    //             .x = i,
    //             .y = j,
    //             // .type,
    //         };
    //     }
    // }

}

void TilemapManager::LoadCollision() {


}

void TilemapManager::ChangeLevel() {


}