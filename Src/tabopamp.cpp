#include "../Inc/tabopamp.h"
#include "../Inc/opamp.h"
#include "../Inc/imageProcessor.h"

tabopamp::tabopamp(wxNotebook *parent) : wxPanel(parent, wxID_ANY) {

    auto *sizer1 = new wxBoxSizer(wxVERTICAL);
    auto *gridSizer1 = new wxFlexGridSizer(8, 2, 20, 50);
    SetBackgroundColour(*wxBLACK);

    auto *labelR1 = new wxStaticText(this, wxID_ANY, "Rfb (Ω):");
    inputR1 = new wxTextCtrl(this, wxID_ANY);
    auto *labelR2 = new wxStaticText(this, wxID_ANY, "Rin (Ω):");
    inputR2 = new wxTextCtrl(this, wxID_ANY);

    gridSizer1->Add(labelR1, 0, wxALIGN_CENTER_VERTICAL);
    gridSizer1->Add(inputR1, 0, wxEXPAND);
    gridSizer1->Add(labelR2, 0, wxALIGN_CENTER_VERTICAL);
    gridSizer1->Add(inputR2, 0, wxEXPAND);

    auto *calculateButton = new wxButton(this, wxID_ANY, "Calculate Parameters");
    calculateButton->Bind(wxEVT_BUTTON, &tabopamp::OnCalculate, this);
    gridSizer1->Add(calculateButton, 0, wxALIGN_CENTER_HORIZONTAL, 10);

    resultGain = new wxStaticText(this, wxID_ANY, "Output gain:");
    gridSizer1->Add(new wxStaticText(this, wxID_ANY, ""), 0, wxEXPAND);
    gridSizer1->Add(resultGain, 0, wxALIGN_LEFT | wxTOP, 10);

    wxBitmap processedBitmap = ProcessImage(
            "/Users/simple_waveform/Documents/programming/3/coursework v3.0/Resources/opamp.png", 530, 330, true);
    auto *imageCtrl = new wxStaticBitmap(this, wxID_ANY, processedBitmap);
    imageCtrl->Move(320, -20);

    sizer1->Add(gridSizer1, 1, wxALL | wxEXPAND, 10);
    SetSizer(sizer1);

}

void tabopamp::OnCalculate(wxCommandEvent &) {

    Opamp opamp;
    if (!(inputR1->GetValue().ToDouble(&opamp.Rfb) && inputR2->GetValue().ToDouble(&opamp.Rin)
          && circuitComponent::validateInput(&opamp.Rfb, &opamp.Rin))) return;
    opamp.calculateParameters();
    resultGain->SetLabel(wxString::Format("Output gain: %.2f", opamp.gain));

}