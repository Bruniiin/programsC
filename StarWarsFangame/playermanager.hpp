#pragma once
#include <raylib.h>

class PlayerManager {

    public:
        PlayerManager();
        ~PlayerManager();
        void Draw();
        void Move();
        void Action();
        Texture2D blank;
    private:
        Vector2 p1pos;
        Vector2 p2pos;
//        Vector2 blankpos;
//        float blankspeed;
//        Texture2D blank;
        typedef struct {
            Vector2 blankpos;
            float blankSpeed;
            Texture2D blank;
        } player0;
        player0 player01;


};