#ifndef CIRCUITWAVE_BASETAB_H
#define CIRCUITWAVE_BASETAB_H

#include <wx/wx.h>

class BaseTab {

public:
    virtual ~BaseTab() = default;
    virtual wxString GetData() const = 0;

};

#endif //CIRCUITWAVE_BASETAB_H