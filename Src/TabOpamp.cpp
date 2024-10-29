#include "../Inc/TabOpamp.h"
#include "../Inc/NonInvOpamp.h"
#include "../Inc/InvOpamp.h"
#include "../Inc/CircuitComponent.h"
#include "../Inc/imageProcessor.h"

enum {
    ID_CALCULATE_NON_INV = 6000,
    ID_CALCULATE_INV = 6001
};

tabOpamp::tabOpamp(wxNotebook *parent) : wxPanel(parent, wxID_ANY) {

    auto *mainSizer = new wxBoxSizer(wxVERTICAL);
    auto *gridSizer = new wxFlexGridSizer(14, 2, 20, 50);

    SetBackgroundColour(*wxBLACK);

    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Non-Inverting Amplifier"), 0, wxALIGN_LEFT | wxALL, 5);
    gridSizer->Add(new wxStaticText(this, wxID_ANY, ""));
    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Rfb (Ω):"));
    inputRfbNonInv = new wxTextCtrl(this, wxID_ANY);
    gridSizer->Add(inputRfbNonInv, 0, wxEXPAND);

    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Rg (Ω):"));
    inputRgNonInv = new wxTextCtrl(this, wxID_ANY);
    gridSizer->Add(inputRgNonInv, 0, wxEXPAND);

    calculateButtonNonInv = new wxButton(this, ID_CALCULATE_NON_INV, "Calculate gain");
    calculateButtonNonInv->Bind(wxEVT_BUTTON, &tabOpamp::OnCalculate, this);
    gridSizer->Add(calculateButtonNonInv, 0, wxALIGN_LEFT, 10);
    gridSizer->Add(new wxStaticText(this, wxID_ANY, ""));

    resultGainNonInv = new wxStaticText(this, wxID_ANY, "Output gain:");
    gridSizer->Add(resultGainNonInv, 0, wxALIGN_LEFT | wxTOP, 10);

    // Инвертирующий усилитель
    gridSizer->Add(new wxStaticText(this, wxID_ANY, ""));
    gridSizer->Add(new wxStaticText(this, wxID_ANY, ""));
    gridSizer->Add(new wxStaticText(this, wxID_ANY, ""));
    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Inverting Amplifier"), 0, wxALIGN_LEFT | wxALL, 5);
    gridSizer->Add(new wxStaticText(this, wxID_ANY, ""));

    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Rin (Ω):"));
    inputRinInv = new wxTextCtrl(this, wxID_ANY);
    gridSizer->Add(inputRinInv, 0, wxEXPAND);

    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Rfb (Ω):"));
    inputRfbInv = new wxTextCtrl(this, wxID_ANY);
    gridSizer->Add(inputRfbInv, 0, wxEXPAND);

    calculateButtonInv = new wxButton(this, ID_CALCULATE_INV, "Calculate gain");
    calculateButtonInv->Bind(wxEVT_BUTTON, &tabOpamp::OnCalculate, this);
    gridSizer->Add(calculateButtonInv, 0, wxALIGN_LEFT, 10);

    gridSizer->Add(new wxStaticText(this, wxID_ANY, ""));
    resultGainInv = new wxStaticText(this, wxID_ANY, "Output gain:");
    gridSizer->Add(resultGainInv, 0, wxALIGN_LEFT | wxTOP, 10);

    auto *imageCtrlNonInv = new wxStaticBitmap(this, wxID_ANY, ProcessImage("../Resources/noninvopamp.png", 470, 180, true));
    imageCtrlNonInv->Move(350, 30);
    auto *imageCtrlInv = new wxStaticBitmap(this, wxID_ANY, ProcessImage("../Resources/invopamp.png", 470, 180, true));
    imageCtrlInv->Move(350, 290);

    mainSizer->Add(gridSizer, 1, wxALL | wxEXPAND, 10);
    SetSizer(mainSizer);

}

void tabOpamp::OnCalculate(wxCommandEvent &event) {

    if (event.GetEventObject() == calculateButtonNonInv) {
        NonInvertingOpamp nonInvOpamp;
        if (!(inputRfbNonInv->GetValue().ToDouble(&nonInvOpamp.Rfb) && inputRgNonInv->GetValue().ToDouble(&nonInvOpamp.Rg)
              && CircuitComponent::validateInput(nonInvOpamp.Rfb, nonInvOpamp.Rg))) return;
        nonInvOpamp.calculateParameters();
        RgNonInv = nonInvOpamp.Rg;
        RfbNonInv = nonInvOpamp.Rfb;
        gainNonInv = nonInvOpamp.gain;
        resultGainNonInv->SetLabel(wxString::Format("Output gain: %.2f", gainNonInv));
    } else if (event.GetEventObject() == calculateButtonInv) {
        InvertingOpamp invOpamp;
        if (!(inputRfbInv->GetValue().ToDouble(&invOpamp.Rfb) && inputRinInv->GetValue().ToDouble(&invOpamp.Rin)
              && CircuitComponent::validateInput(invOpamp.Rfb, invOpamp.Rin))) return;
        invOpamp.calculateParameters();
        RinInv = invOpamp.Rin;
        RfbInv = invOpamp.Rfb;
        gainInv = invOpamp.gain;
        resultGainInv->SetLabel(wxString::Format("Output gain: %.2f", gainInv));
    }

}

wxString tabOpamp::GetData() const {

    return wxString::Format("Opamp parameters:\n   Inverting amplifier:\nRin: %.2f Ohm\nRfb: %.2f Ohm\n"
                            "   Gain: %.2f\nNon-Inverting amplifier:\nRg: %.2f Ohm\nRfb: %.2f Ohm\nGain: %.2f\n",
                            RgNonInv, RfbNonInv, gainNonInv, RinInv, RfbInv, gainInv);

}
