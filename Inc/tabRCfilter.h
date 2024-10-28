#ifndef TABRCFILTER_H
#define TABRCFILTER_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include "../Inc/BaseTab.h"
#include <wx/textctrl.h>
#include <vector>

class tabRCfilter : public wxPanel {
public:
    tabRCfilter(wxNotebook *parent);
    virtual wxString GetData() const;

private:
    void OnCalculate(wxCommandEvent &event);
    void OnPaint(wxPaintEvent &event); // Добавляем обработчик для рисования

    wxTextCtrl *inputR1;
    wxTextCtrl *inputC1;
    wxStaticText *resultCutoff;
    wxStaticText *resultTimeConstant;

    double resistance;
    double capacitance;
    double calculatedFrequency, calculatedTime;

    std::vector<double> timeValues; // Для хранения значений времени
    std::vector<double> responseValues; // Для хранения значений отклика

wxDECLARE_EVENT_TABLE(); // Объявляем событие
};

#endif