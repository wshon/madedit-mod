///////////////////////////////////////////////////////////////////////////////
// Name:        MadFileAssociationDialog.cpp
// Description: File Type Association Dialog for MSWindows
// Author:      madedit@gmail.com
// Maintainer:  minggang.li@gmail.com
// Licence:     GPL
///////////////////////////////////////////////////////////////////////////////

#include "MadFileAssociationDialog.h"

#ifdef __WXMSW__

#include "MadUtils.h"

#ifdef _MSC_VER
# pragma warning( push )
# pragma warning( disable : 4996 )
#endif
// disable 4996 {
#include <wx/config.h>
#include <wx/log.h>

//(*InternalHeaders(MadFileAssociationDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)
// disable 4996 }
#ifdef _MSC_VER
# pragma warning( pop )
#endif

#ifdef _DEBUG
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK ,__FILE__, __LINE__)
#endif


const wxChar *g_PredefinedTypes[] =
{
	wxT( ".txt" ),
	wxT( ".c" ),
	wxT( ".cpp" ),
	wxT( ".cc" ),
	wxT( ".cxx" ),
	wxT( ".h" ),
	wxT( ".hpp" ),
	wxT( ".d" ),
	wxT( ".asm" ),
	wxT( ".java" ),
	//    wxT(".htm"),
	//    wxT(".html"),
	wxT( ".pas" ),
	//    wxT(".dpr"),
	wxT( ".css" ),
	wxT( ".js" ),
	wxT( ".xml" ),
	wxT( ".sql" ),
	wxT( ".php" ),
	wxT( ".asp" ),
	wxT( ".inc" ),
	wxT( ".cs" ),
	//    wxT(".vbs"),
	wxT( ".bas" ),
	wxT( ".frm" ),
	wxT( ".cls" ),
	//    wxT(".reg"),
	//    wxT(".inf"),
	wxT( ".ini" ),
	wxT( ".cfg" ),
	wxT( ".conf" ),
	wxT( ".mak" ),
	wxT( ".nfo" ),
	wxT( ".diz" ),
	//    wxT(".bat"),
	//    wxT(".cmd"),
	wxT( ".awk" ),
	wxT( ".py" ),
	wxT( ".python" ),
	wxT( ".pl" ),
	wxT( ".perl" ),
	wxT( ".rb" ),
	wxT( ".rbw" ),
	wxT( ".diff" ),
	wxT( ".patch" ),
	wxT( ".lua" ),
	wxT( ".nut" ),
	wxT( ".f90" ),
	wxT( ".f77" ),
	wxT( ".for" ),
	wxT( ".ftn" ),
	wxT( ".lat" ),
	wxT( ".tex" ),
	wxT( ".lex" ),
	wxT( ".as" ),
	wxT( ".v" ),
	wxT( ".vl" ),
	wxT( ".vmd" ),
	wxT( ".vhd" ),
	wxT( ".vho" ),
	wxT( ".vhdl" ),
	wxT( ".syn" ),
	wxT( ".sch" ),
	wxT( ".att" ),
};

const int g_PredefinedTypes_Count = sizeof(g_PredefinedTypes) / sizeof(g_PredefinedTypes[0]);

bool DetectType(wxString type)
{
	wxLogNull nolog; // disable error log
	wxString value;
	wxRegKey *pRegKey = new wxRegKey( g_MadEditRegkeyPath + type );

	if( pRegKey->Exists() ) { pRegKey->QueryValue( wxEmptyString, value ); }

	delete pRegKey;

	if( !value.IsEmpty() )
	{
		pRegKey = new wxRegKey( g_MadEditRegkeyPath
								+ value
								+ wxString( wxT( "\\shell\\open\\command" ) ) );
		value.Empty();

		if( pRegKey->Exists() ) { pRegKey->QueryValue( wxEmptyString, value ); }

		delete pRegKey;
		wxString exepath = GetExecutablePath();

		if( value.Upper().Find( exepath.Upper() ) >= 0 )
		{
			return true;
		}
	}

	return false;
}

