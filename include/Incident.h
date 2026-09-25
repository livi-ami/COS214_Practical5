#ifndef INCIDENT_H
#define INCIDENT_H

#include <vector>
#include <string>

class IncidentObserver;

//to replace with Member 1's real Incident, which stores an
class Incident {
private:
    int id;
    std::string stateName;
    std::vector<IncidentObserver*> observers;

public:
    explicit Incident(int incidentId);
    void attach(IncidentObserver* obs);
    void detach(IncidentObserver* obs);
    void notifyObservers();

    void setStateName(const std::string& name);

    int getId() const;
    std::string getStateName() const;

    virtual ~Incident();
};

#endif