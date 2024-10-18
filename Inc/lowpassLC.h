#ifndef CIRCUITWAVE_LOWPASSLC_H
#define CIRCUITWAVE_LOWPASSLC_H

#include "../Inc/filter.h"

class lowpassLC : public filter {

public:
    double L, C, frequency, time;
    lowpassLC(double R, double C);
    void calculateParameters() override;

};

#endif //CIRCUITWAVE_LOWPASSLC_H