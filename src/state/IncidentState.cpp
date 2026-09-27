#include "state/IncidentState.h"  
#include "domain/Incident.h"

#include <iostream>

IncidentState* IncidentState::reject(const Incident& i, const std::string& request){

    std::cout << "[Incident #" << i.getId() << "] REJECTED: cannot " << request << " while " << getName() << std::endl;
    return nullptr;
}

IncidentState::~IncidentState(){}