///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MADMACRODLG_H__
#define __MADMACRODLG_H__

#include <wx/richtext/richtextctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

class EmbeddedPython;
class wxStreamToTextRedirector;
class MadEdit;
///////////////////////////////////////////////////////////////////////////
////Dialog Style Start
#undef MadMacroDlg_STYLE
#define MadMacroDlg_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX
////Dialog Style End

///////////////////////////////////////////////////////////////////////////////
/// Class MadMacroDlg
///////////////////////////////////////////////////////////////////////////////
class MadMacroDlg : public wxDialog 
{
	private:
		DECLARE_EVENT_TABLE()
	protected:
		MadEdit* m_pymacro;
		wxTextCtrl* m_output;
		wxButton* m_run;
		wxButton* m_close;
		
		// Virtual event handlers, overide them in your derived class
		void MadMacroDlgClose(wxCloseEvent& event);
		void OnRunClick( wxCommandEvent& event );
		void OnCloseClick( wxCommandEvent& event ) ;
		
	
	public:
			enum {
////GUI Enum Control ID Start
			ID_WXBUTTONCLOSE = 13,
			ID_WXBUTTONRUN = 12,

////GUI Enum Control ID End
            ID_MADEDIT=1500,

   ID_DUMMY_VALUE_ //Dont Delete this DummyValue
   }; //End of Enum
		MadMacroDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("MadEdit Macro"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 717,448 ), long style = MadMacroDlg_STYLE ); 
		virtual ~MadMacroDlg();
		void SetPyScript(wxString & pyscript);
};

extern MadMacroDlg * g_MadMacroDlg;

#endif //__MADMACRODLG_H__
