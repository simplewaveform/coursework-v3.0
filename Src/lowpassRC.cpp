#include "../Inc/lowpassRC.h"
#include <cmath>

lowpassRC::lowpassRC(double R, double C) : R(R), C(C), frequency(0.0), time(0.0) {
    calculateParameters();
}

void lowpassRC::calculateParameters() {
    frequency = 1.0 / (2 * M_PI * R * C);
    time = R * C;
}
