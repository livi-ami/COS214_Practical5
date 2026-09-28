#include "command/ActivateAlertCommand.h"
#include "domain/FacilitiesTeam.h"
#include "domain/Incident.h"

#include <iostream>


ActivateAlertCommand::ActivateAlertCommand(FacilitiesTeam& team, Incident& incident) : team(team), incident(incident){}

bool ActivateAlertCommand::execute(){

    return team.activateAlarm(incident);
}

bool ActivateAlertCommand::undo(){
    
    std::cout << "[Command] Broadcast alert cannot be recalled" << std::endl;
    return false;
}

std::string ActivateAlertCommand::describe() const{

    return "ActivateAlert(" + team.getName() + ", Incident #" + std::to_string(incident.getId()) + ")";
}