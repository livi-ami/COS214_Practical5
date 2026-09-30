#ifndef AREA_H
#define AREA_H

// necessary library
#include <string>

class Area {
    public:
        Area(int id, const std::string& name);
        int getId() const;
        std::string getName() const;
    private:
        int id;
        std::string name;
        
};

// standalone domain: translation purposes (NOT PART OF ADAPTER,TO DEMO INTERFACE CONVERSION)

#endif