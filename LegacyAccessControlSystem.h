#ifndef LEGACYACCESSCONTROLSYSTEM_H
#define LEGACYACCESSCONTROLSYSTEM_H


class LegacyAccessControlSystem {
    public:
        LegacyAccessControlSystem();
        void lockDoorById(int doorID);
        void unlockDoorById(int doorID);
};

// incompatible interface

#endif