#ifndef CIRCUITWAVE_IMAGEPROCESSOR_H
#define CIRCUITWAVE_IMAGEPROCESSOR_H

#include <wx/wx.h>

/**
 * @brief Image processing utility class.
 * Provides methods for loading, scaling, and inverting image colors.
 */
class ImageProcessor {
public:
    static wxBitmap processImage(const wxString& filePath, int width, int height);

};

#endif //CIRCUITWAVE_IMAGEPROCESSOR_H