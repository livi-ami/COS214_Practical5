#ifndef ACTIVATE_ALERT_COMMAND_H
#define ACTIVATE_ALERT_COMMAND_H

#include "command/Command.h"
#include <string>

class FacilitiesTeam;
class Incident;

class ActivateAlertCommand : public Command {
public:
    ActivateAlertCommand(FacilitiesTeam& team, Incident& incident);
    
    bool execute() override;
    bool undo() override;
    std::string describe() const override;

private:
    FacilitiesTeam& team;
    Incident& incident;
};

#endif