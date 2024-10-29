#ifndef CIRCUITWAVE_NONINVOPAMP_H
#define CIRCUITWAVE_NONINVOPAMP_H

#include "../Inc/Opamp.h"

class NonInvertingOpamp : public Opamp {

public:
    void calculateParameters() override;

};

#endif //CIRCUITWAVE_NONINVOPAMP_H