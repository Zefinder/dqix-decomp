#include <globaldefs.h>
#include "Save/SaveTime.h"

// Triggered when saving game, is it about time played???
ARM void SetPlayedTime1(struct MainStruct *mainStruct, short *hourPtr, char *secondPtr1, char *secondPtr2) {
    unsigned long long value = func_020c8d5c() << 6;
    unsigned long long firstDiv = value / BUS_CLOCKSPEED;

    value = mainStruct->unk3e8 << 6;
    unsigned long long secondDiv = value / BUS_CLOCKSPEED;

    unsigned long long subtracted = firstDiv - secondDiv;
    
    unsigned long long thirdDiv = subtracted / 3600;
    
    unsigned long long fourthDiv = subtracted / 60;

    unsigned int firstMod = fourthDiv % 60;

    unsigned int secondMod = subtracted % 60;

    if (thirdDiv > 10000) {
        thirdDiv = 9999;
    }

    hourPtr[0] = thirdDiv;
    secondPtr1[0] = firstMod;
    secondPtr2[0] = secondMod;
}

// Same as SetPlayedTime1 but with unk3f0
ARM void SetPlayedTime2(struct MainStruct *mainStruct, short *hourPtr, char *secondPtr1, char *secondPtr2) {
    unsigned long long value = func_020c8d5c() << 6;
    unsigned long long firstDiv = value / BUS_CLOCKSPEED;

    value = mainStruct->unk3f0 << 6;
    unsigned long long secondDiv = value / BUS_CLOCKSPEED;

    unsigned long long subtracted = firstDiv - secondDiv;
    
    unsigned long long thirdDiv = subtracted / 3600;
    
    unsigned long long fourthDiv = subtracted / 60;

    unsigned int firstMod = fourthDiv % 60;

    unsigned int secondMod = subtracted % 60;

    if (thirdDiv > 10000) {
        thirdDiv = 9999;
    }

    hourPtr[0] = thirdDiv;
    secondPtr1[0] = firstMod;
    secondPtr2[0] = secondMod;
}

ARM void SetPlayedSeconds(struct MainStruct *mainStruct, int *valuePtr) {
    unsigned long long value = func_020c8d5c() << 6;
    unsigned long long firstDiv = value / BUS_CLOCKSPEED;
    unsigned long long secondDiv = (mainStruct->unk3e8 << 6) / BUS_CLOCKSPEED;
    valuePtr[0] = firstDiv - secondDiv;
}

