#include "../Inc/lowpassRC.h"
#include <cmath>

lowpassRC::lowpassRC() = default;

void lowpassRC::calculateParameters() {
    frequency = 1.0 / (2 * M_PI * R * C);
    time = R * C;
}