#include "entrypoint.h"
#include "../bussines/calculator.h"

void doOperation(AppParams& params, AppContext& context) {
    Calculator(params.input, context.output);
}
