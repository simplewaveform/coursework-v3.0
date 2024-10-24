#include "../Inc/LM317.h"

LM317::LM317() = default;

void LM317::calculateParameters() {

    outputVoltage = 1.25 * (1 + R1 / R2);

}