#include "../Inc/GraphRenderer.h"
#include <algorithm>

GraphRenderer::GraphRenderer(int startX, int startY, int width, int height, int numMarks)
        : startX(startX), startY(startY), width(width), height(height), numMarks(numMarks) {}

void GraphRenderer::Draw(wxDC &dc, const std::vector<double>& xValues, const std::vector<double>& yValues) const {
    if (xValues.empty() || yValues.empty()) return;

    double minX = *std::min_element(xValues.begin(), xValues.end());
    double maxX = *std::max_element(xValues.begin(), xValues.end());
    if (minX == maxX) return;

    double xScale;
    wxString xUnit;
    DetermineScaleAndUnit(maxX, xScale, xUnit);

    dc.SetPen(*wxWHITE_PEN);
    dc.DrawLine(startX, startY, startX + width, startY);
    dc.DrawLine(startX, startY, startX, startY - height);
    DrawXAxisLabels(dc, minX, maxX, xScale, xUnit);
    DrawYAxisLabels(dc);
    dc.SetPen(*wxCYAN_PEN);
    DrawGraph(dc, xValues, yValues, minX, maxX);
}

void GraphRenderer::DetermineScaleAndUnit(double maxX, double &scale, wxString &unit) {

    if (maxX >= 5e5) {
        scale = 1e6;
        unit = "s";
    } else if (maxX >= 5e2) {
        scale = 1e3;
        unit = "m";
    } else {
        scale = 1;
        unit = "μ";
    }

}

void GraphRenderer::DrawXAxisLabels(wxDC &dc, double minX, double maxX, double xScale, const wxString &unit) const {

    for (int i = 0; i <= numMarks; ++i) {
        double value = (minX + i * (maxX - minX) / numMarks) / xScale;
        int x = startX + static_cast<int>(i * (width / numMarks));
        wxString label = wxString::Format("%.1f%s", value, unit);
        dc.DrawText(label, x - 10, startY + 5);
    }

}

void GraphRenderer::DrawYAxisLabels(wxDC &dc) const {

    const int numYMarks = 10;
    for (int i = 1; i <= numYMarks; ++i) {
        double value = static_cast<double>(i) / numYMarks;
        int y = startY - static_cast<int>((value) * height);
        dc.DrawText(wxString::Format("%.1f", value), startX - 25, y - 5);
    }

}

void GraphRenderer::DrawGraph(wxDC &dc, const std::vector<double>& xValues, const std::vector<double>& yValues,
                              double minX, double maxX) const {

    for (size_t i = 1; i < xValues.size(); ++i) {
        int x1 = startX + static_cast<int>(((xValues[i - 1] - minX) / (maxX - minX)) * width);
        int y1 = startY - static_cast<int>((yValues[i - 1]) * height);
        int x2 = startX + static_cast<int>(((xValues[i] - minX) / (maxX - minX)) * width);
        int y2 = startY - static_cast<int>((yValues[i]) * height);

        if (x1 >= startX && x1 <= startX + width && y1 >= 0 && y1 <= startY) {
            dc.DrawLine(x1, y1, x2, y2);
        }
    }

}