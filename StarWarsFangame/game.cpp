#include <raylib.h>
#include <iostream>
#include "game.hpp"
#include <raymath.h>

using namespace std;

// #define REBELLION 0
// #define EMPIRE 1

Game::Game()
{

    currentTime = GetTime();
    isGameActive = false;

    isGameRunning = true;

    GameMode = false;

    *WinCondition = 0;

    scenario.hasRenderingBegan = 1;

    entities = 0;

    // parties.resize(4);

    // char * pointer = "TESTPOINTER";

    // char ** p1 = &pointer;

}

// parties.push_back(
//     {
//         "Rebelião",
//         NULL,
//         0,
//         32,
//         16,
//         // REBELLION,
//         // JEDI,
//         // REBEL_SOLDIER,
//         // LOC_REBEL_BASE,
//     }
// );

// parties.push_back(
//     {
//         "Império Galáctico",
//         NULL,
//         0,
//         32,
//         16,
//         // EMPIRE,
//         // SITH,
//         // IMPERIAL_SOLDIER,
//         // IMPERIAL_BOUNTY_HUNTER,
//         // LOC_REBEL_BASE,
//     }
// );

// Rebels = (Party)
// {
//     .name = "Rebelião",
//     .PLY = 0,
//     .MAXCOUNT_PLY = 32,
//     .MAXCOUNT_VEH = 16,
//     .party = {REBELLION},
//     .classType = {JEDI, REBEL_SOLDIER},
//     .startLocation = {LOC_REBEL_BASE},
// };

// Empire = (Party)
// {
//     .name = "Império Galáctico",
//     .PLY = 1,
//     .MAXCOUNT_PLY = 32,
//     .MAXCOUNT_VEH = 16,
//     .party = {EMPIRE},
//     .classType = {SITH, IMPERIAL_SOLDIER, IMPERIAL_BOUNTY_HUNTER},
//     .startLocation = {LOC_REBEL_BASE},
// };

Game::~Game()
{

}

void Game::GameBegin()
{

    player.GameMode = Players - 1;
    // player.GameMode = GameMode;
    pLevel = scenario.currentLevel;;

    // for (int i = 0; i < actors; ++i)
    // {
    //     if(entities < actors)
    //     {
    //             character.Add(entities);
    //             entities++;
    //     }
    // }

    // entities = 0;

    // for (int i = 0; i < vehicles; ++i)
    // {
    //     if(entities < vehicles)
    //     {
    //             vehicle.Add(entities);
    //             entities++;
    //     }
    // } 

    character.Init();
    vehicle.Init();

    Party parties[2] = 
    {
        {"Rebelião", NULL, 0, 32, 16},
        {"Império Galáctico", NULL, 0, 32, 16}
    };

    isGameActive = true;

}

void Game::GameRun() 
{

    if (isGameRunning)
    {
        if (!isGameActive && *WinCondition == 0)
        {
            GameBegin();
        }

        if (isGameActive) // gameplay loop
        {
            Update();
            Render();
        }
    }

    // characterManager.PlayerRec(Position()); // debug
    //  characterManager.Update();
    //  Player();
    //  player.Update();
    //  if(player.status == 0)
    //  {
    //      RenderManager();
    //      player.status = 1;
    //  }
    //  ui.Element(0, {200, 200, 100, 100}, {200, 200}, true, WHITE);
    //  DrawFPS(10, 10);
    //  DrawText("GAME MODE ON", 20, 250, 5, RED);
    //  for(auto& Ui: ui) {
    //      ui.Element();
    //  }
}

