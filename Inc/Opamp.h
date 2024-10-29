#ifndef CIRCUITWAVE_OPAMP_H
#define CIRCUITWAVE_OPAMP_H

class Opamp {

public:
    double Rfb, Rin, Rg, gain;
    Opamp() : Rfb(0), Rin(0), Rg(0), gain(0) {}
    virtual void calculateGain() = 0;

};

#endif
