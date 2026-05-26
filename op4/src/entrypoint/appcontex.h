#ifndef OOP4_APPCONTEX_H
#define OOP4_APPCONTEX_H

#include <qstring.h>
#include "../business/camera.h"

typedef enum {
    NONE = 0,

    INVALID_FILE,
    INVALID_ARGUMENT,
    INVALID_GAP,
} Errors;

typedef struct {
    char* filePath;

    float a = 0;
    float b = 0;
} AppParams;

typedef struct {
    Errors err = NONE;
    Point* points = nullptr;
    size_t count = 0;

    int* indexLines;
    size_t indexCount = 0;
} AppContext;

#endif //OOP4_APPCONTEX_H
