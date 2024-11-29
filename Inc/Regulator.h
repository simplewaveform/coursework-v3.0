#ifndef CIRCUITWAVE_REGULATOR_H
#define CIRCUITWAVE_REGULATOR_H

#include "CircuitComponent.h"

/**
 * @brief Abstract base class for voltage regulators.
 * This class provides common functionality for calculating output
 * voltage and fetching regulator data.
 */
class Regulator : public CircuitComponent {
protected:
    double outputVoltage{};

public:
    [[nodiscard]] virtual wxString getData() const = 0;
    [[nodiscard]] double getVoltage() const { return outputVoltage; };

};

#endif //CIRCUITWAVE_REGULATOR_H