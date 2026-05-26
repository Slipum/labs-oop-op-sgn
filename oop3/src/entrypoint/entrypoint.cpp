#include "entrypoint.h"
#include "../bussines/facade/facade.h"

void doOperation(AppParams& params, AppContext& context) {
    CalcucateFacade application;
    application.getCalculate(params.input, context.output);
}
