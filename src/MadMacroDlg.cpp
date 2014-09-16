///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////
#include <wx/textctrl.h>
#include "MadEdit/MadEdit.h"
#include "MadEditFrame.h"
#include "MadMacroDlg.h"
#include "EmbeddedPython.hpp"

MadMacroDlg * g_MadMacroDlg = NULL;
    ////Event Table Start
BEGIN_EVENT_TABLE(MadMacroDlg,wxDialog)
	
	EVT_CLOSE(MadMacroDlg::MadMacroDlgClose)
	EVT_BUTTON(ID_WXBUTTONRUN,MadMacroDlg::OnRunClick)
	EVT_BUTTON(ID_WXBUTTONCLOSE,MadMacroDlg::OnCloseClick)
END_EVENT_TABLE()
    ////Event Table End

///////////////////////////////////////////////////////////////////////////

MadMacroDlg::MadMacroDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
    //this->SetSizeHints( wxDefaultSize, wxDefaultSize );
    
    wxBoxSizer* bSizer6;
    bSizer6 = new wxBoxSizer( wxVERTICAL );

    m_pymacro=new MadEdit(this, ID_MADEDIT, wxDefaultPosition, wxDefaultSize);
    m_pymacro->SetFixedWidthMode(false);
    m_pymacro->SetRecordCaretMovements(false);
    m_pymacro->SetInsertSpacesInsteadOfTab(false);
    m_pymacro->SetWantTab(false);
    m_pymacro->SetSyntax(wxT("MadPython"));
    wxString endline(wxT("\r"));
    if (m_pymacro->GetInsertNewLineType() == nltDOS) endline += wxT("\n");
    else if (m_pymacro->GetInsertNewLineType() == nltUNIX) endline = wxT("\n");
    m_pymacro->SetText((wxString(wxT("#Create MadEdit Object for active edit")) + endline + wxT("medit = MadEdit()") + endline + endline));
    bSizer6->Add( m_pymacro, 1, wxEXPAND | wxALL, 5 );

    m_output = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxSIMPLE_BORDER|wxWANTS_CHARS );
    bSizer6->Add( m_output, 1, wxEXPAND | wxALL, 5 );
    
    m_run = new wxButton( this, ID_WXBUTTONRUN, _("Run"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer6->Add( m_run, 0, wxALL, 5 );
    
    m_close = new wxButton( this, ID_WXBUTTONCLOSE, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer6->Add( m_close, 0, wxALL, 5 );
    
    
    this->SetSizer( bSizer6 );
    this->Layout();
    
    this->Centre( wxBOTH );
}

MadMacroDlg::~MadMacroDlg()
{
}

void MadMacroDlg::OnRunClick( wxCommandEvent& event )
{
    wxString pystr;
    m_pymacro->GetText(pystr);
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
                wxMessageBox(_("Memory allocation failed"), _("Error"),  wxOK|wxICON_ERROR);
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
}
void MadMacroDlg::OnCloseClick( wxCommandEvent& event ) 
{
    EndModal(ID_WXBUTTONCLOSE);
}

void MadMacroDlg::SetPyScript(wxString & pyscript)
{
    m_pymacro->SetText(pyscript);
}

void MadMacroDlg::MadMacroDlgClose(wxCloseEvent& event)
{
    // --> Don't use Close with a Dialog,
    // use Destroy instead.
    Destroy();
    g_MadMacroDlg = NULL;
}

