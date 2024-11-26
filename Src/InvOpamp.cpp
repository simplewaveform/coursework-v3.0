#include "../Inc/InvOpamp.h"

/**
 * @brief Calculates the gain of an inverting operational amplifier.
 * Gain is calculated using the formula: gain = -Rfb / Rin.
 * If Rin is zero, the gain is set to zero.
 */
void InvertingOpamp::calculateParameters() {

    gain = (Rin != 0) ? (-Rfb / Rin) : 0;

}