void Game::Update()
{

    float dt = GetFrameTime();
    scenario.LoadCollision();
    player.PlayerUpdate();
    player.InputUpdate();
    player.AsyncUpdate();
    ui.Update();
    character.Update();
    vehicle.Update();
    laser.Update();

    // for (auto& lasers : laser.lasers)

    for (size_t i = 0; i < parties.size(); i++)
    {
        if (!parties[i].isActive)
        {
            GameWon();
        }
    }

    player.FireDelay += 1.f * dt;

    if(player.P1.isFiring && player.FireDelay >= player.FireSpeed) // && player.FireDelay > 1.f) // player.FireSpeed && !P1.hasStartedFiring)
    {       

        laserDest = {player.P1.Angle.x, player.P1.Angle.y};
        laser.lasers.push_back({player.P1.playerPos, laserDest, 7, true, BLUE});
        player.FireDelay = 0;

    }

    for (auto &actor : character.actors)
    {
        actor.isCollidedPlayer = false;

        // for (size_t j = 0; j < character.actors.size(); j++)
        {
            if (CheckCollisionRecs(player.P1.destination, actor.Destinations))
            {
                if (player.P1.destination.x + player.P1.destination.width > actor.Destinations.x)
                {
                    player.P1.playerPos.x = actor.Destinations.x - player.P1.destination.width;
                }

                if (player.P1.playerPos.x < actor.Destinations.x + actor.Destinations.width)
                {
                    player.P1.playerPos.x = actor.Destinations.x + actor.Destinations.width;
                }

                if (player.P1.playerPos.y < actor.Destinations.y + actor.Destinations.height)
                {
                    player.P1.playerPos.y = actor.Destinations.y + actor.Destinations.height;
                }

                if (player.P1.playerPos.y + player.P1.destination.height > actor.Destinations.y)
                {
                    player.P1.playerPos.y = actor.Destinations.y - player.P1.destination.height;
                }
            }
            // else if (CheckCollisionRecs(Position(1), actor.Destinations))
            // {
            //     character.actors[j].isCollidedPlayer = true;
            //     break;
            // }
        }
        if (actor.isCollidedPlayer)
        {
            // if (player.P1.playerPos.x + player.P1.destination.width > actor.Destinations.x && player.P1.playerPos.x < actor.Destinations.x)
            // {
            //     player.P1.playerPos.x = actor.Destinations.x - player.P1.destination.width;
            // }

            // if (player.P1.playerPos.x < actor.Destinations.x + actor.Destinations.width && player.P1.playerPos.x > actor.Destinations.x)
            // {
            //     player.P1.playerPos.x = actor.Destinations.x + actor.Destinations.width;
            // }

            // if (player.P1.playerPos.y < actor.Destinations.y + actor.Destinations.height && player.P1.playerPos.y > actor.Destinations.y)
            // {
            //     player.P1.playerPos.y = actor.Destinations.y + actor.Destinations.height;
            // }

            // if (player.P1.playerPos.y + player.P1.destination.height > actor.Destinations.y && player.P1.playerPos.y < actor.Destinations.y)
            // {
            //     player.P1.playerPos.y = actor.Destinations.y - player.P1.destination.height;
            // }
        }



    }

    // for(auto& actor : actors) // checks for collision.
    // {
    //     for(auto& position : positions)
    //     if(actor.isCollidedPlayer)
    //     {
    //         // CloseWindow();
    //     }
    // }

    for (auto &actor : character.actors)
    {
        actor.isCollided = false;

        for (size_t i = 0; i < character.actors.size(); i++)
        {
            // actors[i].isCollided = false;

            for (size_t j = 0; j < character.actors.size(); j++)
            {
                if (i != j && CheckCollisionRecs(character.actors[i].Destinations, character.actors[j].Destinations))
                {
                    character.actors[i].isCollided = true;
                    break;
                }

                // actors[i].isCollided = CheckCollisionRecs(destinations[i], destinations[i]);

                // for (auto it = actors.begin(); it != actors.end(); )
                // {
                //     if(it->isCollided) {
                //         it = actors.erase(it);
                //     }
                //     else {
                //         ++it;
                //     }
                // }
                // if(actor.isCollided)
                // {
                //     if(character.actors[i].Destinations.x + character.actors[i].Destinations.width > )
                // }
                if (character.actors[i].isCollided)
                {
                    if (character.actors[i].Destinations.x + character.actors[j].Destinations.width > character.actors[i].Destinations.x && character.actors[j].Destinations.x < character.actors[i].Destinations.x)
                    {
                        character.actors[j].Destinations.x = character.actors[i].Destinations.x - character.actors[j].Destinations.width;
                    }

                    if (character.actors[j].Destinations.x < character.actors[i].Destinations.x + character.actors[i].Destinations.width && character.actors[j].Destinations.x > character.actors[i].Destinations.x)
                    {
                        character.actors[j].Destinations.x = character.actors[i].Destinations.x + character.actors[i].Destinations.width;
                    }

                    if (character.actors[j].Destinations.y < character.actors[i].Destinations.y + character.actors[i].Destinations.height && character.actors[j].Destinations.y > character.actors[i].Destinations.y)
                    {
                        character.actors[j].Destinations.y = character.actors[i].Destinations.y + character.actors[j].Destinations.height;
                    }

                    if (character.actors[j].Destinations.y + character.actors[j].Destinations.height > character.actors[i].Destinations.y && character.actors[j].Destinations.y < character.actors[i].Destinations.y)
                    {
                        character.actors[j].Destinations.y = character.actors[i].Destinations.y - character.actors[j].Destinations.height;
                    }
                }
            }
        }
    }

    for (auto &actor : character.actors)
    {
        for (auto &lasers : laser.lasers)
        {
            actor.isCollidedProjectile = false;
            //for (size_t i = 0; i < laser.lasers.size(); i++)
            {
                //for (size_t j = 0; j < character.actors.size(); i++)
                {
                    if (CheckCollisionPointRec(lasers.pPosition, actor.Destinations))
                    {
                        actor.isCollidedProjectile = true;
                        lasers.isAlive = false;
                        break;
                    }
                }
            }
        }
    }

    for (auto &actor : character.actors)
    {
        actor.PreviousHealth = actor.Health;

        if (actor.isCollidedProjectile)
        {
            actor.Health -= GetRandomValue(15, 35);
            actor.PreviousHealth -= actor.Health;
            DrawText(TextFormat("-%d", actor.PreviousHealth), actor.Destinations.x, actor.Destinations.y, 10, RED);
        }

        if (actor.Health <= 0)
        {
            actor.isAlive = false;
        }
    }

    for (auto &vehicle : vehicle.vehicles) // collision detection
    {
        vehicle.isCollided = false;

        if (CheckCollisionRecs(Position(0), vehicle.Destinations)) //|| CheckCollisionRecs(pPosition001, vehicle.Destinations))
        {
            vehicle.isCollidedPlayer = true;
            break;
        }

        for (auto &actor : character.actors)
        {
            if (CheckCollisionRecs(actor.Destinations, vehicle.Destinations)) //|| CheckCollisionRecs(pPosition001, vehicle.Destinations))
            {
                vehicle.isCollided = true;
                break;
            }
            if (vehicle.isCollided)
            {
                if (actor.Destinations.x + actor.Destinations.width > vehicle.Destinations.x && actor.Destinations.x < vehicle.Destinations.x)
                {
                    actor.Destinations.x = vehicle.Destinations.x - actor.Destinations.width;
                }

                if (actor.Destinations.x < vehicle.Destinations.x + vehicle.Destinations.width && actor.Destinations.x > vehicle.Destinations.x)
                {
                    actor.Destinations.x = vehicle.Destinations.x + vehicle.Destinations.width;
                }

                if (actor.Destinations.y < vehicle.Destinations.y + vehicle.Destinations.height && actor.Destinations.y > vehicle.Destinations.y)
                {
                    actor.Destinations.x = vehicle.Destinations.y + actor.Destinations.height;
                }

                if (actor.Destinations.y + actor.Destinations.height > vehicle.Destinations.y && actor.Destinations.y < vehicle.Destinations.y)
                {
                    actor.Destinations.y = vehicle.Destinations.y - actor.Destinations.height;
                }
            }
    
            for (auto &lasers : laser.lasers)
            {
                if (CheckCollisionPointRec(lasers.pPosition, vehicle.Destinations))
                {
                    vehicle.isCollidedProjectile = true;
                    break;
                }
            }
        }
    }

    for (auto &vehicle : vehicle.vehicles)
    {

        if (vehicle.isCollidedPlayer)
        {
            if (IsKeyPressed(KEY_F))
                vehicle.Engine = !vehicle.Engine;

            if (player.P1.isOnVehicle == false)
            {

                DrawTextEx(GetFontDefault(), TextFormat("Press %s to enter", KEY_E), (Vector2){vehicle.Destinations.x, vehicle.Destinations.y}, 30, 10, RED);
                if (IsKeyPressed(KEY_E)) // || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP));
                {
                    player.P1.isOnVehicle = true;
                }

                // if(vehicle.Altitude > scenario.GroundLevel) // vehicle altitude physics
                // {
                //     player.P1.Altitude -= player.fallSpeed * player.fallDuration;

                //     if(player.P1.Altitude < scenario.GroundLevel)
                //     {
                //         player.P1.Altitude == scenario.GroundLevel;
                //         player.P1.Health -= player.fallDuration;
                //         player.fallDuration = 0;
                //     }
                // }
            }

            if (player.P1.isOnVehicle == true)
            {
                vehicle.Destinations = player.P1.destination;

                if (IsKeyPressed(KEY_T))
                {
                    player.P1.isOnVehicle = false;
                }

                if (vehicle.Altitude <= scenario.GroundLevel)
                    vehicle.Altitude = scenario.GroundLevel;

                if (vehicle.isAirVehicle)
                {
                    player.P1.Altitude = vehicle.Altitude;
                    if (IsKeyDown(KEY_DOWN))
                        vehicle.Altitude += 0.1f;
                    if (IsKeyDown(KEY_UP))
                        vehicle.Altitude -= 0.1f;

                    if (vehicle.isSpaceship)
                    {
                        if (vehicle.Altitude >= 10)
                        {
                            if (IsKeyPressed(KEY_G))
                            {
                                vehicle.hasTakenOff = true;
                            }
                        }

                        if (vehicle.hasTakenOff)
                        {
                            player.P1.Location = ZONE_SPACE;
                        }
                    }
                }
            }

            if (player.P1.isOnVehicle == true)
            {
                vehicle.Destinations = player.P1.destination;

                if (IsKeyPressed(KEY_T))
                {
                    player.P1.isOnVehicle = false;
                }

                if (vehicle.Altitude <= scenario.GroundLevel)
                    vehicle.Altitude = scenario.GroundLevel;

                if (vehicle.isAirVehicle)
                {
                    if (IsKeyDown(KEY_DOWN))
                        vehicle.Altitude += 0.1f;
                    if (IsKeyDown(KEY_UP))
                        vehicle.Altitude -= 0.1f;
                    player.P1.Altitude = vehicle.Altitude;

                    if (vehicle.hasTakenOff)
                    {
                        player.P1.Location = 0;
                    }

                    if (vehicle.isSpaceship)
                    {
                        if (vehicle.Altitude >= 10)
                        {
                            if (IsKeyPressed(KEY_G))
                            {
                                vehicle.hasTakenOff = true;
                            }
                        }
                    }
                }
            }
        }
    }

    for (auto &vehicle : vehicle.vehicles)
    {
        vehicle.PreviousHealth = vehicle.Health;

        if (vehicle.isCollidedProjectile)
        {
            vehicle.Health -= GetRandomValue(5, 15);
            vehicle.PreviousHealth -= vehicle.Health;
            DrawText(TextFormat("-%d", vehicle.PreviousHealth), vehicle.Destinations.x, vehicle.Destinations.y, 10, RED);
        }

        if (vehicle.Health <= 20)
        {
            vehicle.Engine = false;

            if (vehicle.Health <= 0)
            {
                vehicle.isAlive = false;
            }
        }
        else
        {
            vehicle.Engine = true;
        }

        if (!vehicle.Engine)
        {
            if (vehicle.Speed >= 1)
            {
                t += 0.1 * GetFrameTime();
                vehicle.Speed = Lerp(vehicle.currentSpeed, 0, t);
            }
            else
                vehicle.Speed = 0;
        }
    }

    // for(auto& laser: lasers) {
    //     laser.Update();
    // }
    // for(auto& actor : character.actors)
    //     {
    //         for(size_t i = 0; i < character.actors.size(); i++)
    //         {
    //             // character.actors[i].isCollided = false;
    //             //character.actors[i].isCollidedProjectile = false;
    // //            for(int j = 0; j < character.actors.size(); i++)
    // //            {
    //                 if (CheckCollisionPointRec(player.P1.playerPos, character.actors[i].Destinations))
    //                 {
    //                     character.actors[i].isCollided = true;
    //                     break;
    //                 }
    //         //    }
    //         }
    //     }
}

