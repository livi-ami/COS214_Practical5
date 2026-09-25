#ifndef INCIDENT_OBSERVER_H
#define INCIDENT_OBSERVER_H

class Incident;

//Observer interface
class IncidentObserver {
public:
    virtual void update(Incident* incident) = 0;
    virtual ~IncidentObserver() {}
};

#endif