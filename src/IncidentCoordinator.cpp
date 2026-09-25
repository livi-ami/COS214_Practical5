#include "IncidentCoordinator.h"
#include "ResponseUnit.h"
#include "SecurityTeam.h"
#include "MedicalTeam.h"
#include "FacilitiesTeam.h"
#include <iostream>
#include <algorithm>

IncidentCoordinator::IncidentCoordinator()
    : security(nullptr), medical(nullptr), facilities(nullptr) {}

void IncidentCoordinator::registerColleague(ResponseUnit* unit) {
    if (!unit) return;
    units.push_back(unit);
    unit->setMediator(this);

    if (SecurityTeam* s = dynamic_cast<SecurityTeam*>(unit)) security = s;
    if (MedicalTeam* m = dynamic_cast<MedicalTeam*>(unit)) medical = m;
    if (FacilitiesTeam* f = dynamic_cast<FacilitiesTeam*>(unit)) facilities = f;
}

void IncidentCoordinator::coordinate(ResponseUnit* sender, const std::string& event) {
    std::cout << "[IncidentCoordinator] event \"" << event << "\" from "
              << sender->getRole() << "\n";

    if (event == "area_secured") 
    {
        if (medical) medical->proceed();
        if (facilities) facilities->prepareAccess();
    } 
    else if (event == "medical_cleared") 
    {
        if (facilities) facilities->normaliseAccess();
    } 
    else 
    {
        std::cout << "[IncidentCoordinator] no coordination rule for \""
                  << event << "\"\n";
    }
}

IncidentCoordinator::~IncidentCoordinator() {}