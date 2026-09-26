#include "MedicalTeam.h"
#include <iostream>

MedicalTeam::MedicalTeam() : ResponseUnit("MedicalTeam") {}

void MedicalTeam::proceed() {
    std::cout << "[MedicalTeam] proceeding into secured area\n";
    reportEvent("medical_cleared");
}
