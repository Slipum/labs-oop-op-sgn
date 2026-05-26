#include "entrypoint.h"

#include <qtextstream.h>

#include "../business/logic_graphics.h"

void doOperation(AppParams *app, AppContext *context, Operation operation, Type type) {
    if (type == Type::PLACE) switch(operation) {
    case Operation::RESET:
        if (context->points == nullptr) return;
        reset(app->filePath, &context->points, &(context->count), &(context->err));
        break;
    case Operation::CLEAR_ERROR:
        error(&(context->err));
        break;
    case Operation::CLEAR_ARGUMENTS:
        clear(&(context->count), &context->points);
        break;
    case Operation::GET_POINTS:
        if (context->err == NONE) getPoints(app->filePath, &context->points, &(context->err), &(context->count));
        break;
    case Operation::MOV_FORWARD:
        if (context->points == nullptr) return;
        moveForward(&context->points, context->count, MOVE);
        break;
    case Operation::MOV_BACKWARD:
        if (context->points == nullptr) return;
        moveBackward(&context->points, context->count, MOVE);
        break;
    case Operation::MOV_LEFT:
        if (context->points == nullptr) return;
        moveLeft(&context->points, context->count, MOVE);
        break;
    case Operation::MOV_RIGHT:
        if (context->points == nullptr) return;
        moveRight(&context->points, context->count, MOVE);
        break;
    case Operation::MOV_DOWN:
        if (context->points == nullptr) return;
        moveDown(&context->points, context->count, MOVE);
        break;
    case Operation::MOV_UP:
        if (context->points == nullptr) return;
        moveUp(&context->points, context->count, MOVE);
        break;
    case Operation::ROTATE_LEFT:
        if (context->points == nullptr) return;
        rotateZ(&context->points, context->count, ANGLE);
        break;
    case Operation::ROTATE_RIGHT:
        if (context->points == nullptr) return;
        rotateZ(&context->points, context->count, -ANGLE);
        break;
    case Operation::ROTATE_FRONT:
        if (context->points == nullptr) return;
        rotateX(&context->points, context->count, ANGLE);
        break;
    case Operation::ROTATE_BACK:
        if (context->points == nullptr) return;
        rotateX(&context->points, context->count, -ANGLE);
        break;
    case Operation::ROTATE_Y_RIGHT:
        if (context->points == nullptr) return;
        rotateY(&context->points, context->count, ANGLE);
        break;
    case Operation::ROTATE_Y_LEFT:
        if (context->points == nullptr) return;
        rotateY(&context->points, context->count, -ANGLE);
        break;
    case Operation::NORMALIZE:
        normalize(app->filePath, &context->points, context->count, &context->err, app->a, app->b);
        break;
    case Operation::ROTATE_ANIMATION:
        if (context->points == nullptr) return;
        rotateY(&context->points, context->count, ANGLE/30);
        break;
    }
}
