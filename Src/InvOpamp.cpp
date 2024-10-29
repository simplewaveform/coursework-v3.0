#include "../Inc/InvOpamp.h"

void InvertingOpamp::calculateParameters() {

    if (Rin != 0) {
        gain = -Rfb / Rin;
    } else {
        gain = 0;
    }

}