#ifndef TABLM317_H
#define TABLM317_H

#include <wx/wx.h>
#include <wx/notebook.h>

class tabLM317 : public wxPanel
{
public:
    explicit tabLM317(wxNotebook* parent);
    void OnCalculate(wxCommandEvent& event);

private:
    wxTextCtrl* inputR1;
    wxTextCtrl* inputR2;
    wxStaticText* resultVoltage;
};

#endif