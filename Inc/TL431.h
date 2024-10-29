#ifndef CIRCUITWAVE_TL431_H
#define CIRCUITWAVE_TL431_H

#include "../Inc/Regulator.h"

class TL431 : public Regulator {

public:
    explicit TL431();
    void calculateParameters() override;

};

#endif //CIRCUITWAVE_TL431_H