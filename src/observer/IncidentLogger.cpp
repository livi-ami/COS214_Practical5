#include "observer/IncidentLogger.h"
#include "domain/Incident.h"

void IncidentLogger::onIncidentChanged(Incident& incident, const std::string& oldState, const std::string& newState) {
    entries.push_back("Incident #" + std::to_string(incident.getId()) + ": " + oldState + " -> " + newState);
}

const std::vector<std::string>& IncidentLogger::getEntries() const {
    return entries;
}
