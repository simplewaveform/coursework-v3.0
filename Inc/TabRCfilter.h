#ifndef TABRCFILTER_H
#define TABRCFILTER_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/textctrl.h>
#include <vector>

class TabRCfilter : public wxPanel {
public:
    explicit TabRCfilter(wxNotebook *parent);
    wxString GetData() const;

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

wxDECLARE_EVENT_TABLE();

};

#endif