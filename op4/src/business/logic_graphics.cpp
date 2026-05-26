#include "logic_graphics.h"

void error(Errors* err)
{
    *err = NONE;
}

void reset(char* filePath, Point** points, size_t *size, Errors *err) {
    clear(size, points);

    FILE *f = getFile(filePath, err);
    if (*err != Errors::NONE) return;
    size_t rows = getSize(f, size);
    *points = (Point*)malloc(rows * rows * sizeof(Point));

    if (!*points) {
        fclose(f);
        *err = Errors::INVALID_FILE;
        return;
    }

    getPoints(filePath, points, err, size);
    fclose(f);
}

void clear(size_t* size, Point** points)
{
    if (*points) {
        free(*points);
        *points = nullptr;
    }
    *size = 0;
}

FILE* getFile(char* filePath, Errors* err) {
    if (strlen(filePath) < 1) {
        *err = Errors::INVALID_FILE;
        return nullptr;
    }
    FILE *f = fopen(filePath, "r");
    if (!f) {
        *err = Errors::INVALID_FILE;
        return nullptr;
    }
    return f;
}

size_t getSize(FILE* f, size_t* size) {
    size_t rows = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), f)) rows++;
    *size = rows*rows;
    rewind(f);
    return rows;
}

void getPoints(char* filePath, Point **points, Errors *err, size_t *size) {
    FILE *f = getFile(filePath, err);
    if (*err != Errors::NONE) { return; }

    size_t rows = getSize(f, size);

    *points = (Point*)malloc(rows * rows * sizeof(Point));
    if (!*points) {
        fclose(f);
        *err = Errors::INVALID_FILE;
        return;
    }

    if (createPoints(rows, f, err, size, points)) {
        fclose(f);
        return;
    }

    float angle = 0.0f, dz = 25.0f;
    for (size_t i = 0; i < *size; i++) {
        rotate_xz(&((*points)[i]), angle);
        translateZ(&((*points)[i]), dz);
    }

    fclose(f);
}

int createPoints(size_t rows, FILE *f, Errors *err, size_t *size, Point **points) {
    float z;
    for (size_t x = 0; x < rows; x++) for (size_t y = 0; y < rows; y++) {
        if (fscanf(f, "%f", &z) != 1) {
            fclose(f);
            *err = Errors::INVALID_ARGUMENT;
            *size = 0;
            return 1;
        }

        if (y < rows - 1) {
            int c = fgetc(f);
            if (c != ',' && c != ' ' && c != '\t' && c != '\n') {
                ungetc(c, f);
            }
        }

        (*points)[x*rows + y] = {
            static_cast<float>(x),
            z,
            static_cast<float>(y),
        };
    }
    return 0;
}

void rotate_xz(Point* p, float angle)
{
    float c = cosf(angle);
    float s = sinf(angle);

    float y = p->y;
    float z = p->z;

    p->y = y * c - z * s;
    p->z = y * s + z * c;
}

void translateZ(Point* p, float dz) {
    p->x = p->x;
    p->y = p->y;
    p->z = p->z + dz;
}

void moveForward(Point** p, size_t size, float move) {
    for (size_t i = 0; i < size; i++) {
        (*p)[i].z += move;
    }
}

void moveBackward(Point** p, size_t size, float move) {
    for (size_t i = 0; i < size; i++) {
        (*p)[i].z -= move;
    }
}

void moveLeft(Point** p, size_t size, float move) {
    for (size_t i = 0; i < size; i++) {
        (*p)[i].x -= move;
    }
}

void moveRight(Point** p, size_t size, float move) {
    for (size_t i = 0; i < size; i++) {
        (*p)[i].x += move;
    }
}

void moveDown(Point** p, size_t size, float move)
{
    for (size_t i = 0; i < size; i++) {
        (*p)[i].y -= move;
    }
}

void moveUp(Point** p, size_t size, float move)
{
    for (size_t i = 0; i < size; i++) {
        (*p)[i].y += move;
    }
}

void rotateZ(Point** p, size_t size, float angle)
{
    float rad = angle * M_PI / 180.0f;
    float c = cosf(rad);
    float s = sinf(rad);

    float cx, cy, cz;
    getCenter(*p, size, &cx, &cy, &cz);

    for (size_t i = 0; i < size; i++) {
        float x = (*p)[i].x - cx;
        float y = (*p)[i].y - cy;

        float newX = x * c - y * s;
        float newY = x * s + y * c;

        (*p)[i].x = newX + cx;
        (*p)[i].y = newY + cy;
    }
}

void getCenter(Point* p, size_t size, float* cx, float* cy, float* cz)
{
    float minX = p[0].x, maxX = p[0].x;
    float minY = p[0].y, maxY = p[0].y;
    float minZ = p[0].z, maxZ = p[0].z;

    for (size_t i = 1; i < size; i++) {
        if (p[i].x < minX) minX = p[i].x;
        if (p[i].x > maxX) maxX = p[i].x;

        if (p[i].y < minY) minY = p[i].y;
        if (p[i].y > maxY) maxY = p[i].y;

        if (p[i].z < minZ) minZ = p[i].z;
        if (p[i].z > maxZ) maxZ = p[i].z;
    }

    *cx = (minX + maxX) / 2.0f;
    *cy = (minY + maxY) / 2.0f;
    *cz = (minZ + maxZ) / 2.0f;
}

void rotateX(Point** p, size_t size, float angle)
{
    float rad = angle * M_PI / 180.0f;
    float c = cosf(rad);
    float s = sinf(rad);

    float cx, cy, cz;
    getCenter(*p, size, &cx, &cy, &cz);
    for (size_t i = 0; i < size; i++) {
        float y = (*p)[i].y - cy;
        float z = (*p)[i].z - cz;

        float newY = y * c - z * s;
        float newZ = y * s + z * c;

        (*p)[i].y = newY + cy;
        (*p)[i].z = newZ + cz;
    }
}

void rotateY(Point** p, size_t size, float angle)
{
    float rad = angle * M_PI / 180.0f;
    float c = cosf(rad);
    float s = sinf(rad);

    float cx, cy, cz;
    getCenter(*p, size, &cx, &cy, &cz);
    for (size_t i = 0; i < size; i++) {
        float x = (*p)[i].x - cx;
        float z = (*p)[i].z - cz;

        float newX = x * c - z * s;
        float newZ = x * s + z * c;

        (*p)[i].x = newX + cx;
        (*p)[i].z = newZ + cz;
    }
}

float max(Point** p, size_t size) {
    float max = (*p)[0].y;
    for (size_t i = 1; i < size; i++) if (max < (*p)[i].y) max = (*p)[i].y;
    return max;
}

float min(Point** p, size_t size) {
    float min = (*p)[0].y;
    for (size_t i = 1; i < size; i++) if (min > (*p)[i].y) min = (*p)[i].y;
    return min;
}

void normalize(char* filePath, Point** p, size_t size, Errors *err, float a, float b)
{
    size_t t = 0;
    getPoints(filePath, p, err, &t);

    if (a >= b) {
        *err = Errors::INVALID_GAP;
        return;
    }

    for (size_t i = 0; i < size; i++) {
        float t1 = ((*p)[i].y - min(p, size));
        float t2 = (max(p, size) - min(p, size));
        (*p)[i].y = a + (t1 / t2) * (b - a);
    }
}
