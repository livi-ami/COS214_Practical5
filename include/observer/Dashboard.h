#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "observer/IncidentObserver.h"

//Concrete observer: a live view that prints incident state changes
class Dashboard : public IncidentObserver {
public:
    void onIncidentChanged(Incident& incident, const std::string& oldState, const std::string& newState) override;
};

#endif
