#include <globaldefs.h>
#include "Combat/Main/UnknownFunctions.h"

ARM float UnknwownFunction1(int unknown1) {
    return unknown1 * -0.25f + 1f; 
}

ARM float UnknwownFunction2(int unknown1) { // Exactly the same up
    return unknown1 * -0.25f + 1f; 
}

ARM float ObfuscatedZero(float useless1, unsigned int useless2) {
    float zero = 0f;
    float tmp = useless2;
    return (1f / tmp) * (zero * useless1);
}
