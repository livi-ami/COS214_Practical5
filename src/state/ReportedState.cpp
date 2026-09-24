#include "state/ReportedState.h"
#include "state/DispatchedState.h"
#include "state/CancelledState.h"

std::string ReportedState::getName() const{

    return "Reported";
}
bool ReportedState::isActive(){

    return true;
}

IncidentState* ReportedState::dispatch(const Incident& i){

    return new DispatchedState();
}
IncidentState* ReportedState::cancel(const Incident& i){
    
    return new CancelledState();
}

IncidentState* ReportedState::beginResponse(const Incident& i){
    
    return reject(i, "begin response");
}

IncidentState* ReportedState::resolve(const Incident& i){
    
    return reject(i, "resolve");
}