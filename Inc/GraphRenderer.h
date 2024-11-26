#ifndef CIRCUITWAVE_GRAPHRENDERER_H
#define CIRCUITWAVE_GRAPHRENDERER_H

#include <wx/dc.h>
#include <vector>
#include <wx/string.h>

/**
 * @brief Responsible for rendering graphs on the screen.
 * This class handles the drawing of graphs based on given data points,
 * including drawing axes, labels, and graph lines.
 */
class GraphRenderer {
public:
    static void Draw(wxDC &dc, const std::vector<double>& xValues, const std::vector<double>& yValues);
    static void InitializeEmptyGraph(std::vector<double>& xValues, std::vector<double>& yValues);

private:
    static void DetermineScaleAndUnit(double maxX, double &scale, wxString &unit);
    static void DrawXAxisLabels(wxDC &dc, double minX, double maxX, double xScale, const wxString &unit);
    static void DrawYAxisLabels(wxDC &dc);
    static void DrawGraph(wxDC &dc, const std::vector<double>& xValues,
                          const std::vector<double>& yValues, double minX, double maxX);

};

#endif //CIRCUITWAVE_GRAPHRENDERER_H