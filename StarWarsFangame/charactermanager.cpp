#include "charactermanager.hpp"
#include <raylib.h>
#include <raymath.h>

CharacterManager::CharacterManager() {

    Actors[0] = LoadTexture("graphics/testsprite.png");

}

CharacterManager::~CharacterManager() {
    
}

Rectangle CharacterManager::PlayerRec(Rectangle pPlayer1)
{
    Rectangle Rec = {pPlayer1.x, pPlayer1.y, pPlayer1.width, pPlayer1.height};
    return Rec;
}

Character::Character() {

    entitySize = 0;
    Entities = 8; // max entities.

    Actors[0] = LoadTexture("graphics/testsprite.png");

}

Character::~Character() {

    for (int i = 0; i < ACTORS; i++)
    {
        UnloadTexture(Actors[i]);    
    }

}

void Character::Init() {



    for (int i = 0; i < Entities; ++i)
    {
        if(entitySize < Entities) // not sure if these many loops are needed.
        {
                Add(entitySize);
                entitySize++;

                if(entitySize == Entities)
                    isReady = true;
        }
    }
}

// Rectangle Character::PlayerRec(Rectangle pPlayer1)
// {
    // Rectangle Rec = {pPlayer1.x, pPlayer1.y, pPlayer1.width, pPlayer1.height};
    // return Rec;
// }

void Character::Entity(int pId, int pType, Texture2D pTexture, Vector2 pPosition, int pParty, bool pIsAlive, Color pColor) {

    this->Position = pPosition;
    this->Id = pId;
    this->Type = pType;

    positions.push_back({pPosition.x, pPosition.y});
    actors.push_back({pTexture, pPosition, (Rectangle){0, 0, (float)pTexture.width, (float)pTexture.height}, (Rectangle){pPosition.x, pPosition.y, (float)pTexture.width, (float)pTexture.height}, pId, pType, 100, 0, pParty, tilemap.GroundLevel, 0, 0, true});
    //sources.push_back((Rectangle){0, 0, pTexture.width, pTexture.height});
    //destinations.push_back((Rectangle){pPosition.x, pPosition.y, pTexture.width, pTexture.height});

    //Actor* actor = new Actor;

}


void Character::Add(int pId) {

    // for (int i = 0; i < 32; i++)
        Entity(pId, 0, Actors[0], (Vector2){(float)(GetRandomValue(0, 2000)), (float)(GetRandomValue(0, 2000))}, REBEL_SOLDIER, 1, {255, 255, 255, 255}); // spawn new entity

}

void Character::Render() {

    // for(const auto& actor : actors)
    // {
    //     for(size_t i = 0; i < actors.size(); i++) {
    //         DrawTexturePro(Actors[0], actors[i].Sources, actors[i].Destinations, (Vector2){Actors->width/2, Actors->height/2}, 0, WHITE);
    //         // DrawTextureV(Actors[0], positions[i], WHITE);
    //     }
    // }

    for(const auto& actor : actors)
    {
        DrawTexturePro(Actors[0], actor.Sources, actor.Destinations, (Vector2){0, 0}, 0, WHITE); // (Vector2){Actors->width/Actors->width, Actors->height}
        DrawRectangleRec(actor.Destinations, Fade(RED, 0.5f));
    }
        // for(size_t i = 0; i < actors.size(); i++)
        // {  
        // }   

}

