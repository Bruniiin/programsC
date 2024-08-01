#include <raylib.h>
#include "playermanager.hpp"
#include "levelmanager.hpp"
#include "ui.hpp"
//#include "coroutinemanager.hpp"
#include "laser.hpp"
#include "charactermanager.hpp"
#include <vector>


#define PLAYER_COUNT 4

class Game {

    public:
        Game();
        ~Game();
        void GameBegin();
        void GameRun();
        void Update();
        void GameWon();
        void Render();
        void RenderManager();
        void Logic();
        void Element();
        int Reset();
        void PushElement(int pId2, int pTypeId, int pObject, Vector2 pObjectPos, bool pIsAlive2, bool pCollision);
        void GameUi();
        Rectangle Position(int pPlayer);
        void Elements();
        // void ItemTest(int pId, Texture2D pTexture, bool pColl, bool pActive);

        int pLevel;

    typedef enum {
        ZONE_SPACE = 0,
        ZONE_HOTH,
        ZONE_YAVIN,
    } ZoneVar;

    ZoneVar zone;

    typedef enum {
        LOC_REBEL_BASE = 0,
        LOC_IMPERIAL_BASE,
        LOC_MAIN,
        LOC_OUTSIDE,
        LOC_INSIDE,
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
        PHY_TOW_CABLE, // https://www.youtube.com/watch?v=yrIyUklclNM&t=8s me deseje boa sorte fazendo a física disso    
    } EntityType;

    typedef enum {
        UI_STATUS = 0,
        UI_EQUIPMENT,
        UI_ACTION,
        UI_OBJECTIVE,
        UI_SHOW_MODE,
    } UiType;

    Laser laser;

    Vector2 laserDest;

typedef enum {
    IN_GAME = 0,
    GAME_SET,
} GameState;

typedef enum {
    LOC_SPACE = 0,
    LOC_HOTH,
} Locations;

    int CoroutineStatus;
    Coroutine coroutine;
    CharacterManager characterManager;
    Character character;
    Vehicle vehicle;
    //CharacterManager::Character character;

    std::vector<Camera2D>cameras;
    std::vector<RenderTexture>renders;

    Camera2D Camera001;
    Camera2D Camera002;
    Camera2D CameraFullscreen;

    RenderTexture Render001;
    RenderTexture Render002;
    RenderTexture RenderFullscreen;

    typedef struct ItemTest{
        int pId;
        Texture2D pTexture;
        bool pActive;
        bool pColl;
    } ItemTest;

    typedef struct {
        char* name;
        char* leader; // cheerleader?
        int PLY; // 0 é player 1, 1 é player 2
        int MAXCOUNT_PLY;
        int MAXCOUNT_VEH;
        bool isActive;
        PartyType party;
        CharType classType;
        LocationVar startLocation;
    //  CharMode modeType;
    } Party;

        int entities;
        int maxEntities;
        int isReady;

        int actors;
        // int vehicles;

        std::vector<Party>parties;

        std::vector<PlayerManager::Player>players;

        std::vector<PlayerManager::Weapon>weapons;

        std::vector<ItemTest>test;

    float t;

    struct sEmpire : Party {
    };

    struct sRebels : Party {
    };

        Texture2D tPlayer[PLAYER_COUNT];

        PlayerManager player;
        LevelManager scenario;
        Ui ui;

        Party Rebels;
        Party Empire;

    // std::vector<Laser>lasers;

    int Campaign;

    int Players;

    // int P1 = 0;
    // int P2 = 1;

    private:
        float currentTime;
        bool isGameRunning;
        bool isGameActive;
        int WinCondition[2] = {0, 1};
        int WinConditionExtra[4] = {0, 1, 2, 3};

        int currentCampaign;

        typedef struct {
            double StartTime;
            bool isTimerActive;
        } Timer; // temporizador

};