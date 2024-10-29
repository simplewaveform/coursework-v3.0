#include "../Inc/InvOpamp.h"

void InvertingOpamp::calculateGain() {

    if (Rin != 0) {
        gain = -Rfb / Rin;
    } else {
        gain = 0;
    }

}