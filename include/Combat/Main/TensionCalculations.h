#pragma once

extern float data_020e88f8[10];
#define tensionMultiplierTable data_020e88f8

float GetTensionMultiplier(int tensionLevel, int unknown);
float CalculateTensionBonus(int tension, int attackerLevel);