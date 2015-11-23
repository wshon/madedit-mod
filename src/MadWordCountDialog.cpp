///////////////////////////////////////////////////////////////////////////////
// Name:		MadWordCountDialog.cpp
// Description:	WordCount Dialog
// Author:		madedit@gmail.com
// Maintainer:	minggang.li@gmail.com
// Licence:		GPL
///////////////////////////////////////////////////////////////////////////////

#include "MadWordCountDialog.h"
#include "MadEdit/MadEdit.h"


//Do not add custom	headers
//wxDev-C++	designer will remove them
////Header Include Start
////Header Include End


#ifdef _DEBUG
#include <crtdbg.h>
#define	new	new(_NORMAL_BLOCK ,__FILE__, __LINE__)
#endif

extern void	RecordAsMadMacro(MadEdit *,	const wxString&);
//----------------------------------------------------------------------------
// MadWordCountDialog
//----------------------------------------------------------------------------
//Add Custom Events	only in	the	appropriate	block.
//Code added in	other places will be removed by	wxDev-C++
////Event Table	Start
BEGIN_EVENT_TABLE(MadWordCountDialog,wxDialog)
	////Manual Code	Start
	////Manual Code	End
	
	EVT_CLOSE(MadWordCountDialog::MadWordCountDialogClose)
END_EVENT_TABLE()
////Event Table	End

MadWordCountDialog::MadWordCountDialog(wxWindow	*parent, wxWindowID	id,	const wxString &title, const wxPoint &position, const	wxSize&	size, long style)
: wxDialog(parent, id, title, position,	size, style)
{
	CreateGUIControls();
}

MadWordCountDialog::~MadWordCountDialog() {} 

//static int gs_MinX=0;

static void	ResizeItem(wxBoxSizer* sizer, wxWindow *item, int ax, int ay)
{
	int	x, y;
	wxString str=item->GetLabel();
	item->GetTextExtent(str, &x, &y);
	item->SetSize(x+=ax, y+=ay);
	sizer->SetItemMinSize(item,	x, y);
	
	//wxPoint pos=item->GetPosition();
	//if(pos.x + x > gs_MinX) gs_MinX =	pos.x +	x;
}


