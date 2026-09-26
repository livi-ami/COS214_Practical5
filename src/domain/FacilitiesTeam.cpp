#include "domain/FacilitiesTeam.h"
#include "domain/Incident.h"
#include <iostream>

FacilitiesTeam::FacilitiesTeam(const std::string& name) 
    : ResponseUnit(name, UnitRole::Facilities){}

bool FacilitiesTeam::respond(){

    if(!checkIn()){
        return false;
    }
    
    std::cout << "[" << getName() << "] isolating gas and power lines at " << getAssignment()->getLocation() << "\n";

    return true;
}

bool FacilitiesTeam::activateAlarm(Incident& incident){

    if(getAssignment() != &incident){

        std::cout << "[" << getName() << "] is not assigned to Incident #" << incident.getId() << "\n";

        return false;
    }
    
    std::cout << "[" << getName() << "] building alarm sounding at " << incident.getLocation() << "\n";

    notifyMediator(UnitEvent::AlarmActivated);
    
    return true;
}