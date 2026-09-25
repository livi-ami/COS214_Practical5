#include "IncidentLogger.h"
#include "Incident.h"

void IncidentLogger::update(Incident* incident) {
    std::string entry = "Incident #" + std::to_string(incident->getId()) +
                         " -> " + incident->getStateName();
    entries.push_back(entry);
}

const std::vector<std::string>& IncidentLogger::getEntries() const {
    return entries;
}