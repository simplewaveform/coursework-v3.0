#include "../Inc/NonInvertingOpamp.h"

/**
 * @brief Calculates the gain of a non-inverting operational amplifier.
 * Gain is calculated using the formula: gain = 1 + (Rfb / Rg).
 * If Rg is zero, the gain is set to zero.
 */
void NonInvertingOpamp::calculateParameters() {

    gain = (Rg != 0) ? (1 + (Rfb / Rg)) : 0;

}