void Game::Render()
{

    if (player.GameMode)
    {
        BeginTextureMode(player.CameraP1);
        ClearBackground(WHITE);
        BeginMode2D(player.cameraposp1);
    }
    else
    {
        BeginTextureMode(player.CameraP1fullscr);
        ClearBackground(WHITE);
        BeginMode2D(player.cameraPosFull);
    }
    
    RenderManager(); // método de renderização de entidades / entity rendering method

    EndMode2D();
    EndTextureMode();

    if (player.GameMode)
    {

        BeginTextureMode(player.CameraP2);
        ClearBackground(WHITE);
        BeginMode2D(player.cameraposp2);

        RenderManager();

        EndMode2D();
        EndTextureMode();

    }

    if (player.GameMode)
    {
        player.cameraposp1.target = (Vector2){player.P1.playerPos.x, player.P1.playerPos.y};
        player.cameraposp2.target = (Vector2){player.P2.playerPos.x, player.P2.playerPos.y};
        DrawTextureRec(player.CameraP1.texture, player.splitscreen, (Vector2){0, 0}, WHITE);
        DrawTextureRec(player.CameraP2.texture, player.splitscreen, (Vector2){0, GetScreenHeight() / 2.0f}, WHITE);
    }
    else
    {
        player.cameraPosFull.target = (Vector2){player.P1.playerPos.x, player.P1.playerPos.y};
        DrawTextureRec(player.CameraP1fullscr.texture, player.fullscr, (Vector2){0, 0}, WHITE);
    }
}

