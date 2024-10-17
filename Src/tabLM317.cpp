#include "../Inc/tabLM317.h"
#include "../Inc/calculations.h"

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

    resultVoltage = new wxStaticText(this, wxID_ANY, "Output voltage:");
    gridSizer1->Add(emptyCell1, 0, wxEXPAND);
    gridSizer1->Add(resultVoltage, 0, wxALIGN_LEFT | wxTOP, 10);


    wxBitmap processedBitmap = ProcessImage("/Users/simple_waveform/Documents/programming/3/coursework/Resources/LM317.png", 530, 330, true);
    auto* imageCtrl = new wxStaticBitmap(this, wxID_ANY, processedBitmap);
    imageCtrl->Move(320, 0);


    sizer1->Add(gridSizer1, 1, wxALL | wxEXPAND, 10);
    SetSizer(sizer1);

}

void tabLM317::OnCalculate(wxCommandEvent&) {

    double R1, R2;

    if (!inputR1->GetValue().ToDouble(&R1) || !inputR2->GetValue().ToDouble(&R2)) {
        wxMessageBox("Please enter valid numeric values.", "Error", wxOK | wxICON_ERROR);
        return;
    }
    if (R1 <= 0 || R2 <= 0) {
        wxMessageBox("Values must be positive and non-zero.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    resultVoltage->SetLabel(wxString::Format("Output voltage: %.2f V", lm317(R1, R2)));

}