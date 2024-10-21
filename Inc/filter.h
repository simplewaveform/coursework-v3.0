#ifndef CIRCUITWAVE_FILTER_H
#define CIRCUITWAVE_FILTER_H
#include "../Inc/circuitComponent.h"

class filter : public circuitComponent {

public:
    double C{}, frequency{}, time{};

};

#endif //CIRCUITWAVE_FILTER_H
