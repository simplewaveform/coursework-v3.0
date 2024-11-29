#ifndef CIRCUITWAVE_INVOPAMP_H
#define CIRCUITWAVE_INVOPAMP_H

#include "../Inc/Opamp.h"

/**
 * @brief Inverting operational amplifier class.
 * Inherits from `Opamp` and calculates the gain for an inverting amplifier.
 */
class InvertingOpamp : public Opamp {
private:
    double Rfb{}, Rin{};

public:
    void setRfb(double rfb) { this->Rfb = rfb; }
    void setRin(double rin) { this->Rin = rin; }
    [[nodiscard]] double getRfb() const { return Rfb; };
    [[nodiscard]] double getRin() const { return Rin; };
    void calculateParameters() override;

};

#endif //CIRCUITWAVE_INVOPAMP_H