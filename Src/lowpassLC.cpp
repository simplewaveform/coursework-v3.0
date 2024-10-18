#include "../Inc/lowpassLC.h"
#include <cmath>

lowpassLC::lowpassLC(double L, double C) : L(L), C(C), frequency(0.0), time(0.0) {
    calculateParameters();
}

void lowpassLC::calculateParameters() {
    frequency = 1.0 / (2 * M_PI * L * C);
    time = L * C;
}