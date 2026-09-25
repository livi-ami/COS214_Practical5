#ifndef MEDICAL_TEAM_H
#define MEDICAL_TEAM_H

#include "domain/ResponseUnit.h"

class Incident;

class MedicalTeam : public ResponseUnit {
public:
    explicit MedicalTeam(const std::string& name);
    
    bool respond() override;
    
    void receive(UnitEvent event, const Incident& incident) override;

private:
    void treatCasualties();
    
    int clearedIncidentId;
    int holdingIncidentId;
};

#endif