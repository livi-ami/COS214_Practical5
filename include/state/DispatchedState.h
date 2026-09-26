#ifndef DISPATCHEDSTATE_H
#define DISPATCHEDSTATE_H

#include "state/IncidentState.h"

class DispatchedState : public IncidentState
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