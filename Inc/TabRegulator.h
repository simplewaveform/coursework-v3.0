#ifndef tabRegulator_H
#define tabRegulator_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/choice.h>
#include <wx/statbmp.h>

class TabRegulator : public wxPanel
{
public:
    wxString GetData();
    explicit TabRegulator(wxNotebook* parent);
    void OnCalculate(wxCommandEvent& event);

private:
    void OnRegulatorChoice(wxCommandEvent& event);
    double R1;
    double R2;
    double voltage;
    wxChoice* regulatorChoice;
    wxTextCtrl* inputR1;
    wxTextCtrl* inputR2;
    wxStaticText* outputVoltage;
    wxStaticBitmap* imageCtrl;

};

#endif //tabRegulator_H
