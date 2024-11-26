#ifndef CIRCUITWAVE_FILTER_H
#define CIRCUITWAVE_FILTER_H

#include "../Inc/CircuitComponent.h"

/**
 * @brief Abstract class for filter components.
 * Derived classes must implement the `calculateParameters` method
 * to calculate specific parameters for each type of filter.
 */
class Filter : public CircuitComponent {
protected:
    double frequency{}, time{};

public:
    [[nodiscard]] double getFrequency() const { return frequency; };
    [[nodiscard]] double getTime() const { return time; };

};

#endif //CIRCUITWAVE_FILTER_H