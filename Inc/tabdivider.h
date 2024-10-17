#ifndef TABDIVIDER_H
#define TABDIVIDER_H

#include <wx/wx.h>
#include <wx/notebook.h>

class tabdivider : public wxPanel
{
public:
    explicit tabdivider(wxNotebook* parent);
    void OnCalculate(wxCommandEvent& event);

private:
    wxTextCtrl* inputR1;
    wxTextCtrl* inputR2;
    wxStaticText* resultVoltage;
};

#endif