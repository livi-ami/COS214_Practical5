#include "DispatchUnitCommand.h"
#include "ResponseUnit.h"
#include "Incident.h"

#include <iostream>


DispatchUnitCommand::DispatchUnitCommand(ResponseUnit& unit, Incident& incident) : unit(unit), incident(incident){
    this->executed = false;
}

bool DispatchUnitCommand::execute(){

    if(executed){
        std::cout << "[Command] already executed" << std::endl;
        return false;
    }

    if(!unit.isAvailable()){
        std::cout << "[Command] " << unit.getName() << " is already committed to Incident #" << unit.getAssignment()->getId() << std::endl;
        return false;
    }

    if(!incident.dispatch()){
        return false;
    }

    if(!unit.dispatchTo(incident)){
        return false;
    }

    executed = true;
    return true;
}

bool DispatchUnitCommand::undo(){

    if(!executed){
        return false;
    }

    if(unit.getAssignment() != &incident){
        std::cout << "[Command] unit is no longer assigned to this incident" << std::endl;
        return false;
    }else{

        unit.standDown();
        executed = false;
        return true;
    }
}

std::string DispatchUnitCommand::describe() const{

    return "DispatchUnit(" + unit.getName() + " -> Incident #" + std::to_string(incident.getId()) + ")";
}