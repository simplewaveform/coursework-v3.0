#ifndef CIRCUITWAVE_CIRCUITCOMPONENT_H
#define CIRCUITWAVE_CIRCUITCOMPONENT_H

class CircuitComponent {
public:
    virtual void calculateParameters() = 0;
    static bool validateInput(double param1, double param2);
    virtual ~CircuitComponent() = default;

};

#endif //CIRCUITWAVE_CIRCUITCOMPONENT_H
