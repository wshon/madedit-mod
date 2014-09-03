///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////
#include <wx/textctrl.h>
#include "MadMacroDlg.h"
#include "EmbeddedPython.hpp"

///////////////////////////////////////////////////////////////////////////
enum
{
    MARGIN_LINE_NUMBERS,
    MARGIN_FOLD
};

// Python
wxChar* PythonWordlist1 =
    _T("and assert break class continue def del elif else except exec ")
    _T("finally for from global if import in is lambda None not or pass ")
    _T("print raise return try while yield");
wxChar* PythonWordlist2 =
    _T("ACCELERATORS ALT AUTO3STATE AUTOCHECKBOX AUTORADIOBUTTON BEGIN ")
    _T("BITMAP BLOCK BUTTON CAPTION CHARACTERISTICS CHECKBOX CLASS ")
    _T("COMBOBOX CONTROL CTEXT CURSOR DEFPUSHBUTTON DIALOG DIALOGEX ")
    _T("DISCARDABLE EDITTEXT END EXSTYLE FONT GROUPBOX ICON LANGUAGE ")
    _T("LISTBOX LTEXT MENU MENUEX MENUITEM MESSAGETABLE POPUP PUSHBUTTON ")
    _T("RADIOBUTTON RCDATA RTEXT SCROLLBAR SEPARATOR SHIFT STATE3 ")
    _T("STRINGTABLE STYLE TEXTINCLUDE VALUE VERSION VERSIONINFO VIRTKEY");

