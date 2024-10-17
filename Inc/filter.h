#ifndef CIRCUITWAVE_FILTER_H
#define CIRCUITWAVE_FILTER_H
#include "../Inc/circuitComponent.h"

class filter : public circuitComponent {
protected:
    void calculateParameters() override = 0;

};

#endif //CIRCUITWAVE_FILTER_H
