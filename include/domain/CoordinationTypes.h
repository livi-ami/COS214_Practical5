#ifndef COORDINATION_TYPES_H
#define COORDINATION_TYPES_H

// Shared vocabulary between ResponseUnit (Member 1) and IncidentMediator (Member 2).
// To add a value: append at the END and tell the team. Never rename or reorder.

enum class UnitRole {
    Security,
    Medical,
    Facilities
};

enum class UnitEvent {
    AreaSecured,        // Security unit: scene cordoned off
    EvacuationStarted,  // Security unit: evacuation under way
    AlarmActivated,     // Facilities unit: building alarm sounding
    CasualtiesTreated   // Medical unit: treatment complete
};

inline const char* toString(UnitRole role) {
    switch (role) {
        case UnitRole::Security:   return "Security";
        case UnitRole::Medical:    return "Medical";
        case UnitRole::Facilities: return "Facilities";
    }
    return "Unknown";
}

inline const char* toString(UnitEvent event) {
    switch (event) {
        case UnitEvent::AreaSecured:       return "AreaSecured";
        case UnitEvent::EvacuationStarted: return "EvacuationStarted";
        case UnitEvent::AlarmActivated:    return "AlarmActivated";
        case UnitEvent::CasualtiesTreated: return "CasualtiesTreated";
    }
    return "Unknown";
}

#endif