void AddType( wxString type )
{
	wxString value;
	wxString madedit_type = wxString( wxT( "MadEdit-Mod" ) ) + type;
	wxRegKey *pRegKey = new wxRegKey( g_MadEditRegkeyPath + type );

	if( !pRegKey->Exists() ) { pRegKey->Create(); }
	else { pRegKey->QueryValue( wxEmptyString, value ); }

	if( value != madedit_type )
	{
		if( !value.IsEmpty() ) //save old default value
		{
			pRegKey->SetValue( wxT( "Old_Default" ), value );
			//if(type == wxT(".txt"))
			//{
			//    wxRegKey *pRegKey1 = new wxRegKey(wxString(wxT("HKEY_CLASSES_ROOT\\")) + type);
			//    pRegKey->QueryValue(wxEmptyString, txt_name);
			//    delete pRegKey1;
			//}
		}

		value = madedit_type;
		pRegKey->SetValue( wxEmptyString, value );
	}

	delete pRegKey;
	wxString name( g_MadEditRegkeyPath );
	name += value;

	if( type == wxT( ".txt" ) )
	{
		wxString txt_name;
		pRegKey = new wxRegKey( wxString( g_MadEditRegkeyPath + wxT( "txtfile" ) ) );

		if( pRegKey->Exists() ) { pRegKey->QueryValue( wxEmptyString, txt_name ); }

		delete pRegKey;

		if( txt_name.IsEmpty() ) { txt_name = wxT( "Text file" ); }

		pRegKey = new wxRegKey( name );
		pRegKey->Create();
		pRegKey->SetValue( wxEmptyString, txt_name );
		delete pRegKey;
	}

	name += wxT( "\\shell\\open\\command" );
	pRegKey = new wxRegKey( name );
	pRegKey->Create();
	wxString exepath = GetExecutablePath();
	pRegKey->SetValue( wxEmptyString, wxString( wxT( '"' ) ) + exepath + wxString( wxT( "\" \"%1\"" ) ) );
	delete pRegKey;
	name = g_MadEditRegkeyPath;
	name += value;
	name += wxT( "\\DefaultIcon" );
	pRegKey = new wxRegKey( name );
	pRegKey->Create();
	pRegKey->SetValue( wxEmptyString, exepath + wxString( wxT( ",1" ) ) );
	delete pRegKey;
}

void RemoveType( wxString type )
{
	if( type.IsEmpty() ) { return; }

	wxString value, old_default;
	wxString madedit_type = wxString( wxT( "MadEdit-Mod" ) ) + type;
	wxRegKey *pRegKey = new wxRegKey( g_MadEditRegkeyPath + type );

	if( pRegKey->Exists() )
	{
		pRegKey->QueryValue( wxT( "Old_Default" ), old_default );
		pRegKey->QueryValue( wxEmptyString, value );
	}

	if( !old_default.IsEmpty() )
	{
		pRegKey->DeleteValue( wxT( "Old_Default" ) );
		pRegKey->SetValue( wxEmptyString, old_default );
	}
	else
		if( !value.IsEmpty() )
		{
			if( value == madedit_type )
			{
				pRegKey->DeleteSelf();
			}
		}

	delete pRegKey;

	if( value == madedit_type )
	{
		pRegKey = new wxRegKey( g_MadEditRegkeyPath + value );

		if( pRegKey->Exists() ) { pRegKey->DeleteSelf(); }

		delete pRegKey;
	}
}


wxArrayString as_remove; // the types will be removed

void GetListBoxSelections( wxListBox *lb, wxArrayString &as )
{
	wxArrayInt sel;
	lb->GetSelections( sel );
	int idx = 0;
	const int count = int( sel.Count() );

	while( idx < count )
	{
		as.Add( lb->GetString( sel[idx] ) );
		++idx;
	}
}

void AddTypeToAssociated( wxListBox *WxListBoxAssociated,
						  wxListBox *WxListBoxPredefined,
						  const wxArrayString &as )
{
	int idx = 0;
	const int count = int( as.Count() );
	wxString type;

	while( idx < count )
	{
		type = as[idx];
		int n = WxListBoxPredefined->FindString( type );

		if( n != wxNOT_FOUND ) { WxListBoxPredefined->Delete( n ); }

		n = WxListBoxAssociated->FindString( type );

		if( n == wxNOT_FOUND ) { WxListBoxAssociated->Append( type ); }

		n = as_remove.Index( type );

		if( n != wxNOT_FOUND ) { as_remove.RemoveAt( n ); }

		++idx;
	}
}