void Character::Update()
{

    for (auto& actor : actors)
    {
        if(actor.Altitude > tilemap.GroundLevel) // npc altitude physics
        {
            actor.Altitude -= actor.fallSpeed * actor.fallDuration;
        }

        if (actor.Altitude < tilemap.GroundLevel)
        {
            actor.Altitude = tilemap.GroundLevel;

            if(actor.fallDuration >= 1.f)
            {
                actor.Health -= actor.fallDuration;
            }

            actor.fallDuration = 0;
        }
    }

    for (auto& actor : actors)
    {



    }

    // for(auto& actor : actors)
    // {
    //     actor.isCollidedPlayer = false;

    //     for(size_t j = 0; j < actors.size(); j++) 
    //     {
    //         if (CheckCollisionRecs(PlayerRec(player.P1.destination), actors[j].Destinations)) 
    //         {
    //             actors[j].isCollidedPlayer = true;
    //             break;
    //         }
    //         else if (CheckCollisionRecs(PlayerRec(player.P2.destination), actors[j].Destinations))
    //         {
    //             actors[j].isCollidedPlayer = true;
    //             break;
    //         }
    //     }
    //     if(actor.isCollidedPlayer)
    //     {
    //         // CloseWindow();
    //     }
    // }

    // // for(auto& actor : actors) // checks for collision.
    // // {
    // //     for(auto& position : positions)


    // //     if(actor.isCollidedPlayer)
    // //     {
    // //         // CloseWindow();
    // //     }
    // // }


    // for(auto& actor : actors) // set all entity collisions to false before starting loop.
    // {
    //     actor.isCollided = false;

    //     for(size_t i = 0; i < actors.size(); i++)
    //     {
    //         // actors[i].isCollided = false;

    //             for(size_t j = 0; j < actors.size(); j++) 
    //         {
    //             if (i != j && CheckCollisionRecs(actors[i].Destinations, actors[j].Destinations)) 
    //             {
    //                 actors[i].isCollided = true;
    //                 break;
    //             }
            
            
    //             // actors[i].isCollided = CheckCollisionRecs(destinations[i], destinations[i]);

    //             // for (auto it = actors.begin(); it != actors.end(); ) 
    //             // {
    //             //     if(it->isCollided) {
    //             //         it = actors.erase(it);
    //             //     }
    //             //     else {
    //             //         ++it; 
    //             //     }
    //             // }
    //         }
    //     }
    //     if(actor.isCollided)
    //     {
    //         // EndDrawing();
    //     }
    // }

    // for(auto& actor : actors)
    // {
        
    //     actor.isCollidedProjectile = false;

    //     for(size_t i = 0; i < laser.positions.size(); i++)
    //     {
    //         for(size_t j = 0; j < actors.size(); i++)
    //         {
    //             if (CheckCollisionPointRec(laser.positions[i], actors[j].Destinations))
    //             {
    //                 CloseWindow();
    //                 actors[i].isCollidedProjectile = true;
    //                 break;
    //             }
    //         }
    //     }
    // } 

    // for(auto& actor : actors)
    // {
    //     if(actor.isCollidedProjectile)
    //     {
    //         CloseWindow();
    //         actor.Health -= GetRandomValue(20, 50);
    //         // DrawText("COLL CHECKED 2", 100, 100, 20, RED);
    //     }

    //         if(actor.Health <= 0)
    //         {
    //             actor.isAlive = false;
    //         }
    // }

    for (auto it = actors.begin(); it != actors.end(); ) // iterates to check if npc was defeated.
    {   
        if(!it->isAlive) {
            it = actors.erase(it);
        }
        else {
            ++it;
        }
    } 

}

Vehicle::Vehicle() {

    entitySize = 0;
    Entities = 4;

    Actors[0] = LoadTexture("graphics/testsprite.png");
}

Vehicle::~Vehicle() {

    
}

void Vehicle::Init() {

    for (int i = 0; i < Entities; ++i)
    {
        if(entitySize < Entities) // not sure if these many loops are needed.
        {
                Add(entitySize);
                entitySize++;

                // if(entitySize == Entities)
                //     isReady = true;
        }
    }

}

void Vehicle::Add(int pId) {

    Entity(pId, 0, Actors[0], (Vector2){(float)(GetRandomValue(0, 2000)), (float)(GetRandomValue(0, 2000))}, 1, {0, 255, 255, 255}); // spawn new entity

}

void Vehicle::Entity(int pId, int pType, Texture2D pTexture, Vector2 pPosition, bool pIsAlive, Color pColor)
{
    vehicles.push_back({pTexture, pPosition, (Rectangle){0, 0, (float)pTexture.width, (float)pTexture.height}, (Rectangle){pPosition.x, pPosition.y, (float)pTexture.width, (float)pTexture.height}, pId, pType, 100, 0, 10, 0, tilemap.GroundLevel, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1});
}

void Vehicle::Render() {

    for (const auto& vehicle : vehicles)
    {
        DrawTexturePro(Actors[0], vehicle.Sources, vehicle.Destinations, (Vector2){0, 0}, 0, RED);
        // DrawRectangleRec(vehicle.Destinations, RED);
    }

}

