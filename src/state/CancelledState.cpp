#include "state/CancelledState.h"

std::string CancelledState::getName() const{

    return "Cancelled";
}
bool CancelledState::isActive(){

    return false;
}

IncidentState* CancelledState::dispatch(const Incident& i){

    return reject(i, "dispatch");
}
IncidentState* CancelledState::cancel(const Incident& i){
    
    return reject(i, "cancel");
}

IncidentState* CancelledState::beginResponse(const Incident& i){
    
    return reject(i, "begin response");
}

IncidentState* CancelledState::resolve(const Incident& i){
    
    return reject(i, "resolve");
}