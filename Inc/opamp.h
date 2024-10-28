#ifndef CIRCUITWAVE_OPAMP_H
#define CIRCUITWAVE_OPAMP_H

#include "../Inc/circuitComponent.h"

class Opamp : public circuitComponent {

public:
    void calculateParameters() override;
    double gain{}, Rin{}, Rfb{};

};

#endif //CIRCUITWAVE_OPAMP_H