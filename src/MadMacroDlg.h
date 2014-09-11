///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MADMACRODLG_H__
#define __MADMACRODLG_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/stc/stc.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

class EmbeddedPython;
class wxStreamToTextRedirector;
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MadMacroDlg
///////////////////////////////////////////////////////////////////////////////
class MadMacroDlg : public wxDialog 
{
	private:
	
	protected:
		wxStyledTextCtrl* m_pymacro;
		wxRichTextCtrl* m_output;
		wxButton* m_run;
		wxButton* m_close;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnRun( wxCommandEvent& event );
		virtual void OnClose( wxCommandEvent& event ) ;
		
	
	public:
		
		MadMacroDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 717,448 ), long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER ); 
		~MadMacroDlg();
		void SetPyScript(wxString & pyscript);
};

#endif //__MADMACRODLG_H__
