#include <globaldefs.h>
#include "Combat/Main/BattleList.h"
#include "Combat/Main/UnknownFunctions.h"

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
    struct CombatantStruct *combatant;
    if (check < 0) {
        return 0;
    }

    for (int combatantId = 0x70; combatantId <= 0x9f; combatantId += 1){
        combatant = battleStruct->combatantList[combatantId];
        if (combatant != 0 && (combatant->flags & 0x20) != 0) {
            if (check == (combatant + 1)->unk[0x16]) {
                return &combatant->flags;
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
    int combatantNumber = 1;
    
    for (combatantId = 0; combatantId < 4; combatantId++) {
        unsigned short *combatantFlag = GetCombatantFlagIfUnknown4(battleStruct, combatantId);
        if (combatantFlag != 0x0) {
            unknown[combatantNumber] = (char)combatantId;
            combatantNumber += 1;
        }
    }
    return combatantNumber;
}

ARM bool IsUnknownIntOdd(struct BattleStruct *battleStruct) {
    return battleStruct->unk4cStruct->unk[5] & 1;
}

ARM void SetUnk3ac(struct BattleStruct *battleStruct, int value) {
    battleStruct->unk3ac = value;
}

ARM int GetUnk3ac(struct BattleStruct *battleStruct) {
    return battleStruct->unk3ac;
}

ARM unsigned char GetUnk3000Char(struct BattleStruct *battleStruct) {
    return battleStruct->unk3000[0x97c];
}

ARM int* GetUnk3b0(struct BattleStruct *battleStruct) {
    return battleStruct->unk3b0.unk0;
}

ARM void SetUnk3b0(struct BattleStruct *battleStruct, int *value) {
    battleStruct->unk3b0.unk0 = value;
}

ARM int* GetUnk3b0IfEqual2(struct BattleStruct *battleStruct) {
    int *intArray = battleStruct->unk3b0.unk0;
    if (intArray != 0 && (GetIntValue(intArray) & 2)) {
        return battleStruct->unk3b0.unk0;
    }

    return 0;
}

ARM int* GetUnk3b0IfEqual4(struct BattleStruct *battleStruct) {
    int *intArray = battleStruct->unk3b0.unk0;
    if (intArray != 0 && (GetIntValue(intArray) & 4)) {
        return battleStruct->unk3b0.unk0;
    }

    return 0;
}

ARM void InitUnk3b0(BattleStruct *battleStruct) {
    battleStruct->unk3b0.unk4 = 0x21;
    battleStruct->unk3b0.unk8 = 0x21;
    battleStruct->unk3b0.unkc = 0x1000;
    battleStruct->unk3b0.unk14 = 2;
    battleStruct->unk3b0.unk10 = 0x2000;
}

#ifdef __MWERKS__
// TODO Replace by a function when understand how to proc cmp -> cmpeq
extern unsigned int func_0200cedc(unsigned int, unsigned int, int, int);
extern int _ffix();
extern int _ffixu();
extern int _fmul();
extern int _fdiv();
extern int _fflt();
extern int _ffltu();
asm void ComputeUnk3b0Unk4Unk10(struct BattleStruct *battleStruct, unsigned int index, int param_3) {
	stmdb sp!,{r3,r4,r5,lr}
	ldr r3,=0x0000c350
	mov r4,r0
	cmp r2,#0x0
	cmpeq r1,r3
	movhi r1,r3
	ldr r3,[r4,#0x3c8]
	mov r0,#0x0
	movhi r2,r0
	str r3,[r4,#0x3c4]
	mov r0,#0x0
	str r0,[r4,#0x3c8]
	ldr r0,[r4,#0x3c4]
	mov r3,#0x0
	cmp r0,#0x3
	movhi r0,#0x3
	strhi r0,[r4,#0x3c4]
	mov r0,r1
	mov r1,r2
	mov r2,#0x3e8
	bl func_0200cedc
	str r0,[r4,#0x3b8]
	bl _ffltu
	add r1,r4,#0x300
	mov r5,r0
	ldrsh r0,[r1,#0xbc]
	bl _fflt
	ldr r1,=0x45800000
	bl _fdiv
	mov r1,r0
	mov r0,r5
	bl _fmul
	bl _ffixu
	str r0,[r4,#0x3b4]
	bl _ffltu
	ldr r1,=0x41880000
	bl _fdiv
	mov r1,r0
	ldr r0,=0x45800000
	bl _fmul
	bl _ffix
	str r0,[r4,#0x3c0]
	ldmia sp!,{r3,r4,r5,pc}
}
#endif

// void ComputeUnk3b0Unk4Unk10(struct BattleStruct *battleStruct, unsigned int index, int param_3) {
//     // param_2 looks like an index
//     if (param_3 == 0 && index > 50000) {
//         index = 50000;
//         param_3 = 0;
//     } 
//     if (param_3 > 0) {
//         index = 50000;
//         param_3 = 0;
//     }
//     // param_3 stays when < 0? Or is unsigned? Unclear... 
    
//     battleStruct->unk3b0.unk14 = battleStruct->unk3c8;
//     battleStruct->unk3c8 = 0;
//     if (battleStruct->unk3b0.unk14 > 3) {
//         battleStruct->unk3b0.unk14 = 3;
//     }

//     // Compute and set to unk8
//     index = func_0200cedc(index, param_3, 1000, 0);
//     battleStruct->unk3b0.unk8 = index;
    
//     float fVar2 = index;
//     float fVar3 = battleStruct->unk3b0.unkc / 4096.0f;
//     fVar2 = fVar2 * fVar3;
//     index = fVar2;
//     battleStruct->unk3b0.unk4 = index; // (index * (a / 4096))
//     fVar2 = index;
//     fVar2 = fVar2 / 17.0f;
//     fVar2 = 4096.0f * fVar2;
//     battleStruct->unk3b0.unk10 = fVar2;

//     // (int) (((int) (index * (a / 4096)) / 17) * 4096)
// }


int GetUnk3b0Unk4(BattleStruct *param_1) {
    return param_1->unk3b0.unk4;
}

int GetUnk3b0Unk8(BattleStruct *param_1) {
    return param_1->unk3b0.unk8;
}

int GetUnk3b0Unk10(BattleStruct *param_1) {
    return param_1->unk3b0.unk10;
}

unsigned int GetUnk3b0Unk14(BattleStruct *param_1) {
    return param_1->unk3b0.unk14;
}

void SetUnk3b0Unkc(BattleStruct *param_1,short param_2) {
    param_1->unk3b0.unkc = param_2;
    return;
}

short GetUnk3b0Unkc(BattleStruct *param_1) {
    return param_1->unk3b0.unkc;
}

void ComputeSomething(struct BattleStruct *battleStruct) {
    if (battleStruct->unk3d8 == 0) {
        return;
    }
    
    // TODO This is a return but decomp function first to know!
    func_02010288(battleStruct, battleStruct->unk3cc + battleStruct->unk3b0.unk14 * battleStruct->unk3d4);
}
