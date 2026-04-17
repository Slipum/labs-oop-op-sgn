#ifndef OP2_ENTRYPOINT_H
#define OP2_ENTRYPOINT_H

#include "appcontext.h"

enum Operations {
    LOAD,
    METRICS,
    FREE,
    CLEAR_ERROR,
};

void doOperation(AppParams* app, AppContext* context, int operation);

#endif //OP2_ENTRYPOINT_H
