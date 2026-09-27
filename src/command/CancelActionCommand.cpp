#include "command/CancelActionCommand.h"
#include "domain/Incident.h"

#include <iostream>

CancelActionCommand::CancelActionCommand(Incident& incident) : incident(incident){}

bool CancelActionCommand::execute(){

    return incident.cancel();
}

bool CancelActionCommand::undo(){

    std::cout << "[Command] a cancelled incident cannot be reopened" << std::endl;
    return false;
}

std::string CancelActionCommand::describe() const{

    return "CancelAction(Incident #" + std::to_string(incident.getId())+ ")";
}