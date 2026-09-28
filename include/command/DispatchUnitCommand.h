#ifndef DISPATCH_UNIT_COMMAND_H
#define DISPATCH_UNIT_COMMAND_H

#include "command/Command.h"
#include <string>

class ResponseUnit;
class Incident;

class DispatchUnitCommand : public Command{

public:
    DispatchUnitCommand(ResponseUnit& unit, Incident& incident);
    
    bool execute() override;
    bool undo() override;
    std::string describe() const override;

private:
    ResponseUnit& unit;
    Incident& incident;
    bool executed;
};

#endif