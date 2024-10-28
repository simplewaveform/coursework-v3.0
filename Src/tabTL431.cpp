#include "../Inc/tabTL431.h"
#include "../Inc/TL431.h"
#include "../Inc/imageProcessor.h"

tabTL431::tabTL431(wxNotebook* parent) : wxPanel(parent, wxID_ANY) {

    //sizer creating
    auto* sizer1 = new wxBoxSizer(wxVERTICAL);
    auto* gridSizer1 = new wxFlexGridSizer(4, 2, 20, 50);
    SetBackgroundColour(*wxBLACK);

    //R1 label and control field
    auto* labelR1 = new wxStaticText(this, wxID_ANY, "R1 (Ω):");
    gridSizer1->Add(labelR1, 0, wxALIGN_CENTER_VERTICAL);
    inputR1 = new wxTextCtrl(this, wxID_ANY);
    gridSizer1->Add(inputR1, 0, wxEXPAND);

    //R2 label and control field
    auto* labelR2 = new wxStaticText(this, wxID_ANY, "R2 (Ω):");
    gridSizer1->Add(labelR2, 0, wxALIGN_CENTER_VERTICAL);
    inputR2 = new wxTextCtrl(this, wxID_ANY);
    gridSizer1->Add(inputR2, 0, wxEXPAND);

    //dummy cell for proper spacing
    auto* emptyCell1 = new wxStaticText(this, wxID_ANY, "");

    //calculate button
    auto* calculateButton = new wxButton(this, wxID_ANY, "Calculate voltage");
    calculateButton->Bind(wxEVT_BUTTON, &tabTL431::OnCalculate, this);
    gridSizer1->Add(calculateButton, 0, wxALIGN_CENTER_HORIZONTAL, 10);

    //output voltage field
    outputVoltage = new wxStaticText(this, wxID_ANY, "Output voltage:");
    gridSizer1->Add(emptyCell1, 0, wxEXPAND);
    gridSizer1->Add(outputVoltage, 0, wxALIGN_LEFT | wxTOP, 10);

    //image handling
    wxBitmap processedBitmap = ProcessImage("/Users/simple_waveform/Documents/programming/3/coursework v3.0/Resources/tl431.png", 530, 330, true);
    auto* imageCtrl = new wxStaticBitmap(this, wxID_ANY, processedBitmap);
    imageCtrl->Move(300, 0);

    //sizer initializing
    sizer1->Add(gridSizer1, 2, wxALL | wxEXPAND, 10);
    SetSizer(sizer1);

}

void tabTL431::OnCalculate(wxCommandEvent&) {

    TL431 regulator;
    if (!(inputR1->GetValue().ToDouble(&regulator.R1) && inputR2->GetValue().ToDouble(&regulator.R2)
          && circuitComponent::validateInput(&regulator.R1, &regulator.R2))) return;
    regulator.calculateParameters();
    outputVoltage->SetLabel(wxString::Format("Output voltage: %.2f V", regulator.outputVoltage));

}