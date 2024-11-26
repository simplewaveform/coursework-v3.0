#ifndef TABOPAMP_H
#define TABOPAMP_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include "../Inc/InvOpamp.h"
#include "../Inc/NonInvOpamp.h"
#include "../Inc/BaseTab.h"

/**
 * @brief Tab for operational amplifier calculations.
 * This tab allows the user to input values for both inverting and non-inverting amplifiers
 * and calculates their gain based on resistor values.
 */
class TabOpamp : public BaseTab {
private:
    wxTextCtrl *inputRfbNonInv, *inputRgNonInv, *inputRfbInv, *inputRinInv;
    wxStaticText *resultGainNonInv, *resultGainInv;
    wxButton *calculateButtonNonInv{}, *calculateButtonInv{};

public:
    InvertingOpamp invertingOpamp;
    NonInvertingOpamp nonInvertingOpamp;
    explicit TabOpamp(wxNotebook* parent);
    void OnCalculate(wxCommandEvent& event);
    wxString GetData() const override;
    template <typename T>
    static void CalculateOpampGain(wxTextCtrl* inputRfb, wxTextCtrl* inputRin, wxStaticText* resultGain);

};

#endif
