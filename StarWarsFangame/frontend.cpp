#include "raylib.h"
#include "frontend.hpp"
#include <iostream>



Frontend::Frontend() {

    CurrentTime = GetTime();

}

Frontend::~Frontend() {

}

void Frontend::MainFrontend() {


}

void Frontend::StartFrontend() {

    scene.OpeningBegin();
    scene.SceneDebug();
    textUtils.Draw();

};