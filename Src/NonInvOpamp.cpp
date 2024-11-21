#include "../Inc/NonInvOpamp.h"

void NonInvertingOpamp::calculateParameters() {

    if (Rin != 0) {
        gain = 1 + (Rfb / Rin);
    } else {
        gain = 0;
    }

}