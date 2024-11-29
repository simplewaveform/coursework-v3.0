#include "../Inc/TabTools.h"

/**
 * @brief Creates a labeled input field.
 * @param parent Parent window for the input field.
 * @param sizer Layout manager to arrange the field.
 * @param labelText Label text for the input field.
 * @return Pointer to the created text control.
 */
wxTextCtrl* TabTools::createInputField(wxWindow* parent, wxFlexGridSizer* sizer, const wxString& labelText) {

    auto* label = new wxStaticText(parent, wxID_ANY, labelText);
    auto* input = new wxTextCtrl(parent, wxID_ANY);
    sizer->Add(label, 0, wxALIGN_CENTER_VERTICAL);
    sizer->Add(input, 0, wxEXPAND);

    return input;
}

/**
 * @brief Adds empty cells to a layout for spacing.
 * @param parent Parent window for the empty cells.
 * @param sizer Layout manager where cells are added.
 * @param count Number of empty cells to add.
 */
void TabTools::addEmptyCell(wxWindow* parent, wxFlexGridSizer* sizer, int count) {

    for (int i = 0; i < count; ++i) {
        sizer->Add(new wxStaticText(parent, wxID_ANY, ""));
    }

}