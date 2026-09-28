#include "domain/ResponseUnit.h"
#include "domain/Incident.h"
#include "mediator/IncidentMediator.h"

#include <iostream>

ResponseUnit::ResponseUnit(const std::string& name, UnitRole role)
    : name(name), role(role), assignment(nullptr), mediator(nullptr) {}

ResponseUnit::~ResponseUnit(){}


const std::string& ResponseUnit::getName() const{

    return this->name;
}

UnitRole ResponseUnit::getRole() const{

    return this->role;
}

Incident* ResponseUnit::getAssignment() const{

    return this->assignment;
}

void ResponseUnit::setMediator(IncidentMediator* mediator){

    this->mediator = mediator;    
}

void ResponseUnit::receive(UnitEvent /*event*/, const Incident& /*incident*/){}

bool ResponseUnit::dispatchTo(Incident& incident){
    if(assignment != nullptr){

        std::cout << "[" << this->getName() << "] is already committed to Incident #" << this->assignment->getId() << "\n";
        return false;
    }
    
    this->assignment = &incident;
    incident.assignUnit(this);
    std::cout << "[" << this->getName() << "] dispatched to Incident #" << incident.getId() << " (" << incident.getLocation() << ")\n";
    return true;
}

void ResponseUnit::standDown(){

    if(this->assignment == nullptr){
        return;
    }else{

        Incident* dup;
        dup = this->assignment;

        this->assignment = nullptr;

        dup->releaseUnit(this);

        std::cout << "["<< this->getName() << "] stood down from Incident #" << dup->getId() << std::endl;
    }
}

bool ResponseUnit::isAvailable() const{

    return this->assignment == nullptr;
}

bool ResponseUnit::checkIn(){

    if(!this->assignment){
        std::cout << "[" << this->name << "] cannot respond: not assigned to an incident" << std::endl;
        return false;
    }else{

        return assignment->beginResponse();
    }
}


void ResponseUnit::notifyMediator(UnitEvent event){
    if(!this->assignment){
        std::cout << "[" << this->name << "] cannot notify mediator: not assigned to an incident\n";
        return;
    }
    if(mediator == nullptr){

        std::cout << "[" << this->getName() << "] no mediator registered; " << toString(event) << " not coordinated\n";
        return;
    }

    mediator->notify(this, event, *assignment);
}

const char* toString(UnitEvent event) {
    
    switch (event){
        case UnitEvent::AreaSecured:       return "AreaSecured";
        case UnitEvent::EvacuationStarted: return "EvacuationStarted";
        case UnitEvent::AlarmActivated:    return "AlarmActivated";
        case UnitEvent::CasualtiesTreated: return "CasualtiesTreated";
    }
    return "Unknown";
}

const char* toString(UnitRole role) {
    switch (role) {
        case UnitRole::Security:   return "Security";
        case UnitRole::Medical:    return "Medical";
        case UnitRole::Facilities: return "Facilities";
    }
    return "Unknown";
}