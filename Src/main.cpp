#include <wx/menu.h>
#include <wx/textfile.h>
#include "../Inc/TabRCfilter.h"
#include "../Inc/TabRegulator.h"
#include "../Inc/TabOpamp.h"
#include "../Inc/main.h"
#include "../Inc/textManipulations.h"

bool MyApp::OnInit() {

    wxInitAllImageHandlers();
    auto* frame = new MyFrame("Калькулятор параметров электронных компонентов и схем");
    frame->Show(true);
    return true;

}

MyFrame::MyFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(850, 600)) {

    SetBackgroundColour(*wxBLACK);

    auto* fileMenu = new wxMenu;
    fileMenu->Append(wxID_EXIT, wxString::Format("Quit\t%s-Q", "ctrl"), "");
    fileMenu->Append(wxID_SAVE, wxString::Format("Export data\t%s-S", "ctrl"), "");

    auto* menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "&File");
    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnSaveData, this, wxID_SAVE);

    notebook = new wxNotebook(this, wxID_ANY);
    notebook->SetBackgroundColour(*wxBLACK);

    auto* tab1 = new TabRCfilter(notebook);
    notebook->AddPage(tab1, "Lowpass RC Filter");

    auto* tab2 = new TabRegulator(notebook);
    notebook->AddPage(tab2, "Voltage regulators");

    auto* tab3 = new tabOpamp(notebook);
    notebook->AddPage(tab3, "Operational amplifiers");

}

wxIMPLEMENT_APP(MyApp);

void MyFrame::OnExit(wxCommandEvent&) {

    Close(true);

}

void MyFrame::OnSaveData(wxCommandEvent&) {

    wxFileDialog saveFileDialog(this, _("Export data"), "", "",
                                "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL) return;

    wxString filePath = saveFileDialog.GetPath();
    wxString dataToSave;

    int activeTab = notebook->GetSelection();
    auto* activeTabPtr = notebook->GetPage(activeTab);

    if (auto* tab1 = dynamic_cast<TabRCfilter*>(activeTabPtr)) {
        dataToSave = tab1->GetData();
    } else if (auto* tab2 = dynamic_cast<TabRegulator*>(activeTabPtr)) {
        dataToSave = tab2->GetData();
    } else if (auto* tab3 = dynamic_cast<tabOpamp*>(activeTabPtr)) {
        dataToSave = tab3->GetData();
    } else {
        wxMessageBox("Cannot read data from active tab.", "Error", wxICON_ERROR);
        return;
    }

    if (SaveDataToFile(filePath, dataToSave)) {
        wxMessageBox("Data is saved successfully.", "Info", wxICON_INFORMATION);
    } else {
        wxMessageBox("No data to save on this tab.", "Warning", wxICON_WARNING);
    }

}
