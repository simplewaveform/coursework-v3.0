#include "../Inc/tabfilter.h"
#include "../Inc/calculations.h"

tabfilter::tabfilter(wxNotebook* parent) : wxPanel(parent, wxID_ANY) {

    auto* sizer1 = new wxBoxSizer(wxVERTICAL);
    auto* gridSizer1 = new wxFlexGridSizer(8, 2, 20, 50);
    SetBackgroundColour(*wxBLACK);

    auto* labelR1 = new wxStaticText(this, wxID_ANY, "R1 (Ω):");
    inputR1 = new wxTextCtrl(this, wxID_ANY);
    auto* labelC1 = new wxStaticText(this, wxID_ANY, "C1 (μF):");
    inputC1 = new wxTextCtrl(this, wxID_ANY);

    auto* emptyCell1 = new wxStaticText(this, wxID_ANY, "");
    auto* emptyCell2 = new wxStaticText(this, wxID_ANY, "");

    gridSizer1->Add(labelR1, 0, wxALIGN_CENTER_VERTICAL);
    gridSizer1->Add(inputR1, 0, wxEXPAND);
    gridSizer1->Add(labelC1, 0, wxALIGN_CENTER_VERTICAL);
    gridSizer1->Add(inputC1, 0, wxEXPAND);

    auto* calculateButton = new wxButton(this, wxID_ANY, "Calculate Parameters");
    calculateButton->Bind(wxEVT_BUTTON, &tabfilter::OnCalculate, this);
    gridSizer1->Add(calculateButton, 0, wxALIGN_CENTER_HORIZONTAL, 10);

    resultCutoff = new wxStaticText(this, wxID_ANY, "Cutoff Frequency:");
    resultTimeConstant = new wxStaticText(this, wxID_ANY, "Time Constant:");
    gridSizer1->Add(emptyCell1, 0, wxEXPAND);
    gridSizer1->Add(resultCutoff, 0, wxALIGN_LEFT | wxTOP, 10);
    gridSizer1->Add(emptyCell2, 0, wxEXPAND);
    gridSizer1->Add(resultTimeConstant, 0, wxALIGN_LEFT | wxTOP, 10);

    wxBitmap processedBitmap = ProcessImage("/Users/simple_waveform/Documents/programming/3/coursework/Resources/filter.png", 530, 330, true);
    auto* imageCtrl = new wxStaticBitmap(this, wxID_ANY, processedBitmap);
    imageCtrl->Move(320, -20);

    sizer1->Add(gridSizer1, 1, wxALL | wxEXPAND, 10);
    SetSizer(sizer1);

}

void tabfilter::OnCalculate(wxCommandEvent&) {

    double R, C;

    if (!inputR1->GetValue().ToDouble(&R) || !inputC1->GetValue().ToDouble(&C)) {
        wxMessageBox("Please enter valid numeric values.", "Error", wxOK | wxICON_ERROR);
        return;
    }
    if (R <= 0 || C <= 0) {
        wxMessageBox("Values must be positive and non-zero.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    double* results = filter(R, C);
    resultCutoff->SetLabel(wxString::Format("Cutoff Frequency: %.2f Hz", results[0]));
    resultTimeConstant->SetLabel(wxString::Format("Time Constant: %.2f us", results[1]));
    delete[] results;

}