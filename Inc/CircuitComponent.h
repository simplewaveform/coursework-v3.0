#ifndef CIRCUITWAVE_CIRCUITCOMPONENT_H
#define CIRCUITWAVE_CIRCUITCOMPONENT_H

#include <wx/wx.h>
#include "../Inc/ExceptionHandler.h"

/**
 * @brief Abstract base class for all circuit components.
 * Provides a common interface for components that require parameter
 * calculation, such as resistors, capacitors, and regulators.
 */
class CircuitComponent {
public:
    virtual void calculateParameters() = 0;
    virtual ~CircuitComponent() = default;

    /**
     * @brief Checks and sets a parameter for the given object.
     * Validates the input value and sets the parameter using the provided setter.
     * Throws exceptions if the validation fails.
     * @param obj The object to set the parameter on.
     * @param setter The setter method to use.
     * @param value The value to set.
     */
    template <typename Object, typename Setter>
    static bool CheckAndSetParameter(Object& obj, Setter setter, const wxString& value) {
        try {
            double temp;
            if (!value.ToDouble(&temp)) throw std::invalid_argument("Failed to convert input to a number");
            if (temp <= 0) throw std::invalid_argument("Value must be positive");
            (obj.*setter)(temp);
            return true;
        } catch (const std::exception& e) {
            ExceptionHandler::handleException(e, "Invalid parameter setting");
            return false;
        }
    }

};

#endif //CIRCUITWAVE_CIRCUITCOMPONENT_H