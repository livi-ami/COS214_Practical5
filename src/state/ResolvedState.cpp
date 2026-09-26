#include "state/ResolvedState.h"

std::string ResolvedState::getName() const{

    return "Resolved";
}
bool ResolvedState::isActive(){

    return false;
}

IncidentState* ResolvedState::dispatch(const Incident& i){

    return reject(i, "dispatch");
}
IncidentState* ResolvedState::cancel(const Incident& i){
    
    return reject(i, "cancel");
}

IncidentState* ResolvedState::beginResponse(const Incident& i){
    
    return reject(i, "begin response");
}

IncidentState* ResolvedState::resolve(const Incident& i){
    
    return reject(i, "resolve");
}