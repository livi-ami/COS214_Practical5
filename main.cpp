#include "include/AccessControlAdapter.h"
#include "include/Area.h"
#include "include/EmergencyResponseFacade.h"
#include "include/LegacyAccessControlSystem.h"

#include "include/command/ActivateAlertCommand.h"
#include "include/command/CancelActionCommand.h"
#include "include/command/IssueEvacuationCommand.h"
#include "include/command/OperatorConsole.h"

#include "include/domain/FacilitiesTeam.h"
#include "include/domain/Incident.h"
#include "include/domain/MedicalTeam.h"
#include "include/domain/SecurityTeam.h"

#include "include/mediator/IncidentCoordinator.h"

#include "include/observer/Dashboard.h"
#include "include/observer/IncidentLogger.h"

#include <iostream>

int main()
{
    std::cout << "========================================\n";
    std::cout << " =========== CampusGuard =========== ";
    std::cout << "========================================\n";

    // Shared application services.
    OperatorConsole console;
    IncidentCoordinator coordinator;

    // Response-unit colleagues used by the Mediator.
    SecurityTeam security("Campus Security");
    MedicalTeam medical("Campus Medical");
    FacilitiesTeam facilities("Campus Facilities");

    // Legacy access-control system and its Adapter.
    LegacyAccessControlSystem* legacySystem =
        new LegacyAccessControlSystem();

    AccessControlAdapter accessControl(legacySystem);

    // Facade hides the coordination of these subsystems.
    EmergencyResponseFacade facade(
        console,
        coordinator,
        accessControl);

    Dashboard dashboard;
    IncidentLogger logger;

    Area scienceBuilding(101, "Science Building");
    Area residenceHall(202, "Residence Hall");

    // ------------------------------------------------------------
    // Scenario 1: Full emergency-response workflow.
    // ------------------------------------------------------------
    std::cout << "\n\n=== SCENARIO 1: LABORATORY FIRE ===\n";

    Incident* fire = facade.reportEmergency(
        1001,
        "Science Building",
        "Laboratory fire reported on the second floor.",
        scienceBuilding,
        security,
        medical,
        facilities);

    // Attach observers to monitor subsequent state changes.
    fire->attach(&dashboard);
    fire->attach(&logger);

    // Response units now act.
    // The Mediator coordinates their events.
    security.respond();
    medical.respond();
    facilities.respond();

    // Additional operator actions use Command objects.
    console.execute(
        new IssueEvacuationCommand(security, *fire));

    console.execute(
        new ActivateAlertCommand(facilities, *fire));

    // Resolve the incident.
    // This also releases all assigned response units.
    fire->resolve();

    std::cout << "[Main] Incident #" << fire->getId()
              << " final state: "
              << fire->getStateName()
              << std::endl;

    accessControl.releaseArea(scienceBuilding);

    // ------------------------------------------------------------
    // Scenario 2: Cancellation and invalid-action handling.
    // ------------------------------------------------------------
    std::cout << "\n\n=== SCENARIO 2: CANCELLED SECURITY INCIDENT ===\n";

    Incident* securityIncident = facade.reportEmergency(
        1002,
        "Residence Hall",
        "Unauthorized access alarm reported at the residence hall.",
        residenceHall,
        security,
        medical,
        facilities);

    securityIncident->attach(&dashboard);
    securityIncident->attach(&logger);

    // Cancel through the Command pattern.
    console.execute(
        new CancelActionCommand(*securityIncident));

    // This should fail because the State pattern rejects
    // evacuation after cancellation.
    console.execute(
        new IssueEvacuationCommand(
            security,
            *securityIncident));

    accessControl.releaseArea(residenceHall);

    // Show accumulated command history.
    std::cout << "\n=== OPERATOR COMMAND HISTORY ===\n";
    console.printHistory();

    // Show observer audit trail.
    std::cout << "\n=== INCIDENT AUDIT LOG ===\n";

    for (const std::string& entry : logger.getEntries())
    {
        std::cout << "[Logger] "
                  << entry
                  << std::endl;
    }

    std::cout << "\n========================================\n";
    std::cout << " Integration demo complete.\n";
    std::cout << "========================================\n";

    return 0;
}