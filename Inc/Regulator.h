#ifndef CIRCUITWAVE_REGULATOR_H
#define CIRCUITWAVE_REGULATOR_H

#include "CircuitComponent.h"

class Regulator : public CircuitComponent {
public:
    double R1{}, R2{}, outputVoltage{};
    ~Regulator() override = default;

};

#endif //CIRCUITWAVE_REGULATOR_H
