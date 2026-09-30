#ifndef ISSUE_EVACUATION_COMMAND_H
#define ISSUE_EVACUATION_COMMAND_H

#include "Command.h"
#include <string>

class SecurityTeam;
class Incident;

class IssueEvacuationCommand : public Command{

public:
    IssueEvacuationCommand(SecurityTeam& team, Incident& incident);
    
    bool execute() override;
    bool undo() override;
    std::string describe() const override;

private:
    SecurityTeam& team;
    Incident& incident;
};

#endif