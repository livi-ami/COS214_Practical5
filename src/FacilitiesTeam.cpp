#include "FacilitiesTeam.h"
#include <iostream>

FacilitiesTeam::FacilitiesTeam() : ResponseUnit("FacilitiesTeam") {}

void FacilitiesTeam::prepareAccess() {
    std::cout << "[FacilitiesTeam] preparing access for responders\n";
}

void FacilitiesTeam::normaliseAccess() {
    std::cout << "[FacilitiesTeam] restoring normal access controls\n";
}