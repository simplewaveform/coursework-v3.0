#ifndef CIRCUITWAVE_OPAMP_H
#define CIRCUITWAVE_OPAMP_H

#include "../Inc/CircuitComponent.h"

/**
 * @brief Abstract class for operational amplifiers.
 * This class provides basic functionality for calculating the gain
 * of both inverting and non-inverting operational amplifiers.
 */
class Opamp : public CircuitComponent {
protected:
    double gain{};

public:
    [[nodiscard]] double getGain() const { return gain; };

};

#endif //CIRCUITWAVE_OPAMP_H