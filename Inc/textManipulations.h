#ifndef CIRCUITWAVE_TEXTMANIPULATIONS_H
#define CIRCUITWAVE_TEXTMANIPULATIONS_H

#include <wx/wx.h>
#include <wx/dcclient.h>
#include <wx/txtstrm.h>
#include <wx/string.h>
#include <fstream>
#include <wx/menu.h>
#include <wx/textfile.h>

wxString LoadHelpText(const wxString &filename);
bool SaveDataToFile(const wxString& filePath, const wxString& data);


#endif //CIRCUITWAVE_TEXTMANIPULATIONS_H