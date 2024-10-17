#include "../Inc/tabfilter.h"
#include "../Inc/imageProcessor.h"
#include "../Inc/lowpassRC.h"

tabfilter::tabfilter(wxNotebook* parent) : wxPanel(parent, wxID_ANY) {
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    auto* gridSizer = new wxFlexGridSizer(8, 2, 20, 50);
    SetBackgroundColour(*wxBLACK);

    auto* labelR1 = new wxStaticText(this, wxID_ANY, "R1 (Ω):");
    inputR1 = new wxTextCtrl(this, wxID_ANY);
    auto* labelC1 = new wxStaticText(this, wxID_ANY, "C1 (μF):");
    inputC1 = new wxTextCtrl(this, wxID_ANY);
    auto* emptyCell1 = new wxStaticText(this, wxID_ANY, "");
    auto* emptyCell2 = new wxStaticText(this, wxID_ANY, "");

    gridSizer->Add(labelR1, 0, wxALIGN_CENTER_VERTICAL);
    gridSizer->Add(inputR1, 0, wxEXPAND);
    gridSizer->Add(labelC1, 0, wxALIGN_CENTER_VERTICAL);
    gridSizer->Add(inputC1, 0, wxEXPAND);

    auto* calculateButton = new wxButton(this, wxID_ANY, "Calculate Parameters");
    calculateButton->Bind(wxEVT_BUTTON, &tabfilter::OnCalculate, this);
    gridSizer->Add(calculateButton, 0, wxALIGN_CENTER_HORIZONTAL, 10);

    resultCutoff = new wxStaticText(this, wxID_ANY, "Cutoff Frequency:");
    resultTimeConstant = new wxStaticText(this, wxID_ANY, "Time Constant:");
    gridSizer->Add(emptyCell1, 0, wxEXPAND);
    gridSizer->Add(resultCutoff, 0, wxALIGN_LEFT | wxTOP, 10);
    gridSizer->Add(emptyCell2, 0, wxEXPAND);
    gridSizer->Add(resultTimeConstant, 0, wxALIGN_LEFT | wxTOP, 10);

    wxBitmap processedBitmap = ProcessImage("/Users/simple_waveform/Documents/programming/3/coursework v3.0/Resources/filter.png", 530, 330, true);
    auto* imageCtrl = new wxStaticBitmap(this, wxID_ANY, processedBitmap);
    imageCtrl->Move(320, -20);

    sizer->Add(gridSizer, 1, wxALL | wxEXPAND, 10);
    SetSizer(sizer);
}

void tabfilter::OnCalculate(wxCommandEvent&) {

    lowpassRC filter(0, 0);

    if (!inputR1->GetValue().ToDouble(&filter.R) || !inputC1->GetValue().ToDouble(&filter.C)) {
        wxMessageBox("Please enter valid numeric values.", "Error", wxOK | wxICON_ERROR);
        return;
    }
    if (filter.R <= 0 || filter.C <= 0) {
        wxMessageBox("Values must be positive and non-zero.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    filter.calculateParameters();

    resultCutoff->SetLabel(wxString::Format("Cutoff Frequency: %.2f Hz", filter.frequency));
    resultTimeConstant->SetLabel(wxString::Format("Time Constant: %.2f us", filter.time));

}