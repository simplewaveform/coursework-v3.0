#ifndef TABREGULATOR_H
#define TABREGULATOR_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/choice.h>
#include <wx/statbmp.h>

class tabregulator : public wxPanel
{
public:
    explicit tabregulator(wxNotebook* parent);
    void OnCalculate(wxCommandEvent& event);

private:
    void OnRegulatorChoice(wxCommandEvent& event);
    wxChoice* regulatorChoice;
    wxTextCtrl* inputR1;
    wxTextCtrl* inputR2;
    wxStaticText* outputVoltage;
    wxStaticBitmap* imageCtrl;

};

#endif //TABREGULATOR_H
