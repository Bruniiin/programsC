#include <raylib.h>
#include <iostream>
#include "game.hpp"


    using namespace std;

// #define REBELLION 0
// #define EMPIRE 1

Game::Game() {

    currentTime = GetTime();
    isGameActive = false;

    *WinCondition = 0;

    // parties.resize(4);

    parties.push_back(
        {
            "Rebelião",
            NULL,
            1,
            32,
            16,
            // REBELLION,
            // JEDI,
            // REBEL_SOLDIER,
            // LOC_REBEL_BASE,
        }
    );

    parties.push_back(
        {
            "Império Galáctico",
            NULL,
            0,
            32,
            16,
            // EMPIRE,
            // SITH,
            // IMPERIAL_SOLDIER,
            // IMPERIAL_BOUNTY_HUNTER,
            // LOC_IMPERIAL_BASE,
        }
    );

    // Party parties[2] = { // fixed size array, not vector
    //     {
    //         "Rebelião",
    //         NULL,
    //         0,
    //         32,
    //         16,
    //         REBELLION,
    //         (JEDI, REBEL_SOLDIER),
    //         LOC_REBEL_BASE,     
    //     },

    //     {
    //         "Império Galáctico",
    //         NULL,
    //         0,
    //         32,
    //         16,
    //         EMPIRE,
    //         (JEDI,  IMPERIAL_SOLDIER, IMPERIAL_BOUNTY_HUNTER),
    //         LOC_REBEL_BASE,     
    //     }
    // };

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


}

Game::~Game() {


}

void Game::GameBegin() { 

    // Rebels.PLY = (Empire.PLY > 0) ? 0 : 1;
    // Empire.PLY = (Rebels.PLY > 0) ? 0 : 1;  

    parties[0].PLY = (parties[1].PLY > 0) ? 0 : 1; // ugh. I prefer the cleaner objects than vectors, but this will do.

    switch(Players)
    {
        case 1:

            player.GameMode = 0;
            for(int i = 0; i < Players; i++)
            {
                players.push_back(
                    {
                    {0, 0},
                    150.f,
                    180.f,
                    LoadTexture("graphics/testsprite"),
                    true,
                    false,
                    false,
                    false,
                    false,
                    false,
                    100,
                    NULL,
                    1,
                    i,
                    {0, 0},
                    {0, 0},
                    }
                );                
            }

        break;
        case 2:

            player.GameMode = 1;
            for(int i = 0; i < Players; i++)
            {
                players.push_back(
                    {
                    {0, 0},
                    150.f,
                    180.f,
                    LoadTexture("graphics/testsprite"),
                    true,
                    false,
                    false,
                    false,
                    false,
                    false,
                    100,
                    NULL,
                    1,
                    i,
                    {0, 0},
                    {0, 0},
                    }
                );                
            }

        break;
        case 3: 
        break;
        case 4:
        break;
        default:
        break;
    }

    switch(Campaign)
    {
        case 1:
            tilemap.currentLevel = 1;
        break;
        case 2:
            tilemap.currentLevel = 2; 
        break;
        case 3:
            tilemap.currentLevel = 3;
        break;
        default:
        break;        
    }

    for(const auto& CheckParty : parties)
    {
        switch(CheckParty.party)
        {
            case EMPIRE:
            break;
            case REBELLION:
            break;
            default:
            break;
        }
    }

    for(const auto& CheckLocation : parties)
    {
        switch(CheckLocation.startLocation)
        {
            case LOC_REBEL_BASE:
            break;
            case LOC_IMPERIAL_BASE:
            break;
            case LOC_MAIN:
            break;
            default:
            break;
        }
    }

    isGameActive = true;

    // player.playerPos.push_back({0, 0});

}



void Game::GameRun() { // geralmente é draw por último na ordem. / usually draw comes last.

    if(!isGameActive && *WinCondition == 0)
    {
        GameBegin();
    }

    if(isGameActive)
    {

        player.AsyncUpdate();
        player.Update();

    }

    GameWon();

    // DrawFPS(10, 10);
    DrawText("GAME MODE ON", 20, 250, 5, RED);

}

void Game::GameWon() {


    if(player.isGameDone)
    {
        if((player.P1.type == JEDI && player.P1.state == player.GAME_SET) || (player.P2.type == JEDI && player.P2.state == player.GAME_SET))
        {
            parties.erase(parties.begin() + 1);
        }
        else if((player.P1.type == SITH && player.P1.state == player.GAME_SET) || (player.P2.type == SITH && player.P2.state == player.GAME_SET))
        {
            parties.erase(parties.begin());
        }
    } 















}