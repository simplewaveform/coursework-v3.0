#ifndef CIRCUITWAVE_LM317_H
#define CIRCUITWAVE_LM317_H

#include "../Inc/Regulator.h"

/**
 * @brief LM317 voltage regulator class.
 * This class calculates the output voltage based on the resistor values
 * and provides the regulator data as a string.
 */
class LM317 : public Regulator {
private:
    double R1{}, R2{};

public:
    void setR1(double r1) { this->R1 = r1; }
    void setR2(double r2) { this->R2 = r2; }
    void calculateParameters() override;
    [[nodiscard]] wxString getData() const override;

};

#endif //CIRCUITWAVE_LM317_H