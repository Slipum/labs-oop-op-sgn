#ifndef OP2_ENTRYPOINT_H
#define OP2_ENTRYPOINT_H

#include "appcontext.h"

enum Operations {
    LOAD,
    METRICS,
};

void doCreateTable(AppContext* context, int operation);

#endif //OP2_ENTRYPOINT_H
