#include <globaldefs.h>
#include "Combat/Main/BattleList.h"
#include "System/MainStruct.h"




ARM void SetCombatantToList(MainStruct *mainStruct, int index, CombatantStruct *value) {
    mainStruct->combatantList[index] = value;
    value->indexInMainList = index;
}

ARM void ResetAddressAtIndex(struct MainStruct *maintStruct,int index) {
  maintStruct->addressList[index] = 0;
}

extern "C" void func_02001aac(struct CombatantStruct **, int, int);
ARM void DoSomething(struct MainStruct *mainStruct) {
    func_02001aac(mainStruct->combatantList, 0, 0x3a4);
} 

// Just a guess that it's not for combatant struct because no check that value is 0
ARM int GetAddressAtIndex(struct MainStruct* mainStruct, int index) {
    if (index < 0) {
        return 0;
    }
    if (index >= 0xe9) {
        return 0;
    }

    return mainStruct->addressList[index];
}

unsigned short* GetCombatantFlagIfUnknown1(struct MainStruct *mainStruct, int combatantId) {
    struct CombatantStruct* combatant;
    if (combatantId < 0) {
        return 0;
    }
    if (combatantId >= 0xe9) {
        return 0;
    }
    combatant = mainStruct->combatantList[combatantId];
    if (combatant == 0) {
        return 0;
    }
    if ((combatant->flags & 2) == 0) {
        combatant = 0;
    }
    return &combatant->flags;
}


ARM int GetAddressAtUnk3ac(struct MainStruct* mainStruct) {
    return GetAddressAtIndex(mainStruct, mainStruct->unk3ac);
}

ARM int GetAddressAtUnk397c(struct MainStruct* mainStruct) {
    return GetAddressAtIndex(mainStruct, mainStruct->unk3000[0x97c]);
}

ARM unsigned short* GetCombatantFlagIfUnknown2(struct MainStruct *mainStruct, int combatantId) {
    struct CombatantStruct* combatant;
    if (combatantId < 0) {
        return 0;
    }
    if (combatantId >= 0xe9) {
        return 0;
    }
    combatant = mainStruct->combatantList[combatantId];
    if (combatant == 0) {
        return 0;
    }
    if ((combatant->flags & 0x800) == 0) {
        combatant = 0;
    }
    return &combatant->flags;
}

ARM unsigned short* GetCombatantFlagIfUnknown3(struct MainStruct *mainStruct, int combatantId) {
    struct CombatantStruct* combatant;
    if (combatantId < 0) {
        return 0;
    }
    if (combatantId >= 0xe9) {
        return 0;
    }
    combatant = mainStruct->combatantList[combatantId];
    if (combatant == 0) {
        return 0;
    }
    if ((combatant->flags & 0x20) == 0) {
        combatant = 0;
    }
    return &combatant->flags;
}

ARM struct CombatantStruct* GetCombatantFromListIfUnknown(struct MainStruct *mainStruct, int combatantId) {
    struct CombatantStruct* combatant;
    if (combatantId < 0) {
        return 0;
    }
    if (combatantId >= 0xe9) {
        return 0;
    }
    combatant = mainStruct->combatantList[combatantId];
    if (combatant == 0) {
        return 0;
    }
    if ((combatant->flags & 0x80) == 0) {
        combatant = 0;
    }
    return combatant;
}

ARM unsigned short* GetCombatantFlagIfUnknown4(struct MainStruct *mainStruct, int combatantId) {
    struct CombatantStruct* combatant;
    if (combatantId < 0) {
        return 0;
    }
    if (combatantId >= 0xe9) {
        return 0;
    }
    combatant = mainStruct->combatantList[combatantId];
    if (combatant == 0) {
        return 0;
    }
    if ((combatant->flags & 0x400) == 0) {
        combatant = 0;
    }
    return &combatant->flags;
}

ARM unsigned short* GetCombatantFlagIfUnknown5(struct MainStruct *mainStruct, int combatantId) {
    struct CombatantStruct* combatant;
    if (combatantId < 0) {
        return 0;
    }
    if (combatantId >= 0xe9) {
        return 0;
    }
    combatant = mainStruct->combatantList[combatantId];
    if (combatant == 0) {
        return 0;
    }
    if ((combatant->flags & 0x200) == 0) {
        combatant = 0;
    }
    return &combatant->flags;
}

ARM unsigned short* GetCombatantFlagIfUnknown6(struct MainStruct *mainStruct, int combatantId) {
    struct CombatantStruct* combatant;
    if (combatantId < 0) {
        return 0;
    }
    if (combatantId >= 0xe9) {
        return 0;
    }
    combatant = mainStruct->combatantList[combatantId];
    if (combatant == 0) {
        return 0;
    }
    if ((combatant->flags & 0x100) == 0) {
        combatant = 0;
    }
    return &combatant->flags;
}

ARM unsigned short* GetCombatantFlagIfUnknown7(struct MainStruct *mainStruct, int combatantId) {
    struct CombatantStruct* combatant;
    if (combatantId < 0) {
        return 0;
    }
    if (combatantId >= 0xe9) {
        return 0;
    }
    combatant = mainStruct->combatantList[combatantId];
    if (combatant == 0) {
        return 0;
    }
    if ((combatant->flags & 0x1000) == 0) {
        combatant = 0;
    }
    return &combatant->flags;
}

ARM struct CombatantStruct* GetCombatantFromList(struct MainStruct *mainStruct, int combatantId) {
    struct CombatantStruct* combatant;
    if (combatantId < 0) {
        return 0;
    }
    if (combatantId >= 0xe9) {
        return 0;
    }
    combatant = mainStruct->combatantList[combatantId];
    if (combatant == 0) {
        return 0;
    }
    
    return combatant;
}

ARM struct UnknownC9Struct* GetEnvironmentInfo(struct MainStruct *mainStruct) {
    // TODO Check that it is really the environment...
    struct UnknownC9Struct* environmentStruct;

    environmentStruct = mainStruct->environmentStruct;
    if (environmentStruct == 0) {
        return 0;
    }
    
    return environmentStruct;
}

ARM struct CombatantStruct* GetUnknownInfo(struct MainStruct *mainStruct) {
    struct CombatantStruct* combatant;

    combatant = mainStruct->combatantListRest[0];
    if (combatant == 0) {
        return 0;
    }
    
    return combatant;
}

ARM unsigned short* GetCombatantFlagIfUnknown8(struct MainStruct* mainStruct, int check) {
    struct CombatantStruct *combatant;
    if (check < 0) {
        return 0;
    }

    for (int combatantId = 0x70; combatantId <= 0x9f; combatantId += 1){
        combatant = mainStruct->combatantList[combatantId];
        if (combatant != 0 && (combatant->flags & 0x20) != 0) {
            if (check == (combatant + 1)->unk6[0x14]) {
                return &combatant->flags;
            }
        }
    }

    return 0;
}

ARM int GetNumberCombatant(struct MainStruct *mainStruct, char *unknown) {
    if (unknown == 0) {
        return 0;
    }
    
    *unknown = 0;
    int combatantId = 0;
    int combatantNumber = 1;
    
    for (combatantId = 0; combatantId < 4; combatantId++) {
        unsigned short *combatantFlag = GetCombatantFlagIfUnknown7(mainStruct, combatantId);
        if (combatantFlag != 0x0) {
            unknown[combatantNumber] = (char)combatantId;
            combatantNumber += 1;
        }
    }
    return combatantNumber;
}

ARM bool IsUnknownIntOdd(struct MainStruct *mainStruct) {
    return mainStruct->unk4cStruct->unk[5] & 1;
}
