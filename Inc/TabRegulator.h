#ifndef TABREGULATOR_H
#define TABREGULATOR_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/choice.h>

class TabRegulator : public wxPanel {
public:
    wxString GetData();
    explicit TabRegulator(wxNotebook* parent);
    void OnCalculate(wxCommandEvent& event);

private:
    void OnRegulatorChoice(wxCommandEvent& event);
    void UpdateRegulatorImage(const wxString& regulatorType);
    double R1{}, R2{}, voltage{};
    wxChoice *regulatorChoice;
    wxTextCtrl *inputR1, *inputR2;
    wxStaticText *outputVoltage;
    wxStaticBitmap *imageCtrl;

};

#endif //TABREGULATOR_H