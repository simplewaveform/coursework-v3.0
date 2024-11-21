#ifndef CIRCUITWAVE_GRAPHRENDERER_H
#define CIRCUITWAVE_GRAPHRENDERER_H

#include <wx/dc.h>
#include <vector>
#include <wx/string.h>

class GraphRenderer {
public:
    GraphRenderer(int startX, int startY, int width, int height, int numMarks);
    void Draw(wxDC &dc, const std::vector<double>& xValues, const std::vector<double>& yValues) const;

private:
    int startX, startY, width, height, numMarks;

    static void DetermineScaleAndUnit(double maxX, double &scale, wxString &unit) ;
    void DrawXAxisLabels(wxDC &dc, double minX, double maxX, double xScale, const wxString &unit) const;
    void DrawYAxisLabels(wxDC &dc) const;
    void DrawGraph(wxDC &dc, const std::vector<double>& xValues, const std::vector<double>& yValues, double minX, double maxX) const;
};

#endif //CIRCUITWAVE_GRAPHRENDERER_H
