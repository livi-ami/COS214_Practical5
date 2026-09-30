#ifndef INCIDENT_COORDINATOR_H
#define INCIDENT_COORDINATOR_H

#include "IncidentMediator.h"
#include <vector>

class ResponseUnit;
class Incident;

//Concrete mediator
class IncidentCoordinator : public IncidentMediator {
private:
    std::vector<ResponseUnit*> units;

public:
    void registerColleague(ResponseUnit* unit) override;
    void notify(ResponseUnit* sender, UnitEvent event, const Incident& incident) override;
    ~IncidentCoordinator() override;
};

#endif
