#include "../Inc/textManipulations.h"

wxString LoadHelpText(const wxString& filename) {

    wxString content;
    std::ifstream file(filename.ToStdString());

    if (!file.is_open()) {
        return "Error: cannot open info file.";
    }

    std::string line;
    while (std::getline(file, line)) {
        content += wxString::FromUTF8(line) + "\n";
    }

    file.close();

    return content;
}

bool SaveDataToFile(const wxString& filePath, const wxString& data) {

    wxTextFile file(filePath);
    if (file.Exists()) {
        file.Open();
        file.Clear();
    } else {
        file.Create();
    }

    if (data.IsEmpty()) return false;

    file.AddLine(data);
    file.Write();
    file.Close();

    return true;
}
