#include "../Inc/TabBase.h"
#include "../Inc/TabRCfilter.h"
#include "../Inc/TabOpamp.h"
#include "../Inc/TabRegulator.h"

TabBase::TabBase(wxNotebook* parent) : wxPanel(parent, wxID_ANY) {
    SetBackgroundColour(*wxBLACK);
}

wxTextCtrl* TabBase::CreateInputField(wxWindow* parent, wxFlexGridSizer* sizer, const wxString& labelText) {
    auto* label = new wxStaticText(parent, wxID_ANY, labelText);
    auto* input = new wxTextCtrl(parent, wxID_ANY);
    sizer->Add(label, 0, wxALIGN_CENTER_VERTICAL);
    sizer->Add(input, 0, wxEXPAND);
    return input;
}

template <typename T>
wxButton* TabBase::CreateButton(wxWindow* parent, wxFlexGridSizer* sizer, const wxString& labelText, T* handler, void (T::*eventHandler)(wxCommandEvent&)) {
    try {
        auto* button = new wxButton(parent, wxID_ANY, labelText);
        button->Bind(wxEVT_BUTTON, eventHandler, handler);
        sizer->Add(button, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
        return button;
    } catch (const std::exception& e) {
        //HandleException(e, "Error creating button");
        return nullptr;
    }
}

template wxButton* TabBase::CreateButton<TabRegulator>(wxWindow*, wxFlexGridSizer*, const wxString&, TabRegulator*, void (TabRegulator::*)(wxCommandEvent&));
template wxButton* TabBase::CreateButton<TabOpamp>(wxWindow*, wxFlexGridSizer*, const wxString&, TabOpamp*, void (TabOpamp::*)(wxCommandEvent&));
template wxButton* TabBase::CreateButton<TabRCfilter>(wxWindow*, wxFlexGridSizer*, const wxString&, TabRCfilter*, void (TabRCfilter::*)(wxCommandEvent&));

void TabBase::AddEmptyCell(wxWindow* parent, wxFlexGridSizer* sizer, int count) {
    for (int i = 0; i < count; ++i) {
        sizer->Add(new wxStaticText(parent, wxID_ANY, ""), 0, wxEXPAND);
    }
}