MadMacroDlg::MadMacroDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );
    
    wxBoxSizer* bSizer6;
    bSizer6 = new wxBoxSizer( wxVERTICAL );
    
    m_pymacro = new wxStyledTextCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxEmptyString );
    m_pymacro->StyleClearAll();
    m_pymacro->SetLexer(wxSTC_LEX_PYTHON);
    m_pymacro->SetMarginWidth (MARGIN_LINE_NUMBERS, 50);
    m_pymacro->StyleSetForeground (wxSTC_STYLE_LINENUMBER, wxColour (75, 75, 75) );
    m_pymacro->StyleSetBackground (wxSTC_STYLE_LINENUMBER, wxColour (220, 220, 220));
    m_pymacro->SetMarginType (MARGIN_LINE_NUMBERS, wxSTC_MARGIN_NUMBER);
    int font_size = 16;
    wxFont font (font_size, wxMODERN, wxNORMAL, wxNORMAL);
    m_pymacro->StyleSetFont(wxSTC_STYLE_DEFAULT,font);
    // default fonts for all styles!
    int Nr;
    for (Nr = 0; Nr < wxSTC_STYLE_LASTPREDEFINED; Nr++) {
        m_pymacro->StyleSetSize (Nr, font_size);
    }

    // ---- Enable code folding
    m_pymacro->SetMarginType (MARGIN_FOLD, wxSTC_MARGIN_SYMBOL);
    m_pymacro->SetMarginWidth(MARGIN_FOLD, 15);
    m_pymacro->SetMarginMask (MARGIN_FOLD, wxSTC_MASK_FOLDERS);
    m_pymacro->StyleSetBackground(MARGIN_FOLD, wxColor(200, 200, 200) );
    m_pymacro->SetMarginSensitive(MARGIN_FOLD, true);

    // Properties found from http://www.scintilla.org/SciTEDoc.html
    m_pymacro->SetProperty (wxT("fold"),         wxT("1") );
    m_pymacro->SetProperty (wxT("fold.comment"), wxT("1") );
    m_pymacro->SetProperty (wxT("fold.compact"), wxT("1") );

    wxColor grey( 100, 100, 100 );
    m_pymacro->MarkerDefine (wxSTC_MARKNUM_FOLDER, wxSTC_MARK_ARROW );
    m_pymacro->MarkerSetForeground (wxSTC_MARKNUM_FOLDER, grey);
    m_pymacro->MarkerSetBackground (wxSTC_MARKNUM_FOLDER, grey);

    m_pymacro->MarkerDefine (wxSTC_MARKNUM_FOLDEROPEN,    wxSTC_MARK_ARROWDOWN);
    m_pymacro->MarkerSetForeground (wxSTC_MARKNUM_FOLDEROPEN, grey);
    m_pymacro->MarkerSetBackground (wxSTC_MARKNUM_FOLDEROPEN, grey);

    m_pymacro->MarkerDefine (wxSTC_MARKNUM_FOLDERSUB,     wxSTC_MARK_EMPTY);
    m_pymacro->MarkerSetForeground (wxSTC_MARKNUM_FOLDERSUB, grey);
    m_pymacro->MarkerSetBackground (wxSTC_MARKNUM_FOLDERSUB, grey);

    m_pymacro->MarkerDefine (wxSTC_MARKNUM_FOLDEREND,     wxSTC_MARK_ARROW);
    m_pymacro->MarkerSetForeground (wxSTC_MARKNUM_FOLDEREND, grey);
    m_pymacro->MarkerSetBackground (wxSTC_MARKNUM_FOLDEREND, _T("WHITE"));

    m_pymacro->MarkerDefine (wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_ARROWDOWN);
    m_pymacro->MarkerSetForeground (wxSTC_MARKNUM_FOLDEROPENMID, grey);
    m_pymacro->MarkerSetBackground (wxSTC_MARKNUM_FOLDEROPENMID, _T("WHITE"));

    m_pymacro->MarkerDefine (wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY);
    m_pymacro->MarkerSetForeground (wxSTC_MARKNUM_FOLDERMIDTAIL, grey);
    m_pymacro->MarkerSetBackground (wxSTC_MARKNUM_FOLDERMIDTAIL, grey);

    m_pymacro->MarkerDefine (wxSTC_MARKNUM_FOLDERTAIL,    wxSTC_MARK_EMPTY);
    m_pymacro->MarkerSetForeground (wxSTC_MARKNUM_FOLDERTAIL, grey);
    m_pymacro->MarkerSetBackground (wxSTC_MARKNUM_FOLDERTAIL, grey);
    // ---- End of code folding part

    m_pymacro->SetWrapMode (wxSTC_WRAP_WORD); // other choice is wxSCI_WRAP_NONE

    m_pymacro->StyleSetForeground (wxSTC_P_STRING,            wxColour(150,0,0));
    //m_pymacro->StyleSetForeground (wxSTC_P_PREPROCESSOR,      wxColour(165,105,0));
    m_pymacro->StyleSetForeground (wxSTC_P_IDENTIFIER,        wxColour(40,0,60));
    m_pymacro->StyleSetForeground (wxSTC_P_NUMBER,            wxColour(0,150,0));
    m_pymacro->StyleSetForeground (wxSTC_P_CHARACTER,         wxColour(150,0,0));
    m_pymacro->StyleSetForeground (wxSTC_P_WORD,              wxColour(0,0,150));
    m_pymacro->StyleSetForeground (wxSTC_P_WORD2,             wxColour(0,150,0));
    //m_pymacro->StyleSetForeground (wxSTC_P_COMMENT,           wxColour(150,150,150));
    m_pymacro->StyleSetForeground (wxSTC_P_COMMENTLINE,       wxColour(150,150,150));
    //m_pymacro->StyleSetForeground (wxSTC_P_COMMENTDOC,        wxColour(150,150,150));
    //m_pymacro->StyleSetForeground (wxSTC_P_COMMENTDOCKEYWORD, wxColour(0,0,200));
    //m_pymacro->StyleSetForeground (wxSTC_P_COMMENTDOCKEYWORDERROR, wxColour(0,0,200));
    m_pymacro->StyleSetBold(wxSTC_P_WORD, true);
    m_pymacro->StyleSetBold(wxSTC_P_WORD2, true);
    //m_pymacro->StyleSetBold(wxSTC_P_COMMENTDOCKEYWORD, true);

    // a sample list of keywords, I haven't included them all to keep it short...
    m_pymacro->SetKeyWords(0, PythonWordlist1);
    m_pymacro->SetKeyWords(1, PythonWordlist2);
    bSizer6->Add( m_pymacro, 1, wxEXPAND | wxALL, 5 );

    m_output = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
    bSizer6->Add( m_output, 1, wxEXPAND | wxALL, 5 );
    
    m_run = new wxButton( this, wxID_ANY, wxT("Run"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer6->Add( m_run, 0, wxALL, 5 );
    
    m_close = new wxButton( this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer6->Add( m_close, 0, wxALL, 5 );
    
    
    this->SetSizer( bSizer6 );
    this->Layout();
    
    this->Centre( wxBOTH );
    
    // Connect Events
    m_run->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MadMacroDlg::OnRun ), NULL, this );
    m_close->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MadMacroDlg::OnClose ), NULL, this );
}

MadMacroDlg::~MadMacroDlg()
{
    // Disconnect Events
    m_run->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MadMacroDlg::OnRun ), NULL, this );
    m_close->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MadMacroDlg::OnClose ), NULL, this );
}

void MadMacroDlg::OnRun( wxCommandEvent& event )
{
    wxString pystr = m_pymacro->GetText();
    wxStreamToTextRedirector redirector((wxTextCtrl *)m_output);
    if(!g_EmbeddedPython)
        try
        {
            g_EmbeddedPython = new EmbeddedPython();
            g_EmbeddedPython->exec(std::string(pystr.mb_str()));
        }
        catch(std::bad_alloc &)
        {
            wxMessageBox(_("Memory allocation failed"), wxT("Error"),  wxOK|wxICON_ERROR );
        }

    event.Skip(); 
}
void MadMacroDlg::OnClose( wxCommandEvent& event ) 
{
    Destroy();
}
