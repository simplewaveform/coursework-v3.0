#include "../Inc/TabRCfilter.h"
#include "../Inc/TabRegulator.h"
#include "../Inc/TabOpamp.h"
#include "../Inc/app.h"
#include "../Inc/TextManipulator.h"
#include "../Inc/TabTools.h"

wxIMPLEMENT_APP(MyApp);

/**
 * @brief Initializes the application and creates the main frame.
 * @return true if initialization is successful, false otherwise.
 */
bool MyApp::OnInit() {

    try {
        wxInitAllImageHandlers();
        auto* frame = new MyFrame("Калькулятор параметров электронных компонентов и схем");
        frame->Show(true);
        return true;
    } catch (const std::exception& e) {
        ExceptionHandler::HandleException(e, "Application initialization failed");
        return false;
    }

}

/**
 * @brief Constructs the main application frame.
 * @param title The title of the frame.
 */
MyFrame::MyFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title,
                                                  wxDefaultPosition, wxSize(850, 600)) {

    MyFrame::SetBackgroundColour(*wxBLACK);

    auto* fileMenu = new wxMenu;
    fileMenu->Append(wxID_EXIT, wxString::Format("Quit\t%s-Q", "ctrl"));
    fileMenu->Append(wxID_SAVE, wxString::Format("Export data\t%s-S", "ctrl"));
    auto* menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "File");
    MyFrame::SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnSaveData, this, wxID_SAVE);

    notebook = new wxNotebook(this, wxID_ANY);
    notebook->AddPage(new TabRCfilter(notebook), "Lowpass RC Filter");
    notebook->AddPage(new TabRegulator(notebook), "Voltage regulators");
    notebook->AddPage(new TabOpamp(notebook), "Operational amplifiers");

}

/**
 * @brief Handles the application exit event.
 * @param event Command event for exit action.
 */
void MyFrame::OnExit(wxCommandEvent&) {

    Close(true);

}

/**
 * @brief Saves data from the active tab to a file.
 * @param event Command event for saving data.
 */
void MyFrame::OnSaveData(wxCommandEvent&) {

    wxFileDialog saveFileDialog(
            this, _("Export data"), "", "",
            "Text files (*.txt)|*.txt",
            wxFD_SAVE | wxFD_OVERWRITE_PROMPT
    );

    if (saveFileDialog.ShowModal() != wxID_OK) return;

    wxString dataToSave = GetDataFromActiveTab();
    if (dataToSave.IsEmpty()) return;

    try {
        if (!TextManipulator::saveDataToFile(saveFileDialog.GetPath(), dataToSave)) {
            throw std::runtime_error("Failed to save data to file.");
        }
        wxMessageBox("Data is saved successfully.", "Info", wxICON_INFORMATION);
    } catch (const std::exception& e) {
        ExceptionHandler::HandleException(e, "Error exporting data");
    }

}

/**
 * @brief Retrieves data from the currently active tab.
 * @return A string containing the tab's data.
 */
wxString MyFrame::GetDataFromActiveTab() {

    auto* activeTabPtr = dynamic_cast<BaseTab*>(notebook->GetPage(notebook->GetSelection()));
    return activeTabPtr ? activeTabPtr->GetData() : "";

}
