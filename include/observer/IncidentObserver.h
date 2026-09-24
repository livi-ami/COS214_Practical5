#ifndef INCIDENT_OBSERVER_H
#define INCIDENT_OBSERVER_H

#include <string>

class Incident;

class IncidentObserver {
public:
    virtual ~IncidentObserver() {}

    // Called by Incident right AFTER its state changed. Read-only: never call
    // dispatch/beginResponse/resolve/cancel from in here.
    virtual void onIncidentChanged(const Incident& incident,
                                   const std::string& oldState,
                                   const std::string& newState) = 0;
};

#endif