#include "charactermanager.hpp"
#include <raylib.h>

CharacterManager::CharacterManager() {

    entitySize = 0;
    Entities = 8; // max entities.

}

CharacterManager::~CharacterManager() {
    
}

CharacterManager::Character::Character() {

    Actors[0] = LoadTexture("graphics/testsprite.png");




}

CharacterManager::Character::~Character() {

    for (int i = 0; i < ACTORS; i++)
    {
        UnloadTexture(Actors[i]);    
    }

}

void CharacterManager::Update() {

    for (int i = 0; i < Entities; ++i)
    {
        if(entitySize < Entities) 
        {
                Actor.Update(entitySize);
                entitySize++;

                if(entitySize == Entities)
                    isReady = true;
        }
    }

    Actor.Render();    







    //Actor.positions.erase(Actor.positions.begin()); 
    //if(!isReady)

}

void CharacterManager::Character::Entity(int pId, int pType, Texture2D pTexture, Vector2 pPosition, bool pIsAlive, Color pColor) {

    this->Position = pPosition;
    this->Id = pId;
    this->Type = pType;

    positions.push_back({pPosition.x, pPosition.y});
    actors.push_back({pTexture, pPosition, (Rectangle){0, 0, (float)pTexture.width, (float)pTexture.height}, (Rectangle){pPosition.x, pPosition.y, (float)pTexture.width, (float)pTexture.height}, pId, pType, 100, 0, true});
    //sources.push_back((Rectangle){0, 0, pTexture.width, pTexture.height});
    //destinations.push_back((Rectangle){pPosition.x, pPosition.y, pTexture.width, pTexture.height});

    //Actor* actor = new Actor;

}


void CharacterManager::Character::Update(int pId) {

    // for (int i = 0; i < 32; i++)
        Entity(pId, 0, Actors[0], (Vector2){(float)(GetRandomValue(0, 2000)), (float)(GetRandomValue(0, 2000))}, 1, {255, 255, 255, 255}); // spawn new entity

}

void CharacterManager::Character::Render() {

    for(const auto& actor : actors)
    {
        for(size_t i = 0; i < actors.size(); i++) {
            DrawTexturePro(Actors[0], actors[i].Sources, actors[i].Destinations, (Vector2){Actors->width/2, Actors->height/2}, 0, WHITE);

        }
    }

    for(auto& actor : actors) // set all entity collisions to false before starting loop.
    {
            actor.isCollided = false;
    }
        for(size_t i = 0; i < actors.size(); i++)
        {
            // actors[i].isCollided = false;

              for(size_t j = 0; j < actors.size(); j++) 
            {
                if (i != j && CheckCollisionRecs(actors[i].Destinations, actors[j].Destinations)) 
                {
                    // actors[i].isCollided = true;
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
            }
        }

    for(auto& actor : actors)
    {
        actor.isCollidedPlayer = false;
    }

    for(size_t j = 0; j < actors.size(); j++) 
    {
        if (CheckCollisionRecs(player.P1.destination, actors[j].Destinations)) 
        {
            actors[j].isCollidedPlayer = true;
            break;
        }
    }


    for(auto& actor : actors) 
    {
        // for(auto& position : positions)
        if(actor.isCollided)
        {
            EndDrawing();
        }

        if(actor.isCollidedPlayer)
        {
            EndDrawing();
        }
    }

    for(auto& actor : actors)
    {
        for(size_t i = 0; i < laser.positions.size(); i++)
        {
            actors[i].isCollidedProjectile = false;

            for(size_t j = 0; j < actors.size(); i++)
            {
                if (CheckCollisionPointRec(laser.positions[i], actors[j].Destinations))
                {
                    CloseWindow();
                    actors[i].isCollidedProjectile = true;
                    break;
                }
            }
        }
    } 

    for(auto& actor : actors)
    {
        if(actor.isCollidedProjectile)
        {
            actor.Health -= GetRandomValue(20, 50);
        }

            if(actor.Health <= 0)
            {
                actor.isAlive = false;
            }
    }

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

