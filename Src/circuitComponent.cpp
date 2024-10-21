#include "../Inc/circuitComponent.h"
#include <wx/wx.h>

bool circuitComponent::validateInput(const double *param1, const double *param2) {

    if (*param1 <= 0 || *param2 <= 0) {
        wxMessageBox("Values must be positive and non-zero.", "Error", wxOK | wxICON_ERROR);
        return false;
    }
    return true;
}