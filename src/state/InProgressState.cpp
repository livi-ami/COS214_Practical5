#include "state/InProgressState.h"
#include "state/ResolvedState.h"
#include "state/CancelledState.h"

std::string InProgressState::getName() const{

    return "InProgress";
}
bool InProgressState::isActive(){

    return true;
}

IncidentState* InProgressState::dispatch(const Incident& /*i*/){

    return this;
}
IncidentState* InProgressState::cancel(const Incident& i){
    
    return new CancelledState();
}

IncidentState* InProgressState::beginResponse(const Incident& /*i*/){
    
    return this;
}
IncidentState* InProgressState::resolve(const Incident& i){
    
    return new ResolvedState();
}