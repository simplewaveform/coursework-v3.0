#include "../Inc/imageProcessor.h"

wxBitmap ProcessImage(const wxString& filePath, int width, int height, bool invertColors) {

    wxImage image(filePath, wxBITMAP_TYPE_ANY);

    if (!image.IsOk()) {
        wxMessageBox("Failed to load image", "Error", wxOK | wxICON_ERROR);
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
//    for (int i = 0; i < size; i++) {
//        if (data[i] < 100) {
//            data[i] = data[i] + 47;
//        }
//    }

    return image;
}