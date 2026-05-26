#ifndef OOP4_ENTRYPOINT_H
#define OOP4_ENTRYPOINT_H
#include "appcontex.h"

#define ANGLE 10.0f
#define MOVE 5.0f

typedef enum {
    PLACE,
    CAMERA,
} Type;

typedef enum {
    GET_FILE = 1,
    CLEAR_ERROR,
    CLEAR_ARGUMENTS,
    GET_POINTS,

    MOV_FORWARD,
    MOV_BACKWARD,
    MOV_LEFT,
    MOV_RIGHT,

    MOV_DOWN,
    MOV_UP,

    ROTATE_LEFT,
    ROTATE_RIGHT,

    ROTATE_FRONT,
    ROTATE_BACK,

    ROTATE_Y_RIGHT,
    ROTATE_Y_LEFT,

    NORMALIZE,

    ROTATE_ANIMATION,

    RESET,
} Operation;

void doOperation(AppParams *app, AppContext *context, Operation operation, Type type);

#endif //OOP4_ENTRYPOINT_H
