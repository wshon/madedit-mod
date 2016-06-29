#include "NewMadOptionDialog.h"

//(*InternalHeaders(NewMadOptionDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(NewMadOptionDialog)
const long NewMadOptionDialog::ID_LISTVIEW1 = wxNewId();
const long NewMadOptionDialog::ID_CHECKBOX1 = wxNewId();
const long NewMadOptionDialog::ID_PANEL1 = wxNewId();
const long NewMadOptionDialog::ID_AUINOTEBOOK1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(NewMadOptionDialog,wxDialog)
	//(*EventTable(NewMadOptionDialog)
	//*)
END_EVENT_TABLE()

NewMadOptionDialog::NewMadOptionDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(NewMadOptionDialog)
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, id, _("Options"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxRESIZE_BORDER|wxCLOSE_BOX, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	ListView1 = new wxListView(this, ID_LISTVIEW1, wxDefaultPosition, wxSize(50,80), wxLC_ICON, wxDefaultValidator, _T("ID_LISTVIEW1"));
	BoxSizer2->Add(ListView1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	AuiNotebook1 = new wxAuiNotebook(this, ID_AUINOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE);
	Panel1 = new wxPanel(AuiNotebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	CheckBox1 = new wxCheckBox(Panel1, ID_CHECKBOX1, _("Label"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBox1->SetValue(false);
	BoxSizer4->Add(CheckBox1, 0, wxALL|wxEXPAND, 5);
	Panel1->SetSizer(BoxSizer4);
	BoxSizer4->Fit(Panel1);
	BoxSizer4->SetSizeHints(Panel1);
	AuiNotebook1->AddPage(Panel1, _("New page"));
	BoxSizer3->Add(AuiNotebook1, 0, wxALL|wxEXPAND, 5);
	BoxSizer1->Add(BoxSizer3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	//*)
}

NewMadOptionDialog::~NewMadOptionDialog()
{
	//(*Destroy(NewMadOptionDialog)
	//*)
}

