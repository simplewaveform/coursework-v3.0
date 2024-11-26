#include "../Inc/TabRegulator.h"
#include "../Inc/LM317.h"
#include "../Inc/TL431.h"
#include "../Inc/ImageProcessor.h"
#include "../Inc/TabTools.h"
#include "../Inc/magic.h"

/**
 * @brief Constructor for the TabRegulator class.
 * @param parent Parent notebook for this tab.
 */
TabRegulator::TabRegulator(wxNotebook* parent) : BaseTab(parent) {

    auto* sizer = new wxBoxSizer(wxVERTICAL);
    auto* gridSizer = new wxFlexGridSizer(8, 2, 20, 50);
    TabRegulator::SetBackgroundColour(*wxBLACK);

    auto* labelRegulatorType = new wxStaticText(this, wxID_ANY, "Regulator type:");
    regulatorChoice = new wxChoice(this, wxID_ANY);
    regulatorChoice->Append("LM317");
    regulatorChoice->Append("TL431");
    regulatorChoice->SetSelection(0);

    gridSizer->Add(labelRegulatorType, 0, wxALIGN_CENTER_VERTICAL);
    gridSizer->Add(regulatorChoice, 0, wxEXPAND);
    currentRegulator = std::make_unique<LM317>();
    regulatorChoice->SetSelection(0);

    inputR1 = TabTools::CreateInputField(this, gridSizer, "R1 (Ω):");
    inputR2 = TabTools::CreateInputField(this, gridSizer, "R2 (Ω):");
    TabTools::CreateButton(this, gridSizer, "Calculate voltage", this, &TabRegulator::OnCalculate);

    outputVoltage = new wxStaticText(this, wxID_ANY, "Output voltage:");
    TabTools::AddEmptyCell(this, gridSizer, 1);
    gridSizer->Add(outputVoltage);

    regulatorChoice->Bind(wxEVT_CHOICE, &TabRegulator::OnRegulatorChoice, this);

    wxBitmap processedBitmap = ImageProcessor::processImage("../Resources/LM317.png", regulatorImageW, regulatorImageH);
    imageCtrl = new wxStaticBitmap(this, wxID_ANY, processedBitmap);
    imageCtrl->Move(regulatorImageX, regulatorImageY);

    sizer->Add(gridSizer, 1, wxALL | wxEXPAND, 10);
    SetSizer(sizer);

    UpdateRegulatorImage(regulatorChoice->GetStringSelection());

}

/**
 * @brief Handles regulator type selection.
 */
void TabRegulator::OnRegulatorChoice(wxCommandEvent&) {

    wxString regulatorType = regulatorChoice->GetStringSelection();
    currentRegulator.reset();
    if (regulatorType == "LM317") currentRegulator = std::make_unique<LM317>();
    else if (regulatorType == "TL431") currentRegulator = std::make_unique<TL431>();
    UpdateRegulatorImage(regulatorType);

}

/**
 * @brief Updates the displayed regulator image based on the selection.
 * @param regulatorType Selected regulator type.
 */
void TabRegulator::UpdateRegulatorImage(const wxString& regulatorType) {

    wxString imagePath = wxString::Format("../Resources/%s.png", regulatorType);
    imageCtrl->SetBitmap(ImageProcessor::processImage(imagePath, regulatorImageW, regulatorImageH));
    Layout();

}

/**
 * @brief Calculates the output voltage of the selected regulator.
 */
void TabRegulator::OnCalculate(wxCommandEvent&) {

    if (!currentRegulator) return;
    try {
        if (auto lm317Regulator = dynamic_cast<LM317*>(currentRegulator.get())) {
            CircuitComponent::CheckAndSetParameter(*lm317Regulator, &LM317::setR1, inputR1->GetValue());
            CircuitComponent::CheckAndSetParameter(*lm317Regulator, &LM317::setR2, inputR2->GetValue());
        } else if (auto tl431Regulator = dynamic_cast<TL431*>(currentRegulator.get())) {
            CircuitComponent::CheckAndSetParameter(*tl431Regulator, &TL431::setR1, inputR1->GetValue());
            CircuitComponent::CheckAndSetParameter(*tl431Regulator, &TL431::setR2, inputR2->GetValue());
        }
    } catch (const std::exception& e) {
        ExceptionHandler::HandleException(e, "Error calculating regulator parameters");
        return;
    }
    currentRegulator->calculateParameters();
    outputVoltage->SetLabel(wxString::Format("Output voltage: %.2lf V", currentRegulator->getVoltage()));

}

/**
 * @brief Retrieves the parameters of the selected regulator as a formatted string.
 * @return String containing regulator data or a message if none is selected.
 */
wxString TabRegulator::GetData() const {

    if (!currentRegulator) return "No regulator selected.";
    return currentRegulator->GetData();

}
