#ifndef RESOLVEDSTATE_H
#define RESOLVEDSTATE_H

#include "state/IncidentState.h"

class ResolvedState : public IncidentState
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