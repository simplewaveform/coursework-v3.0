#ifndef TABRCFILTER_H
#define TABRCFILTER_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/textctrl.h>
#include <vector>
#include "../Inc/LowpassRC.h"

class TabRCfilter : public wxPanel {
public:
    explicit TabRCfilter(wxNotebook *parent);
    static wxString GetData(LowpassRC &filter) ;

private:
    void InitializeEmptyGraph();
    void OnCalculate(wxCommandEvent &event);
    void OnPaint(wxPaintEvent &event);
    wxTextCtrl *inputR1, *inputC1;
    wxStaticText *resultCutoff, *resultTimeConstant;
    std::vector<double> timeValues, responseValues;

wxDECLARE_EVENT_TABLE();

};

#endif