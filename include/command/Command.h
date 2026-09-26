#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command {
public:
    virtual ~Command() {}
    virtual bool execute() = 0;
    virtual bool undo() = 0;
    virtual std::string describe() const = 0;
};

#endif