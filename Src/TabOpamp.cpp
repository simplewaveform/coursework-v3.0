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
    TabTools::addEmptyCell(this, gridSizer, 1);
    inputRfbNonInv = TabTools::createInputField(this, gridSizer, "Rfb (Ω):");
    inputRgNonInv = TabTools::createInputField(this, gridSizer, "Rg (Ω):");
    calculateButtonNonInv = TabTools::createButton(this, gridSizer, "Calculate gain",
                                                   this, &TabOpamp::OnCalculate);
    TabTools::addEmptyCell(this, gridSizer, 1);
    resultGainNonInv = new wxStaticText(this, wxID_ANY, "Output gain:");
    gridSizer->Add(resultGainNonInv, 0, wxALIGN_LEFT | wxTOP, 10);

    TabTools::addEmptyCell(this, gridSizer, 3);
    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Inverting Amplifier"));
    TabTools::addEmptyCell(this, gridSizer, 1);
    inputRinInv = TabTools::createInputField(this, gridSizer, "Rin (Ω):");
    inputRfbInv = TabTools::createInputField(this, gridSizer, "Rfb (Ω):");
    calculateButtonInv = TabTools::createButton(this, gridSizer, "Calculate gain",
                                                this, &TabOpamp::OnCalculate);
    TabTools::addEmptyCell(this, gridSizer, 1);
    resultGainInv = new wxStaticText(this, wxID_ANY, "Output gain:");
    gridSizer->Add(resultGainInv, 0, wxALIGN_LEFT | wxTOP, 10);

    auto *imageCtrlNonInv = new wxStaticBitmap(this, wxID_ANY,
                                               ImageProcessor::processImage(
                                                       "../Resources/noninvopamp.png",
                                                            nonInvOpampImageW, nonInvOpampImageH));
    imageCtrlNonInv->Move(nonInvOpampImageX, nonInvOpampImageY);
    auto *imageCtrlInv = new wxStaticBitmap(this, wxID_ANY,
                                            ImageProcessor::processImage(
                                                    "../Resources/invopamp.png",
                                                         invOpampImageW, invOpampImageH));
    imageCtrlInv->Move(invOpampImageX, invOpampImageY);

    mainSizer->Add(gridSizer, 1, wxALL | wxEXPAND, 10);
    SetSizer(mainSizer);

}

/**
 * @brief Handles button events to calculate op-amp gain.
 * Determines the op-amp type and updates its parameters.
 * @param event wxCommandEvent triggered by a button.
 */
void TabOpamp::OnCalculate(wxCommandEvent &event) {

    try {
        if (event.GetEventObject() == calculateButtonNonInv) {
            updateOpamp<NonInvertingOpamp>(inputRfbNonInv, inputRgNonInv,
                                           resultGainNonInv, nonInvertingOpamp);
        } else if (event.GetEventObject() == calculateButtonInv) {
            updateOpamp<InvertingOpamp>(inputRfbInv, inputRinInv,
                                        resultGainInv, invertingOpamp);
        }
    } catch (const std::exception& e) {
        ExceptionHandler::handleException(e, "Error calculating op-amp gain");
    }

}

/**
 * @brief Updates op-amp parameters and calculates gain.
 * @tparam T Op-amp type (InvertingOpamp or NonInvertingOpamp).
 * @param inputRfb Field for Rfb value.
 * @param inputRgOrRin Field for Rg (non-inverting) or Rin (inverting).
 * @param resultGain UI element to display the result.
 * @param opamp Reference to the op-amp object being updated.
 */
template <typename T>
void TabOpamp::updateOpamp(wxTextCtrl* inputRfb, wxTextCtrl* inputRgOrRin, wxStaticText* resultGain, T& opamp) {

    try {
        CircuitComponent::CheckAndSetParameter(opamp, &T::setRfb, inputRfb->GetValue());
        if constexpr (std::is_same_v<T, NonInvertingOpamp>) {
            CircuitComponent::CheckAndSetParameter(opamp, &T::setRg, inputRgOrRin->GetValue());
        } else if constexpr (std::is_same_v<T, InvertingOpamp>) {
            CircuitComponent::CheckAndSetParameter(opamp, &T::setRin, inputRgOrRin->GetValue());
        }
    } catch (const std::invalid_argument& e) {
        ExceptionHandler::handleException(e, "Invalid input");
        return;
    }
    opamp.calculateParameters();
    resultGain->SetLabel(wxString::Format("Output gain: %.2lf", opamp.getGain()));

}

/**
 * @brief Returns formatted op-amp parameters for export or display.
 * @return A string with op-amp details.
 */
wxString TabOpamp::getData() const {

    return wxString::Format(
            "Opamp parameters:\n"
            "   Non-Inverting amplifier:\n"
            "Rg: %.2lf Ohm\n"
            "Rfb: %.2lf Ohm\n"
            "Gain: %.2lf\n"
            "   Inverting amplifier:\n"
            "Rin: %.2lf Ohm\n"
            "Rfb: %.2lf Ohm\n"
            "Gain: %.2lf\n",
            nonInvertingOpamp.getRg(), nonInvertingOpamp.getRfb(), nonInvertingOpamp.getGain(),
            invertingOpamp.getRin(), invertingOpamp.getRfb(), invertingOpamp.getGain()
    );

}