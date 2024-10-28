#ifndef CIRCUITWAVE_REGULATOR_H
#define CIRCUITWAVE_REGULATOR_H

#include "circuitComponent.h"

class regulator : public circuitComponent {

public:
    double R1{}, R2{}, outputVoltage{}, tolerance{};

};

#endif //CIRCUITWAVE_REGULATOR_H