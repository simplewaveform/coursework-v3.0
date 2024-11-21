#ifndef CIRCUITWAVE_MAIN_H
#define CIRCUITWAVE_MAIN_H

#include "../Inc/TabOpamp.h"

class MyApp : public wxApp {
public:
    bool OnInit() override;

};

class MyFrame : public wxFrame {
public:
    explicit MyFrame(const wxString& title);
    void OnSaveData(wxCommandEvent&);
    wxString GetDataFromActiveTab();
    static wxTextCtrl* CreateInputField(wxWindow* parent, wxFlexGridSizer* sizer, const wxString& labelText);
    static void AddEmptyCell(wxWindow* parent, wxFlexGridSizer *sizer, int count);
    template <typename T>
    static wxButton* CreateButton(wxWindow* parent, wxFlexGridSizer* sizer, const wxString& labelText, T* handler, void (T::*eventHandler)(wxCommandEvent&));

private:
    wxNotebook* notebook;
    void OnExit(wxCommandEvent &event);

};

#endif //CIRCUITWAVE_MAIN_H