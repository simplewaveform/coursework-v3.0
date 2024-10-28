#include "../Inc/tabLM317.h"
#include "../Inc/LM317.h"
#include "../Inc/imageProcessor.h"

tabLM317::tabLM317(wxNotebook* parent) : wxPanel(parent, wxID_ANY) {

    auto* sizer1 = new wxBoxSizer(wxVERTICAL);
    auto* gridSizer1 = new wxFlexGridSizer(8, 2, 20, 50);
    SetBackgroundColour(*wxBLACK);

    auto* labelR1 = new wxStaticText(this, wxID_ANY, "R1 (Ω):");
    inputR1 = new wxTextCtrl(this, wxID_ANY);
    auto* labelR2 = new wxStaticText(this, wxID_ANY, "R2 (Ω):");
    inputR2 = new wxTextCtrl(this, wxID_ANY);

    auto* emptyCell1 = new wxStaticText(this, wxID_ANY, "");

    gridSizer1->Add(labelR1, 0, wxALIGN_CENTER_VERTICAL);
    gridSizer1->Add(inputR1, 0, wxEXPAND);
    gridSizer1->Add(labelR2, 0, wxALIGN_CENTER_VERTICAL);
    gridSizer1->Add(inputR2, 0, wxEXPAND);

    auto* calculateButton = new wxButton(this, wxID_ANY, "Calculate Parameters");
    calculateButton->Bind(wxEVT_BUTTON, &tabLM317::OnCalculate, this);
    gridSizer1->Add(calculateButton, 0, wxALIGN_CENTER_HORIZONTAL, 10);

    outputVoltage = new wxStaticText(this, wxID_ANY, "Output voltage:");
    gridSizer1->Add(emptyCell1, 0, wxEXPAND);
    gridSizer1->Add(outputVoltage, 0, wxALIGN_LEFT | wxTOP, 10);


    wxBitmap processedBitmap = ProcessImage("/Users/simple_waveform/Documents/programming/3/coursework v3.0/Resources/LM317.png", 530, 330, true);
    auto* imageCtrl = new wxStaticBitmap(this, wxID_ANY, processedBitmap);
    imageCtrl->Move(320, 0);


    sizer1->Add(gridSizer1, 1, wxALL | wxEXPAND, 10);
    SetSizer(sizer1);

}

void tabLM317::OnCalculate(wxCommandEvent&) {

    LM317 regulator;
    if (!(inputR1->GetValue().ToDouble(&regulator.R1) && inputR2->GetValue().ToDouble(&regulator.R2)
          && circuitComponent::validateInput(&regulator.R1, &regulator.R2))) return;
    regulator.calculateParameters();
    outputVoltage->SetLabel(wxString::Format("Output voltage: %.2f V", regulator.outputVoltage));

}