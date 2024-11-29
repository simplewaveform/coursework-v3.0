#ifndef CIRCUITWAVE_LOWPASSRC_H
#define CIRCUITWAVE_LOWPASSRC_H

#include "../Inc/Filter.h"

/**
 * @brief Lowpass RC filter class.
 * Calculates the cutoff frequency and time constant for an RC lowpass filter.
 */
class LowpassRC : public Filter {
private:
    double R{}, C{};

public:
    void setR(double r) { this->R = r; }
    void setC(double c) { this->C = c; }
    [[nodiscard]] double getR() const { return R; };
    [[nodiscard]] double getC() const { return C; };
    void calculateParameters() override;

};

#endif //CIRCUITWAVE_LOWPASSRC_H