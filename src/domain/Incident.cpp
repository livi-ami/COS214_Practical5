#include "domain/Incident.h"
#include "state/ReportedState.h"
#include "domain/ResponseUnit.h"
#include "observer/IncidentObserver.h"
#include "state/IncidentState.h"
#include <algorithm>

Incident::Incident(int id, const std::string& location, const std::string& description)
    : id(id), location(location), description(description), state(new ReportedState()) {}

    Incident::~Incident(){

        delete state;
    }

    int Incident::getId() const{

        return this->id;
    }

    const std::string& Incident::getLocation() const{

        return this->location;
    }

    const std::string& Incident::getDescription() const{

        return this->description;
    }

    std::string Incident::getStateName() const{

        return state->getName();
    }

    bool Incident::isActive() const{

        return state->isActive();
    }

    bool Incident::dispatch(){

        return applyTransition(state->dispatch(*this));
    }

    bool Incident::beginResponse(){

        return applyTransition(state->beginResponse(*this));
    }

    bool Incident::resolve(){

        return applyTransition(state->resolve(*this));
    }

    bool Incident::cancel(){

        return applyTransition(state->cancel(*this));
    }

    bool Incident::applyTransition(IncidentState* next){

        if(next == nullptr){
            return false;
        }

        if(next != state){
            setState(next);
        }

        return true;
    }

    void Incident::setState(IncidentState* next){

        std::string oldName = state->getName();

        IncidentState* old = state;
        state = next;
        delete old;

        notifyObservers(oldName, state->getName());

        if(!state->isActive()){
            releaseAllUnits();
        }
    }

    void Incident::assignUnit(ResponseUnit* unit){

        if(unit == nullptr){
            return;
        }

        if(std::find(this->units.begin(), this->units.end(), unit) != this->units.end()){
            return;
        }

        this->units.push_back(unit);
    }
    

    void Incident::releaseUnit(ResponseUnit* unit){
        
        this->units.erase(std::remove(this->units.begin(), this->units.end(), unit), this->units.end());
    }

    const std::vector<ResponseUnit*>& Incident::getAssignedUnits() const{

        return this->units;
    }

    void Incident::releaseAllUnits(){

        std::vector<ResponseUnit*> old = {};

        old = this->units;
        this->units.clear();

        for(auto a : old){

            a->standDown();
        }
    }

    void Incident::attach(IncidentObserver* observer){

        if(observer == nullptr){
            return;
        }

        if(std::find(this->observers.begin(), this->observers.end(), observer) != this->observers.end()){
            return;
        }

        this->observers.push_back(observer);

    }
    void Incident::detach(IncidentObserver* observer){
        
        auto it = std::find(this->observers.begin(), this->observers.end(), observer);
        if(it != this->observers.end()){

            this->observers.erase(it);
        }
    }

    void Incident::notifyObservers(const std::string& oldState, const std::string& newState){

        std::vector<IncidentObserver*> dup;

        dup = this->observers;

        for(auto a : dup){
            
            a->onIncidentChanged(*this, oldState, newState);
        }
    }