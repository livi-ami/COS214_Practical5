#ifndef FACILITIES_TEAM_H
#define FACILITIES_TEAM_H

#include "domain/ResponseUnit.h"

class Incident;

class FacilitiesTeam : public ResponseUnit {
public:
    explicit FacilitiesTeam(const std::string& name);
    
    bool respond() override;
    bool activateAlarm(Incident& incident);
};

#endif