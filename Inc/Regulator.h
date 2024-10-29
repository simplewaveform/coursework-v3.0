#ifndef CIRCUITWAVE_REGULATOR_H
#define CIRCUITWAVE_REGULATOR_H

#include "CircuitComponent.h"

class Regulator : public CircuitComponent {
public:
    double R1{}, R2{}, outputVoltage{};

    void setResistors(double r1, double r2) {
        R1 = r1;
        R2 = r2;
    }

    ~Regulator() override = default;
};

#endif //CIRCUITWAVE_REGULATOR_H
