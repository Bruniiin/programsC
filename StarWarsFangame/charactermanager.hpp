#pragma once
#include <raylib.h>
#include <vector>
#include "laser.hpp"
#include "playermanager.hpp"

#define ACTORS 32

class CharacterManager { //: public PlayerManager {

    public:
        CharacterManager();
        ~CharacterManager();
        class Character { 
            public:
                Character();
                ~Character();
                void Entity(int pId, int pType, Texture2D pTexture, Vector2 pPosition, bool pIsAlive, Color pColor);
                void Update(int pId);
                void Render();
                typedef struct Actor {
                    Texture2D Actors;
                    //Vector2 Position2;
                    Vector2 Positions;
                    Rectangle Sources;
                    Rectangle Destinations;
                    int Id;
                    int Type;
                    int Health;
                    int Weapon;
                    bool isAlive;
                    bool isCollided;
                    bool isCollidedPlayer;
                    bool isCollidedProjectile;
                    // sActor(Vector2 sPosition)
                } Actor;

                // typedef struct Positions {
                //     Vector2 Position;
                //     bool isActive;
                //     // bool canMove;
                // } Positions;

                std::vector<Vector2>positions;
                std::vector<Rectangle>sources;
                std::vector<Rectangle>destinations;                
                //std::vector<Positions>positions2;
                std::vector<Actor>actors;
                std::vector<bool>collisions;

            private:
                Texture2D Actors[ACTORS];
                int Id;
                int Type;
                Vector2 Position;

                Laser laser;

                typedef enum {
                    REBEL_SOLDIER = 0,
                    IMPERIAL_SOLDIER,
                }ActorType;

                PlayerManager player;

        };
        void Update();

    private:
        Character Actor;

        int Entities;
        int entitySize;
        bool isReady;
        // std::vector<CharacterManager::Actor>actors;

        // typedef struct Actor{

        // } Actor;


};

    