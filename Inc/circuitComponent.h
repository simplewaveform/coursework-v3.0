#ifndef CIRCUITWAVE_CIRCUITCOMPONENT_H
#define CIRCUITWAVE_CIRCUITCOMPONENT_H

class circuitComponent {
protected:
    virtual void calculateParameters() = 0;

public:
    static bool validateInput(const double *param1, const double *param2);
};

#endif //CIRCUITWAVE_CIRCUITCOMPONENT_H