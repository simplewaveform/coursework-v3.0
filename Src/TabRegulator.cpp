#include "../Inc/TabRegulator.h"
#include "../Inc/LM317.h"
#include "../Inc/TL431.h"
#include "../Inc/main.h"
#include "../Inc/imageProcessor.h"

TabRegulator::TabRegulator(wxNotebook* parent) : wxPanel(parent, wxID_ANY) {
    auto* sizer1 = new wxBoxSizer(wxVERTICAL);
    auto* gridSizer = new wxFlexGridSizer(8, 2, 20, 50);
    SetBackgroundColour(*wxBLACK);

    auto* labelRegulatorType = new wxStaticText(this, wxID_ANY, "Regulator type:");
    regulatorChoice = new wxChoice(this, wxID_ANY);
    regulatorChoice->Append("LM317");
    regulatorChoice->Append("TL431");
    regulatorChoice->SetSelection(0);

    gridSizer->Add(labelRegulatorType, 0, wxALIGN_CENTER_VERTICAL);
    gridSizer->Add(regulatorChoice, 0, wxEXPAND);

    inputR1 = MyFrame::CreateInputField(this, gridSizer, "R1 (Ω):");
    inputR2 = MyFrame::CreateInputField(this, gridSizer, "R2 (Ω):");
    MyFrame::CreateButton(this, gridSizer, "Calculate voltage", this, &TabRegulator::OnCalculate);

    outputVoltage = new wxStaticText(this, wxID_ANY, "Output voltage:");
    MyFrame::AddEmptyCell(this, gridSizer, 1);
    gridSizer->Add(outputVoltage, 0, wxALIGN_LEFT | wxTOP, 10);

    regulatorChoice->Bind(wxEVT_CHOICE, &TabRegulator::OnRegulatorChoice, this);

    wxBitmap processedBitmap = ProcessImage("../Resources/LM317.png", 400, 250, true);
    imageCtrl = new wxStaticBitmap(this, wxID_ANY, processedBitmap);
    imageCtrl->Move(400, 50);

    sizer1->Add(gridSizer, 1, wxALL | wxEXPAND, 10);
    SetSizer(sizer1);

    UpdateRegulatorImage(regulatorChoice->GetStringSelection());
}

void TabRegulator::OnRegulatorChoice(wxCommandEvent&) {
    wxString regulatorType = regulatorChoice->GetStringSelection();
    UpdateRegulatorImage(regulatorType);
}

void TabRegulator::UpdateRegulatorImage(const wxString& regulatorType) {
    wxBitmap processedBitmap;
    if (regulatorType == "LM317") {
        processedBitmap = ProcessImage("../Resources/LM317.png", 400, 250, true);
    } else if (regulatorType == "TL431") {
        processedBitmap = ProcessImage("../Resources/TL431.png", 400, 250, true);
    }

    imageCtrl->SetBitmap(processedBitmap);
    Layout();
}

void TabRegulator::OnCalculate(wxCommandEvent&) {

    std::unique_ptr<Regulator> reg;
    if (regulatorChoice->GetStringSelection() == "LM317") {
        reg = std::make_unique<LM317>();
    } else if (regulatorChoice->GetStringSelection() == "TL431") {
        reg = std::make_unique<TL431>();
    }

    //if (!(CircuitComponent::validateValue(inputR1, reg->R1) &&
    //      CircuitComponent::validateValue(inputR2, reg->R2))) return;

    reg->calculateParameters();
    R1 = reg->R1;
    R2 = reg->R2;
    voltage = reg->outputVoltage;

    outputVoltage->SetLabel(wxString::Format("Output voltage: %.2f V", reg->outputVoltage));
}

wxString TabRegulator::GetData() {
    return wxString::Format("Regulator type: %s\nR1: %.2f Ω\nR2: %.2f Ω\nOutput voltage: %.2f V\n",
                            regulatorChoice->GetStringSelection(),R1, R2, voltage);
}