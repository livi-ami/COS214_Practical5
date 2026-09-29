#include "mediator/IncidentCoordinator.h"
#include "domain/ResponseUnit.h"
#include "domain/Incident.h"
#include <iostream>

void IncidentCoordinator::registerColleague(ResponseUnit* unit) {
    if (!unit) return;
    units.push_back(unit);
    unit->setMediator(this);
}

void IncidentCoordinator::notify(ResponseUnit* sender, UnitEvent event, const Incident& incident) {
    std::cout << "[IncidentCoordinator] " << sender->getName() << " reported "
              << toString(event) << " for Incident #" << incident.getId() << "\n";

    for (ResponseUnit* unit : units) 
    {
        if (unit != sender) 
        {
            unit->receive(event, incident);
        }
    }
}

IncidentCoordinator::~IncidentCoordinator() {}