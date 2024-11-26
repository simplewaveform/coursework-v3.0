#include "../Inc/TabRCfilter.h"
#include "../Inc/TextManipulator.h"
#include "../Inc/ImageProcessor.h"
#include "../Inc/magic.h"
#include "../Inc/GraphRenderer.h"
#include "../Inc/TabTools.h"

#include <wx/dcclient.h>

BEGIN_EVENT_TABLE(TabRCfilter, wxPanel)
                EVT_PAINT(TabRCfilter::OnPaint)
END_EVENT_TABLE()

/**
 * @brief Constructor for the TabRCfilter class.
 * @param parent Parent notebook for this tab.
 */
TabRCfilter::TabRCfilter(wxNotebook *parent) : BaseTab(parent) {

    GraphRenderer::InitializeEmptyGraph(timeValues, responseValues);

    auto *sizer = new wxBoxSizer(wxVERTICAL);
    auto *gridSizer = new wxFlexGridSizer(5, 2, 20, 50);
    inputR1 = TabTools::CreateInputField(this, gridSizer, "R1 (Ω):");
    inputC1 = TabTools::CreateInputField(this, gridSizer, "C1 (μF):");
    TabTools::CreateButton(this, gridSizer, "Calculate parameters",
                           this, &TabRCfilter::OnCalculate);

    resultCutoff = new wxStaticText(this, wxID_ANY, "Cutoff frequency:");
    resultTimeConstant = new wxStaticText(this, wxID_ANY, "Time constant:");
    TabTools::AddEmptyCell(this, gridSizer, 1);
    gridSizer->Add(resultCutoff);
    TabTools::AddEmptyCell(this, gridSizer, 1);
    gridSizer->Add(resultTimeConstant);

    auto *imageCtrl = new wxStaticBitmap(this, wxID_ANY, ImageProcessor::processImage(
            "../Resources/Filter.png", filterImageW, filterImageH));
    imageCtrl->Move(filterImageX, filterImageY);

    sizer->Add(gridSizer, 1, wxALL | wxEXPAND, 10);
    SetSizer(sizer);

    TextManipulator manipulator;
    manipulator.loadHelpText("../Resources/help.txt");
    manipulator.transformText(this, filterTextOffsetX, filterTextOffsetY);

}

/**
 * @brief Calculates and updates the parameters of the RC filter.
 */
void TabRCfilter::OnCalculate(wxCommandEvent &) {

    try {
        CircuitComponent::CheckAndSetParameter(filter, &LowpassRC::setR, inputR1->GetValue());
        CircuitComponent::CheckAndSetParameter(filter, &LowpassRC::setC, inputC1->GetValue());
        filter.calculateParameters();
        resultCutoff->SetLabel(wxString::Format("Cutoff frequency : %.2lf Hz", filter.getFrequency()));
        resultTimeConstant->SetLabel(wxString::Format("Time constant: %.2lf μs", filter.getTime()));
    } catch (const std::exception& e) {
        ExceptionHandler::HandleException(e, "Error calculating RC filter parameters");
    }

    timeValues.clear();
    responseValues.clear();
    for (int t = 0; t <= 5 * filter.getTime(); t += 1) {
        timeValues.push_back(t);
        responseValues.push_back(1.0 - exp(-t / filter.getTime()));
    }
    Refresh();

}

/**
 * @brief Renders the graph on the tab.
 */
void TabRCfilter::OnPaint(wxPaintEvent &) {

    wxPaintDC dc(this);
    GraphRenderer::Draw(dc, timeValues, responseValues);

}

/**
 * @brief Retrieves RC filter parameters as a formatted string.
 * @return String containing R, C, cutoff frequency, and time constant.
 */
wxString TabRCfilter::GetData() const {

    return wxString::Format(
            "RC Filter parameters:\n"
            "R: %.2lf Ohm\n"
            "C: %.2lf μF\n"
            "Cutoff frequency: %.2lf Hz\n"
            "Time constant: %.2lf μs\n",
            filter.getR(), filter.getC(), filter.getFrequency(), filter.getTime()
    );

}