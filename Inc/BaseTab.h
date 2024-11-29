#ifndef CIRCUITWAVE_BASETAB_H
#define CIRCUITWAVE_BASETAB_H

#include <wx/wx.h>

/**
 * @brief Abstract base class for all tab classes.
 * This class serves as a base for creating specific tabs that represent
 * different sections of the application. Each tab must implement the
 * `getData` method to return relevant data for the active tab.
 */
class BaseTab : public wxPanel {
public:
    using wxPanel::wxPanel;
    virtual wxString getData() const = 0;

};

#endif //CIRCUITWAVE_BASETAB_H
