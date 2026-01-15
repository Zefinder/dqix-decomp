#pragma once
#ifdef __MWERKS__
#define AT_ADDRESS(xyz) : (xyz)
#define DECL_SECTION(x) __declspec(section x)
#define EXPORT __declspec(export)
#define WEAK __declspec(weak)
#define ASM asm
#define ARM _Pragma("thumb off")
#define THUMB _Pragma("thumb on")
#else
#define AT_ADDRESS(xyz)
#define DECL_SECTION(x)
#define EXPORT
#define WEAK
#define ASM
#define ARM 
#define THUMB
#endif
#define NULL 0 // appeases vs code
#define BUS_CLOCKSPEED 0x1ff6210
#define ARM7_CLOCKSPEED 0x1ff6210
#define ARM9_CLOCKSPEED 0x3fec420
