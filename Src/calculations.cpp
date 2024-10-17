#include "../Inc/calculations.h"

double tl431(double param1, double param2){

    return 2.5 * (1 + param1/param2);
}

double lm317(double param1, double param2){

    return 1.25 * (1 + param1/param2);
}

double divider(double param1, double param2, double param3){

    return param1 * param3 / (param2 + param3);
}