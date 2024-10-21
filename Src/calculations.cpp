#include "../Inc/calculations.h"

double lm317(double param1, double param2){

    return 1.25 * (1 + param1/param2);
}

double divider(double param1, double param2, double param3){

    return param1 * param3 / (param2 + param3);
}