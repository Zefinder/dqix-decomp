#include <globaldefs.h>
#include "Combat/Main/UnknownFunctions.h"

/**
 * Used in:
 * func_ov024_021e6a90
 * func_ov024_021fa7ec
 * func_ov024_021fdf04
 */
ARM float UnknwownFunction1(int unknown1) {
    return unknown1 * -0.25f + 1; 
}

/**
 * Used in:
 * func_ov024_021e6a90
 * func_ov024_021fa7ec
 * func_ov024_021fdf04
 */
ARM float UnknwownFunction2(int unknown1) { // Exactly the same up
    return unknown1 * -0.25f + 1; 
}

/**
 * Used in func_ov000_02156cc4
 */
ARM float ObfuscatedZero(float useless1, unsigned int useless2) {
    float zero = 0;
    float tmp = useless2;
    return (1 / tmp) * (zero * useless1);
}

/**
 * Used in:
 * func_ov024_021e67c8
 * func_ov024_021e67c8
 * func_ov024_021e6948
 * func_ov024_021e6948
 * func_ov024_021e6a90
 * func_ov024_021e6a90
 * func_ov024_021fa7ec
 * func_ov024_021fa7ec
 * func_ov024_021fdf04
 * func_ov024_021fdf04
 */
ARM float GetUnknownFloat(int index) {
    return data_020e88c0[index];
}

/**
 * Used in:
 * func_ov024_021eb5d0
 * func_ov024_021fb490
 */
ARM float GetUnknownFloat2(int index) {
    if (index < 0) {
        index = 0;
    }
    if (4 < index) {
        index = 4;
    }
    return data_020e88d0[index];
}

/**
 * Used in func_ov000_02157288
 */
ARM float GetScaleMultiplier(bool toScale) {
    return toScale ? 1 : 0.5f;
}

/**
 * Used in func_ov000_02157288
 */
ARM float GetScaleMultiplier2(bool toScale) { 
    return toScale ? 0.5f : 0.25f;
}

/**
 * Used in:
 * func_ov000_02156118
 * func_ov000_02156270 
 */
ARM float GetUnknownFloat3(int index) {
    if (index < 0) {
        return 0;
    }
    if (index > 4) {
        return 0;
    }
    
    return data_020e88e4[index];
}