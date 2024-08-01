#pragma once
#include <raylib.h>
#include <vector>
#include "laser.hpp"
#include "playermanager.hpp"
#include "ui.hpp"
#include "levelmanager.hpp"

#define ACTORS 32

//#define REBEL_SOLDIER 0
//#define IMPERIAL_SOLDIER 1

class CharacterManager { //: public PlayerManager {

    public:
        CharacterManager();
        ~CharacterManager();
        void Update(int pId);
        void Begin();
        void Add(int pId);
        Rectangle PlayerRec(Rectangle pPlayer1);
        Rectangle Rec;

            PlayerManager player;
            Laser laser;

            typedef struct {
                Texture2D Actors;
                //Vector2 Position2;
                Vector2 Positions;
                Rectangle Sources;
                Rectangle Destinations;
                int Id;
                int Type;
                int Health;
                int Weapon;
                float Altitude;
                float fallSpeed;
                float fallDuration;
                bool isAlive;
                bool isCollided;
                bool isCollidedPlayer;
                bool isCollidedProjectile;
                bool isOnVehicle;
                bool isFriendly;
                // sActor(Vector2 sPosition)
            } Actor;

        Ui ui;
        LevelManager tilemap;

    // //std::vector<Actor>actors;

    // std::vector<Vector2>positions;
    // std::vector<Rectangle>sources;
    // std::vector<Rectangle>destinations;                
    // std::vector<Actor>actors;
    // std::vector<bool>collisions;
    
    //std::vector<Positions>positions2;

        int Entities;
        int i;
        int entitySize;
        bool isReady;
        bool testcondition;
        Texture2D Actors[ACTORS];
        float t;

    std::vector<Vector2>positions;
    std::vector<Rectangle>sources;
    std::vector<Rectangle>destinations;                
    std::vector<bool>collisions;

    private:

        // Character Actor;


        // std::vector<CharacterManager::Actor>actors;

        // typedef struct Actor{

        // } Actor;

    // PlayerManager player;

            // typedef struct Positions {
            //     Vector2 Position;
            //     bool isActive;
            //     // bool canMove;
            // } Positions;


};

    class Character : public CharacterManager {
        public:
            Character();
            ~Character();
            void Entity(int pId, int pType, Texture2D pTexture, Vector2 pPosition, int pParty, bool pIsAlive, Color pColor);
            void Add(int pId);
            void Render();
            void Update();
            void Init();

            typedef struct {
                Texture2D Actors;
                //Vector2 Position2;
                Vector2 Positions;
                Rectangle Sources;
                Rectangle Destinations;
                int Id;
                int Type;
                int Health;
                int Weapon;
                int Party;
                float Altitude;
                float fallSpeed;
                float fallDuration;
                bool isAlive;
                bool isCollided;
                bool isCollidedPlayer;
                bool isCollidedProjectile;
                int PreviousHealth;
                // sActor(Vector2 sPosition)
            } Actor;

            std::vector<Actor>actors;

        private:
            Texture2D Actors[ACTORS];
            int Id;
            int Type;
            Vector2 Position;



            typedef enum {
                REBEL_SOLDIER = 0,
                IMPERIAL_SOLDIER,
            }ActorType;

    };

    class Vehicle : public CharacterManager {

        public:
            Vehicle();
            ~Vehicle();
            void Init();
            void Render();
            void Update();
            void Add(int pId);
            void Entity(int pId, int pType, Texture2D pTexture, Vector2 pPosition, bool pIsAlive, Color pColor);

            typedef enum {
                veh1 = 0,
                veh2,
                veh3,
            } VehicleType;
            

            typedef struct Vehicles {
                Texture2D Actors;
                Vector2 Positions;
                Rectangle Sources;
                Rectangle Destinations;
                int Id;
                int Type;
                int Health;
                int PreviousHealth;
                int Speed;
                int currentSpeed;
                float Altitude;
                float fallSpeed;
                float fallDuration;
                // int Weapon;
                bool Engine;
                bool isActive;
                bool isAlive;
                bool isCollided;
                bool isCollidedPlayer;
                bool isCollidedProjectile;
                bool isAirVehicle;
                bool isSpaceship;
                bool hasTakenOff;
                VehicleType type;
            } Vehicles;
    
            int RandV001;
            int RandV002;

            std::vector<Vehicles>vehicles;

            Character character;

        private:

    };

    