#include "EmergencyResponseFacade.h"

#include "Incident.h"
#include "SecurityTeam.h"
#include "MedicalTeam.h"
#include "FacilitiesTeam.h"

#include "Command.h"
#include "OperatorConsole.h"
#include "DispatchUnitCommand.h"

#include "IncidentCoordinator.h"

#include "AccessControlService.h"
#include "Area.h"

#include <iostream>

EmergencyResponseFacade::EmergencyResponseFacade(
    OperatorConsole& console,
    IncidentCoordinator& coordinator,
    AccessControlService& accessControl)
    : console(console),
      coordinator(coordinator),
      accessControl(accessControl)
{
}

Incident* EmergencyResponseFacade::reportEmergency(
    int incidentId,
    const std::string& location,
    const std::string& description,
    const Area& area,
    SecurityTeam& securityTeam,
    MedicalTeam& medicalTeam,
    FacilitiesTeam& facilitiesTeam)
{
    std::cout << "\n[Facade] === Reporting Emergency ===" << std::endl;

    // 1. Create the incident.
    Incident* incident =
        new Incident(incidentId, location, description);

    incidents.push_back(incident);

    std::cout << "[Facade] Incident #" << incidentId << " created at " << location << std::endl;

    // 2. Restrict access to the affected area through
    //    the AccessControlService abstraction.
    accessControl.restrictArea(area);

    // 3. Register response teams with the Mediator.
    coordinator.registerColleague(&securityTeam);
    coordinator.registerColleague(&medicalTeam);
    coordinator.registerColleague(&facilitiesTeam);

    // 4. Dispatch the security team through the Command pattern.
    //
    //    DispatchUnitCommand performs the incident state transition
    //    and assigns the security team.
    Command* dispatchSecurity = new DispatchUnitCommand(securityTeam, *incident);

    if (!console.execute(dispatchSecurity)) {
        std::cout << "[Facade] Failed to dispatch security team." << std::endl;

        return incident;
    }

    // 5. Assign the remaining response teams directly.
    //
    //    We do not use DispatchUnitCommand again because that
    //    command also calls incident.dispatch(), which has already
    //    transitioned the incident from Reported to Dispatched.
    if (!medicalTeam.dispatchTo(*incident)) {
        std::cout << "[Facade] Failed to assign medical team." << std::endl;
    }

    if (!facilitiesTeam.dispatchTo(*incident)) {
        std::cout << "[Facade] Failed to assign facilities team." << std::endl;
    }

    std::cout << "[Facade] Emergency response setup complete." << std::endl;

    return incident;
}

EmergencyResponseFacade::~EmergencyResponseFacade() {
    for (Incident* incident : incidents) {
        delete incident;
    }
}