#ifndef CIRCUITWAVE_FILTER_H
#define CIRCUITWAVE_FILTER_H
#include "../Inc/CircuitComponent.h"

class Filter : public CircuitComponent {

protected:
    double frequency{};
    double time{};
public:
    [[nodiscard]] double getFrequency() const { return frequency; };
    [[nodiscard]] double getTime() const { return time; };

};

#endif //CIRCUITWAVE_FILTER_H
