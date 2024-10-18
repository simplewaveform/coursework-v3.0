#ifndef CIRCUITWAVE_LOWPASSRC_H
#define CIRCUITWAVE_LOWPASSRC_H

#include "../Inc/filter.h"

class lowpassRC : public filter {

public:
    double R, C, frequency, time;
    lowpassRC(double R, double C);
    void calculateParameters() override;

};

#endif //CIRCUITWAVE_LOWPASSRC_H