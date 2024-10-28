#include "../Inc/opamp.h"

void Opamp::calculateParameters() {

    gain = Rfb / Rin;
    
}