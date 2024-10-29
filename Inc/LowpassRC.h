#ifndef CIRCUITWAVE_LOWPASSRC_H
#define CIRCUITWAVE_LOWPASSRC_H

#include "../Inc/Filter.h"

class LowpassRC : public Filter {

public:
    explicit LowpassRC();
    void calculateParameters() override;

};

#endif //CIRCUITWAVE_LOWPASSRC_H