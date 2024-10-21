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
    void OnExit(wxCommandEvent &event);
    wxNotebook* notebook;
};

#endif //CIRCUITWAVE_MAIN_H