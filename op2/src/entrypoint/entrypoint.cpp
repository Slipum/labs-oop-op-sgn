#include "entrypoint.h"

#include "../bussines/logic.h"

void doOperation(AppParams* app,  AppContext* context, int operation) {
    if (app->filePath == nullptr) {
        context->error = INVALID_PATH;
        return;
    }
    if (app->colum != YEAR) app->colum++;
    switch (operation) {
    case LOAD: {
        Row** table = createTable(context, app->filePath, app->region);
        if (table == nullptr) {
            context->error = INVALID_PATH;
            return;
        }
        for (int row = 0; row < context->rows; row++) {
            printf("%s", table[row]->region);
        }
        context->outputMetrics = table;
        break;
    }

    case METRICS: {
        Row** table = createTable(context, app->filePath, app->region);
        if (table == nullptr) {
            context->error = INVALID_PATH;
            return;
        }
        context->outputMetrics = table;
        getMetrics(context, app->colum);
        if (context->outputMetrics == nullptr) {
            context->error = INVALID_FILE;
        }
        break;
    }

    case FREE: {
        freeTable(context->outputMetrics, context->rows);
        break;
    }

    case CLEAR_ERROR: {
        context->error = 0;
        break;
    }

    }
}