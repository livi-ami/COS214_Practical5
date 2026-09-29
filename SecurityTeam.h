#ifndef SECURITY_TEAM_H
#define SECURITY_TEAM_H

#include "ResponseUnit.h"

class Incident;

class SecurityTeam : public ResponseUnit {
public:
    explicit SecurityTeam(const std::string& name);
    
    bool respond() override;
    
    bool evacuateArea(Incident& incident);
};

#endif