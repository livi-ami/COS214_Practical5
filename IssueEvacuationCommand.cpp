#include "IssueEvacuationCommand.h"
#include "SecurityTeam.h"
#include "Incident.h"

#include <iostream>

IssueEvacuationCommand::IssueEvacuationCommand(SecurityTeam& team, Incident& incident) : team(team), incident(incident){}


bool IssueEvacuationCommand::execute(){

    return team.evacuateArea(incident);
}

bool IssueEvacuationCommand::undo(){

    std::cout << "[Command] evacuation orders cannot be recalled, issue a new instruction" << std::endl;
    return false;
}

std::string IssueEvacuationCommand::describe() const{

    return "IssueEvacuation(" + team.getName() + ", Incident #" + std::to_string(incident.getId()) + ")";
}