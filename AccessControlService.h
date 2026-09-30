#ifndef ACCESSCONTROLSERVICE_H
#define ACCESSCONTROLSERVICE_H

// Standalone domain class (IMPORTANT: helps with interface translation) // (Target)
class Area;

class AccessControlService {
    public: 
        virtual void restrictArea(const Area& area) = 0;
        virtual void releaseArea(const Area& area) = 0;
        virtual ~AccessControlService() {}
};

// This class defines the contract (No implementation in here)

#endif