#include "../Inc/LowpassRC.h"
#include <cmath>

/**
 * @brief Calculates parameters for the low-pass RC filter.
 * The cutoff frequency is calculated as: f = 1 / (2 * π * R * C).
 * The time constant is calculated as: τ = R * C.
 */
void LowpassRC::calculateParameters() {

    frequency = 1.0 / (2e-6 * M_PI * R * C);
    time = R * C;

}