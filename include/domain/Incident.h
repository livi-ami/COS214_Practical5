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
    ~Incident();                                    // deletes state_ ONLY

    int getId() const;
    const std::string& getLocation() const;
    const std::string& getDescription() const;
    std::string getStateName() const;
    bool isActive() const;

    // Lifecycle requests. Each delegates to the current state.
    // true = accepted (state may or may not have changed), false = rejected.
    bool dispatch();
    bool beginResponse();
    bool resolve();
    bool cancel();

    // Unit bookkeeping (called by ResponseUnit::dispatchTo / standDown).
    void assignUnit(ResponseUnit* unit);
    void releaseUnit(ResponseUnit* unit);
    const std::vector<ResponseUnit*>& getAssignedUnits() const;

    // Observer plumbing (Incident is the Subject).
    void attach(IncidentObserver* observer);
    void detach(IncidentObserver* observer);

private:
    Incident(const Incident&) = delete;
    Incident& operator=(const Incident&) = delete;

    bool applyTransition(IncidentState* next);
    void setState(IncidentState* next);
    void notifyObservers(const std::string& oldState, const std::string& newState);
    void releaseAllUnits();

    // Keep this declaration order: the constructor's initialiser list must match it.
    int id_;
    std::string location;
    std::string description;
    IncidentState* state;                          // OWNED
    std::vector<ResponseUnit*> units;              // NOT owned
    std::vector<IncidentObserver*> observers;      // NOT owned
};

#endif