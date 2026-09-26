#ifndef RESPONSE_UNIT_H
#define RESPONSE_UNIT_H

#include <string>

class IncidentMediator;

//replace with real ResponseUnit
class ResponseUnit {
protected:
    IncidentMediator* mediator;
    std::string role;

public:
    explicit ResponseUnit(const std::string& roleName);
    void setMediator(IncidentMediator* m);
    std::string getRole() const;
    void reportEvent(const std::string& event);
    virtual ~ResponseUnit();
};

#endif