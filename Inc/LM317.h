#ifndef CIRCUITWAVE_LM317_H
#define CIRCUITWAVE_LM317_H

#include "../Inc/Regulator.h"

class LM317 : public Regulator {

public:
    explicit LM317();
    void calculateParameters() override;

};

#endif //CIRCUITWAVE_LM317_H
