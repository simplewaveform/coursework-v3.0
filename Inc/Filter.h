#ifndef CIRCUITWAVE_FILTER_H
#define CIRCUITWAVE_FILTER_H
#include "../Inc/CircuitComponent.h"

class Filter : public CircuitComponent {

public:
    double R {}, C{}, frequency{}, time{};

};

#endif //CIRCUITWAVE_FILTER_H
