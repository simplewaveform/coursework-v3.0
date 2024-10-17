#include <wx/menu.h>
#include "../Inc/tabfilter.h"
#include "../Inc/tabTL431.h"
#include "../Inc/tabLM317.h"
#include "../Inc/tabdivider.h"
#include "../Inc/main.h"

bool MyApp::OnInit() {

    wxInitAllImageHandlers();
    auto* frame = new MyFrame("Калькулятор параметров электронных компонентов и схем");
    frame->Show(true);

    return true;
}

MyFrame::MyFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(850, 400)) {

    SetBackgroundColour(*wxBLACK);
    auto* fileMenu = new wxMenu;
    fileMenu->Append(wxID_EXIT, wxString::Format("Выход\t%s-Q", "Cmd"), "Выход из приложения");
    auto* menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "&Файл");
    SetMenuBar(menuBar);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

    notebook = new wxNotebook(this, wxID_ANY);
    notebook->SetBackgroundColour(*wxBLACK);

    auto* tab1 = new tabfilter(notebook);
    notebook->AddPage(tab1, "RC фильтр");

    auto* tab2 = new tabTL431(notebook);
    notebook->AddPage(tab2, "TL431");

    auto* tab3 = new tabLM317(notebook);
    notebook->AddPage(tab3, "LM317");

    auto* tab4 = new tabdivider(notebook);
    notebook->AddPage(tab4, "Voltage divider");

}

wxIMPLEMENT_APP(MyApp);

void MyFrame::OnExit(wxCommandEvent&) {

    Close(true);

}