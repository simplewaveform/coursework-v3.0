#ifndef CIRCUITWAVE_LOWPASSRC_H
#define CIRCUITWAVE_LOWPASSRC_H

#include "../Inc/Filter.h"

class LowpassRC : public Filter {

public:
    explicit LowpassRC();
    double R{};
    void calculateParameters() override;

};

#endif //CIRCUITWAVE_LOWPASSRC_H