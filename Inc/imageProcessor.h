#ifndef CIRCUITWAVE_IMAGEPROCESSOR_H
#define CIRCUITWAVE_IMAGEPROCESSOR_H

#include <wx/wx.h>
#include <wx/image.h>

wxBitmap ProcessImage(const wxString& filePath, int width, int height, bool invertColors);

#endif //CIRCUITWAVE_IMAGEPROCESSOR_H
