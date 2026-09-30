#include "OperatorConsole.h"
#include "Command.h"

#include <iostream>

OperatorConsole::OperatorConsole(){}

bool OperatorConsole::execute(Command* c){

    if(c == nullptr){

        std::cout << "[Console] ignored null command" << std::endl;

        return false;
    }

    std::cout << "[Console] >> " << c->describe() << std::endl;
    bool ok = c->execute();
    history.push_back({c, ok, false});

    if(ok){
        std::cout << "[Console] OK" << std::endl;
    }else{
        std::cout << "[Console] FAILED" << std::endl;
    }

    return ok;
}

bool OperatorConsole::undoLast() {

    if(history.empty()){

        std::cout << "[Console] nothing to undo" << std::endl;
        return false;
    }

    for(int i = static_cast<int>(history.size()) - 1; i >= 0; --i){
        
        if(history[i].succeeded && !history[i].undone){
            
            std::cout << "[Console] UNDO >> " << history[i].command->describe() << std::endl;
            
            bool ok = history[i].command->undo();
            
            if(ok){
                
                history[i].undone = true;
                std::cout << "[Console] OK" << std::endl;
            }else{
                
                std::cout << "[Console] FAILED" << std::endl;
            }
            
            return ok; 
        }
    }

    std::cout << "[Console] nothing to undo" << std::endl;
    return false;
}

void OperatorConsole::printHistory() const{

    for (const auto& entry : history){

        std::string status = entry.undone ? "UNDONE" : (entry.succeeded ? "OK" : "FAILED");

        std::cout << "[Console] " << entry.command->describe() << " : " << status << std::endl;
    }
}

std::size_t OperatorConsole::historySize() const{

    return history.size();
}

OperatorConsole::~OperatorConsole(){

    for(auto& a : history){

        delete a.command;
    }
}