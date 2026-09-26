#ifndef INCIDENT_H
#define INCIDENT_H

#include <string>
#include <vector>

class IncidentState;
class IncidentObserver;
class ResponseUnit;

class Incident {
public:
    Incident(int id, const std::string& location, const std::string& description);
    ~Incident();

    int getId() const;
    const std::string& getLocation() const;
    const std::string& getDescription() const;
    std::string getStateName() const;
    bool isActive() const;

    bool dispatch();
    bool beginResponse();
    bool resolve();
    bool cancel();

    void assignUnit(ResponseUnit* unit);
    void releaseUnit(ResponseUnit* unit);
    const std::vector<ResponseUnit*>& getAssignedUnits() const;

    void attach(IncidentObserver* observer);
    void detach(IncidentObserver* observer);

private:
    Incident(const Incident&) = delete;
    Incident& operator=(const Incident&) = delete;

    bool applyTransition(IncidentState* next);
    void setState(IncidentState* next);
    void notifyObservers(const std::string& oldState, const std::string& newState);
    void releaseAllUnits();

    int id;
    std::string location;
    std::string description;
    IncidentState* state;
    std::vector<ResponseUnit*> units;
    std::vector<IncidentObserver*> observers;
};

#endif