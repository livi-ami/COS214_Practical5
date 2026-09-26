#include "state/DispatchedState.h"
#include "state/InProgressState.h"
#include "state/CancelledState.h"

std::string DispatchedState::getName() const{

    return "Dispatched";
}
bool DispatchedState::isActive(){

    return true;
}

IncidentState* DispatchedState::dispatch(const Incident& /*i*/){

    return this;
}
IncidentState* DispatchedState::cancel(const Incident& i){
    
    return new CancelledState();
}

IncidentState* DispatchedState::beginResponse(const Incident& i){
    
    return new InProgressState();
}

IncidentState* DispatchedState::resolve(const Incident& i){
    
    return reject(i, "resolve");
}