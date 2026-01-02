#include <globaldefs.h>
#include "Combat/Main/BattleList.h"

ARM struct CombatantStruct* GetCombatantFromListIfUnknown(struct BattleStruct *battleStruct, int combatantId) {
    struct CombatantStruct* combatant;
    if (combatantId < 0) {
        return 0;
    }
    if (combatantId >= 0xe9) {
        return 0;
    }
    combatant = battleStruct->combatantList[combatantId];
    if (combatant == 0) {
        return 0;
    }
    if ((combatant->flags & 0x80) == 0) {
        combatant = 0;
    }
    return combatant;
}

ARM unsigned short* GetCombatantFlagIfUnknown1(struct BattleStruct *battleStruct, int combatantId) {
    struct CombatantStruct* combatant;
    if (combatantId < 0) {
        return 0;
    }
    if (combatantId >= 0xe9) {
        return 0;
    }
    combatant = battleStruct->combatantList[combatantId];
    if (combatant == 0) {
        return 0;
    }
    if ((combatant->flags & 0x400) == 0) {
        combatant = 0;
    }
    return &combatant->flags;
}

ARM unsigned short* GetCombatantFlagIfUnknown2(struct BattleStruct *battleStruct, int combatantId) {
    struct CombatantStruct* combatant;
    if (combatantId < 0) {
        return 0;
    }
    if (combatantId >= 0xe9) {
        return 0;
    }
    combatant = battleStruct->combatantList[combatantId];
    if (combatant == 0) {
        return 0;
    }
    if ((combatant->flags & 0x200) == 0) {
        combatant = 0;
    }
    return &combatant->flags;
}

ARM unsigned short* GetCombatantFlagIfUnknown3(struct BattleStruct *battleStruct, int combatantId) {
    struct CombatantStruct* combatant;
    if (combatantId < 0) {
        return 0;
    }
    if (combatantId >= 0xe9) {
        return 0;
    }
    combatant = battleStruct->combatantList[combatantId];
    if (combatant == 0) {
        return 0;
    }
    if ((combatant->flags & 0x100) == 0) {
        combatant = 0;
    }
    return &combatant->flags;
}

ARM unsigned short* GetCombatantFlagIfUnknown4(struct BattleStruct *battleStruct, int combatantId) {
    struct CombatantStruct* combatant;
    if (combatantId < 0) {
        return 0;
    }
    if (combatantId >= 0xe9) {
        return 0;
    }
    combatant = battleStruct->combatantList[combatantId];
    if (combatant == 0) {
        return 0;
    }
    if ((combatant->flags & 0x1000) == 0) {
        combatant = 0;
    }
    return &combatant->flags;
}

ARM struct CombatantStruct* GetCombatantFromList(struct BattleStruct *battleStruct, int combatantId) {
    struct CombatantStruct* combatant;
    if (combatantId < 0) {
        return 0;
    }
    if (combatantId >= 0xe9) {
        return 0;
    }
    combatant = battleStruct->combatantList[combatantId];
    if (combatant == 0) {
        return 0;
    }
    
    return combatant;
}

ARM struct UnknownC9Struct* GetEnvironmentInfo(struct BattleStruct *battleStruct) {
    // TODO Check that it is really the environment...
    struct UnknownC9Struct* environmentStruct;

    environmentStruct = battleStruct->environmentStruct;
    if (environmentStruct == 0) {
        return 0;
    }
    
    return environmentStruct;
}

ARM struct CombatantStruct* GetUnknownInfo(struct BattleStruct *battleStruct) {
    struct CombatantStruct* combatant;

    combatant = battleStruct->combatantListRest[0];
    if (combatant == 0) {
        return 0;
    }
    
    return combatant;
}

ARM unsigned short* GetCombatantFlagIfUnknown5(struct BattleStruct* battleStruct, int check) {
    struct CombatantStruct *var;
    if (check < 0) {
        return 0;
    }

    for (int combatantId = 0x70; combatantId <= 0x9f; combatantId += 1){
        var = battleStruct->combatantList[combatantId];
        if (var != 0 && (var->flags & 0x20) != 0) {
            if (check == (var + 1)->unk[0x16]) {
                return &var->flags;
            }
        }
    }

    return 0;
}

ARM int GetNumberCombatant(BattleStruct *battleStruct, char *unknown) {
    if (unknown == 0) {
        return 0;
    }
    
    *unknown = 0;
    int combatantId = 0;
    int a = 1;
    
    for (combatantId = 0; combatantId < 4; combatantId++) {
        unsigned short *combatantFlag = GetCombatantFlagIfUnknown4(battleStruct, combatantId);
        if (combatantFlag != 0x0) {
            unknown[a] = (char)combatantId;
            a += 1;
        }
    }
    return a;
}