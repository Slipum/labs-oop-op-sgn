#include "facade.h"
#include "../command/commands.h"

#include <ostream>

void CalcucateFacade::getCalculate(std::string& input, std::string& output) {
    Invoker invoke;

    invoke.addCommand(make_unique<NormalizeInputCommand>(calculator, input));
    invoke.addCommand(make_unique<GetPostfixCommand>(input, output));
    invoke.addCommand(make_unique<CalculateCommand>(calculator, output));
    invoke.addCommand(make_unique<NormalizeOutputCommand>(calculator, output));

    try {
        invoke.executeAllCommands();
    } catch (std::exception& e) {
        output = e.what();
        invoke.undoAllCommands();
    }
}
