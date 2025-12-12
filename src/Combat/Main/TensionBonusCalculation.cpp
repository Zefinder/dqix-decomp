#include <globaldefs.h>
#include "Combat/Main/TensionCalculations.h"

// Unknown = 0 or 1
ARM float GetTensionMultiplier(int tensionLevel, int unknown) {
    float tensionMultiplier = *(tensionMultiplierTable + tensionLevel * 2 + unknown);
    if (tensionMultiplier < 1) {
        tensionMultiplier = 1.0f;
    }

    return tensionMultiplier;
}

ARM float CalculateTensionBonus(int tension, int attackerLevel) {
    float levelMultiplier = attackerLevel / 10;
    levelMultiplier = 1.0f + levelMultiplier;
    return levelMultiplier * tension;
}