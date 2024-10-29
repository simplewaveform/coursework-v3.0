#ifndef CIRCUITWAVE_OPAMP_H
#define CIRCUITWAVE_OPAMP_H

#include "../Inc/CircuitComponent.h"

class Opamp : public CircuitComponent {

public:
    double Rfb, Rin, Rg, gain;
    Opamp() : Rfb(0), Rin(0), Rg(0), gain(0) {}

};

#endif