void AddTypeToPredefined( wxListBox *WxListBoxAssociated,
						  wxListBox *WxListBoxPredefined,
						  const wxArrayString &as )
{
	int idx = 0;
	const int count = int( as.Count() );
	wxString type;

	while( idx < count )
	{
		type = as[idx];
		int n = WxListBoxAssociated->FindString( type );

		if( n != wxNOT_FOUND ) { WxListBoxAssociated->Delete( n ); }

		n = WxListBoxPredefined->FindString( type );

		if( n == wxNOT_FOUND ) { WxListBoxPredefined->Append( type ); }

		n = as_remove.Index( type );

		if( n == wxNOT_FOUND ) { as_remove.Add( type ); }

		++idx;
	}
}


//(*IdInit(MadFileAssociationDialog)
const long MadFileAssociationDialog::ID_STATICTEXT1 = wxNewId();
const long MadFileAssociationDialog::ID_WXLISTBOXASSOCIATED = wxNewId();
const long MadFileAssociationDialog::ID_WXBUTTONADD = wxNewId();
const long MadFileAssociationDialog::ID_WXBUTTONREMOVE = wxNewId();
const long MadFileAssociationDialog::ID_STATICTEXT2 = wxNewId();
const long MadFileAssociationDialog::ID_WXLISTBOXPREDEFINED = wxNewId();
const long MadFileAssociationDialog::ID_WXEDITCUSTOMTYPE = wxNewId();
const long MadFileAssociationDialog::ID_WXBUTTONADDCUSTOM = wxNewId();
//*)

BEGIN_EVENT_TABLE(MadFileAssociationDialog,wxDialog)
	//(*EventTable(MadFileAssociationDialog)
	//*)
END_EVENT_TABLE()