void MadWordCountDialog::CreateGUIControls(void)
{
	//Do not add custom	code here
	//wxDev-C++	designer will remove them.
	//Add the custom code before or	after the blocks
	////GUI	Items Creation Start

	WxBoxSizer1	= new wxBoxSizer(wxVERTICAL);
	this->SetSizer(WxBoxSizer1);
	this->SetAutoLayout(true);

	WxFlexGridSizer1 = new wxFlexGridSizer(0, 2, 0,	150);
	WxBoxSizer1->Add(WxFlexGridSizer1, 0, wxALIGN_CENTER | wxALL, 4);

	WxStaticText1 =	new	wxStaticText(this, ID_WXSTATICTEXT1, _("Words"), wxPoint(47, 5), wxDefaultSize,	0, wxT("WxStaticText1"));
	WxFlexGridSizer1->Add(WxStaticText1,0,wxALIGN_LEFT | wxALL,5);

	WxStaticTextWordCount =	new	wxStaticText(this, ID_WXSTATICTEXTWORDCOUNT, wxT("999999"),	wxPoint(285, 5), wxDefaultSize, 0, wxT("WxStaticTextWordCount"));
	WxFlexGridSizer1->Add(WxStaticTextWordCount,0,wxALIGN_RIGHT	| wxALL,5);

	WxStaticText2 =	new	wxStaticText(this, ID_WXSTATICTEXT2, _("Characters (no spaces)"), wxPoint(8, 32), wxDefaultSize, 0, wxT("WxStaticText2"));
	WxFlexGridSizer1->Add(WxStaticText2,0,wxALIGN_LEFT | wxALL,5);

	WxStaticTextCharCount =	new	wxStaticText(this, ID_WXSTATICTEXTCHARCOUNT, wxT("999999"),	wxPoint(285, 32), wxDefaultSize, 0, wxT("WxStaticTextCharCount"));
	WxFlexGridSizer1->Add(WxStaticTextCharCount,0,wxALIGN_RIGHT	| wxALL,5);

	WxStaticText3 =	new	wxStaticText(this, ID_WXSTATICTEXT3, _("Characters (with spaces)"),	wxPoint(5, 59),	wxDefaultSize, 0, wxT("WxStaticText3"));
	WxFlexGridSizer1->Add(WxStaticText3,0,wxALIGN_LEFT | wxALL,5);

	WxStaticTextSpaceCount = new wxStaticText(this,	ID_WXSTATICTEXTSPACECOUNT, wxT("999999"), wxPoint(285, 59),	wxDefaultSize, 0, wxT("WxStaticTextSpaceCount"));
	WxFlexGridSizer1->Add(WxStaticTextSpaceCount,0,wxALIGN_RIGHT | wxALL,5);

	WxStaticText4 =	new	wxStaticText(this, ID_WXSTATICTEXT4, _("Halfwidth Words"), wxPoint(24, 86),	wxDefaultSize, 0, wxT("WxStaticText4"));
	WxFlexGridSizer1->Add(WxStaticText4,0,wxALIGN_LEFT | wxALL,5);

	WxStaticTextHalfwidthCount = new wxStaticText(this,	ID_WXSTATICTEXTHALFWIDTHCOUNT, wxT("999999"), wxPoint(285, 86), wxDefaultSize,	0, wxT("WxStaticTextHalfwidthCount"));
	WxFlexGridSizer1->Add(WxStaticTextHalfwidthCount,0,wxALIGN_RIGHT | wxALL,5);

	WxStaticText5 =	new	wxStaticText(this, ID_WXSTATICTEXT5, _("Fullwidth Words"), wxPoint(25, 113), wxDefaultSize,	0, wxT("WxStaticText5"));
	WxFlexGridSizer1->Add(WxStaticText5,0,wxALIGN_LEFT | wxALL,5);

	WxStaticTextFullwidthCount = new wxStaticText(this,	ID_WXSTATICTEXTFULLWIDTHCOUNT, wxT("999999"), wxPoint(285, 113), wxDefaultSize, 0,	wxT("WxStaticTextFullwidthCount"));
	WxFlexGridSizer1->Add(WxStaticTextFullwidthCount,0,wxALIGN_RIGHT | wxALL,5);

	WxStaticText7 =	new	wxStaticText(this, ID_WXSTATICTEXT7, _("Lines"), wxPoint(50, 140), wxDefaultSize, 0, wxT("WxStaticText7"));
	WxFlexGridSizer1->Add(WxStaticText7,0,wxALIGN_LEFT | wxALL,5);

	WxStaticTextLineCount =	new	wxStaticText(this, ID_WXSTATICTEXTLINECOUNT, wxT("999999"),	wxPoint(285, 140), wxDefaultSize, 0, wxT("WxStaticTextLineCount"));
	WxFlexGridSizer1->Add(WxStaticTextLineCount,0,wxALIGN_RIGHT	| wxALL,5);

	WxStaticLine1 =	new	wxStaticLine(this, ID_WXSTATICLINE1, wxPoint(149, 172),	wxSize(150,	-1), wxLI_HORIZONTAL);
	WxBoxSizer1->Add(WxStaticLine1,0,wxEXPAND |	wxALL,2);

	WxStaticText6 =	new	wxStaticText(this, ID_WXSTATICTEXT6, _("Detail Information of Characters:"), wxPoint(146, 183), wxDefaultSize, 0,	wxT("WxStaticText6"));
	WxBoxSizer1->Add(WxStaticText6,0,wxALIGN_CENTER	| wxALL,2);

	WxMemo1	= new wxTextCtrl(this, ID_WXMEMO1, wxT(""),	wxPoint(4, 206), wxSize(440, 160), wxTE_DONTWRAP | wxTE_MULTILINE,	wxDefaultValidator,	wxT("WxMemo1"));
	//Not sure if it's OK to remove	the	SetMaxLength which would introduce Assertion failure under Linux because of	wxTE_MULTILINE
	//WxMemo1->SetMaxLength(0);
	WxMemo1->SetFocus();
	WxMemo1->SetInsertionPointEnd();
	WxBoxSizer1->Add(WxMemo1,1,wxALIGN_CENTER |	wxEXPAND | wxALL,4);

	WxButton1 =	new	wxButton(this, wxID_CANCEL,	_("&Close"), wxPoint(191, 373),	wxSize(75, 30),	0, wxDefaultValidator,	wxT("WxButton1"));
	WxBoxSizer1->Add(WxButton1,0,wxALIGN_CENTER	| wxALL,5);

	SetTitle(_("Word Count"));
	SetIcon(wxNullIcon);
	
	GetSizer()->Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();
	
	////GUI	Items Creation End

	extern MadEdit *g_ActiveMadEdit;
	int	words, chars, spaces, lines, halfwidths, fullwidths;
	wxArrayString detail;
	g_ActiveMadEdit->WordCount(g_ActiveMadEdit->IsSelected(), words, chars,	spaces,	halfwidths,	fullwidths,	lines, &detail);
	RecordAsMadMacro(g_ActiveMadEdit, wxString::Format(wxT("WordCount(%s)"), g_ActiveMadEdit->IsSelected()?wxT("True"):wxT("False")));

	if(g_ActiveMadEdit->IsSelected())
	{
		this->SetTitle(_("Word Count(Selected Text)"));
	}
	
	WxStaticTextWordCount->SetLabel(wxString()<<words);
	WxStaticTextCharCount->SetLabel(wxString()<<chars);
	WxStaticTextSpaceCount->SetLabel(wxString()<<(chars+spaces));
	WxStaticTextHalfwidthCount->SetLabel(wxString()<<halfwidths);
	WxStaticTextFullwidthCount->SetLabel(wxString()<<fullwidths);
	WxStaticTextLineCount->SetLabel(wxString()<<lines);
	wxString str;
	for(size_t i=0;i<detail.Count();++i)
	{
		str<<detail[i]<<wxT("\n");
	}
	WxMemo1->SetValue(str);

	ResizeItem(WxBoxSizer1,	WxStaticText1, 2, 2);
	ResizeItem(WxBoxSizer1,	WxStaticText2, 2, 2);
	ResizeItem(WxBoxSizer1,	WxStaticText3, 2, 2);
	ResizeItem(WxBoxSizer1,	WxStaticText4, 2, 2);
	ResizeItem(WxBoxSizer1,	WxStaticText5, 2, 2);
	ResizeItem(WxBoxSizer1,	WxStaticText7, 2, 2);
	ResizeItem(WxBoxSizer1,	WxStaticTextWordCount, 2, 2);
	ResizeItem(WxBoxSizer1,	WxStaticTextCharCount, 2, 2);
	ResizeItem(WxBoxSizer1,	WxStaticTextSpaceCount,	2, 2);
	ResizeItem(WxBoxSizer1,	WxStaticTextHalfwidthCount,	2, 2);
	ResizeItem(WxBoxSizer1,	WxStaticTextFullwidthCount,	2, 2);
	ResizeItem(WxBoxSizer1,	WxStaticTextLineCount, 2, 2);

	ResizeItem(WxBoxSizer1,	WxStaticText6, 2, 2);

	WxButton1->SetFocus();
}

void MadWordCountDialog::MadWordCountDialogClose(wxCloseEvent& event)
{
	Destroy();
}

