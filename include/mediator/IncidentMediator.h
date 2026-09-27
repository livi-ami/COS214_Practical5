#ifndef INCIDENT_MEDIATOR_H
#define INCIDENT_MEDIATOR_H

class ResponseUnit;
class Incident;
enum class UnitEvent;

//Mediator interface
class IncidentMediator {
public:
    virtual void registerColleague(ResponseUnit* unit) = 0;
    virtual void notify(ResponseUnit* sender, UnitEvent event, const Incident& incident) = 0;
    virtual ~IncidentMediator() {}
};

#endif
