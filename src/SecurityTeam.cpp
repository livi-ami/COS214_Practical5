#include "SecurityTeam.h"
#include <iostream>

SecurityTeam::SecurityTeam() : ResponseUnit("SecurityTeam") {}

void SecurityTeam::secureArea() {
    std::cout << "[SecurityTeam] area secured\n";
    reportEvent("area_secured");
}