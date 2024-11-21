#include "../Inc/TabOpamp.h"
#include "../Inc/NonInvOpamp.h"
#include "../Inc/InvOpamp.h"
#include "../Inc/main.h"
#include "../Inc/imageProcessor.h"
#include <format>
#include <sstream>

TabOpamp::TabOpamp(wxNotebook *parent) : wxPanel(parent, wxID_ANY) {

    auto *mainSizer = new wxBoxSizer(wxVERTICAL);
    auto *gridSizer = new wxFlexGridSizer(14, 2, 20, 50);
    SetBackgroundColour(*wxBLACK);

    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Non-Inverting Amplifier"), 0, wxALIGN_LEFT | wxALL, 5);
    MyFrame::AddEmptyCell(this, gridSizer, 1);
    inputRfbNonInv = MyFrame::CreateInputField(this, gridSizer, "Rfb (Ω):");
    inputRgNonInv = MyFrame::CreateInputField(this, gridSizer, "Rg (Ω):");
    calculateButtonNonInv = MyFrame::CreateButton(this, gridSizer, "Calculate gain", this, &TabOpamp::OnCalculate);
    MyFrame::AddEmptyCell(this, gridSizer, 1);
    resultGainNonInv = new wxStaticText(this, wxID_ANY, "Output gain:");
    gridSizer->Add(resultGainNonInv, 0, wxALIGN_LEFT | wxTOP, 10);

    MyFrame::AddEmptyCell(this, gridSizer, 3);
    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Inverting Amplifier"), 0, wxALIGN_LEFT | wxALL, 5);
    MyFrame::AddEmptyCell(this, gridSizer, 1);
    inputRinInv = MyFrame::CreateInputField(this, gridSizer, "Rin (Ω):");
    inputRfbInv = MyFrame::CreateInputField(this, gridSizer, "Rfb (Ω):");
    calculateButtonInv = MyFrame::CreateButton(this, gridSizer, "Calculate gain", this, &TabOpamp::OnCalculate);
    MyFrame::AddEmptyCell(this, gridSizer, 1);
    resultGainInv = new wxStaticText(this, wxID_ANY, "Output gain:");
    gridSizer->Add(resultGainInv, 0, wxALIGN_LEFT | wxTOP, 10);

    auto *imageCtrlNonInv = new wxStaticBitmap(this, wxID_ANY, ProcessImage("../Resources/noninvopamp.png", 470, 180, true));
    imageCtrlNonInv->Move(350, 30);
    auto *imageCtrlInv = new wxStaticBitmap(this, wxID_ANY, ProcessImage("../Resources/invopamp.png", 470, 180, true));
    imageCtrlInv->Move(350, 290);

    mainSizer->Add(gridSizer, 1, wxALL | wxEXPAND, 10);
    SetSizer(mainSizer);
}

void TabOpamp::OnCalculate(wxCommandEvent &event) {
    if (event.GetEventObject() == calculateButtonNonInv) {
        CalculateOpampGain<NonInvertingOpamp>(inputRfbNonInv, inputRgNonInv, resultGainNonInv);
    } else if (event.GetEventObject() == calculateButtonInv) {
        CalculateOpampGain<InvertingOpamp>(inputRfbInv, inputRinInv, resultGainInv);
    }
}

template <typename T>
void TabOpamp::CalculateOpampGain(wxTextCtrl* inputRfb, wxTextCtrl* inputRin, wxStaticText* resultGain) {
    T opamp;
    //if (!(CircuitComponent::validateValue(inputRfb, opamp.Rfb) &&
    //      CircuitComponent::validateValue(inputRin, opamp.Rin))) return;

    opamp.calculateParameters();
    resultGain->SetLabel(wxString::Format("Output gain: %.2f", opamp.gain));
}

wxString TabOpamp::GetData() const {
    return std::format (
            "Opamp parameters:\n   Inverting amplifier:\n"
            "Rin: {:.2f} Ohm\n"
            "Rfb: {:.2f} Ohm\n"
            "Gain: {:.2f}\nNon-Inverting amplifier:\n"
            "Rg: {:.2f} Ohm\n"
            "Rfb: {:.2f} Ohm\n"
            "Gain: {:.2f}\n",
            RinInv, RfbInv, gainInv, RgNonInv, RfbNonInv, gainNonInv);
}