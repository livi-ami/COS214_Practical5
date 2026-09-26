#include "include/Area.h"

// constructor 
Area::Area(int id,const std::string& name) : id (id), name (name) {}

// returns id
int Area::getId() const { return this->id; }

// returns name
std::string Area::getName() const { return this->name; }