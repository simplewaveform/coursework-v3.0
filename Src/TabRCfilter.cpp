#include "../Inc/TabRCfilter.h"
#include "../Inc/textManipulations.h"
#include "../Inc/imageProcessor.h"
#include "../Inc/LowpassRC.h"
#include <wx/dcclient.h>
#include <wx/txtstrm.h>
#include <wx/string.h>
#include <fstream>

BEGIN_EVENT_TABLE(TabRCfilter, wxPanel)
EVT_PAINT(TabRCfilter::OnPaint)
END_EVENT_TABLE()

TabRCfilter::TabRCfilter(wxNotebook *parent) : wxPanel(parent, wxID_ANY),
                                               resistance(), capacitance(), calculatedFrequency(0), calculatedTime(0) {

    auto *sizer = new wxBoxSizer(wxVERTICAL);
    auto *gridSizer = new wxFlexGridSizer(5, 2, 20, 50);
    SetBackgroundColour(*wxBLACK);

    auto *labelR1 = new wxStaticText(this, wxID_ANY, "R1 (Ω):");
    inputR1 = new wxTextCtrl(this, wxID_ANY);
    auto *labelC1 = new wxStaticText(this, wxID_ANY, "C1 (μF):");
    inputC1 = new wxTextCtrl(this, wxID_ANY);
    auto *emptyCell1 = new wxStaticText(this, wxID_ANY, "");
    auto *emptyCell2 = new wxStaticText(this, wxID_ANY, "");

    gridSizer->Add(labelR1, 0, wxALIGN_CENTER_VERTICAL);
    gridSizer->Add(inputR1, 0, wxEXPAND);
    gridSizer->Add(labelC1, 0, wxALIGN_CENTER_VERTICAL);
    gridSizer->Add(inputC1, 0, wxEXPAND);

    auto *calculateButton = new wxButton(this, wxID_ANY, "Calculate parameters");
    calculateButton->Bind(wxEVT_BUTTON, &TabRCfilter::OnCalculate, this);
    gridSizer->Add(calculateButton, 0, wxALIGN_CENTER_HORIZONTAL, 10);

    resultCutoff = new wxStaticText(this, wxID_ANY, "Cutoff frequency:");
    resultTimeConstant = new wxStaticText(this, wxID_ANY, "Time constant:");
    gridSizer->Add(emptyCell1);
    gridSizer->Add(resultCutoff, 0, wxALIGN_LEFT | wxTOP, 10);
    gridSizer->Add(emptyCell2);
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
    if (!(inputR1->GetValue().ToDouble(&filter.R) && inputC1->GetValue().ToDouble(&filter.C)
          && CircuitComponent::validateInput(filter.R, filter.C))) return;

    filter.calculateParameters();

    resistance = filter.R;
    capacitance = filter.C;
    calculatedFrequency = filter.frequency;
    calculatedTime = filter.time;

    resultCutoff->SetLabel(wxString::Format("Cutoff frequency: %.2f Hz", calculatedFrequency));
    resultTimeConstant->SetLabel(wxString::Format("Time constant: %.2f μs", calculatedTime));

    timeValues.clear();
    responseValues.clear();
    for (double t = 0; t <= 5 * calculatedTime; t += 0.05) {
        timeValues.push_back(t);
        responseValues.push_back(1.0 - exp(-t / calculatedTime));
    }

    Refresh();
}

void TabRCfilter::OnPaint(wxPaintEvent &) {

    wxPaintDC dc(this);

    const int graphStartX = 390, graphStartY = 490, graphWidth = 400, graphHeight = 210, numMarks = 10;

    if (timeValues.empty() || responseValues.empty()) return;
    double minTime = *std::min_element(timeValues.begin(), timeValues.end());
    double maxTime = *std::max_element(timeValues.begin(), timeValues.end());
    if (minTime == maxTime) return;

    dc.SetPen(*wxWHITE_PEN);
    dc.DrawLine(graphStartX, graphStartY, graphStartX + graphWidth, graphStartY);
    dc.DrawLine(graphStartX, graphStartY, graphStartX, graphStartY - graphHeight);

    for (int i = 0; i <= numMarks; ++i) {
        double value = minTime + i * (maxTime - minTime) / numMarks / 5;
        int x = graphStartX + static_cast<int>(i * (graphWidth / numMarks));
        dc.DrawText(wxString::Format("%.1f", value), x - 10, graphStartY + 5);
    }


    dc.SetPen(*wxCYAN_PEN);
    for (size_t i = 1; i < timeValues.size(); ++i) {
        int x1 = graphStartX + static_cast<int>(((timeValues[i - 1] - minTime) / (maxTime - minTime)) * graphWidth);
        int y1 = graphStartY - static_cast<int>((responseValues[i - 1]) * (graphHeight));
        int x2 = graphStartX + static_cast<int>(((timeValues[i] - minTime) / (maxTime - minTime)) * graphWidth);
        int y2 = graphStartY - static_cast<int>((responseValues[i]) * (graphHeight));

        if (x1 >= graphStartX && x1 <= graphStartX + graphWidth && y1 >= 0 && y1 <= graphStartY) {
            dc.DrawLine(x1, y1, x2, y2);
        }
    }

    const int numYMarks = 10;
    for (int i = 1; i <= numYMarks; ++i) {
        double value = static_cast<double>(i) / numYMarks;
        int y = graphStartY - static_cast<int>((value) * graphHeight);
        dc.DrawText(wxString::Format("%.1f", value), graphStartX - 25, y - 5);
    }

}

wxString TabRCfilter::GetData() const {

    return wxString::Format("RC Filter parameters:\nR: %.2f Ohm\nC: %.2f μF\nCutoff frequency: %.2f Hz\nTime constant: %.2f μs\n",
                            resistance, capacitance, calculatedFrequency, calculatedTime);

}