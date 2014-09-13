///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////
#include <wx/textctrl.h>
#include "MadEditFrame.h"
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
                _T("and assert break class continue def del elif else except exec finally for from global if import ")
                _T("in is lambda None  not or pass print raise return try while yield __import__ abs basestring bool ")
                _T("callable chr classmethod cmp compile complex delattr dict dir divmod enumerate ")
                _T("eval execfile file filter float frozenset getattr globals ")
                _T("hasattr hash help hex id input int isinstance issubclass ")
                _T("iter len list locals long map max min object oct open ")
                _T("ord pow property range raw_input reduce reload repr ")
                _T("reversed round set setattr slice sorted staticmethod ")
                _T("str sum super tuple type type unichr unicode vars xrange ")
                _T("zip apply buffer coerce intern __dict__ Ellipsis False True NotImplemented ")
                _T("__class__ __bases__ __name__ exception Exception StandardError ArithmeticError ")
                _T("LookupError EnvironmentError AssertionError AttributeError EOFError FloatingPointError IOError ")
                _T("ImportError IndexError KeyError KeyboardInterrupt MemoryError NameError NotImplementedError OSError ")
                _T("OverflowError ReferenceError RuntimeError StopIteration SyntaxError SystemError SystemExit ")
                _T("TypeError UnboundLocalError UnicodeError UnicodeEncodeError UnicodeDecodeError UnicodeTranslateError ValueError WindowsError ")
                _T("ZeroDivisionError Warning UserWarning DeprecationWarning PendingDeprecationWarning SyntaxWarning RuntimeWarning FutureWarning");
