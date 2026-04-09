#include "entrypoint.h"

#include "../bussines/logic.h"

void doCreateTable(AppContext* context, int operation) {
    if (context->filePath == nullptr) return;
    switch (operation) {

    case LOAD: {
        Row** table = createTable(context);
        if (table == nullptr) {
            context->error = INVALID_PATH;
            return;
        }
        context->outputMetrics = table;
        break;
    }

    case METRICS: {
        Row** table = createTable(context);
        if (table == nullptr) {
            context->error = INVALID_PATH;
            return;
        }
        context->outputMetrics = table;
        getMetrics(context);
        getMediana(context);
        if (context->outputMetrics == nullptr) {
            context->error = INVALID_FILE;
        }
    }

    }
}