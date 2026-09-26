#ifndef REPORTEDSTATE_H
#define REPORTEDSTATE_H

#include "state/IncidentState.h"

class ReportedState : public IncidentState
{

public:
        
    std::string getName() const override;
    bool isActive() override;
    IncidentState* dispatch(const Incident& i) override;
    IncidentState* beginResponse(const Incident& i) override;
    IncidentState* resolve(const Incident& i) override;
    IncidentState* cancel(const Incident& i) override;

};


#endif