#include "../Inc/calculations.h"

double tl431(double param1, double param2){

    return 2.5 * (1 + param1/param2);
}

double lm317(double param1, double param2){

    return 1.25 * (1 + param1/param2);
}

double* filter(double param1, double param2){

    auto* values = new double[2];
    values[0] = 1.0 / (2e-6 * M_PI * sqrt(param1 * param2));
    values[1] = param1 * param2;

    return values;
}

double divider(double param1, double param2, double param3){

    return param1 * param3 / (param2 + param3);
}

wxBitmap ProcessImage(const wxString& filePath, int width, int height, bool invertColors) {

    wxImage image(filePath, wxBITMAP_TYPE_ANY);

    if (!image.IsOk()) {
        wxMessageBox("Failed to load image", "Error", wxOK | wxICON_ERROR);
        return wxBitmap();
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

    return wxBitmap(image);
}
