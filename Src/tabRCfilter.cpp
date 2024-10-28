#include "../Inc/tabRCfilter.h"
#include "../Inc/imageProcessor.h"
#include "../Inc/lowpassRC.h"
#include <wx/dcclient.h>

BEGIN_EVENT_TABLE(tabRCfilter, wxPanel)
EVT_PAINT(tabRCfilter::OnPaint)
END_EVENT_TABLE()

tabRCfilter::tabRCfilter(wxNotebook *parent) : wxPanel(parent, wxID_ANY),
                                               resistance(), capacitance(), calculatedFrequency(0), calculatedTime(0) {

    auto *sizer = new wxBoxSizer(wxVERTICAL);
    auto *gridSizer = new wxFlexGridSizer(8, 2, 20, 50);
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

    auto *calculateButton = new wxButton(this, wxID_ANY, "Calculate Parameters");
    calculateButton->Bind(wxEVT_BUTTON, &tabRCfilter::OnCalculate, this);
    gridSizer->Add(calculateButton, 0, wxALIGN_CENTER_HORIZONTAL, 10);

    resultCutoff = new wxStaticText(this, wxID_ANY, "Cutoff Frequency:");
    resultTimeConstant = new wxStaticText(this, wxID_ANY, "Time Constant:");
    gridSizer->Add(emptyCell1, 0, wxEXPAND);
    gridSizer->Add(resultCutoff, 0, wxALIGN_LEFT | wxTOP, 10);
    gridSizer->Add(emptyCell2, 0, wxEXPAND);
    gridSizer->Add(resultTimeConstant, 0, wxALIGN_LEFT | wxTOP, 10);

    auto *imageCtrl = new wxStaticBitmap(this, wxID_ANY, ProcessImage("../Resources/filter.png", 470, 200, true));
    imageCtrl->Move(350, 30);

    sizer->Add(gridSizer, 1, wxALL | wxEXPAND, 10);
    SetSizer(sizer);
}

void tabRCfilter::OnCalculate(wxCommandEvent &) {

    lowpassRC filter;
    if (!(inputR1->GetValue().ToDouble(&filter.R) && inputC1->GetValue().ToDouble(&filter.C)
          && circuitComponent::validateInput(&filter.R, &filter.C))) return;

    filter.calculateParameters();

    calculatedFrequency = filter.frequency;
    calculatedTime = filter.time;

    resultCutoff->SetLabel(wxString::Format("Cutoff Frequency: %.2f Hz", calculatedFrequency));
    resultTimeConstant->SetLabel(wxString::Format("Time Constant: %.2f μs", calculatedTime));

    timeValues.clear();
    responseValues.clear();
    for (double t = 0; t <= 5 * calculatedTime; t += 0.1) {
        timeValues.push_back(t);
        responseValues.push_back(1.0 - exp(-t / calculatedTime));
    }

    Refresh();
}

void tabRCfilter::OnPaint(wxPaintEvent &) {

    wxPaintDC dc(this);

    const int graphStartX = 390;
    const int graphStartY = 490;
    const int graphWidth = 400;
    const int graphHeight = 210;
    const int numMarks = 10;

    if (timeValues.empty() || responseValues.empty()) return;
    double minTime = *std::min_element(timeValues.begin(), timeValues.end());
    double maxTime = *std::max_element(timeValues.begin(), timeValues.end());
    if (minTime == maxTime) return;

    dc.SetPen(*wxWHITE_PEN);
    dc.DrawLine(graphStartX, graphStartY, graphStartX + graphWidth, graphStartY); // Ось X
    dc.DrawLine(graphStartX, graphStartY, graphStartX, graphStartY - graphHeight); // Ось Y

    for (int i = 0; i <= numMarks; ++i) {
        double value = minTime + i * (maxTime - minTime) / numMarks / 5;
        int x = graphStartX + static_cast<int>(i * (graphWidth / numMarks));
        dc.DrawText(wxString::Format("%.1f", value), x - 10, graphStartY + 5);
    }

    dc.DrawText(wxString::Format("Response"), graphStartX - 40, graphStartY - graphHeight - 30); // Подпись для оси Y

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
        double value = static_cast<double>(i) / numYMarks; // Значение по оси Y (от 0 до 1)
        int y = graphStartY - static_cast<int>((value) * graphHeight); // Позиция по Y
        dc.DrawText(wxString::Format("%.1f", value), graphStartX - 25, y - 5); // Подписи по оси Y
    }

}

wxString tabRCfilter::GetData() const {

    double resistance, capacitance;
    inputR1->GetValue().ToDouble(&resistance);
    inputC1->GetValue().ToDouble(&capacitance);
    return wxString::Format("Данные для RC фильтра\nСопротивление: %.2f Ohm\nЕмкость: %.2f μF\nCutoff Frequency: %.2f Hz\nTime Constant: %.2f μs\n",
                            resistance, capacitance, calculatedFrequency, calculatedTime);

}