#ifndef SIMPLEWXAPP_MAIN_H
#define SIMPLEWXAPP_MAIN_H

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    explicit MyFrame(const wxString& title);
private:
    void OnExit(wxCommandEvent &event);
    wxNotebook* notebook;
};

#endif //SIMPLEWXAPP_MAIN_H