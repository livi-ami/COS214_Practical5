#include "domain/SecurityTeam.h"
#include "domain/Incident.h"
#include <iostream>

SecurityTeam::SecurityTeam(const std::string& name) 
    : ResponseUnit(name, UnitRole::Security) {}

bool SecurityTeam::respond(){

    if(!checkIn()){
        return false;
    }
    
    std::cout << "[" << getName() << "] on scene at " << getAssignment()->getLocation() << ": securing the area\n";

    notifyMediator(UnitEvent::AreaSecured);

    return true;
}

bool SecurityTeam::evacuateArea(Incident& incident){

    if(getAssignment() != &incident){

        std::cout << "[" << getName() << "] is not assigned to Incident #" << incident.getId() << "\n";

        return false;
    }
    
    std::cout << "[" << getName() << "] marshalling occupants out of " << incident.getLocation() << "\n";

    notifyMediator(UnitEvent::EvacuationStarted);
    
    return true;
}