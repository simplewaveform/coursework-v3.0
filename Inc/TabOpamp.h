#ifndef TABOPAMP_H
#define TABOPAMP_H

#include <wx/wx.h>
#include <wx/notebook.h>

class TabOpamp : public wxPanel {
public:
    explicit TabOpamp(wxNotebook* parent);
    void OnCalculate(wxCommandEvent& event);
    template <typename T>
    void CalculateOpampGain(wxTextCtrl* inputRfb, wxTextCtrl* inputRin, wxStaticText* resultGain);
    wxString GetData() const;
    double RgNonInv{}, RfbNonInv{}, gainNonInv{}, RinInv{}, RfbInv{}, gainInv{};

private:
    wxTextCtrl* inputRfbNonInv;
    wxTextCtrl* inputRgNonInv;
    wxStaticText* resultGainNonInv;
    wxTextCtrl* inputRfbInv;
    wxTextCtrl* inputRinInv;
    wxStaticText* resultGainInv;
    wxButton* calculateButtonNonInv{};
    wxButton* calculateButtonInv{};

};

#endif