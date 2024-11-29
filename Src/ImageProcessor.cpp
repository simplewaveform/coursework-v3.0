#include "../Inc/ImageProcessor.h"
#include "../Inc/ExceptionHandler.h"

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

    try {
        wxImage image(filePath, wxBITMAP_TYPE_ANY);
        if (!image.IsOk()) throw std::runtime_error(wxString::Format("Failed to load image: %s",
                                                                     filePath).ToStdString());
        if (width > 0 && height > 0) image = image.Scale(width, height, wxIMAGE_QUALITY_HIGH);

        unsigned char* data = image.GetData();
        if (!data) throw std::runtime_error("Image data is invalid or corrupted.");

        for (int i = 0; i < image.GetWidth() * image.GetHeight() * 3; ++i) {
            data[i] = 255 - data[i];
        }

        return {image};
    } catch (const std::exception& e) {
        ExceptionHandler::handleException(e, "Error processing image");
        return {};
    }

}