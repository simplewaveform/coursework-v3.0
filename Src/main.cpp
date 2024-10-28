#include <wx/menu.h>
#include <wx/textfile.h>
#include "../Inc/tabRCfilter.h"
#include "../Inc/tabLCfilter.h"
#include "../Inc/tabTL431.h"
#include "../Inc/tabLM317.h"
#include "../Inc/tabopamp.h"
#include "../Inc/main.h"

bool MyApp::OnInit() {

    wxInitAllImageHandlers();
    auto* frame = new MyFrame("Калькулятор параметров электронных компонентов и схем");
    frame->Show(true);

    return true;
}

MyFrame::MyFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(850, 600)) {

    SetBackgroundColour(*wxBLACK);
    auto* fileMenu = new wxMenu;
    fileMenu->Append(wxID_EXIT, wxString::Format("Выход\t%s-Q", "ctrl"), "Выход из приложения");
    fileMenu->Append(wxID_SAVE, wxString::Format("Экспорт данных\t%s-S", "ctrl"), "Экспортировать данные");

    auto* menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "&Файл");
    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnSaveData, this, wxID_SAVE);

    notebook = new wxNotebook(this, wxID_ANY);
    notebook->SetBackgroundColour(*wxBLACK);

    auto* tab1 = new tabRCfilter(notebook);
    notebook->AddPage(tab1, "НЧ фильтр (RC)");

    auto* tab2 = new tabLCfilter(notebook);
    notebook->AddPage(tab2, "НЧ фильтр (LC)");

    auto* tab3 = new tabTL431(notebook);
    notebook->AddPage(tab3, "TL431");

    auto* tab4 = new tabLM317(notebook);
    notebook->AddPage(tab4, "LM317");

    auto* tab5 = new tabopamp(notebook);
    notebook->AddPage(tab5, "Инвертирующий усилитель");

}

wxIMPLEMENT_APP(MyApp);

void MyFrame::OnExit(wxCommandEvent&) {

    Close(true);

}

void MyFrame::OnSaveData(wxCommandEvent&) {

    wxFileDialog saveFileDialog(this, _("Сохранить данные"), "", "",
                                "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL) return;

    wxTextFile file(saveFileDialog.GetPath());
    if (file.Exists()) {
        file.Open();
        file.Clear();
    } else {
        file.Create();
    }

    int activeTab = notebook->GetSelection();
    wxString dataToSave;

    auto* activeTabPtr = notebook->GetPage(activeTab);
    if (auto* tab = dynamic_cast<tabRCfilter*>(activeTabPtr)) {
        dataToSave = tab->GetData();
//    } else if (auto* tab = dynamic_cast<tabLCfilter*>(activeTabPtr)) {
//        //dataToSave = tab->GetData();
//    } else if (auto* tab = dynamic_cast<tabTL431*>(activeTabPtr)) {
//        //dataToSave = tab->GetData();
//    } else if (auto* tab = dynamic_cast<tabLM317*>(activeTabPtr)) {
//        //dataToSave = tab->GetData();
//    } else if (auto* tab = dynamic_cast<tabopamp*>(activeTabPtr)) {
//        //dataToSave = tab->GetData();
    }

    if (!dataToSave.IsEmpty()) {
        file.AddLine(dataToSave);
        file.Write();
        file.Close();
    } else {
        wxMessageBox("Нет данных для сохранения на данной вкладке.", "Предупреждение", wxICON_WARNING);
    }

}
