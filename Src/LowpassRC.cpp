#include "../Inc/LowpassRC.h"
#include <cmath>

void LowpassRC::calculateParameters() {

    frequency = 1.0 / (2e-6 * M_PI * R * C);
    time = R * C;

}