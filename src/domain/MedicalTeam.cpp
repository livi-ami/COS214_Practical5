#include "domain/MedicalTeam.h"
#include "domain/Incident.h"
#include <iostream>

MedicalTeam::MedicalTeam(const std::string& name) 
    : ResponseUnit(name, UnitRole::Medical), clearedIncidentId(-1), holdingIncidentId(-1){}

bool MedicalTeam::respond() {
    if(!checkIn()){
        return false;
    }
    
    if(getAssignment()->getId() == clearedIncidentId){

        treatCasualties();
    }else{

        holdingIncidentId = getAssignment()->getId();

        std::cout << "[" << getName() << "] holding at the perimeter until the area is secured\n";
    }

    return true;
}

void MedicalTeam::receive(UnitEvent event, const Incident& incident){

    if(event == UnitEvent::AreaSecured && getAssignment() == &incident){

        clearedIncidentId = incident.getId();

        std::cout << "[" << getName() << "] cleared to enter " << incident.getLocation() << "\n";
        
        if (holdingIncidentId == incident.getId()) {

            holdingIncidentId = -1;
            treatCasualties();
        }
    }
}

void MedicalTeam::treatCasualties() {
    std::cout << "[" << getName() << "] treating casualties at " << getAssignment()->getLocation() << "\n";
    holdingIncidentId = -1;
    notifyMediator(UnitEvent::CasualtiesTreated);
}