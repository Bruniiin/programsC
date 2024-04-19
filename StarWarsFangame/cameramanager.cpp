#include <raylib.h>
#include "cameram.hpp"
#include "scene.hpp"

CameraM::CameraM() {

   camerat = { 0 };
   camerat.position = (Vector3){10.f, 15.f, 10.f};
   camerat.target = (Vector3){0.f, 0.f, 0.f};
   camerat.up = (Vector3){0.0f, 1.0f, 2.0f};
   camerat.fovy = 45.0f;
   camerat.projection = CAMERA_PERSPECTIVE;

}

CameraM::~CameraM() {


}

void CameraM::InitCamera() {

    BeginMode3D(camerat);


}

void CameraM::DeInitCamera() {

    EndMode3D();

}