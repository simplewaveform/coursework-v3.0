#include "../Inc/tabRegulator.h"
#include "../Inc/LM317.h"
#include "../Inc/TL431.h"
#include "../Inc/imageProcessor.h"

tabregulator::tabregulator(wxNotebook* parent) : wxPanel(parent, wxID_ANY) {

    auto* sizer1 = new wxBoxSizer(wxVERTICAL);
    auto* gridSizer1 = new wxFlexGridSizer(8, 2, 20, 50);
    SetBackgroundColour(*wxBLACK);

    auto* labelRegulatorType = new wxStaticText(this, wxID_ANY, "Тип регулятора:");
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

    auto* calculateButton = new wxButton(this, wxID_ANY, "Рассчитать параметры");
    calculateButton->Bind(wxEVT_BUTTON, &tabregulator::OnCalculate, this);
    gridSizer1->Add(calculateButton, 0, wxALIGN_LEFT, 10);

    outputVoltage = new wxStaticText(this, wxID_ANY, "Выходное напряжение:");
    gridSizer1->Add(emptyCell1, 0, wxEXPAND);
    gridSizer1->Add(outputVoltage, 0, wxALIGN_LEFT | wxTOP, 10);

    regulatorChoice->Bind(wxEVT_CHOICE, &tabregulator::OnRegulatorChoice, this);

    wxBitmap processedBitmap = ProcessImage("/Users/simple_waveform/Documents/programming/3/coursework v3.0/Resources/LM317.png", 400, 250, true);
    imageCtrl = new wxStaticBitmap(this, wxID_ANY, processedBitmap);
    imageCtrl->Move(400, 50);

    sizer1->Add(gridSizer1, 1, wxALL | wxEXPAND, 10);
    SetSizer(sizer1);
}

void tabregulator::OnCalculate(wxCommandEvent&) {
    wxString regulatorType = regulatorChoice->GetStringSelection();

    if (regulatorType == "LM317") {
        LM317 regulator;
        if (!(inputR1->GetValue().ToDouble(&regulator.R1) && inputR2->GetValue().ToDouble(&regulator.R2)
              && circuitComponent::validateInput(&regulator.R1, &regulator.R2))) return;
        regulator.calculateParameters();
        outputVoltage->SetLabel(wxString::Format("Выходное напряжение: %.2f В", regulator.outputVoltage));
    } else if (regulatorType == "TL431") {
        TL431 regulator;
        if (!(inputR1->GetValue().ToDouble(&regulator.R1) && inputR2->GetValue().ToDouble(&regulator.R2)
              && circuitComponent::validateInput(&regulator.R1, &regulator.R2))) return;
        regulator.calculateParameters();
        outputVoltage->SetLabel(wxString::Format("Выходное напряжение: %.2f В", regulator.outputVoltage));
    }
}

void tabregulator::OnRegulatorChoice(wxCommandEvent&) {

    wxString regulatorType = regulatorChoice->GetStringSelection();
    if (regulatorType == "LM317") {
        wxBitmap processedBitmap = ProcessImage("/Users/simple_waveform/Documents/programming/3/coursework v3.0/Resources/LM317.png", 400, 250, true);
        imageCtrl->SetBitmap(processedBitmap);
        outputVoltage->SetLabel("Выходное напряжение:");
    } else if (regulatorType == "TL431") {
        wxBitmap processedBitmap = ProcessImage("/Users/simple_waveform/Documents/programming/3/coursework v3.0/Resources/TL431.png", 400, 250, true);
        imageCtrl->SetBitmap(processedBitmap);
        outputVoltage->SetLabel("Выходное напряжение:");
    }

    Layout();
}
