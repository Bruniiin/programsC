#pragma once
#include <raylib.h>
#include <vector>
#include "tilemapmanager.hpp"

class PlayerManager {

    public:
        PlayerManager();
        ~PlayerManager();
        void Draw();
        void Move();
        void PlayerUpdate();
        void Action();
        void Update();
        void InputUpdate();
        void RenderManager();
        Texture2D blank;
        Texture2D Map01;

typedef enum {
    JEDI = 0, // líder rebelde
    SITH, // líder imperial
} CharType;

typedef enum {
    ON_FOOT = 0,
    VEH_AIRSPEEDER,
    VEH_SNOWSPEEDER, //re-skin de airspeeder na batalha de hoth /airspeeder reskin
    VEH_X_WING,
    VEH_FIGHTER,
} CharMode;

typedef enum {
    WPN_HANDS = 0,
    WPN_PISTOL,
    WPN_RIFLE,
    WPN_LIGHTSABER,
} WeaponType;

        typedef struct {
            Vector2 playerPos;
            float playerVelocity;
            Texture2D player;
            bool isAlive;
            bool isHoldingWeapon;
            bool isFiringWeapon;
            bool isAiming;
            bool isUsingAction;
            bool isRunning;
            int Health;
            int Experience;
            int Level;
            Vector2 laser;
            Vector2 Dir;
            CharType type;
            WeaponType weapon;
            CharMode mode;
        } Player;

        Player player01; // instâncias, Jedi
        Player player02; // Sith

        std::vector<Player> players;        

        

        typedef struct {
            Vector2 weaponPos;
            Texture2D weapon;
            bool isAlive;
            bool isActive;
            bool isRanged;
            WeaponType weapontype;
        } Weapon;

        Weapon pistol;

        std::vector<Weapon> weapons;

        // typedef struct {
        //     Vector2 blankpos;
        //     float blankSpeed;
        //     Texture2D blank;
        // } Player1;
        //  Player1 player02;

    private:
        Vector2 p1pos;
        Vector2 p2pos;
//        Vector2 blankpos;
//        float blankspeed;
//        Texture2D blank;

        typedef struct {
            double StartTime;
            int TimeLimit;
            bool isTimerActive;
        } Timer;

        float velocityModifier;
        Camera2D cameraposp1;
        Camera2D cameraposp2;

        RenderTexture CameraP1;
        RenderTexture CameraP2;
        RenderTexture CameraP1fullscr;
        Rectangle splitscreen;
        Rectangle fullscr;

        int GamepadP1 = 0;
        int GamepadP2 = 1;

        bool GameMode;

        Texture2D mouse;

        TilemapManager tilemap;

};