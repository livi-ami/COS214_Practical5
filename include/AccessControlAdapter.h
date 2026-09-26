#ifndef ACCESSCONTROLADAPTER_H
#define ACCESSCONTROLADAPTER_H

// necessary includes 
#include "AccessControlService.h"
#include "LegacyAccessControlSystem.h"

// (Adapter)
class AccessControlAdapter : public AccessControlService {
    public:
        // Takes ownership of legacySystem
        AccessControlAdapter(LegacyAccessControlSystem* legacySystem);
        
        void restrictArea(const Area& area) override;
        void releaseArea(const Area& area) override;
        virtual ~AccessControlAdapter();

    private:
        LegacyAccessControlSystem* legacySystem;
};


#endif