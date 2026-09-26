#include "include/AccessControlAdapter.h"
#include "include/Area.h"

// Constructor 
AccessControlAdapter::AccessControlAdapter(LegacyAccessControlSystem* legacySystem) : legacySystem (legacySystem) {}

// no access to area
void AccessControlAdapter::restrictArea(const Area& area) {
    legacySystem->lockDoorById(area.getId());
}

// give access to area
void AccessControlAdapter::releaseArea(const Area& area) {
    legacySystem->unlockDoorById(area.getId());
}

// delete the pointer to Adaptee
AccessControlAdapter::~AccessControlAdapter() {
    delete legacySystem;
}