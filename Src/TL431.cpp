#include "../Inc/TL431.h"

/**
 * @brief Calculates the output voltage of the TL431 regulator.
 * The voltage is calculated using the formula: Vout = 2.5 * (1 + R1 / R2).
 */
void TL431::calculateParameters() {

    outputVoltage = 2.5 * (1 + R1 / R2);

}

/**
 * @brief Retrieves the TL431 regulator's parameters as a formatted string.
 * @return A string with R1, R2, and output voltage details.
 */
wxString TL431::getData() const {

    return wxString::Format("TL431 parameters:\nR1: %.2lf Ω\nR2: %.2lf Ω\nVoltage: %.2lf V",
                            R1, R2, outputVoltage);

}