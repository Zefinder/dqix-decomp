#include <globaldefs.h>
#include "Combat/Main/BattleList.h"
#include "System/MainStruct.h"
#include "Combat/Main/UnknownFunctions.h"

ARM void SetUnk3ac(struct MainStruct *mainStruct, int value) {
    mainStruct->unk3ac = value;
}

ARM int GetUnk3ac(struct MainStruct *mainStruct) {
    return mainStruct->unk3ac;
}

ARM unsigned char GetUnk3000Char(struct MainStruct *mainStruct) {
    return mainStruct->unk3000[0x97c];
}

ARM int* GetUnk3b0(struct MainStruct *mainStruct) {
    return mainStruct->unk3b0.unk0;
}

ARM void SetUnk3b0(struct MainStruct *mainStruct, int *value) {
    mainStruct->unk3b0.unk0 = value;
}

ARM int* GetUnk3b0IfEqual2(struct MainStruct *mainStruct) {
    int *intArray = mainStruct->unk3b0.unk0;
    if (intArray != 0 && (GetIntValue(intArray) & 2)) {
        return mainStruct->unk3b0.unk0;
    }

    return 0;
}

ARM int* GetUnk3b0IfEqual4(struct MainStruct *mainStruct) {
    int *intArray = mainStruct->unk3b0.unk0;
    if (intArray != 0 && (GetIntValue(intArray) & 4)) {
        return mainStruct->unk3b0.unk0;
    }

    return 0;
}

ARM void InitUnk3b0(struct MainStruct *mainStruct) {
    mainStruct->unk3b0.unk4 = 0x21;
    mainStruct->unk3b0.unk8 = 0x21;
    mainStruct->unk3b0.unkc = 0x1000;
    mainStruct->unk3b0.unk14 = 2;
    mainStruct->unk3b0.unk10 = 0x2000;
}

void ComputeUnk3b0Unk4Unk10(struct MainStruct *mainStruct, unsigned long long index) {
    // Looks like an index...
    if (index > 0xc350) {
        index = 0xc350;
    }
    
    mainStruct->unk3b0.unk14 = mainStruct->unk3c8;
    mainStruct->unk3c8 = 0;
    if (mainStruct->unk3b0.unk14 > 3) {
        mainStruct->unk3b0.unk14 = 3;
    }

    // Compute and set to unk8
    unsigned int lowerByte = index / 1000; // Only lower byte
    mainStruct->unk3b0.unk8 = lowerByte;

    // Set value to unk4
    float floatValue = lowerByte * (mainStruct->unk3b0.unkc / 4096.0f);
    lowerByte = floatValue;
    mainStruct->unk3b0.unk4 = lowerByte;

    // Set value to unk10
    floatValue = lowerByte;
    floatValue = floatValue / 17.0f;
    floatValue = 4096.0f * floatValue;
    mainStruct->unk3b0.unk10 = floatValue;
}

ARM int GetUnk3b0Unk4(struct MainStruct *mainStruct) {
    return mainStruct->unk3b0.unk4;
}

ARM int GetUnk3b0Unk8(struct MainStruct *mainStruct) {
    return mainStruct->unk3b0.unk8;
}

ARM int GetUnk3b0Unk10(struct MainStruct *mainStruct) {
    return mainStruct->unk3b0.unk10;
}

ARM unsigned int GetUnk3b0Unk14(struct MainStruct *mainStruct) {
    return mainStruct->unk3b0.unk14;
}

ARM void SetUnk3b0Unkc(struct MainStruct *mainStruct, short value) {
    mainStruct->unk3b0.unkc = value;
    return;
}

ARM short GetUnk3b0Unkc(struct MainStruct *mainStruct) {
    return mainStruct->unk3b0.unkc;
}

ARM void ComputeSomething(struct MainStruct *mainStruct) {
    if (mainStruct->unk3d8 == 0) {
        return;
    }
    
    // TODO This is a return but decomp function first to know!
    UpdateUnk3dc(mainStruct, mainStruct->unk3cc + mainStruct->unk3b0.unk14 * mainStruct->unk3d4);
}

ARM float GetUnk3cc(struct MainStruct *mainStruct) {
    return mainStruct->unk3cc;
}

ARM void UpdateUnk3dc(struct MainStruct *mainStruct, float value) {
    if (value >= mainStruct->unk3d0) {
        float tmp = value / mainStruct->unk3d0;
        tmp = (int)tmp * mainStruct->unk3d0;
        value = value - tmp;
    }

    mainStruct->unk3cc = value;
    if (value >= mainStruct->unk3d0) {
        mainStruct->unk3cc = mainStruct->unk3cc - mainStruct->unk3d0;
    }

    if (mainStruct->unk3cc >= data_020f33b4[2]) {
        mainStruct->unk3dc = 3;
    } else if (mainStruct->unk3cc >= data_020f33b4[3]) {
        mainStruct->unk3dc = 2;
    } else if (mainStruct->unk3cc >= data_020f33b4[4]) {
        mainStruct->unk3dc = 1;
    } else { 
        mainStruct->unk3dc = 0;
    }
}

ARM void SetUnk3d8(struct MainStruct *mainStruct, int value) {
    mainStruct->unk3d8 = value;
}

ARM int GetUnk3dc(struct MainStruct *mainStruct) {
    return mainStruct->unk3dc;
}

ARM void UpdateUnk3dcWithValue(struct MainStruct *mainStruct, int index) {
    if (index < 4) {
        float arr[4];
        mainStruct->unk3dc = index;
        arr[0] = data_020f33b4[5];
        arr[1] = data_020f33b4[4];
        arr[2] = data_020f33b4[3];
        arr[3] = data_020f33b4[2]; // Matching indices with UpdateUnk3dc!
        UpdateUnk3dc(mainStruct, arr[index]);
    }
}

ARM bool IsUnk3dcNotZero(struct MainStruct *mainStruct) {
    return mainStruct->unk3dc != 0;
}

ARM void SetUnk3e0(struct MainStruct *mainStruct, float value) {
    if (!(value < 0)) {
        mainStruct->unk3e0 = value;
    }
}

ARM float GetUnk3e0(struct MainStruct *mainStruct) {
    return mainStruct->unk3e0;
}