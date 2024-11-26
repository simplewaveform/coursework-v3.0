#ifndef TABBASE_H
#define TABBASE_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include "../Inc/ExceptionHandler.h"

/**
 * @brief Utility class for creating UI components on tabs.
 * Provides methods to create input fields, buttons, and manage layout on the tabs.
 */
class TabTools : public wxPanel {
public:
    static wxTextCtrl *CreateInputField(wxWindow *parent, wxFlexGridSizer *sizer, const wxString &labelText);
    static void AddEmptyCell(wxWindow *parent, wxFlexGridSizer *sizer, int count);

    template<typename T>
    static wxButton *CreateButton(wxWindow *parent, wxFlexGridSizer *sizer, const wxString &labelText, T *handler,
                                  void (T::*eventHandler)(wxCommandEvent &)) {

        try {
            auto *button = new wxButton(parent, wxID_ANY, labelText);
            button->Bind(wxEVT_BUTTON, eventHandler, handler);
            sizer->Add(button, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
            return button;
        } catch (const std::exception &e) {
            ExceptionHandler::HandleException(e, "Error creating button");
            return nullptr;
        }
    }

};

#endif // TABBASE_H