void Game::RenderManager()
{

    scenario.Render();
    vehicle.Render();
    character.Render();
    player.Render();
    laser.Render();
    ui.Render();

    DrawRectangleRec(player.P1.collision, RED);

    // for (auto& lasers : laser.slasers)
    // DrawRectangleRec(Position(), RED);
    // for(auto& laser: lasers) {
    //     laser.Draw();
    // }
    // DrawRectangleRec(player.P1.destination, RED);
    // for(size_t i = 0; i < character.actors.size(); i++)
    // {
    //     DrawRectangleRec(character.actors[i].Destinations, RED);
    // }
}

void Game::Element()
{

}

int Game::Reset()
{
    return 0;
}

Rectangle Game::Position(int pPlayer)
{

    switch (pPlayer)
    {
    case 0:
        return player.P1.destination;
        break;
    case 1:
        return player.P2.destination;
        break;
    }
}

// void Game::ItemTest(int pId, Texture2D pTexture, bool pColl, bool pActive)
// {

// }

void Game::GameWon()
{

    if (player.isGameDone)
    {
        if ((player.P1.type == JEDI && player.P1.state == player.GAME_SET) || (player.P2.type == JEDI && player.P2.state == player.GAME_SET))
        {
            parties.erase(parties.begin() + 1);
        }
        else if ((player.P1.type == SITH && player.P1.state == player.GAME_SET) || (player.P2.type == SITH && player.P2.state == player.GAME_SET))
        {
            parties.erase(parties.begin());
        }
    }

    // if(!player.P1.isAlive) { *WinCondition = 2; } // jogador 1 perdeu
    // if(!player.P1.isAlive) { *WinCondition = 1; } // jogador 2 perdeu
    //    if(WinCondition > 2) { std::cout << "OVERFLOW! CRASH THE PROGRAM!" << endl; } // minha tentativa de programmer's humor :D
    // UnloadTexture(player.player02.player);
    // switch(WinCondition)
    // {
    // case 1:
    // break;
    // case 2:
    // break;
    // default:
    // }
    // for(int i = 0; i < Players; i++)
    // {
    //     cameras.push_back(
    //         {
    //             (Vector2){GetScreenWidth()/2, GetScreenHeight()/2},
    //             (Vector2){player.P1.playerPos.x, player.P1.playerPos.y},
    //             0.0f,
    //             0.4f,
    //         }
    //     );
    //     renders.push_back({});
    // }
    // if(!parties[0].PLY) // if PLY on first team is set to 0, meaning it's p1's team. PLY 0 is player 1, PLY 1 is player 2.
    // {
    //     player.P1.type = player.JEDI; player.P2.type = player.SITH;
    // }
    // else
    // {
    //     player.P1.type = player.SITH; player.P2.type = player.JEDI;
    // }
    // if(!parties[0].PLY)
    // {
    //     player.P1.type = player.JEDI; player.P2.type = player.SITH;
    // }
    // else
    // {
    //     player.P1.type = player.SITH; player.P2.type = player.JEDI;
    // }
    // for(const auto& CheckParty : parties)
    // {
    //     switch(CheckParty.party)
    //     {
    //         case EMPIRE:
    //         break;
    //         case REBELLION:
    //         break;
    //         default:
    //         break;
    //     }
    // }
    // for(const auto& CheckLocation : parties)
    // {
    //     switch(CheckLocation.startLocation)
    //     {
    //         case LOC_REBEL_BASE:
    //         break;
    //         case LOC_IMPERIAL_BASE:
    //         break;
    //         case LOC_MAIN:
    //         break;
    //         default:
    //         break;
    //     }
    // }
    // Rebels.PLY = (Empire.PLY > 0) ? 0 : 1;
    // Empire.PLY = (Rebels.PLY > 0) ? 0 : 1;
    // parties[0].PLY = (parties[1].PLY > 0) ? 0 : 1;

}