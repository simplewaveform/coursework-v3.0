#include "../Inc/LM317.h"

/**
 * @brief Calculates the output voltage of the LM317 regulator.
 * The voltage is calculated using the formula: Vout = 1.25 * (1 + R1 / R2).
 */
void LM317::calculateParameters() {

    outputVoltage = 1.25 * (1 + R1 / R2);

}

/**
 * @brief Retrieves the LM317 regulator's parameters as a formatted string.
 * @return A string with R1, R2, and output voltage details.
 */
wxString LM317::GetData() const {

    return wxString::Format("LM317 parameters:\nR1: %.2f Ω\nR2: %.2f Ω\nVoltage: %.2f V",
                            R1, R2, outputVoltage);

}