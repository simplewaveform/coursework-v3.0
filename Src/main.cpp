#include <wx/menu.h>
#include <wx/filedlg.h>
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

MyFrame::MyFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(850, 400)) {

    SetBackgroundColour(*wxBLACK);
    auto* fileMenu = new wxMenu;
    fileMenu->Append(wxID_EXIT, wxString::Format("Выход\t%s-Q", "Cmd"), "Выход из приложения");

    // Добавляем пункты для экспорта данных
    fileMenu->Append(wxID_SAVE, wxString::Format("Экспорт RC данных\t%s-S", "Cmd"), "Экспортировать данные RC фильтра");
    fileMenu->Append(wxID_SAVEAS, wxString::Format("Экспорт LC данных\t%s-L", "Cmd"), "Экспортировать данные LC фильтра");

    auto* menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "&Файл");
    SetMenuBar(menuBar);

    // Привязываем обработчики событий к пунктам меню
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnSaveRCData, this, wxID_SAVE);
    Bind(wxEVT_MENU, &MyFrame::OnSaveLCData, this, wxID_SAVEAS);

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
    notebook->AddPage(tab5, "Делитель напряжения");

}

wxIMPLEMENT_APP(MyApp);

void MyFrame::OnExit(wxCommandEvent&) {

    Close(true);

}

// Реализация функции экспорта данных RC фильтра
void MyFrame::OnSaveRCData(wxCommandEvent&) {
    wxFileDialog saveFileDialog(this, _("Сохранить файл RC фильтра"), "", "",
                                "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return; // Если пользователь отменил сохранение, выходим

    wxTextFile file(saveFileDialog.GetPath());
    if (!file.Exists()) {
        file.Create();
    } else {
        file.Open();
        file.Clear(); // Очищаем файл перед записью новых данных
    }

    // Получение данных для записи (пример данных)
    wxString rcData = "Рассчитанные данные для RC фильтра\n";
    rcData += "Значение частоты: 1000 Hz\n";
    rcData += "Сопротивление: 1 kOhm\n";
    rcData += "Емкость: 100 nF\n";

    // Записываем данные в файл
    file.AddLine(rcData);
    file.Write();
    file.Close();
}

// Реализация функции экспорта данных LC фильтра
void MyFrame::OnSaveLCData(wxCommandEvent&) {
    wxFileDialog saveFileDialog(this, _("Сохранить файл LC фильтра"), "", "",
                                "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxTextFile file(saveFileDialog.GetPath());
    if (!file.Exists()) {
        file.Create();
    } else {
        file.Open();
        file.Clear();
    }

    // Получение данных для записи (пример данных)
    wxString lcData = "Рассчитанные данные для LC фильтра\n";
    lcData += "Значение частоты: 500 Hz\n";
    lcData += "Индуктивность: 10 mH\n";
    lcData += "Емкость: 100 nF\n";

    // Записываем данные в файл
    file.AddLine(lcData);
    file.Write();
    file.Close();
}
