#ifndef INCIDENTSTATE_H
#define INCIDENTSTATE_H


#include <string>
#include <iostream>
class Incident;


class IncidentState
{

public:
    
    virtual std::string getName() const = 0;
    virtual bool isActive() = 0;
    virtual IncidentState* dispatch(const Incident& i) = 0; 
    virtual IncidentState* beginResponse(const Incident& i) = 0; 
    virtual IncidentState* resolve(const Incident& i) = 0; 
    virtual IncidentState* cancel(const Incident& i) = 0; 

    virtual ~IncidentState();

protected:

    IncidentState* reject(const Incident& i, const std::string& request);

    
};



#endif