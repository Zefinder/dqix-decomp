#pragma once

#include "System/Random.h"

int RoundUp(float value);
float CalculatePhysicalDamage(int attack, int defense, struct Random* random);
float CalculateAttackBuffMultiplier(signed char buffLevel);
float CalculateDefenseBuffMultiplier(signed char buffLevel);
float CalculateAgilityBuffMultiplier(signed char buffLevel);
float CalculateCharmBuffMultiplier(signed char buffLevel);
float CalculateMagicalMightBuffMultiplier(signed char buffLevel);
float CalculateMagicalMendingBuffMultiplier(signed char buffLevel);
float CalculateDamage(int damage, int isCrit, struct Random *random);