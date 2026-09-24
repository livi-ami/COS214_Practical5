#ifndef INCIDENT_MEDIATOR_H
#define INCIDENT_MEDIATOR_H

#include "domain/CoordinationTypes.h"

class Incident;
class ResponseUnit;

class IncidentMediator {
public:
    virtual ~IncidentMediator() {}

    // Implementation MUST call unit->setMediator(this).
    virtual void registerUnit(ResponseUnit* unit) = 0;
    virtual void unregisterUnit(ResponseUnit* unit) = 0;

    // Called BY a unit when something worth coordinating happened on 'incident'.
    virtual void notify(ResponseUnit* sender, UnitEvent event, const Incident& incident) = 0;
};

#endif