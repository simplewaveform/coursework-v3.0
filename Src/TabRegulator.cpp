#include "../Inc/TabRegulator.h"
#include "../Inc/LM317.h"
#include "../Inc/TL431.h"
#include "../Inc/ImageProcessor.h"
#include "../Inc/TabTools.h"
#include "../Inc/magic.h"
#include "../Inc/TextManipulator.h"

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

    inputR1 = TabTools::createInputField(this, gridSizer, "R1 (Ω):");
    inputR2 = TabTools::createInputField(this, gridSizer, "R2 (Ω):");
    TabTools::createButton(this, gridSizer, "Calculate voltage", this,
                           &TabRegulator::OnCalculate);
    outputVoltage = new wxStaticText(this, wxID_ANY, "Output voltage:");
    TabTools::addEmptyCell(this, gridSizer, 1);
    gridSizer->Add(outputVoltage);

    regulatorChoice->Bind(wxEVT_CHOICE, &TabRegulator::OnRegulatorChoice, this);

    wxBitmap processedBitmap = ImageProcessor::processImage("../Resources/LM317.png",
                                                            regulatorImageW, regulatorImageH);
    imageCtrl = new wxStaticBitmap(this, wxID_ANY, processedBitmap);
    imageCtrl->Move(regulatorImageX, regulatorImageY);

    TextManipulator manipulator;
    manipulator.loadText("../Resources/info.txt");
    manipulator.transformText(this, regulatorTextOffsetX, regulatorTextOffsetY);

    sizer->Add(gridSizer, 1, wxALL | wxEXPAND, 10);
    SetSizer(sizer);

    updateRegulatorImage(regulatorChoice->GetStringSelection());

}

/**
 * @brief Handles regulator type selection.
 */
void TabRegulator::OnRegulatorChoice(wxCommandEvent&) {
    try {
        wxString regulatorType = regulatorChoice->GetStringSelection();
        currentRegulator.reset();
        if (regulatorType == "LM317") {
            currentRegulator = std::make_unique<LM317>();
        } else if (regulatorType == "TL431") {
            currentRegulator = std::make_unique<TL431>();
        } else {
            throw std::runtime_error("Invalid regulator type selected");
        }
        updateRegulatorImage(regulatorType);
    } catch (const std::exception& e) {
        ExceptionHandler::handleException(e, "Error changing regulator type");
    }
}

/**
 * @brief Updates the displayed regulator image based on the selection.
 * @param regulatorType Selected regulator type.
 */
void TabRegulator::updateRegulatorImage(const wxString& regulatorType) {

    wxString imagePath = wxString::Format("../Resources/%s.png", regulatorType);
    imageCtrl->SetBitmap(ImageProcessor::processImage(imagePath, regulatorImageW,
                                                      regulatorImageH));
    Layout();

}

/**
 * @brief Calculates the output voltage of the selected regulator.
 */
void TabRegulator::OnCalculate(wxCommandEvent&) {

    if (!currentRegulator) return;
    try {
        if (auto lm317Regulator = dynamic_cast<LM317*>(currentRegulator.get())) {
            CircuitComponent::CheckAndSetParameter(*lm317Regulator, &LM317::setR1,
                                                   inputR1->GetValue());
            CircuitComponent::CheckAndSetParameter(*lm317Regulator, &LM317::setR2,
                                                   inputR2->GetValue());
        } else if (auto tl431Regulator = dynamic_cast<TL431*>(currentRegulator.get())) {
            CircuitComponent::CheckAndSetParameter(*tl431Regulator, &TL431::setR1,
                                                   inputR1->GetValue());
            CircuitComponent::CheckAndSetParameter(*tl431Regulator, &TL431::setR2,
                                                   inputR2->GetValue());
        }
    } catch (const std::exception& e) {
        ExceptionHandler::handleException(e, "Error calculating regulator parameters");
        return;
    }
    currentRegulator->calculateParameters();
    outputVoltage->SetLabel(wxString::Format("Output voltage: %.2lf V",
                                             currentRegulator->getVoltage()));
}

/**
 * @brief Retrieves the parameters of the selected regulator as a formatted string.
 * @return String containing regulator data or a message if none is selected.
 */
wxString TabRegulator::getData() const {

    if (!currentRegulator) return "No regulator selected.";
    return currentRegulator->getData();

}