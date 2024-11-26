#include "../Inc/ImageProcessor.h"

/**
 * @brief Processes and inverts the colors of an image, then scales it.
 * The image is loaded from the given file path, and its colors are inverted.
 * If valid width and height are provided, the image is scaled accordingly.
 * @param filePath Path to the image file.
 * @param width Desired width for the scaled image.
 * @param height Desired height for the scaled image.
 * @return The processed wxBitmap object with inverted colors and scaled dimensions.
 */
wxBitmap ImageProcessor::processImage(const wxString& filePath, int width, int height) {

    wxImage image(filePath, wxBITMAP_TYPE_ANY);
    if (!image.IsOk()) {
        wxLogError("Failed to load image");
        return image;
    }

    if (width > 0 && height > 0) {
        image = image.Scale(width, height, wxIMAGE_QUALITY_HIGH);
    }

    unsigned char* data = image.GetData();
    int size = image.GetWidth() * image.GetHeight() * 3;

    for (int i = 0; i < size; i++) {
        data[i] = 255 - data[i];
    }

    return image;
}