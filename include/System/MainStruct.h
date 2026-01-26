#pragma once
#include "Combat/Main/BattleList.h"

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

struct UnkStruct {
    unsigned short unk0;    // 0x0
    unsigned char unk2;     // 0x2
    unsigned char unk3;     // 0x3
    unsigned char unk4;     // 0x4
    unsigned char unk5;     // 0x5
    unsigned char unk6;     // 0x6
    unsigned char unk7;     // 0x7
    unsigned char unk8;     // 0x8
    unsigned char unk9;     // 0x9
    unsigned char unka;     // 0xa
    char unkb;              // 0xb
    unsigned char unkc;     // 0xc
    unsigned char unkd;     // 0xd
    unsigned char unke;     // 0xe
    char padding;           // 0xf 
    int unk10[3];           // 0x10
    short unk1c;            // 0x1c
    short unk1e;            // 0x1e
    int unk20;              // 0x20
    int unk24;              // 0x24
    int unk28;              // 0x28
    int unk2c;              // 0x2c
    int unk30[3][4];        // 0x30
    unsigned char unk60;    // 0x60
    unsigned char unk61;    // 0x61
    unsigned char unk62;    // 0x62
    unsigned char unk63;    // 0x63
    unsigned char unk64;    // 0x64
    unsigned char unk65;    // 0x65
    unsigned char unk66;    // 0x66
    unsigned char unk67;    // 0x67
    unsigned char unk68;    // 0x68
    unsigned char unk69;    // 0x69
    short unk6a;            // 0x6a
    short unk6c;            // 0x6c
    unsigned char unk6e;    // 0x6e
    char padding2;          // 0x6f
};

struct Unk7f74Struct {
    unsigned char unk0;          // 0x0
    unsigned char unk1;          // 0x1
    unsigned char unk2[4];       // 0x2
    unsigned char unk6;          // 0x6
};

struct MainStruct { 
    int unk0;                       // 0x0
    unsigned char unk4;             // 0x4
    unsigned char unk5;             // 0x5
    unsigned char unk6_0:1;         // 0x6
    unsigned char unk6_1:7;         // 0x6
    char unk7;                      // 0x7
    
    union {                         // 0x8
        struct CombatantStruct *combatantList[0xe9];        // 0, TODO: validate this size as well as this struct as a whole (base 0xe9)
        int addressList[0xe9];
        // 0x70 to 0xa0, looks like they are not combatants but contains shorts
        // 0xc9 only set when not in battle and does not look like a combatant struct, changes when changing place...
        // TODO Look if changing zone within same room works (ie. beach and land in same zone)
        struct {
            struct CombatantStruct *firstCombatantList[0x4c];        // 0, TODO: validate this size as well as this struct as a whole (base 0xe9)
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
    int unk3e4;                     // 0x3e4
    unsigned long long unk3e8;      // 0x3e8
    unsigned long long unk3f0;      // 0x3f0
    struct UnkStruct unk3f8;        // 0x3f8
    char unk468[0x2b98];            // 0x468
    unsigned char unk3000[0x4f74];  // 0x3000
    struct Unk7f74Struct unk7f74;   // 0x7f74
};