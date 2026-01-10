#pragma once

struct PrimaryCombatStats {
    unsigned short currHP;
    unsigned short currMP;
    unsigned short maxHP;
    unsigned short maxMP;
    unsigned short attack;
    unsigned short defense;
    unsigned short agility;
    unsigned short unk;
    unsigned int charm : 10;
    unsigned int magicalMight : 10;
    unsigned int magicalMending : 10;
};

struct BaseCombatStats {
    char unk[0x2C];
    struct PrimaryCombatStats primaryStats;
};

struct ModifiableCombatStats {
    struct PrimaryCombatStats primaryStats; // 0xE
    char unk1[0x44];
    signed int attackBuff : 3;
    signed int defenseBuff : 3;
    signed int agilityBuff : 3;
    signed int charmBuff : 3;
    signed int magicalMightBuff : 3;
    signed int magicalMendingBuff : 3;
};

struct CombatantStruct {
    unsigned short flags;                       // +0x0
    union {                                     // +0x2
        unsigned short unk[0x99];
        char unkC[0x132];
    };
    struct BaseCombatStats* baseStats;          // +0x134, TODO: holds more general info than just stats
    struct ModifiableCombatStats* currentStats; // +0x138, includes things like buffs being applied
};

struct Unknown4CIntStruct {
    int unk[6];
};

// TODO I give up that struct for now...
// Because it changes with the place the player is in, I guess it's about the environment
// ONLY IN OPEN ZONES
struct UnknownC9Struct {    // 0x02359f34
    struct UnknownC9Content *unk1;  // +0x00;
    char unk2[0x40];                // +0x04
    int unk3;                       // +0x44
};

struct UnknownC9Content {
    char unk1[0x8];         // +0x00
    int unk2;               // +0x08, This is an address!
    char unk3[0x4];         // +0x0c
    int unk4;               // +0x10
    char unk5[0x2c];        // +0x14
    char unk6;              // +0x40
    char unk7;              // +0x41
    char unk8[0x2];         // +0x42
    int unk9[3];            // +0x44, With form 0xffffXXXX
    char unk10[0x1c];       // +0x50
    int unk11;              // +0x6c, number too...
    char unk12[0x24];       // +0x70
    int unk13;              // +0x94
    char unk14[0x8];        // +0x98
    short unk15;            // +0xa0
    char unk16[0x1a];       // +0xa2
    unsigned short unk17;   // +0xbc
    char unk18[0x66];       // +0xbe
    int unk19;              // +0x124, normal number apparently
    char unk20[0x18];       // +0x128
    int unk21;              // +0x140, form 0xffffXXXX?
    char unk22[0x52];       // +0x144
    unsigned short unk23;   // +0x196, normal number apparently
};

struct Unknown3b0Struct {
    int *unk0;          // 0x0
    int unk4;           // 0x4
    int unk8;           // 0x8
    short unkc;         // 0xc
    short padding;      // 0xe
    int unk10;          // 0x10
    unsigned int unk14; // 0x14
};

struct BattleStruct { 
    int unk0;                       // 0x0
    int unk4;                       // 0x4
    
    union {                         // 0x8
        int addressList[0xe9];
        // 0x70 to 0xa0, looks like they are not combatants but contains shorts
        // 0xc9 only set when not in battle and does not look like a combatant struct, changes when changing place...
        // TODO Look if changing zone within same room works (ie. beach and land in same zone)
        struct {
            struct CombatantStruct *combatantList[0x4c];        // 0, TODO: validate this size as well as this struct as a whole (base 0xe9)
            // 1: 22bbbdc
            // 2: 22f001c
            // 3: 22de95c
            // 4: 22cd29c
            struct Unknown4CIntStruct *unk4cStruct;             // 4c
            int addresses1[0x7c];                               // 4d
            struct UnknownC9Struct *environmentStruct;          // c9
            struct CombatantStruct *combatantListRest[0x1f];    // Probably not that but keep the work
        };
    };

    int unk3ac;                     // 0x3ac
    struct Unknown3b0Struct unk3b0; // 0x3b0
    unsigned int unk3c8;            // 0x3c8
    float unk3cc;                   // 0x3cc
    float unk3d0;                   // 0x3d0
    float unk3d4;                   // 0x3d4
    int unk3d8;                     // 0x3d8
    int unk3dc;                     // 0x3dc
    float unk3e0;                   // 0x3e0
    char unk3e4[0x2c1c];            // 0x3e4
    char unk3000[0x97d];            // 0x3000
};

// extern unsigned int func_0200cedc(unsigned int, unsigned int, int, int);

extern float data_020f33b4[6];

struct BattleStruct* GetBattleStruct();
struct CombatantStruct* GetCombatantFromListIfUnknown(struct BattleStruct* battleStruct, int combatantId);
unsigned short* GetCombatantFlagIfUnknown1(struct BattleStruct *battleStruct, int combatantId);
unsigned short* GetCombatantFlagIfUnknown2(struct BattleStruct *battleStruct, int combatantId);
unsigned short* GetCombatantFlagIfUnknown3(struct BattleStruct *battleStruct, int combatantId);
unsigned short* GetCombatantFlagIfUnknown4(struct BattleStruct *battleStruct, int combatantId);
struct CombatantStruct* GetCombatantFromList(struct BattleStruct* battleStruct, int combatantId);
struct UnknownC9Struct* GetEnvironmentInfo(struct BattleStruct *battleStruct);
struct CombatantStruct* GetUnknownInfo(struct BattleStruct *battleStruct);
unsigned short* GetCombatantFlagIfUnknown5(struct BattleStruct* battleStruct, int combatantId);
int GetNumberCombatant(BattleStruct *battleStruct, char *unknown);
bool IsUnknownIntOdd(struct BattleStruct *battleStruct);
void SetUnk3ac(struct BattleStruct *battleStruct, int value);
int GetUnk3ac(struct BattleStruct *battleStruct);
unsigned char GetUnk3000Char(struct BattleStruct *battleStruct);
int* GetUnk3b0(struct BattleStruct *battleStruct);
void SetUnk3b0(struct BattleStruct *battleStruct, int *value);
int* GetUnk3b0IfEqual2(struct BattleStruct *battleStruct);
int* GetUnk3b0IfEqual4(struct BattleStruct *battleStruct);
void InitUnk3b0(BattleStruct *battleStruct);
void ComputeUnk3b0Unk4Unk10(struct BattleStruct *battleStruct, unsigned int index, int param_3);
int GetUnk3b0Unk4(BattleStruct *battleStruct);
int GetUnk3b0Unk8(BattleStruct *battleStruct);
int GetUnk3b0Unk10(BattleStruct *battleStruct);
unsigned int GetUnk3b0Unk14(BattleStruct *battleStruct);
void SetUnk3b0Unkc(BattleStruct *battleStruct,short value);
short GetUnk3b0Unkc(BattleStruct *battleStruct);
void ComputeSomething(struct BattleStruct *battleStruct);
float GetUnk3cc(struct BattleStruct *battleStruct);
void UpdateUnk3dc(struct BattleStruct *battleStruct, float value);
void SetUnk3d8(struct BattleStruct *battleStruct, int value);
int GetUnk3dc(struct BattleStruct *battleStruct);
void UpdateUnk3dcWithValue(struct BattleStruct *battleStruct, int index);
bool IsUnk3dcNotZero(struct BattleStruct *battleStruct);
void SetUnk3e0(struct BattleStruct *battleStruct, float value);