#pragma once
#include "System/MainStruct.h"

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
    unsigned short unk2;                        // +0x2
    unsigned short indexInMainList;           // +0x4
    unsigned short unk6[0x97];                  // +0x6
    struct BaseCombatStats* baseStats;          // +0x134, TODO: holds more general info than just stats
    struct ModifiableCombatStats* currentStats; // +0x138, includes things like buffs being applied
};

extern float data_020f33b4[6];
extern "C" void func_020ca594(struct MainStruct *, int, int);
extern "C" void func_020c99c8(unsigned char *);
extern "C" void func_02001aac(struct CombatantStruct **, int, int);
extern "C" void func_020ca650(int, int);


struct MainStruct* GetMainStruct();

// Get flag if constraint, else 0
unsigned short* GetCombatantFlagIfUnknown1(struct MainStruct *mainStruct, int combatantId);
unsigned short* GetCombatantFlagIfUnknown2(struct MainStruct *mainStruct, int combatantId);
unsigned short* GetCombatantFlagIfUnknown3(struct MainStruct *mainStruct, int combatantId);
unsigned short* GetCombatantFlagIfUnknown4(struct MainStruct *mainStruct, int combatantId);
unsigned short* GetCombatantFlagIfUnknown5(struct MainStruct* mainStruct, int combatantId);
unsigned short* GetCombatantFlagIfUnknown6(struct MainStruct* mainStruct, int combatantId);
unsigned short* GetCombatantFlagIfUnknown7(struct MainStruct* mainStruct, int combatantId);

// Combat related functions (I think)
struct CombatantStruct* GetCombatantFromListIfUnknown(struct MainStruct* mainStruct, int combatantId);
struct CombatantStruct* GetCombatantFromList(struct MainStruct* mainStruct, int combatantId);
struct UnknownC9Struct* GetEnvironmentInfo(struct MainStruct *mainStruct);
struct CombatantStruct* GetUnknownInfo(struct MainStruct *mainStruct);
int GetNumberCombatant(struct MainStruct *mainStruct, char *unknown);
bool IsUnknownIntOdd(struct MainStruct *mainStruct);

// Setters and getters (Prob not battle?)
struct UnkStruct* UnkStructCopy(struct UnkStruct *src, struct UnkStruct *dest);
void InitUnk0(struct MainStruct *mainStruct, int param, int value);
void InitUnk6(struct MainStruct *mainStruct);
unsigned char InitUnk5(struct MainStruct *mainStruct);
void InitUnk3b0(MainStruct *mainStruct);
struct UnkStruct* InitUnk3f8(struct MainStruct *mainStruct, struct UnkStruct *value);
struct UnkStruct* InitUnk3f8Clone(struct MainStruct *mainStruct, struct UnkStruct *value);
void InitUnk7f74(struct MainStruct *mainStruct);

unsigned char GetUnk4(struct MainStruct *mainStruct);
int GetUnk3ac(struct MainStruct *mainStruct);
int* GetUnk3b0(struct MainStruct *mainStruct);
int* GetUnk3b0IfEqual2(struct MainStruct *mainStruct);
int* GetUnk3b0IfEqual4(struct MainStruct *mainStruct);
int GetUnk3b0Unk4(struct MainStruct *mainStruct);
int GetUnk3b0Unk8(struct MainStruct *mainStruct);
short GetUnk3b0Unkc(struct MainStruct *mainStruct);
int GetUnk3b0Unk10(struct MainStruct *mainStruct);
unsigned int GetUnk3b0Unk14(struct MainStruct *mainStruct);
float GetUnk3cc(struct MainStruct *mainStruct);
int GetUnk3dc(struct MainStruct *mainStruct);
float GetUnk3e0(struct MainStruct *mainStruct);
struct UnkStruct* GetUnk3f8(struct MainStruct *mainStruct);
unsigned char GetUnk3000Char(struct MainStruct *mainStruct);

void SetUnk0(struct MainStruct *mainStruct, int value);
void SetUnk4(struct MainStruct *mainStruct, unsigned char value);
void SetUnk3ac(struct MainStruct *mainStruct, int value);
void SetUnk3b0(struct MainStruct *mainStruct, int *value);
void SetUnk3b0Unkc(MainStruct *mainStruct,short value);
void SetUnk3d8(struct MainStruct *mainStruct, int value);
void SetUnk3e0(struct MainStruct *mainStruct, float value);

bool IsUnk3dcNotZero(struct MainStruct *mainStruct);
void UpdateUnk3dc(struct MainStruct *mainStruct, float value);
void UpdateUnk3dcWithValue(struct MainStruct *mainStruct, int index);
void ComputeUnk3b0Unk4Unk10(struct MainStruct *mainStruct, unsigned long long index);
void ComputeSomething(struct MainStruct *mainStruct);