#include <globaldefs.h>

#include "System/Random.h"

ARM float CalculateDamage(int damage, int isCrit, struct Random *random) {
    if (random == NULL) {
        random = &data_02108ddc;
    }

    if (isCrit) {
        return damage * NextRandomFloatBetween(random, 0.95f, 1.05f);
    } else {
        return damage * NextRandomFloatBetween(random, 1.5f, 2f);
    }
}