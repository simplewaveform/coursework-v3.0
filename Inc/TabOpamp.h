#ifndef TABOPAMP_H
#define TABOPAMP_H

#include <wx/wx.h>
#include <wx/notebook.h>

class tabOpamp : public wxPanel {
public:
    explicit tabOpamp(wxNotebook* parent);
    void OnCalculate(wxCommandEvent& event);
    wxString GetData() const;
    double RgNonInv, RfbNonInv, gainNonInv, RinInv, RfbInv, gainInv;

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