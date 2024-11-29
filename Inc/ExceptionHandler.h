#ifndef CIRCUITWAVE_EXCEPTIONHANDLER_H
#define CIRCUITWAVE_EXCEPTIONHANDLER_H

#include <exception>
#include <wx/wx.h>

/**
 * @brief Handles exceptions and provides error dialog display.
 * This class is responsible for handling exceptions by displaying
 * relevant error information in a dialog.
 */
class ExceptionHandler {
public:
    static void handleException(const std::exception& e, const wxString& context);

private:
    static void ShowErrorDialog(const std::exception& e, const wxString& context);

};

#endif // CIRCUITWAVE_EXCEPTIONHANDLER_H