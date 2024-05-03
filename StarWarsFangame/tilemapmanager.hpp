#pragma once
#include <raylib.h>

// definições globais / global defines

#define TILEMAP 1

#define WORLD_WIDTH 20
#define WORLD_HEIGHT 20

class TilemapManager {

    public:
        TilemapManager();
        ~TilemapManager();
        void DrawTile(int posX, int posY, int indexTextureX, int indexTextureY);
        void Render();
        void Check();
        void LoadCollision();
        void ChangeLevel();

        int currentLevel[5] = {0, 1, 2, 3, 4};

        bool hasLevelChanged; 

    private:
        Texture2D dTileset[TILEMAP];

    // typedef struct {
    //     int x;
    //     int y;
    //     int type;
    // } Tileset;

    typedef enum {
        TILEMAP_GENERAL = 0,
        TILEMAP_YAVIN,
        TILEMAP_HOTH,
    } Tilemap;
    Tilemap sTILEMAP;

    // Tileset LEVEL1[WORLD_WIDTH][WORLD_HEIGHT]; // Hoth
    // Tileset LEVEL2[WORLD_WIDTH][WORLD_HEIGHT]; // Yavin

    Image Tilemap001;


// para claridade, os mapas são chamados de levels.

};