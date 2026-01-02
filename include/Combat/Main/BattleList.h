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
    unsigned short unk[0x99];                   // +0x2
    struct BaseCombatStats* baseStats;          // +0x134, TODO: holds more general info than just stats
    struct ModifiableCombatStats* currentStats; // +0x138, includes things like buffs being applied
};

struct BattleStruct { 
    int unk0;
    int unk4; 
    struct CombatantStruct *combatantList[0xc9]; // TODO: validate this size as well as this struct as a whole (base 0xe9)
    // 1: 22bbbdc
    // 2: 22f001c
    // 3: 22de95c
    // 4: 22cd29c
    // 0x70 to 0x9f, looks like they are not combatants but arrays of 2 shorts...
    // 0xc9 only set when not in battle and does not look like a combatant struct, changes when changing place...
    // TODO Look if changing zone within same room works (ie. beach and land in same zone)
    struct UnknownC9Struct *environmentStruct; // c9
    struct CombatantStruct *combatantListRest[0x1f]; // Probably not that but keep the work
};

// TODO I give up that struct for now...
// Because it changes with the place the player is in, I guess it's about the environment
// ONLY IN OPEN ZONES
struct UnknownC9Struct {    // 0x02359f34
    struct UnknownC9Content *ukn1;  // +0x00;
    char ukn2[0x40];                // +0x04
    int ukn3;                       // +0x44
};

struct UnknownC9Content {
    char ukn1[0x8];         // +0x00
    int ukn2;               // +0x08, This is an address!
    char ukn3[0x4];         // +0x0c
    int ukn4;               // +0x10
    char ukn5[0x2c];        // +0x14
    char ukn6;              // +0x40
    char ukn7;              // +0x41
    char ukn8[0x2];         // +0x42
    int ukn9[3];            // +0x44, With form 0xffffXXXX
    char ukn10[0x1c];       // +0x50
    int ukn11;              // +0x6c, number too...
    char ukn12[0x24];       // +0x70
    int ukn13;              // +0x94
    char ukn14[0x8];        // +0x98
    short ukn15;            // +0xa0
    char ukn16[0x1a];       // +0xa2
    unsigned short ukn17;   // +0xbc
    char ukn18[0x66];       // +0xbe
    int ukn19;              // +0x124, normal number apparently
    char ukn20[0x18];       // +0x128
    int ukn21;              // +0x140, form 0xffffXXXX?
    char ukn22[0x52];       // +0x144
    unsigned short ukn23;   // +0x196, normal number apparently
};



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