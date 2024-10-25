#ifndef CIRCUITWAVE_MAIN_H
#define CIRCUITWAVE_MAIN_H

class MyApp : public wxApp {
public:
    bool OnInit() override;
};

class MyFrame : public wxFrame {
public:
    explicit MyFrame(const wxString& title);
private:
    wxNotebook* notebook;
    void OnExit(wxCommandEvent &event);
    void OnSaveRCData(wxCommandEvent&);
    void OnSaveLCData(wxCommandEvent&);
};

#endif //CIRCUITWAVE_MAIN_H