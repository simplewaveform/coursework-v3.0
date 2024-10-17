#ifndef CIRCUITWAVE_CALCULATIONS_H
#define CIRCUITWAVE_CALCULATIONS_H

#include <wx/wx.h>
#include <wx/image.h>

double tl431(double param1, double param2);
double lm317(double param1, double param2);
double* filter(double param1, double param2);
double divider(double param1, double param2, double param3);

#endif //CIRCUITWAVE_CALCULATIONS_H