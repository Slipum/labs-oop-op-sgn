#ifndef OOP3_ENTRYPOINT_H
#define OOP3_ENTRYPOINT_H

#include "appcontext.h"

typedef struct {
    std::string input;
} AppParams;

void doOperation(AppParams& params, AppContext& context);

#endif //OOP3_ENTRYPOINT_H
