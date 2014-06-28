///-----------------------------------------------------------------
///
/// @file      MadPurgeHistoryDialog.cpp
/// @author    GLi
/// Created:   2014/6/27 13:25:39
/// @section   DESCRIPTION
///            MadPurgeHistoryDialog class implementation
///
///------------------------------------------------------------------

#include "MadEditFrame.h"
#include "MadReplaceDialog.h"
#include "MadSearchDialog.h"
#include "MadFindInFilesDialog.h"
#include "MadPurgeHistoryDialog.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// MadPurgeHistoryDialog
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(MadPurgeHistoryDialog,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(MadPurgeHistoryDialog::OnClose)
	EVT_BUTTON(wxID_CANCEL,MadPurgeHistoryDialog::wxButtonCancelClick)
	EVT_BUTTON(wxID_OK,MadPurgeHistoryDialog::WxButtonOKClick)
END_EVENT_TABLE()
////Event Table End

MadPurgeHistoryDialog::MadPurgeHistoryDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

MadPurgeHistoryDialog::~MadPurgeHistoryDialog()
{
} 

void MadPurgeHistoryDialog::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxBoxSizer1 = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(WxBoxSizer1);
	this->SetAutoLayout(true);

	wxStaticBox* WxStaticBoxSizer1_StaticBoxObj = new wxStaticBox(this, wxID_ANY, wxT(""));
	WxStaticBoxSizer1 = new wxStaticBoxSizer(WxStaticBoxSizer1_StaticBoxObj, wxVERTICAL);
	WxBoxSizer1->Add(WxStaticBoxSizer1, 0, wxALIGN_LEFT | wxALIGN_TOP | wxALL, 5);

	wxCheckBoxRecentFiles = new wxCheckBox(this, ID_WXCHECKBOXRECENTFILES, _("Recent Files"), wxPoint(45, 20), wxSize(171, 19), 0, wxDefaultValidator, wxT("wxCheckBoxRecentFiles"));
	WxStaticBoxSizer1->Add(wxCheckBoxRecentFiles, 0, wxALIGN_LEFT | wxALIGN_TOP | wxALL, 5);

	wxCheckBoxRecentFonts = new wxCheckBox(this, ID_WXCHECKBOXRECENTFONTS, _("Recent Fonts"), wxPoint(44, 49), wxSize(172, 20), 0, wxDefaultValidator, wxT("wxCheckBoxRecentFonts"));
	WxStaticBoxSizer1->Add(wxCheckBoxRecentFonts, 0, wxALIGN_LEFT | wxALIGN_TOP | wxALL, 5);

	wxCheckBoxRecentEncodings = new wxCheckBox(this, ID_WXCHECKBOXRECENTENCODINGS, _("Recent Encodings"), wxPoint(35, 79), wxSize(193, 19), 0, wxDefaultValidator, wxT("wxCheckBoxRecentEncodings"));
	WxStaticBoxSizer1->Add(wxCheckBoxRecentEncodings, 0, wxALIGN_LEFT | wxALIGN_TOP | wxALL, 5);

	wxCheckBoxRecentSearchedTexts = new wxCheckBox(this, ID_WXCHECKBOXRECENTSEARCHEDTEXTS, _("Recent Searched Texts"), wxPoint(29, 108), wxSize(202, 20), 0, wxDefaultValidator, wxT("wxCheckBoxRecentSearchedTexts"));
	WxStaticBoxSizer1->Add(wxCheckBoxRecentSearchedTexts, 0, wxALIGN_LEFT | wxALIGN_TOP | wxALL, 5);

	wxCheckBoxRecentReplacedTexts = new wxCheckBox(this, ID_WXCHECKBOXRECENTREPLACEDTEXTS, _("Recent Replaced Texts"), wxPoint(30, 138), wxSize(200, 19), 0, wxDefaultValidator, wxT("wxCheckBoxRecentReplacedTexts"));
	WxStaticBoxSizer1->Add(wxCheckBoxRecentReplacedTexts, 0, wxALIGN_LEFT | wxALIGN_TOP | wxALL, 5);

	wxCheckBoxRecentSearchedDirectories = new wxCheckBox(this, ID_WXCHECKBOXRECENTSEARCHEDDIRECTORIES, _("Recent Searched Directories"), wxPoint(21, 167), wxSize(218, 19), 0, wxDefaultValidator, wxT("wxCheckBoxRecentSearchedDirectories"));
	WxStaticBoxSizer1->Add(wxCheckBoxRecentSearchedDirectories, 0, wxALIGN_LEFT | wxALIGN_TOP | wxALL, 5);

	wxRecentSearchedFileFilters = new wxCheckBox(this, ID_WXRECENTSEARCHEDFILEFILTERS, _("Recent Searched File Filters"), wxPoint(19, 196), wxSize(222, 20), 0, wxDefaultValidator, wxT("wxRecentSearchedFileFilters"));
	WxStaticBoxSizer1->Add(wxRecentSearchedFileFilters, 0, wxALIGN_LEFT | wxEXPAND | wxALL, 5);

	wxCheckBoxRecentSearchedExcludeFilters = new wxCheckBox(this, ID_WXCHECKBOXRECENTSEARCHEDEXCLUDEFILTERS, _("Recent Searched Exclude Filters"), wxPoint(10, 226), wxSize(241, 19), 0, wxDefaultValidator, wxT("wxCheckBoxRecentSearchedExcludeFilters"));
	WxStaticBoxSizer1->Add(wxCheckBoxRecentSearchedExcludeFilters, 0, wxALIGN_LEFT | wxALIGN_TOP | wxALL, 5);

	WxBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer1->Add(WxBoxSizer2, 0, wxALIGN_CENTER | wxALL, 5);

	WxButtonOK = new wxButton(this, wxID_OK, _("&OK"), wxPoint(5, 5), wxSize(85, 28), 0, wxDefaultValidator, wxT("WxButtonOK"));
	WxBoxSizer2->Add(WxButtonOK, 0, wxALIGN_CENTER | wxALL, 5);

	wxButtonCancel = new wxButton(this, wxID_CANCEL, _("&Cancel"), wxPoint(100, 5), wxSize(85, 28), 0, wxDefaultValidator, wxT("wxButtonCancel"));
	WxBoxSizer2->Add(wxButtonCancel, 0, wxALIGN_CENTER | wxALL, 5);

	SetTitle(_("Purge Histories"));
	SetIcon(wxNullIcon);
	
	Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();
	
	////GUI Items Creation End
}

