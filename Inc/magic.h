#ifndef CIRCUITWAVE_MAGIC_H
#define CIRCUITWAVE_MAGIC_H

/**
 * @brief Magic numbers like constraints for positioning
 * GUI elements (buttons, input fields, text fields etc.).
 */

/**
 * @brief BLOCK 1 - TABRCFILTER constants for GUI.
 */
const int filterImageX = 350, filterImageY = 30;            // positioning image
const int filterImageW = 470, filterImageH = 200;           // scaling image
const int graphStartX = 390, graphStartY = 490;             // positioning graph
const int graphWidth = 400, graphHeight = 210;              // scaling graph
const int numMarks = 10;                                    // number of marks for graph (x-axis)
const int filterTextOffsetX = 10, filterTextOffsetY = 290;  // offsets (x, y) for help text

/**
 * @brief BLOCK 2 - TABREGULATOR constants for GUI.
 */
const int regulatorImageX = 400, regulatorImageY = 50;      // positioning image
const int regulatorImageW = 400, regulatorImageH = 250;     // scaling image

/**
 * @brief BLOCK 3 - TABOPAMP constants for GUI.
 */
const int nonInvOpampImageX = 350, nonInvOpampImageY = 30;  // positioning image (non-inverting opamp)
const int nonInvOpampImageW = 470, nonInvOpampImageH = 180; // scaling image (non-inverting opamp)
const int invOpampImageX = 350, invOpampImageY = 290;       // positioning image (inverting opamp)
const int invOpampImageW = 470, invOpampImageH = 180;       // scaling image (inverting opamp)

#endif //CIRCUITWAVE_MAGIC_H