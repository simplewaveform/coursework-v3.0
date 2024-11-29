#ifndef TABRCFILTER_H
#define TABRCFILTER_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <vector>
#include "../Inc/LowpassRC.h"
#include "../Inc/BaseTab.h"

class TabRCfilter : public BaseTab {

wxDECLARE_EVENT_TABLE();

public:
    explicit TabRCfilter(wxNotebook *parent);
    wxString getData() const override;

private:
    LowpassRC filter;
    void OnCalculate(wxCommandEvent &event);
    void OnPaint(wxPaintEvent &event);
    wxTextCtrl *inputR1, *inputC1;
    wxStaticText *resultCutoff, *resultTimeConstant;
    std::vector<double> timeValues, responseValues;

};

#endif //TABRCFILTER_H