#include "../Inc/TL431.h"

TL431::TL431() = default;

void TL431::calculateParameters() {

    outputVoltage = 2.5 * (1 + R1 / R2);

}