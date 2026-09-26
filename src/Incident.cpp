#include "Incident.h"
#include "IncidentObserver.h"
#include <algorithm>

Incident::Incident(int incidentId) : id(incidentId), stateName("Reported") {}

void Incident::attach(IncidentObserver* obs) {
    observers.push_back(obs);
}

void Incident::detach(IncidentObserver* obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}

void Incident::notifyObservers() {
    for (IncidentObserver* obs : observers) 
    {
        obs->update(this);
    }
}

void Incident::setStateName(const std::string& name) {
    stateName = name;
    notifyObservers();
}

int Incident::getId() const { return id; }

std::string Incident::getStateName() const { return stateName; }

Incident::~Incident() {}