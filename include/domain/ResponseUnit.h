#ifndef RESPONSE_UNIT_H
#define RESPONSE_UNIT_H

#include <string>
#include "domain/CoordinationTypes.h"

class Incident;
class IncidentMediator;

class ResponseUnit {
public:
    ResponseUnit(const std::string& name, UnitRole role);
    virtual ~ResponseUnit();                        // touches no other object

    const std::string& getName() const;             // display name, e.g. "Security Alpha"
    UnitRole getRole() const;
    bool isAvailable() const;                       // true = not committed to an incident
    Incident* getAssignment() const;                // nullptr when free

    // ---- Mediator-colleague side ----
    void setMediator(IncidentMediator* mediator);
    virtual void receive(UnitEvent event, const Incident& incident);   // mediator -> unit

    // ---- Command-receiver side ----
    bool dispatchTo(Incident& incident);            // call ONLY from DispatchUnitCommand
    void standDown();
    virtual bool respond() = 0;                     // role-specific work on scene

protected:
    bool checkIn();                                 // asks the incident to begin response
    void notifyMediator(UnitEvent event);           // unit -> mediator

private:
    ResponseUnit(const ResponseUnit&) = delete;
    ResponseUnit& operator=(const ResponseUnit&) = delete;

    std::string name;
    UnitRole role;
    Incident* assignment;                          // NOT owned
    IncidentMediator* mediator;                    // NOT owned (set by the mediator)
};

#endif