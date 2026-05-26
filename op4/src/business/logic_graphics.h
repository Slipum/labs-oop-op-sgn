#ifndef OOP4_LOGIC_GRAPHICS_H
#define OOP4_LOGIC_GRAPHICS_H

#include <string>
#include "../entrypoint/appcontex.h"

void error(Errors* err);
void clear(size_t* size, Point** points);
void reset(char* filePath, Point** points, size_t *size, Errors *err);

FILE* getFile(char* filePath, Errors* err);
void getPoints(char* filePath, Point** points, Errors* err, size_t* size);
size_t getSize(FILE* f, size_t* size);
int createPoints(size_t rows, FILE *f, Errors *err, size_t *size, Point **points);

void rotate_xz(Point* p, float angle);
void translateZ(Point* p, float dz);

void moveForward(Point** p, size_t size, float move);
void moveBackward(Point** p, size_t size, float move);
void moveLeft(Point** p, size_t size, float move);
void moveRight(Point** p, size_t size, float move);

void moveDown(Point** p, size_t size, float move);
void moveUp(Point** p, size_t size, float move);

void rotateX(Point** p, size_t size, float angle);
void rotateY(Point** p, size_t size, float angle);
void rotateZ(Point** p, size_t size, float angle);

void getCenter(Point* p, size_t size, float* cx, float* cy, float* cz);

void normalize(char* filePath, Point** p, size_t size, Errors *err, float a, float b);

float min(Point** p, size_t size);
float max(Point** p, size_t size);

#endif //OOP4_LOGIC_GRAPHICS_H
