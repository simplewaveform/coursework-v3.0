#ifndef TABRCFILTER_H
#define TABRCFILTER_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/textctrl.h>
#include <vector>

class tabRCfilter : public wxPanel {
public:
    tabRCfilter(wxNotebook *parent);
    virtual wxString GetData();

private:
    void InitializeEmptyGraph();
    void OnCalculate(wxCommandEvent &event);
    void OnPaint(wxPaintEvent &event);
    wxTextCtrl *inputR1;
    wxTextCtrl *inputC1;
    wxStaticText *resultCutoff;
    wxStaticText *resultTimeConstant;
    double resistance;
    double capacitance;
    double calculatedFrequency, calculatedTime;
    std::vector<double> timeValues;
    std::vector<double> responseValues;
    wxString LoadHelpText(const wxString& filename);

wxDECLARE_EVENT_TABLE();

};

#endif