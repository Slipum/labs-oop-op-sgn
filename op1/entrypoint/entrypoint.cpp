#include "entrypoint.h"
#include "../bussines/logic.h"
#include <cstdlib>

void doConvert(AppContext* context) {
    if (!context->input) {
        context->input = 0;
        return;
    }
    context->input = convert(context);

    switch(context->error) {
    case (OUTRANGE_ERROR):
        context->input = OUTRANGE_INPUT;
        break;
    case (INVALID_ERROR):
        context->input = INVALID_INPUT;
        break;
    default:
        if (context->error) context->input = ERROR_INPUT;
        break;
    }
}
