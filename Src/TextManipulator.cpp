#include "../Inc/TextManipulator.h"
#include <fstream>
#include <iterator>

/**
 * @brief Loads help text from a file.
 * @param filename Path to the file containing help text.
 */
void TextManipulator::loadHelpText(const wxString& filename) {

    try {
        std::ifstream file(filename.ToStdString(), std::ios::in | std::ios::binary);
        if (!file.is_open()) {
            wxLogError("Failed to open file: %s", filename);
            return;
        }
        text.clear();
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        text = wxString::FromUTF8(content.c_str());
        if (text.IsEmpty()) wxLogWarning("Loaded text is empty or invalid UTF-8: %s", filename);
    } catch (const std::exception& ex) {
        wxLogError("Exception occurred while reading file: %s. Error: %s", filename, ex.what());
    }

}

/**
 * @brief Saves data to a file.
 * @param filePath Path to the file where data will be saved.
 * @param data Data to save.
 * @return True if the save was successful, otherwise false.
 */
bool TextManipulator::saveDataToFile(const wxString& filePath, const wxString& data) {

    try {
        if (data.IsEmpty()) {
            wxLogWarning("Data to save is empty. File: %s", filePath);
            return false;
        }

        std::ofstream file(filePath.ToStdString(), std::ios::out | std::ios::binary | std::ios::trunc);
        if (!file.is_open()) {
            wxLogError("Failed to open file for writing: %s", filePath);
            return false;
        }
        auto utf8Data = data.ToUTF8();
        file.write(utf8Data.data(), static_cast<std::streamsize>(utf8Data.length()));
        if (!file.good()) {
            wxLogError("Error occurred while writing to the file: %s", filePath);
            return false;
        }
        file.close();
        return true;
    } catch (const std::exception& e) {
        wxLogError("Exception occurred while saving to file: %s. Error: %s", filePath, e.what());
        return false;
    }

}

/**
 * @brief Aligns and transforms text for display on a tab.
 * @param parent Parent window where the text will be displayed.
 * @param textOffsetX Horizontal offset for text placement.
 * @param textOffsetY Vertical offset for text placement.
 */
void TextManipulator::transformText(wxWindow* parent, int textOffsetX, int textOffsetY) {

    wxArrayString lines = wxSplit(text, '\n');
    for (const auto& line : lines) {
        if (!line.IsEmpty()) {
            auto* staticText = new wxStaticText(parent, wxID_ANY, line,
                                                wxPoint(textOffsetX, textOffsetY));
            textOffsetY += staticText->GetSize().GetHeight() + 5;
        }
    }

}
