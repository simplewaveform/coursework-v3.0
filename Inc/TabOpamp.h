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
    template <typename T>
    void updateOpamp(wxTextCtrl* inputRfb, wxTextCtrl* inputRgOrRin, wxStaticText* resultGain, T& opamp);
    wxTextCtrl *inputRfbNonInv, *inputRgNonInv, *inputRfbInv, *inputRinInv;
    wxStaticText *resultGainNonInv, *resultGainInv;
    wxButton *calculateButtonNonInv{}, *calculateButtonInv{};

public:
    InvertingOpamp invertingOpamp;
    NonInvertingOpamp nonInvertingOpamp;
    explicit TabOpamp(wxNotebook* parent);
    void OnCalculate(wxCommandEvent& event);
    wxString getData() const override;

};

#endif //TABOPAMP_H