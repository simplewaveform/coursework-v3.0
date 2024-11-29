#ifndef TABREGULATOR_H
#define TABREGULATOR_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/choice.h>
#include "../Inc/Regulator.h"
#include "../Inc/BaseTab.h"

/**
 * @brief Tab for voltage regulator calculations.
 * This tab allows the user to select a regulator type (LM317 or TL431)
 * and input resistor values to calculate the output voltage.
 */
class TabRegulator : public BaseTab {
public:
    std::unique_ptr<Regulator> currentRegulator;
    wxString getData() const override;
    explicit TabRegulator(wxNotebook* parent);
    void OnCalculate(wxCommandEvent& event);

private:
    void OnRegulatorChoice(wxCommandEvent& event);
    void updateRegulatorImage(const wxString& regulatorType);
    wxChoice *regulatorChoice;
    wxTextCtrl *inputR1, *inputR2;
    wxStaticText *outputVoltage;
    wxStaticBitmap *imageCtrl;

};

#endif //TABREGULATOR_H