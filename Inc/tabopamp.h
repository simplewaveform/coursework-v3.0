#ifndef TABOPAMP_H
#define TABOPAMP_H

#include <wx/wx.h>
#include <wx/notebook.h>

class tabopamp : public wxPanel
{
public:
    explicit tabopamp(wxNotebook* parent);
    void OnCalculate(wxCommandEvent& event);

private:
    wxTextCtrl* inputR1;
    wxTextCtrl* inputR2;
    wxStaticText* resultGain;
};

#endif