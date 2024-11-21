#include "../Inc/TabRCfilter.h"
#include "../Inc/textManipulations.h"
#include "../Inc/imageProcessor.h"
#include "../Inc/magic.h"
#include "../Inc/GraphRenderer.h"
#include "../Inc/TabBase.h"
#include <wx/dcclient.h>
#include <wx/string.h>

BEGIN_EVENT_TABLE(TabRCfilter, wxPanel)
EVT_PAINT(TabRCfilter::OnPaint)
END_EVENT_TABLE()

TabRCfilter::TabRCfilter(wxNotebook *parent) : wxPanel(parent, wxID_ANY) {

    auto *sizer = new wxBoxSizer(wxVERTICAL);
    auto *gridSizer = new wxFlexGridSizer(5, 2, 20, 50);
    inputR1 = TabBase::CreateInputField(this, gridSizer, "R1 (Ω):");
    inputC1 = TabBase::CreateInputField(this, gridSizer, "C1 (μF):");
    TabBase::CreateButton(this, gridSizer, "Calculate parameters", this, &TabRCfilter::OnCalculate);

    resultCutoff = new wxStaticText(this, wxID_ANY, "Cutoff frequency:");
    resultTimeConstant = new wxStaticText(this, wxID_ANY, "Time constant:");
    TabBase::AddEmptyCell(this, gridSizer, 1);
    gridSizer->Add(resultCutoff, 0, wxALIGN_LEFT | wxTOP, 10);
    TabBase::AddEmptyCell(this, gridSizer, 1);
    gridSizer->Add(resultTimeConstant, 0, wxALIGN_LEFT | wxTOP, 10);

    auto *imageCtrl = new wxStaticBitmap(this, wxID_ANY, ProcessImage("../Resources/Filter.png", 470, 200, true));
    imageCtrl->Move(350, 30);

    sizer->Add(gridSizer, 1, wxALL | wxEXPAND, 10);
    SetSizer(sizer);

    wxString helpText = LoadHelpText("../Resources/help.txt");
    wxArrayString lines = wxSplit(helpText, '\n');
    int yOffset = 300;
    for (const auto& line : lines) {
        if (!line.IsEmpty()) {
            new wxStaticText(this, wxID_ANY, line, wxPoint(10, yOffset));
            yOffset += 20;
        }
    }

    InitializeEmptyGraph();
}

void TabRCfilter::InitializeEmptyGraph() {

    timeValues.clear();
    responseValues.clear();
    for (double t = 0; t <= 5; t += 5) {
        timeValues.push_back(t);
        responseValues.push_back(0.0);
    }

    Refresh();
}

void TabRCfilter::OnCalculate(wxCommandEvent &) {

    LowpassRC filter;
    try {
        CircuitComponent::CheckAndSetParameter(filter, &LowpassRC::setR, inputR1->GetValue());
        CircuitComponent::CheckAndSetParameter(filter, &LowpassRC::setC, inputC1->GetValue());
    } catch (const std::invalid_argument& e) {
        wxLogError("Invalid input: %s", e.what());
        return;
    }

    filter.calculateParameters();

    resultCutoff->SetLabel(wxString::Format("Cutoff frequency : %.2f Hz", filter.getFrequency()));
    resultTimeConstant->SetLabel(wxString::Format("Time constant: %.2f μs", filter.getTime()));

    timeValues.clear();
    responseValues.clear();
    for (double t = 0; t <= 5 * filter.getTime(); t += 1) {
        timeValues.push_back(t);
        responseValues.push_back(1.0 - exp(-t / filter.getTime()));
    }

    Refresh();
}

void TabRCfilter::OnPaint(wxPaintEvent &) {

    wxPaintDC dc(this);
    GraphRenderer renderer(graphStartX, graphStartY, graphWidth, graphHeight, numMarks);
    renderer.Draw(dc, timeValues, responseValues);

}
wxString TabRCfilter::GetData(LowpassRC &filter) {

    return wxString::Format("RC Filter parameters:\nR: %.2f Ohm\nC: %.2f μF\nCutoff frequency: %.2f Hz\nTime constant: %.2f μs\n",
                            filter.getR(), filter.getC(), filter.getFrequency(), filter.getTime());

}