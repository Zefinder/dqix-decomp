#include <globaldefs.h>
#include "Combat/Main/BattleList.h"
#include "System/MainStruct.h"

void InitUnk6(struct MainStruct *mainStruct) {
    func_020ca594(mainStruct, 0, 6);
    mainStruct->unk6_0 = 0;
    mainStruct->unk6_1 = 0;
    mainStruct->addressList[0] = 0;
}

unsigned char InitUnk5(struct MainStruct *mainStruct) {
    unsigned char str[0x54]; // Is this a string?
    func_020c99c8(str);
    unsigned char firstChar = str[0];

    mainStruct->unk5 = firstChar;
    if (firstChar != 2 && firstChar != 5) {
        mainStruct->unk5 = 1;
    }

    return mainStruct->unk5;
}

ARM void InitUnk7f74(struct MainStruct *mainStruct) {
    mainStruct->unk7f74.unk0 = 0;
    mainStruct->unk7f74.unk1 = 0;
    for (unsigned char i = 0; i < 4; i++) {
        mainStruct->unk7f74.unk2[i] = 0;
    }
    mainStruct->unk7f74.unk6 = 0;
}

ARM void SetUnk0(struct MainStruct *mainStruct, int value) {
    mainStruct->unk0 = value;
}

ARM int GetUnk0(struct MainStruct *mainStruct) {
    return mainStruct->unk0;
}

ARM void SetUnk4(struct MainStruct *mainStruct, unsigned char value) {
    mainStruct->unk4 = value;
}

ARM unsigned char GetUnk4(struct MainStruct *mainStruct) {
    return mainStruct->unk4;
}

ARM struct UnkStruct* InitUnk3f8(struct MainStruct *mainStruct, struct UnkStruct *value) {
    return UnkStructCopy(&mainStruct->unk3f8, value);
}

ARM struct UnkStruct* UnkStructCopy(struct UnkStruct *src, struct UnkStruct *dest) {
    src->unk0 = dest->unk0;
    src->unk2 = dest->unk2;
    src->unk3 = dest->unk3;
    src->unk4 = dest->unk4;
    src->unk5 = dest->unk5;
    src->unk6 = dest->unk6;
    src->unk7 = dest->unk7;
    src->unk8 = dest->unk8;
    src->unk9 = dest->unk9;
    src->unka = dest->unka;
    src->unkb = dest->unkb;
    src->unkc = dest->unkc;
    src->unkd = dest->unkd;
    src->unke = dest->unke;
    #ifndef __INTELLISENSE__
    src->unk10 = dest->unk10; // This works even if VSC says the opposite
    #endif
    src->unk1c = dest->unk1c;
    src->unk1e = dest->unk1e;
    src->unk20 = dest->unk20;
    src->unk24 = dest->unk24;
    src->unk28 = dest->unk28;
    src->unk2c = dest->unk2c;
    #ifndef __INTELLISENSE__
    src->unk30 = dest->unk30;
    #endif
    src->unk60 = dest->unk60;
    src->unk61 = dest->unk61;
    src->unk62 = dest->unk62;
    src->unk63 = dest->unk63;
    src->unk64 = dest->unk64;
    src->unk65 = dest->unk65;
    src->unk66 = dest->unk66;
    src->unk67 = dest->unk67;
    src->unk68 = dest->unk68;
    src->unk69 = dest->unk69;
    src->unk6a = dest->unk6a;
    src->unk6c = dest->unk6c;
    src->unk6e = dest->unk6e;
    return src;
}

ARM struct UnkStruct* InitUnk3f8Clone(struct MainStruct *mainStruct, struct UnkStruct *value) {
    return UnkStructCopy(&mainStruct->unk3f8, value);
}

ARM struct UnkStruct* GetUnk3f8(struct MainStruct *mainStruct) {
    return &mainStruct->unk3f8;
}

ARM void InitUnk0(struct MainStruct *mainStruct, int param, int value) {
    func_020ca650(mainStruct->unk0, param);
    mainStruct->unk0 += value;
}

ARM void SetCombatantToList(MainStruct *mainStruct, int index, CombatantStruct *value) {
    mainStruct->combatantList[index] = value;
    value->indexInMainList = index;
}

ARM void ResetAddressAtIndex(struct MainStruct *maintStruct,int index) {
  maintStruct->addressList[index] = 0;
}

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
