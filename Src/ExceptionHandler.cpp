#include "../Inc/ExceptionHandler.h"

/**
 * @brief Handles an exception and displays an error dialog.
 * @param e Exception details.
 * @param context Additional context about the error.
 */
void ExceptionHandler::handleException(const std::exception& e, const wxString& context) {

    ShowErrorDialog(e, context);

}

/**
 * @brief Shows a dialog with error details.
 * @param e Exception details.
 * @param context Additional context about the error.
 */
void ExceptionHandler::ShowErrorDialog(const std::exception& e, const wxString& context) {

    wxMessageBox(wxString::Format("%s: %s", context, e.what()),
                 "Error", wxICON_ERROR);

}