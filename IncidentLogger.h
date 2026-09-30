#ifndef INCIDENT_LOGGER_H
#define INCIDENT_LOGGER_H

#include "IncidentObserver.h"
#include <vector>
#include <string>

//Concrete observer: keeps an audit trail of state changes
class IncidentLogger : public IncidentObserver {
private:
    std::vector<std::string> entries;

public:
    void onIncidentChanged(Incident& incident, const std::string& oldState, const std::string& newState) override;
    const std::vector<std::string>& getEntries() const;
};

#endif
