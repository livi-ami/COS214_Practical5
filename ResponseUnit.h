#ifndef RESPONSE_UNIT_H
#define RESPONSE_UNIT_H

#include <string>

class Incident;
class IncidentMediator;

enum class UnitRole { Security, Medical, Facilities };
const char* toString(UnitRole role);

enum class UnitEvent { 
    AreaSecured, 
    EvacuationStarted, 
    AlarmActivated, 
    CasualtiesTreated 
};

const char* toString(UnitEvent event); 

class ResponseUnit {
public:
    ResponseUnit(const std::string& name, UnitRole role);
    virtual ~ResponseUnit();

    const std::string& getName() const;
    UnitRole getRole() const;
    bool isAvailable() const;
    Incident* getAssignment() const;

    void setMediator(IncidentMediator* mediator);
    virtual void receive(UnitEvent event, const Incident& incident);

    bool dispatchTo(Incident& incident);
    void standDown();
    virtual bool respond() = 0;      
    
protected:
    bool checkIn();
    void notifyMediator(UnitEvent event);

private:
    ResponseUnit(const ResponseUnit&) = delete;
    ResponseUnit& operator=(const ResponseUnit&) = delete;

    std::string name;
    UnitRole role;
    Incident* assignment;
    IncidentMediator* mediator;
};

#endif