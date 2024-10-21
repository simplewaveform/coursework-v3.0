#ifndef CIRCUITWAVE_TL431_H
#define CIRCUITWAVE_TL431_H

#include "../Inc/regulator.h"

class TL431 : public regulator {

public:
    explicit TL431();
    void calculateParameters() override;

};


#endif //CIRCUITWAVE_TL431_H