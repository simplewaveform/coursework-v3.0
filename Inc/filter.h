#ifndef SIMPLEWXAPP_FILTER_H
#define SIMPLEWXAPP_FILTER_H
#include "../Inc/circuitComponent.h"

class filter : public circuitComponent {
protected:
    virtual void calculateParameters() override = 0;

};

#endif //SIMPLEWXAPP_FILTER_H
