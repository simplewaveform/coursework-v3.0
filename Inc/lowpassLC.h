#ifndef CIRCUITWAVE_LOWPASSLC_H
#define CIRCUITWAVE_LOWPASSLC_H

#include "../Inc/filter.h"

class lowpassLC : public filter {

public:
    explicit lowpassLC();
    double L{};
    void calculateParameters() override;

};

#endif //CIRCUITWAVE_LOWPASSLC_H