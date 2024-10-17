#ifndef TABFILTER_H
#define TABFILTER_H

#include <wx/wx.h>
#include <wx/notebook.h>

class tabfilter : public wxPanel
{
public:
    explicit tabfilter(wxNotebook* parent);
    void OnCalculate(wxCommandEvent& event);

private:
    wxTextCtrl* inputR1;
    wxTextCtrl* inputC1;
    wxStaticText* resultCutoff;
    wxStaticText* resultTimeConstant;
};

#endif