#include "../Inc/imageProcessor.h"

wxBitmap ProcessImage(const wxString& filePath, int width, int height, bool invertColors) {

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
    if (invertColors) {
        for (int i = 0; i < size; i++) {
            data[i] = 255 - data[i];
        }
    }

    return image;
}