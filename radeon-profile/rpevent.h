#ifndef EVENT_H
#define EVENT_H

#include "globalStuff.h"

enum rpeventType {
    TEMPEREATURE, BIANRY
};

struct checkInfoStruct {
    unsigned short checkTemperature;
};

class RPEvent {
public:

    RPEvent() { }

    bool enabled;
    QString name, activationBinary, fanProfileNameChange;
    globalStuff::powerProfiles dpmProfileChange;
    globalStuff::forcePowerLevels powerLevelChange;
    unsigned short fixedFanSpeedChange, activationTemperature, fanComboIndex;
    rpeventType type;

    bool isActivationConditonFullfilled(const checkInfoStruct &check) {
        switch (type) {
            case rpeventType::TEMPEREATURE:
                return activationTemperature < check.checkTemperature;
                break;
            case rpeventType::BIANRY:
                return !globalStuff::grabSystemInfo("pidof \""+activationBinary+"\"")[0].isEmpty();
                break;
        }

        return false;
    }

};

#endif // EVENT_H
