#ifndef INCIDENT_COORDINATOR_H
#define INCIDENT_COORDINATOR_H

#include "IncidentMediator.h"
#include <vector>
#include <string>

class ResponseUnit;
class SecurityTeam;
class MedicalTeam;
class FacilitiesTeam;

//Concrete mediator: coordinates the response units to an incident
class IncidentCoordinator : public IncidentMediator {
private:
    std::vector<ResponseUnit*> units;
    SecurityTeam* security;
    MedicalTeam* medical;
    FacilitiesTeam* facilities;

public:
    IncidentCoordinator();
    void registerColleague(ResponseUnit* unit) override;
    void coordinate(ResponseUnit* sender, const std::string& event) override;
    ~IncidentCoordinator() override;
};

#endif