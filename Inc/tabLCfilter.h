#ifndef TABLCFILTER_H
#define TABLCFILTER_H

#include <wx/wx.h>
#include <wx/notebook.h>

class tabLCfilter : public wxPanel
{
public:
    explicit tabLCfilter(wxNotebook* parent);
    void OnCalculate(wxCommandEvent& event);

private:
    wxTextCtrl* inputL1;
    wxTextCtrl* inputC1;
    wxStaticText* resultCutoff;
    wxStaticText* resultTimeConstant;
};

#endif