void MadPurgeHistoryDialog::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}


/*
 * WxButtonOKClick
 */
void MadPurgeHistoryDialog::WxButtonOKClick(wxCommandEvent& event)
{
	// insert your code here
	if (wxCheckBoxRecentFiles->IsChecked())
		g_MainFrame->PurgeRecentFiles();

	if (wxCheckBoxRecentFonts->IsChecked())
		g_MainFrame->PurgeRecentFonts();

	if (wxCheckBoxRecentEncodings->IsChecked())
		g_MainFrame->PurgeRecentEncodings();

	if (wxCheckBoxRecentSearchedTexts->IsChecked())
		g_SearchDialog->PurgeRecentFindTexts();

	if (wxCheckBoxRecentReplacedTexts->IsChecked())
		g_ReplaceDialog->PurgeRecentReplaceTexts();

	if (wxCheckBoxRecentSearchedDirectories->IsChecked())
		g_FindInFilesDialog->PurgeRecentFindDirs();

	if (wxRecentSearchedFileFilters->IsChecked())
		g_FindInFilesDialog->PurgeRecentFindFilters();

	if (wxCheckBoxRecentSearchedExcludeFilters->IsChecked())
		g_FindInFilesDialog->PurgeRecentFindExcludes();

	Close();
}

/*
 * wxButtonCancelClick
 */
void MadPurgeHistoryDialog::wxButtonCancelClick(wxCommandEvent& event)
{
	// insert your code here
	Destroy();
}
