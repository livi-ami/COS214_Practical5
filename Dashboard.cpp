#include "Dashboard.h"
#include "Incident.h"
#include <iostream>

void Dashboard::onIncidentChanged(Incident& incident, const std::string& oldState, const std::string& newState) {
    std::cout << "[Dashboard] Incident #" << incident.getId() << " (" << incident.getLocation()
              << "): " << oldState << " -> " << newState << "\n";
}
