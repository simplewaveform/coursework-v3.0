#ifndef TABBASE_H
#define TABBASE_H

#include <wx/wx.h>
#include <wx/notebook.h>

class TabBase : public wxPanel {
public:
    explicit TabBase(wxNotebook* parent);
    static wxTextCtrl* CreateInputField(wxWindow* parent, wxFlexGridSizer* sizer, const wxString& labelText);
    static void AddEmptyCell(wxWindow* parent, wxFlexGridSizer* sizer, int count);
    template <typename T>
    static wxButton* CreateButton(wxWindow* parent, wxFlexGridSizer* sizer, const wxString& labelText, T* handler, void (T::*eventHandler)(wxCommandEvent&));};

#endif // TABBASE_H