void Vehicle::Update() {

    for(auto& vehicle : vehicles)
    {
        if(vehicle.Altitude > tilemap.GroundLevel) // vehicle altitude physics
        {
            vehicle.Altitude -= vehicle.fallSpeed * vehicle.fallDuration;
        }

        if (vehicle.Altitude < tilemap.GroundLevel)
        {
            vehicle.Altitude = tilemap.GroundLevel;

            if(vehicle.fallDuration >= 1.f)
            {
                vehicle.Health -= vehicle.fallDuration;
            }

            vehicle.fallDuration = 0;
        }

        // if(vehicle.Altitude > tilemap.GroundLevel) // vehicle altitude physics for NPCs
        // {
        //     player.P1.Altitude -= player.fallSpeed * player.fallDuration;

        //     if(player.P1.Altitude < tilemap.GroundLevel)
        //     {
        //         player.P1.Altitude == tilemap.GroundLevel;
        //         player.P1.Health -= player.fallDuration;
        //         player.fallDuration = 0;
        //     }
        // }


    }

        for (auto it = vehicles.begin(); it != vehicles.end(); )
        {   
            if(!it->isAlive) {
                it = vehicles.erase(it);
            }
            else {
                ++it;
            }
        } 

    //for(auto& vehicle : vehicles)
    //{
        // vehicle.isCollided = false;

        // if (CheckCollisionRecs(PlayerRec(player.P1.destination), vehicle.Destinations) || CheckCollisionRecs(pPosition001, vehicle.Destinations)) 
        // {
        //     vehicle.isCollided = true;
        //     break;
        // }

        // for (auto& laser : laser.positions)
        // {
        //     if (CheckCollisionPointRec(laser, vehicle.Destinations))
        //     {
        //         vehicle.isCollidedProjectile = true;
        //         break;
        //     }
        // }

        // if (vehicle.isCollided)
        // {

        //     if(player.ON_FOOT)
        //     {

        //         DrawTextEx(GetFontDefault(), TextFormat("Press %d to enter", KEY_E), (Vector2){vehicle.Destinations.x, vehicle.Destinations.y}, 30, 10, RED);
        //         if((IsKeyPressed(KEY_E) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP)));
        //         {
        //             player.P1.mode = player.ON_VEHICLE;
        //         }

        //         if(vehicle.Altitude > tilemap.GroundLevel)
        //         {
        //             player.P1.Altitude -= player.fallSpeed * player.fallDuration;

        //             if(player.P1.Altitude < tilemap.GroundLevel)
        //             {
        //                 player.P1.Altitude == tilemap.GroundLevel;
        //                 player.P1.Health -= player.fallDuration;
        //                 player.fallDuration = 0;
        //             }
        //         }
        //     }

        //     if (player.ON_VEHICLE)
        //     {

        //         vehicle.Destinations = pPosition001;

        //         if(IsKeyPressed(KEY_E))
        //         {
        //             player.P1.mode = player.ON_FOOT;
        //         }

        //         if(vehicle.Altitude <= tilemap.GroundLevel)
        //             vehicle.Altitude == tilemap.GroundLevel;


        //         if(IsKeyPressed(KEY_R))
        //             vehicle.Engine = !vehicle.Engine;

        //         if(vehicle.isAirVehicle)
        //         {
        //             if(IsKeyDown(KEY_DOWN))
        //                 vehicle.Altitude += 1;
        //             if(IsKeyDown(KEY_UP))
        //                 vehicle.Altitude -= 1;
        //                 player.P1.Altitude = vehicle.Altitude;

        //             if(vehicle.hasTakenOff)
        //             {
        //                 player.P1.Location = 0;
        //             }

        //             if(vehicle.isSpaceship)
        //             {
        //                 if(vehicle.Altitude >= 10)
        //                 {
        //                     if(IsKeyPressed(KEY_G))
        //                     {
        //                         vehicle.hasTakenOff = true;
        //                     }
        //                 }
        //             }
        //         }
        //     }
        // }



        // if (vehicle.isCollidedProjectile)
        // {
        //     vehicle.PreviousHealth = vehicle.Health;
        //     vehicle.Health -= GetRandomValue(RandV001, RandV002);
        //     vehicle.PreviousHealth -= vehicle.Health;
        //     DrawText(TextFormat("-%d", vehicle.PreviousHealth), vehicle.Destinations.x, vehicle.Destinations.y, 10, RED);
        // }

        // if (vehicle.Health <= 20)
        // {
        //     vehicle.Engine = false;

        //     if (vehicle.Health <= 0)
        //     {
        //         vehicle.isAlive = false;
        //     }
        // }
        // else
        // {
        //     vehicle.Engine = true;
        // }

        // if (!vehicle.Engine)
        // {
        //     if (vehicle.Speed >= 1)
        //     {
        //         t += 0.1 * GetFrameTime();
        //         vehicle.Speed = Lerp(vehicle.currentSpeed, 0, t);
        //     }
        //     else
        //         vehicle.Speed = 0;
        // }

    //}

}