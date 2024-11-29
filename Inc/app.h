#ifndef CIRCUITWAVE_APP_H
#define CIRCUITWAVE_APP_H
/**
 * @brief Main application class.
 * Initializes the application, creates the main frame, and sets up event handling.
 */
class MyApp : public wxApp {
public:
    bool OnInit() override;

};

/**
 * @brief Main frame class for the application.
 * Manages the main window, menu actions, and tab management.
 */
class MyFrame : public wxFrame {
public:
    explicit MyFrame(const wxString& title);
    void OnSaveData(wxCommandEvent&);
    wxString getDataFromActiveTab();

private:
    wxNotebook* notebook;
    void OnExit(wxCommandEvent &event);

};

#endif //CIRCUITWAVE_APP_H