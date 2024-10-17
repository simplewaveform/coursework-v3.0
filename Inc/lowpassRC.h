#ifndef SIMPLEWXAPP_LOWPASSRC_H
#define SIMPLEWXAPP_LOWPASSRC_H
#include "../Inc/filter.h"
#include <cmath>

class lowpassRC : public filter {

private:
    void calculateParameters() override {};

};

#endif //SIMPLEWXAPP_LOWPASSRC_H