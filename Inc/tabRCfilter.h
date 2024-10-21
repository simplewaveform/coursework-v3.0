#ifndef TABRCFILTER_H
#define TABRCFILTER_H

#include <wx/wx.h>
#include <wx/notebook.h>

class tabRCfilter : public wxPanel
{
public:
    explicit tabRCfilter(wxNotebook* parent);
    void OnCalculate(wxCommandEvent& event);

private:

    wxTextCtrl* inputR1;
    wxTextCtrl* inputC1;
    wxStaticText* resultCutoff;
    wxStaticText* resultTimeConstant;
};

#endif