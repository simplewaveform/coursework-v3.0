#ifndef CIRCUITWAVE_INVOPAMP_H
#define CIRCUITWAVE_INVOPAMP_H

#include "../Inc/Opamp.h"

class InvertingOpamp : public Opamp {

public:
    void calculateGain() override;

};

#endif //CIRCUITWAVE_INVOPAMP_H
