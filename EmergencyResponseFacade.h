#ifndef EMERGENCYRESPONSEFACADE_H
#define EMERGENCYRESPONSEFACADE_H

#include <vector>
#include <string>

class Incident;
class SecurityTeam;
class MedicalTeam;
class FacilitiesTeam;
class OperatorConsole;
class IncidentCoordinator;
class AccessControlService;
class Area;

class EmergencyResponseFacade
{
public:
    EmergencyResponseFacade(OperatorConsole& console,IncidentCoordinator& coordinator, AccessControlService& accessControl);

    Incident* reportEmergency(
        int incidentId,
        const std::string& location,
        const std::string& description,
        const Area& area,
        SecurityTeam& securityTeam,
        MedicalTeam& medicalTeam,
        FacilitiesTeam& facilitiesTeam
    );

    ~EmergencyResponseFacade();


private:
    EmergencyResponseFacade(const EmergencyResponseFacade&) = delete;
    EmergencyResponseFacade& operator=(const EmergencyResponseFacade&) = delete;

    OperatorConsole& console;
    IncidentCoordinator& coordinator;
    AccessControlService& accessControl;

    std::vector<Incident*> incidents;
};

#endif