MadFileAssociationDialog::MadFileAssociationDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(MadFileAssociationDialog)
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer8;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, wxID_ANY, _("File Type Associations"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer6 = new wxBoxSizer(wxVERTICAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Associated File Types:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer6->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	WxListBoxAssociated = new wxListBox(this, ID_WXLISTBOXASSOCIATED, wxDefaultPosition, wxSize(121,200), 0, 0, wxLB_EXTENDED, wxDefaultValidator, _T("ID_WXLISTBOXASSOCIATED"));
	BoxSizer6->Add(WxListBoxAssociated, 1, wxALL|wxEXPAND, 5);
	BoxSizer4->Add(BoxSizer6, 1, wxALL|wxEXPAND, 5);
	BoxSizer7 = new wxBoxSizer(wxVERTICAL);
	WxButtonAdd = new wxButton(this, ID_WXBUTTONADD, _("<- Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_WXBUTTONADD"));
	BoxSizer7->Add(WxButtonAdd, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	WxButtonRemove = new wxButton(this, ID_WXBUTTONREMOVE, _("Remove ->"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_WXBUTTONREMOVE"));
	BoxSizer7->Add(WxButtonRemove, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4->Add(BoxSizer7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer8 = new wxBoxSizer(wxVERTICAL);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Predefined File Types:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer8->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	WxListBoxPredefined = new wxListBox(this, ID_WXLISTBOXPREDEFINED, wxDefaultPosition, wxSize(121,200), 0, 0, wxLB_EXTENDED, wxDefaultValidator, _T("ID_WXLISTBOXPREDEFINED"));
	BoxSizer8->Add(WxListBoxPredefined, 1, wxALL|wxEXPAND, 5);
	BoxSizer4->Add(BoxSizer8, 1, wxALL|wxEXPAND, 5);
	BoxSizer2->Add(BoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	WxEditCustomType = new wxTextCtrl(this, ID_WXEDITCUSTOMTYPE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_WXEDITCUSTOMTYPE"));
	BoxSizer5->Add(WxEditCustomType, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
	WxButtonAddCustom = new wxButton(this, ID_WXBUTTONADDCUSTOM, _("<- Add Custom File Type"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_WXBUTTONADDCUSTOM"));
	BoxSizer5->Add(WxButtonAddCustom, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(BoxSizer5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	WxButtonOK = new wxButton(this, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	BoxSizer3->Add(WxButtonOK, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	WxButtonCancel = new wxButton(this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
	WxButtonCancel->SetDefault();
	BoxSizer3->Add(WxButtonCancel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	Center();

	Connect(ID_WXLISTBOXASSOCIATED,wxEVT_COMMAND_LISTBOX_DOUBLECLICKED,(wxObjectEventFunction)&MadFileAssociationDialog::WxListBoxAssociatedDoubleClicked);
	Connect(ID_WXBUTTONADD,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MadFileAssociationDialog::WxButtonAddClick);
	Connect(ID_WXBUTTONREMOVE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MadFileAssociationDialog::WxButtonRemoveClick);
	Connect(ID_WXLISTBOXPREDEFINED,wxEVT_COMMAND_LISTBOX_DOUBLECLICKED,(wxObjectEventFunction)&MadFileAssociationDialog::WxListBoxPredefinedDoubleClicked);
	Connect(ID_WXBUTTONADDCUSTOM,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MadFileAssociationDialog::WxButtonAddCustomClick);
	Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MadFileAssociationDialog::WxButtonOKClick);
	//*)

	wxArrayString as_predefined(g_PredefinedTypes_Count, g_PredefinedTypes);

	wxConfigBase *cfg=wxConfigBase::Get(false);
	wxString oldpath=cfg->GetPath();
	cfg->SetPath(wxT("/AssociatedFileTypes"));

	int idx=0, idx2;
	wxString type;
	while(cfg->Read(wxString()<<idx, &type))
	{
		if(DetectType(type))
		{
			WxListBoxAssociated->Append(type);
			if((idx2=as_predefined.Index(type.c_str()))!=wxNOT_FOUND)
			{
				as_predefined.RemoveAt(idx2);
			}
		}
		++idx;
	}

	WxListBoxPredefined->Set(as_predefined);

	cfg->SetPath(oldpath);

	WxButtonCancel->SetFocus();
}

MadFileAssociationDialog::~MadFileAssociationDialog()
{
	//(*Destroy(MadFileAssociationDialog)
	//*)
}

void MadFileAssociationDialog::MadFileAssociationDialogClose(wxCloseEvent& event)
{
	Destroy();
}


void MadFileAssociationDialog::WxListBoxAssociatedDoubleClicked(wxCommandEvent& event)
{
	wxArrayString sel;
	GetListBoxSelections(WxListBoxAssociated, sel);
	AddTypeToPredefined(WxListBoxAssociated, WxListBoxPredefined, sel);
}

void MadFileAssociationDialog::WxListBoxPredefinedDoubleClicked(wxCommandEvent& event)
{
	wxArrayString sel;
	GetListBoxSelections(WxListBoxPredefined, sel);
	AddTypeToAssociated(WxListBoxAssociated, WxListBoxPredefined, sel);
}

void MadFileAssociationDialog::WxButtonAddClick(wxCommandEvent& event)
{
	wxArrayString sel;
	GetListBoxSelections(WxListBoxPredefined, sel);
	AddTypeToAssociated(WxListBoxAssociated, WxListBoxPredefined, sel);
}

void MadFileAssociationDialog::WxButtonRemoveClick(wxCommandEvent& event)
{
	wxArrayString sel;
	GetListBoxSelections(WxListBoxAssociated, sel);
	AddTypeToPredefined(WxListBoxAssociated, WxListBoxPredefined, sel);
}

void MadFileAssociationDialog::WxButtonAddCustomClick(wxCommandEvent& event)
{
	wxString type = WxEditCustomType->GetValue();
	type.Trim(false);
	type.Trim(true);
	if(!type.IsEmpty())
	{
		type.MakeLower();
		wxString dot(wxT('.'));
		if( type[0] != dot ) { type = dot + type; }

		wxArrayString sel;
		sel.Add(type);
		AddTypeToAssociated(WxListBoxAssociated, WxListBoxPredefined, sel);
	}
}

void MadFileAssociationDialog::WxButtonOKClick(wxCommandEvent& event)
{
	wxConfigBase *cfg=wxConfigBase::Get(false);
	wxString oldpath=cfg->GetPath();

	// clear old filetypes
	cfg->DeleteGroup(wxT("/AssociatedFileTypes"));

	cfg->SetPath(wxT("/AssociatedFileTypes"));

	// remove types
	int idx=0;
	int count = int(as_remove.Count());
	wxString type;
	while(idx<count)
	{
		type = as_remove[idx];
		if(DetectType(type))
		{
			RemoveType(type);
		}
		++idx;
	}

	// add types
	idx=0;
	count = int(WxListBoxAssociated->GetCount());
	while(idx<count)
	{
		type = WxListBoxAssociated->GetString(idx);
		AddType(type);
		cfg->Write(wxString()<<idx, type);
		++idx;
	}

	cfg->SetPath(oldpath);

	Close();
}

#endif //__WXMSW__

