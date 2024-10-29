#include "../Inc/NonInvOpamp.h"

void NonInvertingOpamp::calculateParameters() {

    if (Rg != 0) {
        gain = 1 + (Rfb / Rg);
    } else {
        gain = 0;
    }

}