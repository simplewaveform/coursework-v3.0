#ifndef SIMPLEWXAPP_CALCULATIONS_H
#define SIMPLEWXAPP_CALCULATIONS_H

#include <wx/wx.h>
#include <wx/image.h>

double tl431(double param1, double param2);
double lm317(double param1, double param2);
double* filter(double param1, double param2);
double divider(double param1, double param2, double param3);

wxBitmap ProcessImage(const wxString& filePath, int width, int height, bool invertColors);

#endif //SIMPLEWXAPP_CALCULATIONS_H