#include "../Inc/TabOpamp.h"
#include "../Inc/ImageProcessor.h"
#include "../Inc/TabTools.h"
#include "../Inc/magic.h"

/**
 * @brief Constructs the op-amp tab with UI elements for inverting
 *        and non-inverting amplifier calculations.
 * @param parent Pointer to the parent notebook.
 */
TabOpamp::TabOpamp(wxNotebook *parent) : BaseTab(parent) {

    auto *mainSizer = new wxBoxSizer(wxVERTICAL);
    auto *gridSizer = new wxFlexGridSizer(12, 2, 20, 50);
    TabOpamp::SetBackgroundColour(*wxBLACK);

    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Non-Inverting Amplifier"));
    TabTools::AddEmptyCell(this, gridSizer, 1);
    inputRfbNonInv = TabTools::CreateInputField(this, gridSizer, "Rfb (Ω):");
    inputRgNonInv = TabTools::CreateInputField(this, gridSizer, "Rg (Ω):");
    calculateButtonNonInv = TabTools::CreateButton(this, gridSizer, "Calculate gain",
                                                   this, &TabOpamp::OnCalculate);
    TabTools::AddEmptyCell(this, gridSizer, 1);
    resultGainNonInv = new wxStaticText(this, wxID_ANY, "Output gain:");
    gridSizer->Add(resultGainNonInv, 0, wxALIGN_LEFT | wxTOP, 10);

    TabTools::AddEmptyCell(this, gridSizer, 3);
    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Inverting Amplifier"));
    TabTools::AddEmptyCell(this, gridSizer, 1);
    inputRinInv = TabTools::CreateInputField(this, gridSizer, "Rin (Ω):");
    inputRfbInv = TabTools::CreateInputField(this, gridSizer, "Rfb (Ω):");
    calculateButtonInv = TabTools::CreateButton(this, gridSizer, "Calculate gain",
                                                this, &TabOpamp::OnCalculate);
    TabTools::AddEmptyCell(this, gridSizer, 1);
    resultGainInv = new wxStaticText(this, wxID_ANY, "Output gain:");
    gridSizer->Add(resultGainInv, 0, wxALIGN_LEFT | wxTOP, 10);

    auto *imageCtrlNonInv = new wxStaticBitmap(this, wxID_ANY,
                                               ImageProcessor::processImage("../Resources/noninvopamp.png",
                                                            nonInvOpampImageW, nonInvOpampImageH));
    imageCtrlNonInv->Move(nonInvOpampImageX, nonInvOpampImageY);
    auto *imageCtrlInv = new wxStaticBitmap(this, wxID_ANY,
                                            ImageProcessor::processImage("../Resources/invopamp.png",
                                                         invOpampImageW, invOpampImageH));
    imageCtrlInv->Move(invOpampImageX, invOpampImageY);

    mainSizer->Add(gridSizer, 1, wxALL | wxEXPAND, 10);
    SetSizer(mainSizer);

}

/**
 * @brief Handles the calculation of op-amp gain based on user inputs.
 * @param event The triggered wxCommandEvent.
 */
void TabOpamp::OnCalculate(wxCommandEvent &event) {

    try {
        if (event.GetEventObject() == calculateButtonNonInv) {
            CalculateOpampGain<NonInvertingOpamp>(inputRfbNonInv, inputRgNonInv,
                                                  resultGainNonInv);
        } else if (event.GetEventObject() == calculateButtonInv) {
            CalculateOpampGain<InvertingOpamp>(inputRfbInv, inputRinInv,
                                               resultGainInv);
        }
    } catch (const std::exception& e) {
        ExceptionHandler::HandleException(e, "Error calculating op-amp gain");
    }

}

/**
 * @brief Template method to calculate op-amp gain.
 * @tparam T The op-amp type (NonInvertingOpamp or InvertingOpamp).
 * @param inputRfb Input field for Rfb value.
 * @param inputRg Input field for Rg or Rin value.
 * @param resultGain Output field to display the calculated gain.
 */
template <typename T>
void TabOpamp::CalculateOpampGain(wxTextCtrl* inputRfb, wxTextCtrl* inputRg, wxStaticText* resultGain) {

    T opamp;
    try {
        CircuitComponent::CheckAndSetParameter(opamp, &T::setRfb, inputRfb->GetValue());
        if constexpr (std::is_same_v<T, NonInvertingOpamp>) {
            CircuitComponent::CheckAndSetParameter(opamp, &T::setRg, inputRg->GetValue());
        } else if constexpr (std::is_same_v<T, InvertingOpamp>) {
            CircuitComponent::CheckAndSetParameter(opamp, &T::setRin, inputRg->GetValue());
        }
    } catch (const std::invalid_argument& e) {
        wxLogError("Invalid input: %s", e.what());
        return;
    }
    opamp.calculateParameters();
    resultGain->SetLabel(wxString::Format("Output gain: %.2lf", opamp.getGain()));

}

/**
 * @brief Retrieves data about op-amp parameters as a formatted string.
 * @return A string with details about inverting and non-inverting amplifiers.
 */
wxString TabOpamp::GetData() const {

    return wxString::Format(
            "Opamp parameters:\n"
            "   Inverting amplifier:\n"
            "Rin: %.2f Ohm\n"
            "Rfb: %.2f Ohm\n"
            "Gain: %.2f\n"
            "Non-Inverting amplifier:\n"
            "Rg: %.2f Ohm\n"
            "Rfb: %.2f Ohm\n"
            "Gain: %.2f\n",
            invertingOpamp.getRin(), invertingOpamp.getRfb(), invertingOpamp.getGain(),
            nonInvertingOpamp.getRg(), nonInvertingOpamp.getRfb(), nonInvertingOpamp.getGain()
    );

}