wxChar* PythonWordlist2 =
                _T("self sys gc weakref fpectl atexit types UserDict UserList UserString  operator inspect traceback linecache pickle cPickle copy_reg shelve copy marshal warnings imp zipimport pkgutil ")
                _T("modulefinder code codeop pprint repr new site user __builtin__ __main__ __future__ string re struct difflib fpformat StringIO cStringIO textwrap codecs encodings.idna unicodedata ")
                _T("stringprep pydoc doctest unittest test test.test_support decimal math cmath random whrandom bisect collections heapq array sets itertools ConfigParser fileinput calendar cmd ")
                _T("shlexos os.path dircache stat statcache statvfs filecmp subprocess popen2 datetime time sched mutex getpass curses curses.textpad curses.wrapper curses.ascii curses.panel getopt ")
                _T("optparse tempfile errno glob fnmatch shutil locale gettext logging platform signal socket select thread threading dummy_thread dummy_threading Queue mmap anydbm dbhash whichdb ")
                _T("bsddb dumbdbm zlib gzip bz2 zipfile tarfile readline rlcompleter posix pwd grp crypt dl dbm gdbm termios tty pty fcntl pipes posixfile resource nis syslog commands hotshot timeit ")
                _T("webbrowser cgi cgitb urllib urllib2 httplib ftplib gopherlib poplib imaplib nntplib smtplib smtpd telnetlib urlparse  SocketServer BaseHTTPServer SimpleHTTPServer CGIHTTPServer ")
                _T("cookielib Cookie xmlrpclib SimpleXMLRPCServer DocXMLRPCServer asyncore asynchat formatter email email.Message email.Parser email.Generator email.Header email.Charset email.Encoders ")
                _T("email.Errors email.Utils email.Iterators mailcap mailbox mhlib mimetools mimetypes MimeWriter mimify multifile rfc822 base64 binascii binhex quopri uu xdrlib netrc robotparser csv ")
                _T("HTMLParser sgmllib htmllib htmlentitydefs xml.parsers.expat xml.dom xml.dom.minidom xml.dom.pulldom xml.sax xml.sax.handler xml.sax.saxutils xml.sax.xmlreader xmllib audioop ")
                _T("imageop aifc sunau wave chunk colorsys rgbimg imghdr sndhdr ossaudiodev hmac md5 sha Tkinter Tix ScrolledText turtle parser symbol token keyword tokenize tabnanny pyclbr py_compile ")
                _T("compileall dis pickletools distutils");

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
    int font_size = 14;
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
#if 0
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
#endif
    m_pymacro->StyleSetSpec(wxSTC_STYLE_LINENUMBER, wxT("back:#E0E0E0,face:Monospace"));
    m_pymacro->StyleSetSpec(wxSTC_STYLE_CONTROLCHAR, wxT("face:Courier"));
    m_pymacro->StyleSetSpec(wxSTC_STYLE_BRACELIGHT, wxT("fore:#0000FF,back:#FFFF88"));
    m_pymacro->StyleSetSpec(wxSTC_STYLE_BRACEBAD, wxT("fore:#FF0000,back:#FFFF88"));

    m_pymacro->StyleSetSpec(wxSTC_P_DEFAULT, wxT("face:Monospace"));
    m_pymacro->StyleSetSpec(wxSTC_P_COMMENTLINE, wxT("fore:#007F00,face:Monospace"));
    m_pymacro->StyleSetSpec(wxSTC_P_NUMBER, wxT("fore:#0000C0,face:Monospace"));
    m_pymacro->StyleSetSpec(wxSTC_P_STRING, wxT("fore:#7F007F,face:Monospace"));
    m_pymacro->StyleSetSpec(wxSTC_P_CHARACTER, wxT("fore:#7F007F,face:Monospace"));
    m_pymacro->StyleSetSpec(wxSTC_P_WORD, wxT("fore:#00007F,bold"));
    m_pymacro->StyleSetSpec(wxSTC_P_WORD2, wxT("fore:#00007F,italic,bold"));
    m_pymacro->StyleSetSpec(wxSTC_P_TRIPLE, wxT("fore:#7F0000"));
    m_pymacro->StyleSetSpec(wxSTC_P_TRIPLEDOUBLE, wxT("fore:#000033,back:#FFFFE8"));
    m_pymacro->StyleSetSpec(wxSTC_P_DEFNAME, wxT("fore:#007F7F,bold"));
    m_pymacro->StyleSetSpec(wxSTC_P_CLASSNAME, wxT("fore:#C00000,italic,bold"));
    m_pymacro->StyleSetSpec(wxSTC_P_OPERATOR, wxT(""));
    m_pymacro->StyleSetSpec(wxSTC_P_IDENTIFIER, wxT(""));
    m_pymacro->StyleSetSpec(wxSTC_P_COMMENTBLOCK, wxT("fore:#7F7F7F"));
    m_pymacro->StyleSetSpec(wxSTC_P_STRINGEOL, wxT("fore:#000000,face:Monospace,back:#E0C0E0,eolfilled"));

    // a sample list of keywords, I haven't included them all to keep it short...
    m_pymacro->SetKeyWords(0, PythonWordlist1);
    m_pymacro->SetKeyWords(1, PythonWordlist2);
    bSizer6->Add( m_pymacro, 1, wxEXPAND | wxALL, 5 );
    m_pymacro->SetText(wxString(wxT("#Create MadEdit Object for active edit\nmedit = MadEdit()\n\n")));

    m_output = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxSIMPLE_BORDER|wxWANTS_CHARS );
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
    if(!pystr.IsEmpty())
    {
        if(!g_EmbeddedPython)
        {
            try
            {
                g_EmbeddedPython = new EmbeddedPython();
            }
            catch(std::bad_alloc &)
            {
                wxMessageBox(_("Memory allocation failed"), wxT("Error"),  wxOK|wxICON_ERROR);
                g_EmbeddedPython = 0;
            }
        }
        if(g_EmbeddedPython)
        {
            m_output->Clear();
            wxStreamToTextRedirector redirector((wxTextCtrl *)m_output);
            g_MainFrame->SetMacroRunning();
            g_EmbeddedPython->exec(std::string(pystr.mb_str()));
            g_MainFrame->SetMacroStopped();
        }
    }

    event.Skip(); 
}
void MadMacroDlg::OnClose( wxCommandEvent& event ) 
{
    Destroy();
}

void MadMacroDlg::SetPyScript(wxString & pyscript)
{
    m_pymacro->SetText(pyscript);
}

