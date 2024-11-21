#ifndef CIRCUITWAVE_CIRCUITCOMPONENT_H
#define CIRCUITWAVE_CIRCUITCOMPONENT_H

#include <type_traits>
#include <wx/wx.h>

class CircuitComponent {

public:
    virtual void calculateParameters() = 0;
    virtual ~CircuitComponent() = default;

    template <typename Object, typename Setter>
    static void CheckAndSetParameter(Object& obj, Setter setter, const wxString& value) {

        double temp;
        if (!value.ToDouble(&temp)) throw std::invalid_argument("Failed to convert input to a number");
        if (temp <= 0) throw std::invalid_argument("Value must be positive");
        (obj.*setter)(temp);

    }

};

#endif //CIRCUITWAVE_CIRCUITCOMPONENT_H