#ifndef CIRCUITWAVE_TEXTMANIPULATOR_H
#define CIRCUITWAVE_TEXTMANIPULATOR_H

#include <wx/wx.h>
#include <fstream>

/**
 * @brief Helper class for managing text in the tabs.
 * Provides methods for loading, saving, and displaying help text.
 */
class TextManipulator {
private:
    wxString text;

public:
    void loadText(const wxString &filename);
    void transformText(wxWindow *parent, int textOffsetX, int textOffsetY);
    static bool saveDataToFile(const wxString& filePath, const wxString& data);

};

#endif //CIRCUITWAVE_TEXTMANIPULATOR_H