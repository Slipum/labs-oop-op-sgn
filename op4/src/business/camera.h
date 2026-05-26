#ifndef OP4_CAMERA_H
#define OP4_CAMERA_H

#include "point/point.h"
#include <iostream>

struct Camera {
    float x = 0;
    float y = 0;
    float z = 0;
};

void applyCamera(Point** p, Camera* cam, size_t size);

void CmoveForward(Camera* camera, size_t size, float move);
void CmoveBackward(Camera* camera, size_t size, float move);
void CmoveRight(Camera* camera, size_t size, float move);
void CmoveLeft(Camera* camera, size_t size, float move);

#endif //OP4_CAMERA_H
