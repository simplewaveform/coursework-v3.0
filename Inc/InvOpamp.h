#ifndef CIRCUITWAVE_INVOPAMP_H
#define CIRCUITWAVE_INVOPAMP_H

#include "../Inc/Opamp.h"

class InvertingOpamp : public Opamp {

public:
    void calculateParameters() override;

};

#endif //CIRCUITWAVE_INVOPAMP_H
