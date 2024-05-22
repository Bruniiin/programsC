#include <raylib.h>
#include "playermanager.hpp"
#include "tilemapmanager.hpp"
//#include "coroutinemanager.hpp"
#include <vector>

#define PLAYER_COUNT 4

class Game {

    public:
        Game();
        ~Game();
        void GameBegin();
        void GameRun();
        void GameWon();
        void Player();

    typedef enum {
        ZONE_OUTSIDE = 0,
        ZONE_INSIDE,
    } ZoneVar;

    ZoneVar zone;

    typedef enum {
        LOC_REBEL_BASE = 0,
        LOC_IMPERIAL_BASE,
        LOC_MAIN,
    } LocationVar;

    LocationVar location;

    typedef enum {
        MODE_ONE_PLAYER = 0,
        MODE_TWO_PLAYER,
        MODE_THREE_PLAYER,
        MODE_FOUR_PLAYER,
    } Mode;

    // GameMode mode;

    bool GameMode;

    typedef enum {
        JEDI = 0,
        SITH,
        REBEL_SOLDIER,
        IMPERIAL_SOLDIER,
        IMPERIAL_BOUNTY_HUNTER,
    } CharType;

    CharType type;

    typedef enum {
        ON_FOOT = 0,
        VEH_AIRSPEEDER,
        VEH_SNOWSPEEDER, 
        VEH_X_WING,
        VEH_FIGHTER,
    } CharMode;

    CharMode state;

    typedef enum {
        REBELLION = 0,
        EMPIRE = 1,
    } PartyType;

    PartyType party;

    typedef enum {
        OBJ_AIRSPEEDER,
        OBJ_SNOWSPEEDER,
        OBJ_X_WING,
        OBJ_FIGHTER,

        ENT_WALKER,
        PHY_TOW_CABLE,   

        // ENT são entidades. 
        // OBJ são entidades estáticas. 
        // PHY são entidades estáticas que usam física.
    } EntityType;

    typedef enum {
        UI_STATUS = 0,
        UI_EQUIPMENT,
        UI_ACTION,
        UI_OBJECTIVE,
        UI_SHOW_MODE,
    } Ui;

typedef enum {
    IN_GAME = 0,
    GAME_SET, // smash reference :D
} GameState;

    int CoroutineStatus;
    Coroutine coroutine;

    typedef struct {
        char* name;
        char* leader; // cheerleader?
        int PLY; // 0 é player 1, 1 é player 2
        int MAXCOUNT_PLY;
        int MAXCOUNT_VEH;
        PartyType party;
        CharType classType;
        LocationVar startLocation;
    //  CharMode modeType;
    } Party;

        std::vector<Party>parties;

        std::vector<PlayerManager::Player>players;

        Texture2D tPlayer[PLAYER_COUNT];

        PlayerManager player;
        TilemapManager tilemap;

    // instâncias de equipes

        Party Rebels;
        Party Empire;

    int Campaign;

    int Players;

    private:
        float currentTime;
        bool isGameActive;
        int WinCondition[2] = {0, 1};
        int WinConditionExtra[4] = {0, 1, 2, 3};

        typedef struct {
            double StartTime;
            bool isTimerActive;
        } Timer; // temporizador

};