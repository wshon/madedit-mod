#ifndef NEWMADOPTIONDIALOG_H
#define NEWMADOPTIONDIALOG_H

//(*Headers(NewMadOptionDialog)
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/aui/aui.h>
#include <wx/panel.h>
#include <wx/dialog.h>
//*)

class NewMadOptionDialog: public wxDialog
{
	public:

		NewMadOptionDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~NewMadOptionDialog();

		//(*Declarations(NewMadOptionDialog)
		wxPanel* Panel1;
		wxCheckBox* CheckBox1;
		wxListView* ListView1;
		wxAuiNotebook* AuiNotebook1;
		//*)

	protected:

		//(*Identifiers(NewMadOptionDialog)
		static const long ID_LISTVIEW1;
		static const long ID_CHECKBOX1;
		static const long ID_PANEL1;
		static const long ID_AUINOTEBOOK1;
		//*)

	private:

		//(*Handlers(NewMadOptionDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
