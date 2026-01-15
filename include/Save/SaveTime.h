#pragma once

#include "System/MainStruct.h"

// This is returning an unsigned long long with probably clock info 
extern "C" unsigned long long func_020c8d5c(void);

void SetPlayedTime1(struct MainStruct *mainStruct, short *hourPtr, char *secondPtr1, char *secondPtr2);
void SetPlayedTime2(struct MainStruct *mainStruct, short *hourPtr, char *secondPtr1, char *secondPtr2);
void SetPlayedSeconds(struct MainStruct *mainStruct, int *valuePtr);