#ifndef INCIDENT_LOGGER_H
#define INCIDENT_LOGGER_H

#include "IncidentObserver.h"
#include <vector>
#include <string>

//Concrete observer: keeps an in-memory audit trail of state changes.
class IncidentLogger : public IncidentObserver {
private:
    std::vector<std::string> entries;

public:
    void update(Incident* incident) override;
    const std::vector<std::string>& getEntries() const;
};

#endif