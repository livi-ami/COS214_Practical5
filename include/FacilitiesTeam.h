#ifndef FACILITIES_TEAM_H
#define FACILITIES_TEAM_H

#include "ResponseUnit.h"

//going to replace with FacilitiesTeam
class FacilitiesTeam : public ResponseUnit {
public:
    FacilitiesTeam();
    void prepareAccess();
    void normaliseAccess();
};

#endif