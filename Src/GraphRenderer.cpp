#include "../Inc/GraphRenderer.h"
#include "../Inc/magic.h"

/**
 * @brief Draws a graph using provided data points.
 * @param dc Device context for drawing.
 * @param xValues X-axis values.
 * @param yValues Y-axis values.
 */
void GraphRenderer::Draw(wxDC &dc, const std::vector<double>& xValues, const std::vector<double>& yValues) {

    if (xValues.empty() || yValues.empty()) return;
    double minX = *std::min_element(xValues.begin(), xValues.end());
    double maxX = *std::max_element(xValues.begin(), xValues.end());
    if (minX == maxX) return;

    double xScale;
    wxString xUnit;
    DetermineScaleAndUnit(maxX, xScale, xUnit);

    dc.SetPen(*wxWHITE_PEN);
    dc.DrawLine(graphStartX, graphStartY, graphStartX + graphWidth, graphStartY);
    dc.DrawLine(graphStartX, graphStartY, graphStartX, graphStartY - graphHeight);
    DrawXAxisLabels(dc, minX, maxX, xScale, xUnit);
    DrawYAxisLabels(dc);
    dc.SetPen(*wxCYAN_PEN);
    DrawGraph(dc, xValues, yValues, minX, maxX);

}

/**
 * @brief Determines scale and unit for the X-axis.
 * @param maxX Maximum X value.
 * @param scale Output scale factor.
 * @param unit Output unit as a string.
 */
void GraphRenderer::DetermineScaleAndUnit(double maxX, double &scale, wxString &unit) {

    if (maxX >= 1e6) {
        scale = 1e6;
        unit = "s";
    } else if (maxX >= 1e3) {
        scale = 1e3;
        unit = "m";
    } else {
        scale = 1;
        unit = "μ";
    }

}

/**
 * @brief Draws labels for the X-axis.
 * @param dc Device context for drawing.
 * @param minX Minimum X value.
 * @param maxX Maximum X value.
 * @param xScale Scale factor for X-axis.
 * @param unit Unit for X-axis.
 */
void GraphRenderer::DrawXAxisLabels(wxDC &dc, double minX, double maxX, double xScale, const wxString &unit) {

    for (int i = 0; i <= numMarks; ++i) {
        double value = (minX + i * (maxX - minX) / numMarks) / xScale;
        int x = graphStartX + static_cast<int>(i * (graphWidth / numMarks));
        wxString label = wxString::Format("%.1f%s", value / 5, unit);
        dc.DrawText(label, x - 10, graphStartY + 5);
    }

}

/**
 * @brief Draws labels for the Y-axis.
 * @param dc Device context for drawing.
 */
void GraphRenderer::DrawYAxisLabels(wxDC &dc) {

    const int numYMarks = 10;
    for (int i = 1; i <= numYMarks; ++i) {
        double value = static_cast<double>(i) / numYMarks;
        int y = graphStartY - static_cast<int>((value) * graphHeight);
        dc.DrawText(wxString::Format("%.1f", value), graphStartX - 25, y - 5);
    }

}

/**
 * @brief Draws the graph line based on data points.
 * @param dc Device context for drawing.
 * @param xValues X-axis values.
 * @param yValues Y-axis values.
 * @param minX Minimum X value.
 * @param maxX Maximum X value.
 */
void GraphRenderer::DrawGraph(wxDC &dc, const std::vector<double>& xValues, const std::vector<double>& yValues,
                              double minX, double maxX) {

    for (size_t i = 1; i < xValues.size(); ++i) {
        int x1 = graphStartX + static_cast<int>(((xValues[i - 1] - minX) / (maxX - minX)) * graphWidth);
        int y1 = graphStartY - static_cast<int>((yValues[i - 1]) * graphHeight);
        int x2 = graphStartX + static_cast<int>(((xValues[i] - minX) / (maxX - minX)) * graphWidth);
        int y2 = graphStartY - static_cast<int>((yValues[i]) * graphHeight);

        if (x1 >= graphStartX && x1 <= graphStartX + graphWidth && y1 >= 0 && y1 <= graphStartY) {
            dc.DrawLine(x1, y1, x2, y2);
        }
    }

}

/**
 * @brief Initializes empty data for graph rendering.
 * @param xValues X-axis data to clear.
 * @param yValues Y-axis data to clear.
 */
void GraphRenderer::InitializeEmptyGraph(std::vector<double>& xValues, std::vector<double>& yValues) {

    xValues.clear();
    yValues.clear();
    for (int t = 0; t <= 5; t += 5) {
        xValues.push_back(t);
        yValues.push_back(0.0);
    }

}
