#ifndef CIRCUITWAVE_LOWPASSRC_H
#define CIRCUITWAVE_LOWPASSRC_H

#include "../Inc/filter.h"

class lowpassRC : public filter {

public:
    explicit lowpassRC();
    double R{};
    void calculateParameters() override;

};

#endif //CIRCUITWAVE_LOWPASSRC_H