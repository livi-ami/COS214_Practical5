#include "include/LegacyAccessControlSystem.h"

#include <iostream>

LegacyAccessControlSystem::LegacyAccessControlSystem () {}

void LegacyAccessControlSystem::lockDoorById(int doorID) {
    std::cout << "[LegacyAccessControlSystem] Locking door with ID: "
              << doorID << std::endl;
}

void LegacyAccessControlSystem::unlockDoorById(int doorID) {
    std::cout << "[LegacyAccessControlSystem] Unlocking door with ID: "
              << doorID << std::endl;
}

