#ifndef CANCEL_ACTION_COMMAND_H
#define CANCEL_ACTION_COMMAND_H

#include "command/Command.h"
#include <string>

class Incident;

class CancelActionCommand : public Command {
public:
    CancelActionCommand(Incident& incident);
    
    bool execute() override;
    bool undo() override;
    std::string describe() const override;

private:
    Incident& incident;
};

#endif