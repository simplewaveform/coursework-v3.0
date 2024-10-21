#ifndef TABTL431_H
#define TABTL431_H

#include <wx/wx.h>
#include <wx/notebook.h>

class tabTL431 : public wxPanel
{
public:
    explicit tabTL431(wxNotebook* parent);
    void OnCalculate(wxCommandEvent& event);

private:
    wxTextCtrl* inputR1;
    wxTextCtrl* inputR2;
    wxStaticText* outputVoltage;
};

#endif