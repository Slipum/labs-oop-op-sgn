#include "camera.h"

void applyCamera(Point** p, Camera* cam, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        (*p)[i].x = (*p)[i].x - cam->x;
        (*p)[i].y = (*p)[i].y - cam->y;
        (*p)[i].z = (*p)[i].z - cam->z;
    }
}

void CmoveForward(Camera* camera, size_t size, float move)
{
    for (size_t i = 0; i < size; i++) {
        camera->z += move;
    }
}

void CmoveBackward(Camera* camera, size_t size, float move)
{
    for (size_t i = 0; i < size; i++) {
        camera->z -= move;
    }
}

void CmoveLeft(Camera* camera, size_t size, float move)
{
    for (size_t i = 0; i < size; i++) {
        camera->x -= move;
    }
}

void CmoveRight(Camera* camera, size_t size, float move)
{
    for (size_t i = 0; i < size; i++) {
        camera->x += move;
    }
}

// void moveDown(Point** p, size_t size, float move)
// {
//     for (size_t i = 0; i < size; i++) {
//         (*p)[i].y -= move;
//     }
// }
//
// void moveUp(Point** p, size_t size, float move)
// {
//     for (size_t i = 0; i < size; i++) {
//         (*p)[i].y += move;
//     }
// }
//
// void rotateZ(Point** p, size_t size, float angle)
// {
//     float rad = angle * M_PI / 180.0f;
//     float c = cosf(rad);
//     float s = sinf(rad);
//
//     float cx, cy, cz;
//     getCenter(*p, size, &cx, &cy, &cz);
//
//     for (size_t i = 0; i < size; i++) {
//         float x = (*p)[i].x - cx;
//         float y = (*p)[i].y - cy;
//
//         float newX = x * c - y * s;
//         float newY = x * s + y * c;
//
//         (*p)[i].x = newX + cx;
//         (*p)[i].y = newY + cy;
//     }
// }
//
// void getCenter(Point* p, size_t size, float* cx, float* cy, float* cz)
// {
//     float minX = p[0].x, maxX = p[0].x;
//     float minY = p[0].y, maxY = p[0].y;
//     float minZ = p[0].z, maxZ = p[0].z;
//
//     for (size_t i = 1; i < size; i++) {
//         if (p[i].x < minX) minX = p[i].x;
//         if (p[i].x > maxX) maxX = p[i].x;
//
//         if (p[i].y < minY) minY = p[i].y;
//         if (p[i].y > maxY) maxY = p[i].y;
//
//         if (p[i].z < minZ) minZ = p[i].z;
//         if (p[i].z > maxZ) maxZ = p[i].z;
//     }
//
//     *cx = (minX + maxX) / 2.0f;
//     *cy = (minY + maxY) / 2.0f;
//     *cz = (minZ + maxZ) / 2.0f;
// }
//
// void rotateX(Point** p, size_t size, float angle)
// {
//     float rad = angle * M_PI / 180.0f;
//     float c = cosf(rad);
//     float s = sinf(rad);
//
//     float cx, cy, cz;
//     getCenter(*p, size, &cx, &cy, &cz);
//     for (size_t i = 0; i < size; i++) {
//         float y = (*p)[i].y - cy;
//         float z = (*p)[i].z - cz;
//
//         float newY = y * c - z * s;
//         float newZ = y * s + z * c;
//
//         (*p)[i].y = newY + cy;
//         (*p)[i].z = newZ + cz;
//     }
// }
//
// void rotateY(Point** p, size_t size, float angle)
// {
//     float rad = angle * M_PI / 180.0f;
//     float c = cosf(rad);
//     float s = sinf(rad);
//
//     float cx, cy, cz;
//     getCenter(*p, size, &cx, &cy, &cz);
//     for (size_t i = 0; i < size; i++) {
//         float x = (*p)[i].x - cx;
//         float z = (*p)[i].z - cz;
//
//         float newX = x * c - z * s;
//         float newZ = x * s + z * c;
//
//         (*p)[i].x = newX + cx;
//         (*p)[i].z = newZ + cz;
//     }
// }
//
// float max(Point** p, size_t size) {
//     float max = (*p)[0].y;
//     for (size_t i = 1; i < size; i++) if (max < (*p)[i].y) max = (*p)[i].y;
//     return max;
// }
//
// float min(Point** p, size_t size) {
//     float min = (*p)[0].y;
//     for (size_t i = 1; i < size; i++) if (min > (*p)[i].y) min = (*p)[i].y;
//     return min;
// }
