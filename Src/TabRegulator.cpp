#include "../Inc/TabRegulator.h"
#include "../Inc/LM317.h"
#include "../Inc/TL431.h"
#include "../Inc/imageProcessor.h"

TabRegulator::TabRegulator(wxNotebook* parent) : wxPanel(parent, wxID_ANY) {

    auto* sizer1 = new wxBoxSizer(wxVERTICAL);
    auto* gridSizer1 = new wxFlexGridSizer(8, 2, 20, 50);
    SetBackgroundColour(*wxBLACK);

    auto* labelRegulatorType = new wxStaticText(this, wxID_ANY, "Regulator type:");
    regulatorChoice = new wxChoice(this, wxID_ANY);
    regulatorChoice->Append("LM317");
    regulatorChoice->Append("TL431");
    regulatorChoice->SetSelection(0);

    auto* labelR1 = new wxStaticText(this, wxID_ANY, "R1 (Ω):");
    inputR1 = new wxTextCtrl(this, wxID_ANY);
    auto* labelR2 = new wxStaticText(this, wxID_ANY, "R2 (Ω):");
    inputR2 = new wxTextCtrl(this, wxID_ANY);

    auto* emptyCell1 = new wxStaticText(this, wxID_ANY, "");

    gridSizer1->Add(labelRegulatorType, 0, wxALIGN_CENTER_VERTICAL);
    gridSizer1->Add(regulatorChoice, 0, wxEXPAND);
    gridSizer1->Add(labelR1, 0, wxALIGN_CENTER_VERTICAL);
    gridSizer1->Add(inputR1, 0, wxEXPAND);
    gridSizer1->Add(labelR2, 0, wxALIGN_CENTER_VERTICAL);
    gridSizer1->Add(inputR2, 0, wxEXPAND);

    auto* calculateButton = new wxButton(this, wxID_ANY, "Calculate voltage");
    calculateButton->Bind(wxEVT_BUTTON, &TabRegulator::OnCalculate, this);
    gridSizer1->Add(calculateButton, 0, wxALIGN_LEFT, 10);

    outputVoltage = new wxStaticText(this, wxID_ANY, "Output voltage:");
    gridSizer1->Add(emptyCell1, 0, wxEXPAND);
    gridSizer1->Add(outputVoltage, 0, wxALIGN_LEFT | wxTOP, 10);

    regulatorChoice->Bind(wxEVT_CHOICE, &TabRegulator::OnRegulatorChoice, this);

    wxBitmap processedBitmap = ProcessImage("../Resources/LM317.png", 400, 250, true);
    imageCtrl = new wxStaticBitmap(this, wxID_ANY, processedBitmap);
    imageCtrl->Move(400, 50);

    sizer1->Add(gridSizer1, 1, wxALL | wxEXPAND, 10);
    SetSizer(sizer1);

}

void TabRegulator::OnCalculate(wxCommandEvent&) {

    std::unique_ptr<Regulator> reg;
    if (regulatorChoice->GetStringSelection() == "LM317") {
        reg = std::make_unique<LM317>();
    } else if (regulatorChoice->GetStringSelection() == "TL431") {
        reg = std::make_unique<TL431>();
    }

    if (!(inputR1->GetValue().ToDouble(&reg->R1) &&
          inputR2->GetValue().ToDouble(&reg->R2)) &&
          !CircuitComponent::validateInput(reg->R1, reg->R2)) return;

    reg->calculateParameters();
    R1 = reg->R1;
    R2 = reg->R2;
    voltage = reg->outputVoltage;

    outputVoltage->SetLabel(wxString::Format("Output voltage: %.2f V", reg->outputVoltage));

}

wxString TabRegulator::GetData() {

    return wxString::Format("Regulator type: %s\nR1: %.2f Ω\nR2: %.2f Ω\nOutput voltage: %.2f V\n",
                            regulatorChoice->GetStringSelection(),
                            R1, R2, voltage);

}

void TabRegulator::OnRegulatorChoice(wxCommandEvent&) {

    wxString regulatorType = regulatorChoice->GetStringSelection();
    wxBitmap processedBitmap;
    if (regulatorType == "LM317") {
        processedBitmap = ProcessImage("../Resources/LM317.png", 400, 250, true);
    } else {
        processedBitmap = ProcessImage("../Resources/TL431.png", 400, 250, true);
    }
    imageCtrl->SetBitmap(processedBitmap);
    outputVoltage->SetLabel("Output voltage:");

    Layout();
}
