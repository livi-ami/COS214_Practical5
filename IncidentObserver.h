#ifndef INCIDENT_OBSERVER_H
#define INCIDENT_OBSERVER_H

#include <string>

class Incident;

//Observer interface
class IncidentObserver {
public:
    virtual void onIncidentChanged(Incident& incident, const std::string& oldState, const std::string& newState) = 0;
    virtual ~IncidentObserver() {}
};

#endif
