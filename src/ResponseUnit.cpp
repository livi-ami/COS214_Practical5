#include "ResponseUnit.h"
#include "IncidentMediator.h"

ResponseUnit::ResponseUnit(const std::string& roleName)
    : mediator(nullptr), role(roleName) {}

void ResponseUnit::setMediator(IncidentMediator* m) { mediator = m; }

std::string ResponseUnit::getRole() const { return role; }

void ResponseUnit::reportEvent(const std::string& event) {
    if (mediator) mediator->coordinate(this, event);
}

ResponseUnit::~ResponseUnit() {}