#ifndef OPERATOR_CONSOLE_H
#define OPERATOR_CONSOLE_H

#include <cstddef>
#include <vector>

class Command;

class OperatorConsole {
public:
    OperatorConsole();
    ~OperatorConsole();

    bool execute(Command* command);
    bool undoLast();
    std::size_t historySize() const;
    void printHistory() const;

private:
    OperatorConsole(const OperatorConsole&) = delete;
    OperatorConsole& operator=(const OperatorConsole&) = delete;

    struct Entry {
        Command* command;
        bool succeeded;
        bool undone;
    };
    std::vector<Entry> history;
};

#endif