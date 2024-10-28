#include "../Inc/lowpassLC.h"
#include <cmath>

lowpassLC::lowpassLC() = default;

void lowpassLC::calculateParameters() {

    frequency = 1.0 / (2 * M_PI * L * C);
    time = L * C;

}