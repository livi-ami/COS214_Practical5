#include "Dashboard.h"
#include "Incident.h"
#include <iostream>

void Dashboard::update(Incident* incident) {
    std::cout << "[Dashboard] incident #" << incident->getId()
              << " is now: " << incident->getStateName() << "\n";
}