#ifndef INCIDENT_MEDIATOR_H
#define INCIDENT_MEDIATOR_H

#include <string>

class ResponseUnit;

//Mediator interface
class IncidentMediator {
public:
    virtual void registerColleague(ResponseUnit* unit) = 0;
    virtual void coordinate(ResponseUnit* sender, const std::string& event) = 0;
    virtual ~IncidentMediator() {}
};

#endif