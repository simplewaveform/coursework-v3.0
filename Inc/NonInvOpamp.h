#ifndef CIRCUITWAVE_NONINVOPAMP_H
#define CIRCUITWAVE_NONINVOPAMP_H

#include "../Inc/Opamp.h"

/**
 * @brief Non-inverting operational amplifier class.
 * Inherits from `Opamp` and calculates the gain for a non-inverting amplifier.
 */
class NonInvertingOpamp : public Opamp {
private:
    double Rfb{}, Rg{};

public:
    void setRfb(double rfb) { this->Rfb = rfb; }
    void setRg(double rg) { this->Rg = rg; }
    [[nodiscard]] double getRfb() const { return Rfb; };
    [[nodiscard]] double getRg() const { return Rg; };
    void calculateParameters() override;

};

#endif //CIRCUITWAVE_NONINVOPAMP_H