#pragma once
#include <raylib.h>
#include <vector>
#include "tilemapmanager.hpp"
#include "laser.hpp"
#include "coroutinemanager.hpp"

// class Projectile {

//     public: 
//         Projectile();
//         Projectile(Vector2 pPosition, int pSpeed, Color pColor);

//         std::vector<Projectile>lasers;

// };

class PlayerManager {

    public:
        PlayerManager();
        ~PlayerManager();
        //void Projectile(Vector2 pPosition, int pSpeed, Color pColor);
        void Draw();
        void Update();
        void Move();
        void PlayerUpdate();
        void PlayerAction();
        void AsyncUpdate();
        void InputUpdate();
        void RenderManager();
        void LoadCollision();
        void HandleShooting();
        Vector2 DirCalculate();
//        void Laser(Vector2 position, int speed);
        Texture2D blank;
        Texture2D Map01;

        Vector2 pPosition;
        int pSpeed;
        Color pColor;

        Vector2 P1GamepadDir;
        Vector2 P2GamepadDir;

        Vector2 laserDest;

        int routineThreadStatus;

        Coroutine coroutine;
        int status;

typedef enum charClass {
    NOT_SET = 0,
    JEDI, // líder rebelde
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

typedef enum {
    IN_GAME = 0,
    GAME_SET, // smash reference :D
} GameState;
GameState state;

typedef enum {
    REBELLION = 0,
    EMPIRE,
} PartyType;

        typedef struct Player {
            Vector2 playerPos;
            float playerVelocity;
            float velocityModifier;
            Texture2D player;
            bool isAlive;
            bool isHoldingWeapon;
            bool isHoldingRangedWeapon;
            bool hasStartedFiring;
            bool isFiring;
            bool isAiming;
            // bool isUsingAction;
            bool isRunning;
            int Health;
            int Experience;
            int Level;
            int PLY;
            Vector2 laser;
            Vector2 Dir;
            Vector2 Angle;
            GameState state;
            CharType type;
            WeaponType weapon;
            CharMode mode;
            PartyType party;
        } Player;

        Player P1; // instâncias, Jedi
        Player P2; // Sith

        Player* p1 = new Player;
        Player* p2 = new Player;

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

        std::vector<Weapon> vPistol;
        std::vector<Weapon> vRifle;

        // typedef struct {
        //     Vector2 blankpos;
        //     float blankSpeed;
        //     Texture2D blank;
        // } Player1;
        //  Player1 player02;

        bool isGameDone;

        bool GameMode;

        bool isCoroutineActive;

        Vector2 P1Pos;
        Vector2 P2Pos;
        Vector2 playerPosition;

        std::vector<Vector2>playerPos; // vectors em vectors, muito meta

        float MousePosX;
        float MousePosY;
        float MouseRayPosX;
        float MouseRayPosY;

        Vector2 mousePos;

        Camera2D cameraposp1;
        Camera2D cameraposp2;
        Camera2D cameraPosFull;

        RenderTexture CameraP1;
        RenderTexture CameraP2;
        RenderTexture CameraP1fullscr;
        Rectangle splitscreen;
        Rectangle fullscr;


    private:
        Vector2 p1pos;
        Vector2 p2pos;
//        Vector2 blankpos;
//        float blankspeed;
//        Texture2D blank;

        Vector2 position;
        int speed;

        float FireDelay;
        float FireSpeed;

        float bulletSpeed;
        // Vector2 Dir;

        // Laser laser;

        std::vector<Laser> lasers;

        std::vector<float> angles;

        typedef struct {
            double StartTime;
            int TimeLimit;
            bool isTimerActive;
        } Timer;

        float velocityModifier;

        int GamepadP1 = 0;
        int GamepadP2 = 1;


        Texture2D defaultAim;

        TilemapManager tilemap;

//        Rectangle playerColl = { 0 };
        Rectangle playerColl001;
        Rectangle playerColl002;
        Rectangle pistolColl;

        Rectangle playerColl001Dest;
        Rectangle playerColl002Dest;
        Rectangle pistolCollDest;

        bool Coll001; bool Coll002; bool Coll003; bool Coll004; bool Coll005; bool Coll006; bool Coll007; bool Coll008; bool Coll009;

        float angle;

        float bulletSpread;

        Vector2 weaponPos;

        float mousePosX;
        float mousePosY;

        float P1dirX;
        float P1dirY; 
        float P2dirX;
        float P2dirY;

        char WeaponChar[8];

};