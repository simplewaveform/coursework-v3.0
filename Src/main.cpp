#include <wx/menu.h>
#include <wx/textfile.h>
#include "../Inc/TabRCfilter.h"
#include "../Inc/TabRegulator.h"
#include "../Inc/main.h"
#include "../Inc/textManipulations.h"

void HandleException(const std::exception& e, const wxString& customMessage = "An unknown error occurred") {
    wxMessageBox(wxString::Format("%s: %s", customMessage, e.what()), "Error", wxICON_ERROR);
}

void HandleGenericException(const wxString& customMessage = "An unknown error occurred") {
    wxMessageBox(customMessage, "Error", wxICON_ERROR);
}

bool MyApp::OnInit() {
    try {
        wxInitAllImageHandlers();
        auto* frame = new MyFrame("Калькулятор параметров электронных компонентов и схем");
        frame->Show(true);
        return true;
    } catch (const std::exception& e) {
        HandleException(e, "An error occurred during initialization");
        return false;
    } catch (...) {
        HandleGenericException("An unknown error occurred during initialization");
        return false;
    }
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

    auto* tab3 = new TabOpamp(notebook);
    notebook->AddPage(tab3, "Operational amplifiers");
}

wxIMPLEMENT_APP(MyApp);

void MyFrame::OnExit(wxCommandEvent&) {
    Close(true);
}

void MyFrame::OnSaveData(wxCommandEvent&) {
    wxFileDialog saveFileDialog(this, _("Export data"), "", "", "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() != wxID_OK) return;

    wxString dataToSave = GetDataFromActiveTab();
    if (dataToSave.IsEmpty()) return;

    try {
        if (!SaveDataToFile(saveFileDialog.GetPath(), dataToSave)) {
            throw std::runtime_error("Failed to save data to file.");
        }
        wxMessageBox("Data is saved successfully.", "Info", wxICON_INFORMATION);
    } catch (const std::exception& e) {
        HandleException(e, "Failed to save data");
    } catch (...) {
        HandleGenericException("An unknown error occurred while saving data.");
    }
}

wxString MyFrame::GetDataFromActiveTab() {
    int activeTab = notebook->GetSelection();
    auto* activeTabPtr = notebook->GetPage(activeTab);

    if (auto* tab1 = dynamic_cast<TabRCfilter*>(activeTabPtr)) {
        return tab1->GetData(reinterpret_cast<LowpassRC &>(activeTabPtr));
    } else if (auto* tab2 = dynamic_cast<TabRegulator*>(activeTabPtr)) {
        return tab2->GetData();
    } else if (auto* tab3 = dynamic_cast<TabOpamp*>(activeTabPtr)) {
        return tab3->GetData();
    } else {
        wxMessageBox("Cannot read data from active tab.", "Error", wxICON_ERROR);
        return wxEmptyString;
    }
}

wxTextCtrl* MyFrame::CreateInputField(wxWindow* parent, wxFlexGridSizer* sizer, const wxString& labelText) {
    try {
        auto* label = new wxStaticText(parent, wxID_ANY, labelText);
        auto* input = new wxTextCtrl(parent, wxID_ANY);
        sizer->Add(label, 0, wxALIGN_CENTER_VERTICAL);
        sizer->Add(input, 0, wxEXPAND);
        return input;
    } catch (const std::exception& e) {
        HandleException(e, "Error creating input field");
        return nullptr;
    }
}

void MyFrame::AddEmptyCell(wxWindow* parent, wxFlexGridSizer* sizer, int count) {
    for (int i = 0; i < count; ++i) {
        sizer->Add(new wxStaticText(parent, wxID_ANY, ""), 0, wxEXPAND);
    }
}

template <typename T>
wxButton* MyFrame::CreateButton(wxWindow* parent, wxFlexGridSizer* sizer, const wxString& labelText, T* handler, void (T::*eventHandler)(wxCommandEvent&)) {
    try {
        auto* button = new wxButton(parent, wxID_ANY, labelText);
        button->Bind(wxEVT_BUTTON, eventHandler, handler);
        sizer->Add(button, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
        return button;
    } catch (const std::exception& e) {
        HandleException(e, "Error creating button");
        return nullptr;
    }
}

template wxButton* MyFrame::CreateButton<TabRegulator>(wxWindow*, wxFlexGridSizer*, const wxString&, TabRegulator*, void (TabRegulator::*)(wxCommandEvent&));
template wxButton* MyFrame::CreateButton<TabOpamp>(wxWindow*, wxFlexGridSizer*, const wxString&, TabOpamp*, void (TabOpamp::*)(wxCommandEvent&));
template wxButton* MyFrame::CreateButton<TabRCfilter>(wxWindow*, wxFlexGridSizer*, const wxString&, TabRCfilter*, void (TabRCfilter::*)(wxCommandEvent&));