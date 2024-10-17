#ifndef SIMPLEWXAPP_TABBASE_H
#define SIMPLEWXAPP_TABBASE_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include "../Inc/calculations.h"
#include <vector>

class TabBase : public wxPanel {
public:
    TabBase(wxNotebook* parent, int numParams);
    virtual void OnCalculate(wxCommandEvent& event) = 0;

protected:
    std::vector<wxTextCtrl*> inputFields;
    wxStaticText* resultLabel;

    virtual double Calculate(const std::vector<double>& params) = 0;
    void DisplayResults(double result);
    void ValidateInputs(std::vector<double>& params);
};

#endif //SIMPLEWXAPP_TABBASE_H
