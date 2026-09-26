#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "IncidentObserver.h"

//Concrete observer: renders the current state of an incident
class Dashboard : public IncidentObserver {
public:
    void update(Incident* incident) override;
};

#endif