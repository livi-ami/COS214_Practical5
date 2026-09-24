#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command {
public:
    virtual ~Command() {}
    virtual bool execute() = 0;                     // true = carried out
    virtual bool undo() = 0;                        // true = reversed
    virtual std::string describe() const = 0;       // one-line description for logs
};

#endif