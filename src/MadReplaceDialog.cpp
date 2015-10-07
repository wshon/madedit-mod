///////////////////////////////////////////////////////////////////////////////
// Name:        MadReplaceDialog.cpp
// Description:
// Author:      madedit@gmail.com
// Licence:     GPL
///////////////////////////////////////////////////////////////////////////////

#include <wx/longlong.h>
#include "MadEditFrame.h"
#include "MadReplaceDialog.h"
#include "MadSearchDialog.h"
#include "MadRecentList.h"

#include "MadEdit/MadEdit.h"

//Do not add custom headers.
//wx-dvcpp designer will remove them
////Header Include Start
////Header Include End

#include "../images/down.xpm"

MadReplaceDialog *g_ReplaceDialog=NULL;
extern MadEdit *g_ActiveMadEdit;
extern void RecordAsMadMacro(MadEdit *, const wxString&);
extern int MadMessageBox(const wxString& message,
                             const wxString& caption = wxMessageBoxCaptionStr,
                             long style = wxOK | wxCENTRE,
                             wxWindow *parent = NULL,
                             int x = wxDefaultCoord, int y = wxDefaultCoord);

//----------------------------------------------------------------------------
// MadReplaceDialog
//----------------------------------------------------------------------------
     //Add Custom Events only in the appropriate Block.
    // Code added in  other places will be removed by wx-dvcpp
    ////Event Table Start
BEGIN_EVENT_TABLE(MadReplaceDialog,wxDialog)
	////Manual Code Start
	EVT_BUTTON(ID_WXBITMAPBUTTONRECENTFINDTEXT, MadReplaceDialog::WxBitmapButtonRecentFindTextClick)
	EVT_BUTTON(ID_WXBITMAPBUTTONRECENTREPLACETEXT, MadReplaceDialog::WxBitmapButtonRecentReplaceTextClick)
	EVT_MENU_RANGE(ID_RECENTFINDTEXT1, ID_RECENTFINDTEXT20, MadReplaceDialog::OnRecentFindText)
	EVT_MENU_RANGE(ID_RECENTREPLACETEXT1, ID_RECENTREPLACETEXT20, MadReplaceDialog::OnRecentReplaceText)
	////Manual Code End
	
	EVT_CLOSE(MadReplaceDialog::MadReplaceDialogClose)
	EVT_KEY_DOWN(MadReplaceDialog::MadReplaceDialogKeyDown)
	EVT_ACTIVATE(MadReplaceDialog::MadReplaceDialogActivate)
	
	EVT_COMMAND_SCROLL(ID_WXSLIDERTRANSDEGREE,MadReplaceDialog::WxSliderTransDegreeScroll)
	EVT_RADIOBUTTON(ID_WXRADIOALWAYS,MadReplaceDialog::WxRadioAlwaysClick)
	EVT_RADIOBUTTON(ID_WXRADIOLOSINGFOCUS,MadReplaceDialog::WxRadioLosingFocusClick)
	EVT_BUTTON(ID_WXBUTTONCLOSE,MadReplaceDialog::WxButtonCloseClick)
	EVT_BUTTON(ID_WXBUTTONREPLACEALLINALL,MadReplaceDialog::WxButtonReplaceAllInAllClick)
	EVT_BUTTON(ID_WXBUTTONREPLACEALL,MadReplaceDialog::WxButtonReplaceAllClick)
	EVT_BUTTON(ID_WXBUTTONREPLACE,MadReplaceDialog::WxButtonReplaceClick)
	EVT_BUTTON(ID_WXBUTTONFINDNEXT,MadReplaceDialog::WxButtonFindNextClick)
	EVT_CHECKBOX(ID_WXCHECKBOXSEARCHINSELECTION,MadReplaceDialog::WxCheckBoxSearchInSelectionClick)
	EVT_CHECKBOX(ID_WXCHECKBOXFINDHEX,MadReplaceDialog::WxCheckBoxFindHexClick)	
	EVT_COMMAND_SCROLL(ID_WXSLIDERTRANSDEGREE,MadReplaceDialog::WxSliderTransDegreeScroll)
	EVT_RADIOBUTTON(ID_WXRADIOALWAYS,MadReplaceDialog::WxRadioAlwaysClick)
	EVT_RADIOBUTTON(ID_WXRADIOLOSINGFOCUS,MadReplaceDialog::WxRadioLosingFocusClick)
END_EVENT_TABLE()
    ////Event Table End



MadReplaceDialog::MadReplaceDialog( wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style )
    : wxDialog( parent, id, title, position, size, style)
{
    m_EnableTransparency = CanSetTransparent();
    CreateGUIControls();
}

MadReplaceDialog::~MadReplaceDialog() {}

static void ResizeItem(wxBoxSizer* sizer, wxWindow *item, int ax, int ay)
{
    int x, y;
    wxString str=item->GetLabel();
    item->GetTextExtent(str, &x, &y);
    item->SetSize(x+=ax, y+=ay);
    sizer->SetItemMinSize(item, x, y);
}

void MadReplaceDialog::CreateGUIControls(void)
{
    //Do not add custom Code here
    //wx-devcpp designer will remove them.
    //Add the custom code before or after the Blocks
    ////GUI Items Creation Start

	WxBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(WxBoxSizer1);
	this->SetAutoLayout(true);

	WxBoxSizer2 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer1->Add(WxBoxSizer2, 0, wxALIGN_CENTER | wxALL, 0);

	WxBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer2->Add(WxBoxSizer4, 0, wxALIGN_CENTER | wxALL, 0);

	WxBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer2->Add(WxBoxSizer5, 0, wxALIGN_CENTER | wxALL, 0);

	WxBoxSizer6 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer2->Add(WxBoxSizer6, 0, wxALIGN_LEFT | wxALIGN_TOP | wxALL, 0);

	WxCheckBoxMoveFocus = new wxCheckBox(this, ID_WXCHECKBOXMOVEFOCUS, _("&Move Focus to Editor Window"), wxPoint(2, 2), wxSize(300, 22), 0, wxDefaultValidator, wxT("WxCheckBoxMoveFocus"));
	WxBoxSizer6->Add(WxCheckBoxMoveFocus, 0, wxALIGN_LEFT | wxALL, 2);

	WxCheckBoxCaseSensitive = new wxCheckBox(this, ID_WXCHECKBOXCASESENSITIVE, _("&Case Sensitive"), wxPoint(2, 28), wxSize(300, 22), 0, wxDefaultValidator, wxT("WxCheckBoxCaseSensitive"));
	WxBoxSizer6->Add(WxCheckBoxCaseSensitive, 0, wxALIGN_LEFT | wxALL, 2);

	WxCheckBoxWholeWord = new wxCheckBox(this, ID_WXCHECKBOXWHOLEWORD, _("&Whole Word Only"), wxPoint(2, 54), wxSize(300, 22), 0, wxDefaultValidator, wxT("WxCheckBoxWholeWord"));
	WxBoxSizer6->Add(WxCheckBoxWholeWord, 0, wxALIGN_LEFT | wxALL, 2);

	WxCheckBoxRegex = new wxCheckBox(this, ID_WXCHECKBOXREGEX, _("Use Regular E&xpressions"), wxPoint(2, 80), wxSize(300, 22), 0, wxDefaultValidator, wxT("WxCheckBoxRegex"));
	WxBoxSizer6->Add(WxCheckBoxRegex, 0, wxALIGN_LEFT | wxALL, 2);

	WxCheckBoxFindHex = new wxCheckBox(this, ID_WXCHECKBOXFINDHEX, _("Find &Hex String (Example: BE 00 3A or BE003A)"), wxPoint(2, 106), wxSize(300, 22), 0, wxDefaultValidator, wxT("WxCheckBoxFindHex"));
	WxBoxSizer6->Add(WxCheckBoxFindHex, 0, wxALIGN_LEFT | wxALL, 2);

	WxCheckBoxSearchInSelection = new wxCheckBox(this, ID_WXCHECKBOXSEARCHINSELECTION, _("Search In &Selection"), wxPoint(2, 2), wxSize(300, 22), 0, wxDefaultValidator, wxT("WxCheckBoxSearchInSelection"));
	WxBoxSizer6->Add(WxCheckBoxSearchInSelection, 0, wxALIGN_LEFT | wxALL, 2);

	WxBoxSizer3 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer1->Add(WxBoxSizer3, 0, wxALIGN_TOP | wxALL, 0);

	WxButtonFindNext = new wxButton(this, ID_WXBUTTONFINDNEXT, _("Find &Next"), wxPoint(2, 2), wxSize(100, 28), 0, wxDefaultValidator, wxT("WxButtonFindNext"));
	WxBoxSizer3->Add(WxButtonFindNext, 0, wxALIGN_CENTER | wxALL, 2);

	WxButtonReplace = new wxButton(this, ID_WXBUTTONREPLACE, _("&Replace"), wxPoint(2, 34), wxSize(100, 28), 0, wxDefaultValidator, wxT("WxButtonReplace"));
	WxBoxSizer3->Add(WxButtonReplace, 0, wxALIGN_CENTER | wxALL, 2);

	WxButtonReplaceAll = new wxButton(this, ID_WXBUTTONREPLACEALL, _("Replace &All in\nCurrent"), wxPoint(2, 66), wxSize(100, 42), 0, wxDefaultValidator, wxT("WxButtonReplaceAll"));
	WxBoxSizer3->Add(WxButtonReplaceAll, 0, wxALIGN_CENTER | wxALL, 2);

	WxButtonReplaceAllInAll = new wxButton(this, ID_WXBUTTONREPLACEALLINALL, _("Repl All in All\n&Opened"), wxPoint(2, 98), wxSize(100, 42), 0, wxDefaultValidator, wxT("WxButtonReplaceAllInAll"));
	WxBoxSizer3->Add(WxButtonReplaceAllInAll, 0, wxALIGN_CENTER | wxALL, 2);
	WxButtonClose = new wxButton(this, ID_WXBUTTONCLOSE, _("Close"), wxPoint(17, 130), wxSize(100, 28), 0, wxDefaultValidator, wxT("WxButtonClose"));
	WxBoxSizer3->Add(WxButtonClose, 0, wxALIGN_CENTER | wxALL, 2);

	WxPopupMenuRecentReplaceText = new wxMenu(wxT(""));
	

	wxStaticBox* WxStaticBoxSizer1_StaticBoxObj = new wxStaticBox(this, wxID_ANY, _("Transparency"));
	WxStaticBoxSizer1 = new wxStaticBoxSizer(WxStaticBoxSizer1_StaticBoxObj, wxVERTICAL);
	WxBoxSizer6->Add(WxStaticBoxSizer1, 0, wxALIGN_LEFT | wxALL, 5);

	WxRadioLosingFocus = new wxRadioButton(this, ID_WXRADIOLOSINGFOCUS, _("On Losing Focus"), wxPoint(17, 17), wxSize(113, 22), 0, wxDefaultValidator, wxT("WxRadioLosingFocus"));
	WxStaticBoxSizer1->Add(WxRadioLosingFocus, 0, wxALIGN_LEFT | wxALL, 2);

	WxRadioAlways = new wxRadioButton(this, ID_WXRADIOALWAYS, _("Always"), wxPoint(16, 42), wxSize(113, 22), 0, wxDefaultValidator, wxT("WxRadioAlways"));
	WxStaticBoxSizer1->Add(WxRadioAlways, 0, wxALIGN_LEFT | wxALL, 2);

	WxSliderTransDegree = new wxSlider(this, ID_WXSLIDERTRANSDEGREE, 25, 25, 255, wxPoint(7, 69), wxSize(134, 22), wxSL_HORIZONTAL | wxSL_SELRANGE , wxDefaultValidator, wxT("WxSliderTransDegree"));
	WxSliderTransDegree->SetRange(25,255);
	WxSliderTransDegree->SetValue(25);
	WxStaticBoxSizer1->Add(WxSliderTransDegree, 0, wxALIGN_LEFT | wxALL, 2);

	SetTitle(_("Replace"));
	SetIcon(wxNullIcon);
	
	Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	
    ////GUI Items Creation End

    this->SetPosition(wxPoint(300,100));

    int bw, bh;
    // find
    WxButtonFindNext->GetSize(&bw, &bh);

    m_FindText=new MadEdit(this, ID_MADEDIT1, wxPoint(0, 0), wxSize(400, bh));
    m_FindText->SetSingleLineMode(true);
    if(g_ActiveMadEdit)
        m_FindText->SetEncoding(g_ActiveMadEdit->GetEncodingName());
    else
        m_FindText->SetEncoding(wxT("UTF-32LE"));
    m_FindText->SetFixedWidthMode(false);
    m_FindText->SetRecordCaretMovements(false);
    m_FindText->SetInsertSpacesInsteadOfTab(false);
    m_FindText->SetWantTab(false);
    m_FindText->LoadDefaultSyntaxScheme();
    m_FindText->SetMaxLineLength(DEFAULT_MAX_LINELEN);

    WxBoxSizer4->Add(m_FindText,0,wxALIGN_CENTER_HORIZONTAL | wxALL,2);
    WxBoxSizer4->SetItemMinSize(m_FindText, 400, bh);

    wxBitmap WxBitmapButtonRecentFindText_BITMAP (down_xpm);
    WxBitmapButtonRecentFindText = new wxBitmapButton(this, ID_WXBITMAPBUTTONRECENTFINDTEXT, WxBitmapButtonRecentFindText_BITMAP, wxPoint(0,0), wxSize(bh,bh), wxBU_AUTODRAW, wxDefaultValidator, wxT("WxBitmapButtonRecentFindText"));
    WxBoxSizer4->Add(WxBitmapButtonRecentFindText,0,wxALIGN_CENTER_HORIZONTAL | wxALL,2);

    // replace
    WxButtonReplace->GetSize(&bw, &bh);

    m_ReplaceText=new MadEdit(this, ID_MADEDIT2, wxPoint(0, 0), wxSize(400, bh));
    m_ReplaceText->SetSingleLineMode(true);
    
    if(g_ActiveMadEdit)
        m_ReplaceText->SetEncoding(g_ActiveMadEdit->GetEncodingName());
    else
        m_ReplaceText->SetEncoding(wxT("UTF-32LE"));
    m_ReplaceText->SetFixedWidthMode(false);
    m_ReplaceText->SetRecordCaretMovements(false);
    m_ReplaceText->SetInsertSpacesInsteadOfTab(false);
    m_ReplaceText->SetWantTab(false);
    m_ReplaceText->LoadDefaultSyntaxScheme();
    m_ReplaceText->SetMaxLineLength(DEFAULT_MAX_LINELEN);

    WxBoxSizer5->Add(m_ReplaceText,0,wxALIGN_CENTER_HORIZONTAL | wxALL,2);
    WxBoxSizer5->SetItemMinSize(m_ReplaceText, 400, bh);

    WxBitmapButtonRecentReplaceText = new wxBitmapButton(this, ID_WXBITMAPBUTTONRECENTREPLACETEXT, WxBitmapButtonRecentFindText_BITMAP, wxPoint(0,0), wxSize(bh,bh), wxBU_AUTODRAW, wxDefaultValidator, wxT("WxBitmapButtonRecentReplaceText"));
    WxBoxSizer5->Add(WxBitmapButtonRecentReplaceText,0,wxALIGN_CENTER_HORIZONTAL | wxALL,2);

    // resize checkbox
    ResizeItem(WxBoxSizer6, WxCheckBoxMoveFocus, 25, 4);
    ResizeItem(WxBoxSizer6, WxCheckBoxCaseSensitive, 25, 4);
    ResizeItem(WxBoxSizer6, WxCheckBoxWholeWord, 25, 4);
    ResizeItem(WxBoxSizer6, WxCheckBoxRegex, 25, 4);
    ResizeItem(WxBoxSizer6, WxCheckBoxFindHex, 25, 4);
	ResizeItem(WxBoxSizer6, WxCheckBoxSearchInSelection, 25, 4);

    GetSizer()->Fit(this);

    // connect to KeyDown event handler
    m_FindText->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    m_ReplaceText->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxBitmapButtonRecentFindText->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxBitmapButtonRecentReplaceText->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxCheckBoxMoveFocus->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxCheckBoxCaseSensitive->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxCheckBoxWholeWord->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxCheckBoxRegex->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxCheckBoxFindHex->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxCheckBoxSearchInSelection->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxButtonFindNext->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxButtonReplace->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxButtonReplaceAll->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));
    WxButtonClose->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MadReplaceDialog::MadReplaceDialogKeyDown));


    m_RecentReplaceText=new MadRecentList(20, ID_RECENTREPLACETEXT1, true);
    m_RecentReplaceText->UseMenu(WxPopupMenuRecentReplaceText);

    wxConfigBase *m_Config=wxConfigBase::Get(false);
    wxString oldpath=m_Config->GetPath();
    m_Config->SetPath(wxT("/RecentReplaceText"));
    m_RecentReplaceText->Load(*m_Config);
    m_Config->SetPath(oldpath);


    if(g_SearchDialog!=NULL)
    {
        wxString text;
        g_SearchDialog->m_FindText->GetText(text, true);
        m_FindText->SetText(text);
    }

    if(m_RecentReplaceText->GetCount()>0)
    {
        wxString text=m_RecentReplaceText->GetHistoryFile(0);
        if(!text.IsEmpty())
        {
            m_ReplaceText->SetText(text);
        }
    }

    if(m_EnableTransparency)
    {
        bool bb;
        long trans = 25;
        if(g_SearchDialog)
        {
            bb = g_SearchDialog->WxRadioAlways->GetValue();
            trans = g_SearchDialog->WxSliderTransDegree->GetValue();
        }
        else
        {
            m_Config->Read(wxT("/MadEdit/AlwaysTransparent"), &bb, false);
            m_Config->Read( wxT("/MadEdit/Transparency"), &trans );
        }
        WxRadioAlways->SetValue(bb);
        WxRadioLosingFocus->SetValue(!bb);
        WxSliderTransDegree->SetValue(trans);
    }
    else
    {
        WxRadioLosingFocus->Enable(false);
        WxRadioAlways->Enable(false);
        WxSliderTransDegree->Enable(false);
    }

    SetDefaultItem(WxButtonReplace);
}

void MadReplaceDialog::MadReplaceDialogClose(wxCloseEvent& event)
{
    // --> Don't use Close with a wxDialog,
    // use Destroy instead.
    if(event.CanVeto())
    {
        event.Veto();
        Show(false);
        return;
    }

    g_ReplaceDialog=NULL;
    Destroy();
}

/*
 * WxButtonCloseClick
 */
void MadReplaceDialog::WxButtonCloseClick(wxCommandEvent& event)
{
    Show(false);

    ((wxFrame*)wxTheApp->GetTopWindow())->Raise();

    if(g_ActiveMadEdit!=NULL)
    {
        g_ActiveMadEdit->Refresh(false);
        g_ActiveMadEdit->SetFocus();
    }
}

/*
 * WxButtonFindNextClick
 */
void MadReplaceDialog::WxButtonFindNextClick(wxCommandEvent& event)
{
    wxString text;
    wxCommandEvent e;
    this->ReadWriteSettings(false);
    g_SearchDialog->ReadWriteSettings(true);

    m_FindText->GetText(text, true);
    g_SearchDialog->m_FindText->SetText(text);

    g_SearchDialog->WxButtonFindNextClick(e);
}


void MadReplaceDialog::ReadWriteSettings(bool bRead)
{
    wxConfigBase *m_Config=wxConfigBase::Get(false);
    wxString oldpath=m_Config->GetPath();

    if(bRead)
    {
        bool bb;
        m_Config->Read(wxT("/MadEdit/SearchMoveFocus"), &bb, false);
        WxCheckBoxMoveFocus->SetValue(bb);

        m_Config->Read(wxT("/MadEdit/SearchCaseSensitive"), &bb, false);
        WxCheckBoxCaseSensitive->SetValue(bb);

        m_Config->Read(wxT("/MadEdit/SearchWholeWord"), &bb, false);
        WxCheckBoxWholeWord->SetValue(bb);

        m_Config->Read(wxT("/MadEdit/SearchRegex"), &bb, false);
        WxCheckBoxRegex->SetValue(bb);

        m_Config->Read(wxT("/MadEdit/SearchHex"), &bb, false);
        WxCheckBoxFindHex->SetValue(bb);
        UpdateCheckBoxByCBHex(bb);

        m_Config->Read(wxT("/MadEdit/SearchInSelection"), &bb, false);
        WxCheckBoxSearchInSelection->SetValue(bb);
        UpdateSearchInSelection(bb);
    }
    else
    {
        m_Config->Write(wxT("/MadEdit/SearchMoveFocus"), WxCheckBoxMoveFocus->GetValue());
        m_Config->Write(wxT("/MadEdit/SearchCaseSensitive"), WxCheckBoxCaseSensitive->GetValue());
        m_Config->Write(wxT("/MadEdit/SearchWholeWord"), WxCheckBoxWholeWord->GetValue());
        m_Config->Write(wxT("/MadEdit/SearchRegex"), WxCheckBoxRegex->GetValue());
        m_Config->Write(wxT("/MadEdit/SearchHex"), WxCheckBoxFindHex->GetValue());

        m_Config->Write(wxT("/MadEdit/SearchInSelection"), WxCheckBoxSearchInSelection->GetValue());
        //m_Config->Write(wxT("/MadEdit/SearchFrom"), (wxLongLong(m_SearchFrom)).ToString());
        //m_Config->Write(wxT("/MadEdit/SearchTo"), (wxLongLong(m_SearchTo)).ToString());
    }

    m_Config->SetPath(oldpath);
}

static inline ucs4_t ToHex(int d)// 0 <= d <= 15
{
    if(d < 10)
        return '0' + d;
    return 'A' + d - 10;
}
void MadReplaceDialog::UpdateCheckBoxByCBHex(bool check)
{
    if(check)
    {
        WxCheckBoxCaseSensitive->Disable();
        WxCheckBoxWholeWord->Disable();
        WxCheckBoxRegex->Disable();
    }
    else
    {
        WxCheckBoxCaseSensitive->Enable();
        WxCheckBoxWholeWord->Enable();
        WxCheckBoxRegex->Enable();
    }
}

/*
 * WxCheckBoxFindHexClick
 */
void MadReplaceDialog::WxCheckBoxFindHexClick(wxCommandEvent& event)
{
    bool checked = event.IsChecked();
    wxString text, ws;
    if(checked)
    {
        m_FindText->GetText(text, true);
        if(text.IsEmpty())
        {
            if(g_ActiveMadEdit!=NULL)
            {
                g_ActiveMadEdit->GetSelHexString(ws, true);
                m_FindText->SetText(ws);
            }
        }
        else
        {
            m_FindText->SelectAll();
            m_FindText->GetSelHexString(ws, true);
            m_FindText->SetText(ws);
        }
    }
    else
    {
        m_FindText->GetText(text, true);
        if(text.IsEmpty())
        {
            if(g_ActiveMadEdit!=NULL)
            {
                g_ActiveMadEdit->GetSelText(ws);
                m_FindText->SetText(ws);
            }
        }
    }
    UpdateCheckBoxByCBHex(event.IsChecked());
}

/*
 * MadReplaceDialogKeyDown
 */
void MadReplaceDialog::MadReplaceDialogKeyDown(wxKeyEvent& event)
{
    int key=event.GetKeyCode();

    //g_SearchDialog->SetTitle(wxString()<<key);

    switch(key)
    {
    case WXK_ESCAPE:
        g_ReplaceDialog->Show(false);
        return;
    case WXK_RETURN:
    case WXK_NUMPAD_ENTER:
        if((wxButton*)this!=g_ReplaceDialog->WxButtonFindNext &&
           (wxButton*)this!=g_ReplaceDialog->WxButtonReplace &&
           (wxButton*)this!=g_ReplaceDialog->WxButtonReplaceAll &&
           (wxButton*)this!=g_ReplaceDialog->WxButtonClose)
        {
            wxCommandEvent e;
            g_ReplaceDialog->WxButtonReplaceClick(e);
            return; // no skip
        }
        break;
    case WXK_DOWN:
        if((MadEdit*)this==g_ReplaceDialog->m_FindText)
        {
            int x,y,w,h;
            g_ReplaceDialog->m_FindText->GetPosition(&x, &y);
            g_ReplaceDialog->m_FindText->GetSize(&w, &h);
            g_ReplaceDialog->PopupMenu(g_SearchDialog->WxPopupMenuRecentFindText, x, y+h);
            return;
        }
        else if((MadEdit*)this==g_ReplaceDialog->m_ReplaceText)
        {
            int x,y,w,h;
            g_ReplaceDialog->m_ReplaceText->GetPosition(&x, &y);
            g_ReplaceDialog->m_ReplaceText->GetSize(&w, &h);
            g_ReplaceDialog->PopupMenu(g_ReplaceDialog->WxPopupMenuRecentReplaceText, x, y+h);
            return;
        }
        break;
    }

    event.Skip();
}

void MadReplaceDialog::WxBitmapButtonRecentFindTextClick(wxCommandEvent& event)
{
    PopupMenu(g_SearchDialog->WxPopupMenuRecentFindText);
}

void MadReplaceDialog::WxBitmapButtonRecentReplaceTextClick(wxCommandEvent& event)
{
    PopupMenu(WxPopupMenuRecentReplaceText);
}

void MadReplaceDialog::OnRecentFindText(wxCommandEvent& event)
{
    int idx=event.GetId()-ID_RECENTFINDTEXT1;
    wxString text=g_SearchDialog->m_RecentFindText->GetHistoryFile(idx);
    if(!text.IsEmpty())
    {
        m_FindText->SetText(text);
        m_FindText->SetFocus();
    }
}

void MadReplaceDialog::OnRecentReplaceText(wxCommandEvent& event)
{
    int idx=event.GetId()-ID_RECENTREPLACETEXT1;
    wxString text=m_RecentReplaceText->GetHistoryFile(idx);
    if(!text.IsEmpty())
    {
        m_ReplaceText->SetText(text);
        m_ReplaceText->SetFocus();
    }
}

/*
 * WxButtonReplaceClick
 */
void MadReplaceDialog::WxButtonReplaceClick(wxCommandEvent& event)
{
    if(g_ActiveMadEdit==NULL)
        return;

    wxString text, expr;
    m_FindText->GetText(text, true);

    if(text.Len()>0)
    {
        wxString reptext;
        m_ReplaceText->GetText(reptext, true);

        g_SearchDialog->m_RecentFindText->AddFileToHistory(text);

        if(reptext.Len()>0)
        {
            m_RecentReplaceText->AddFileToHistory(reptext);
        }

        wxFileOffset rangeFrom = -1, rangeTo = -1;
        wxFileOffset caretpos = g_ActiveMadEdit->GetCaretPosition();
        if(WxCheckBoxSearchInSelection->IsChecked())
        {
            rangeTo = m_SearchTo;
            if(caretpos <= m_SearchFrom || caretpos > m_SearchTo)
                rangeFrom = m_SearchFrom;
        }
        else
        {
            rangeFrom = caretpos;
        }

        expr = text;
        expr.Replace(wxT("\\"), wxT("\\\\"));
        expr.Replace(wxT("\""), wxT("\\\""));

        for(;;)
        {
            MadReplaceResult ret=RR_EXPR_ERROR;
            if(WxCheckBoxFindHex->GetValue())
            {
                ret=g_ActiveMadEdit->ReplaceHex(text, reptext, rangeFrom, rangeTo);
                
                if(ret == RR_REP_NEXT || ret == RR_NREP_NEXT)
                {
                    RecordAsMadMacro(g_ActiveMadEdit, wxString::Format(wxT("ReplaceHex(\"%s\", \"%s\", %s, %s)"), expr.c_str(), reptext.c_str(), (wxLongLong(rangeFrom).ToString()).c_str(), (wxLongLong(rangeTo).ToString()).c_str()));
                }
            }
            else
            {
                ret=g_ActiveMadEdit->ReplaceText(text, reptext,
                    WxCheckBoxRegex->GetValue(),
                    WxCheckBoxCaseSensitive->GetValue(),
                    WxCheckBoxWholeWord->GetValue(),
                    rangeFrom, rangeTo);
                if(ret == RR_REP_NEXT || ret == RR_NREP_NEXT)
                {
					wxString fnstr(wxString::Format(wxT("ReplaceText(\"%s\", \"%s\", %s, %s, %s, %s, %s)"), expr.c_str(), reptext.c_str(),
                                        WxCheckBoxRegex->GetValue()?wxT("True"):wxT("False"),
                                        WxCheckBoxCaseSensitive->GetValue()?wxT("True"):wxT("False"),
                                        WxCheckBoxWholeWord->GetValue()?wxT("True"):wxT("False"), (wxLongLong(rangeFrom).ToString()).c_str(), (wxLongLong(rangeTo).ToString()).c_str()));
					RecordAsMadMacro(g_ActiveMadEdit, fnstr);
                }
            }

            switch(ret)
            {
            case RR_REP_NNEXT:
            case RR_NREP_NNEXT:
                // handle latter
                break;
            case RR_REP_NEXT:
            case RR_NREP_NEXT:
                if(WxCheckBoxMoveFocus->GetValue())
                {
                    ((wxFrame*)wxTheApp->GetTopWindow())->Raise();
                    g_ActiveMadEdit->SetFocus();
                    
                    if(WxCheckBoxFindHex->GetValue())
                    {
                        RecordAsMadMacro(g_ActiveMadEdit, wxString::Format(wxT("ReplaceHex(\"%s\", \"%s\", %s, %s)"), expr.c_str(), reptext.c_str(), (wxLongLong(rangeFrom).ToString()).c_str(), (wxLongLong(rangeTo).ToString()).c_str()));
                    }
                    else
                    {
						wxString fnstr(wxString::Format(wxT("ReplaceText(\"%s\", \"%s\", %s, %s, %s, %s, %s)"), expr.c_str(), reptext.c_str(),
                                        WxCheckBoxRegex->GetValue()?wxT("True"):wxT("False"),
                                        WxCheckBoxCaseSensitive->GetValue()?wxT("True"):wxT("False"),
                                        WxCheckBoxWholeWord->GetValue()?wxT("True"):wxT("False"), (wxLongLong(rangeFrom).ToString()).c_str(), (wxLongLong(rangeTo).ToString()).c_str()));
						RecordAsMadMacro(g_ActiveMadEdit, fnstr);
                    }
                }
                break;
            default:
                break;
            }
            if(ret == RR_REP_NNEXT || ret == RR_NREP_NNEXT)
            {
                wxString msg(_("Cannot find the matched string.\nReplace is finished."));
                msg += wxT("\n\n");
                msg += WxCheckBoxSearchInSelection->IsChecked()?
                    _("Do you want to find from begin of selection?"):
                    _("Do you want to find from begin of file?");

                if(wxCANCEL == MadMessageBox(msg, _("Find Next"), wxOK|wxCANCEL
#if (wxMAJOR_VERSION == 2 && wxMINOR_VERSION > 9)
                    |wxCANCEL_DEFAULT
#endif
                    |wxICON_QUESTION ))
                {
                    m_FindText->SetFocus();
                    break;
                }

                if(WxCheckBoxSearchInSelection->IsChecked())
                {
                    rangeFrom = m_SearchFrom;
                    rangeTo = m_SearchTo;
                    g_ActiveMadEdit->SetSelection(m_SearchFrom, m_SearchTo);
                }
                else
                {
                    rangeFrom = 0;
                    rangeTo = -1;
                }
            }
            else
            {
                // Not done, just pause
                m_FindText->SetFocus();
                break;
            }
        }
    }
}

/*
 * WxButtonReplaceAllClick
 */
void MadReplaceDialog::WxButtonReplaceAllClick(wxCommandEvent& event)
{
    if(g_ActiveMadEdit!=NULL)
        ReplaceAll(g_ActiveMadEdit);
}

void MadReplaceDialog::WxButtonReplaceAllInAllClick(wxCommandEvent& event)
{
    int count = int( ((wxAuiNotebook*)g_MainFrame->m_Notebook)->GetPageCount() );

    for( int id = 0; id < count; ++id )
    {
        MadEdit *madedit = ( MadEdit* )((wxAuiNotebook*)g_MainFrame->m_Notebook)->GetPage( id );
        ReplaceAll(madedit, madedit==g_ActiveMadEdit);
    }
}

/*
 * MadReplaceDialogActivate
 */
void MadReplaceDialog::MadReplaceDialogActivate(wxActivateEvent& event)
{
    ReadWriteSettings(event.GetActive());
    if(event.GetActive())
    {
        if(g_ActiveMadEdit)
        {
            m_ReplaceText->SetEncoding( g_ActiveMadEdit->GetEncodingName() );
            m_FindText->SetEncoding( g_ActiveMadEdit->GetEncodingName() );
            
            wxString fname;
            int fsize;
            //g_ReplaceDialog->UpdateCheckBoxByCBHex( g_ReplaceDialog->WxCheckBoxFindHex->GetValue() );
            g_ActiveMadEdit->GetFont( fname, fsize );
            m_FindText->SetFont( fname, 14 );
            m_ReplaceText->SetFont( fname, 14 );
        }
        UpdateCheckBoxByCBHex( WxCheckBoxFindHex->GetValue() );

        if(m_EnableTransparency && WxRadioLosingFocus->GetValue())
        {
            SetTransparent(wxIMAGE_ALPHA_OPAQUE);
        }
    }
}

void MadReplaceDialog::UpdateSearchInSelection(bool check)
{
    if(check && g_ActiveMadEdit!=NULL)
    {
        m_SearchFrom = wxLongLong(g_ActiveMadEdit->GetSelectionBeginPos()).GetValue();
        m_SearchTo = wxLongLong(g_ActiveMadEdit->GetSelectionEndPos()).GetValue();
    }
    else
    {
        m_SearchFrom = -1;
        m_SearchTo = -1;
    }
}

void MadReplaceDialog::WxCheckBoxSearchInSelectionClick(wxCommandEvent& event)
{
    UpdateSearchInSelection(event.IsChecked());
}

void MadReplaceDialog::PurgeRecentReplaceTexts()
{
    int n = (int) m_RecentReplaceText->GetCount();
    for(int i = n-1; i>=0; --i)
        m_RecentReplaceText->RemoveFileFromHistory((size_t)i);
}

void MadReplaceDialog::ReplaceAll(MadEdit * madedit, bool needRec/*=true*/)
{
    wxString text;
    m_FindText->GetText(text, true);

    if(text.Len()>0)
    {
        wxString reptext;
        m_ReplaceText->GetText(reptext, true);

        g_SearchDialog->m_RecentFindText->AddFileToHistory(text);

        if(reptext.Len()>0)
        {
            m_RecentReplaceText->AddFileToHistory(reptext);
        }

        wxFileOffset rangeFrom = -1, rangeTo = -1;
        if(WxCheckBoxSearchInSelection->IsChecked())
        {
            rangeTo = m_SearchTo;
            rangeFrom = m_SearchFrom;
        }

        int count=0;
        if(WxCheckBoxFindHex->GetValue())
        {
            count=madedit->ReplaceHexAll(text, reptext, NULL, NULL, rangeFrom, rangeTo);
            if(needRec)
                RecordAsMadMacro(madedit, wxString::Format(wxT("ReplaceHexAll(\"%s\", \"%s\", %s, %s)"), text.c_str(), reptext.c_str(), (wxLongLong(rangeFrom).ToString()).c_str(), (wxLongLong(rangeTo).ToString()).c_str()));
        }
        else
        {
            count=madedit->ReplaceTextAll(text, reptext,
                WxCheckBoxRegex->GetValue(),
                WxCheckBoxCaseSensitive->GetValue(),
                WxCheckBoxWholeWord->GetValue(),
                NULL, NULL, rangeFrom, rangeTo);
            if(needRec)
            {
                text.Replace(wxT("\\"), wxT("\\\\"));
                text.Replace(wxT("\""), wxT("\\\""));
    			wxString fnstr(wxString::Format(wxT("ReplaceTextAll(\"%s\", \"%s\", %s, %s, %s, %s)"), text.c_str(), reptext.c_str(),
                                WxCheckBoxRegex->GetValue()?wxT("True"):wxT("False"),
                                WxCheckBoxCaseSensitive->GetValue()?wxT("True"):wxT("False"),
                                WxCheckBoxWholeWord->GetValue()?wxT("True"):wxT("False"), (wxLongLong(rangeFrom).ToString()).c_str(), (wxLongLong(rangeTo).ToString()).c_str()));
    			RecordAsMadMacro(madedit, fnstr);
            }
        }

        if(count>=0)
        {
            wxString msg;
            if(count==0)
                msg=wxString(_("Cannot find any matched string."));
            else
                msg=wxString::Format(_("%d string(s) were replaced."), count);

            wxMessageDialog dlg(this, msg, wxT("MadEdit-Mod"));
            dlg.SetYesNoLabels(wxMessageDialog::ButtonLabel(_("&Yes")), wxMessageDialog::ButtonLabel(_("&No")));
            dlg.ShowModal();
        }

        m_FindText->SetFocus();
    }
}

/*
 * WxRadioLosingFocusClick
 */
void MadReplaceDialog::WxRadioLosingFocusClick(wxCommandEvent& event)
{
	// insert your code here
	if(m_EnableTransparency)
    {
        SetTransparent(wxIMAGE_ALPHA_OPAQUE);
    }
}

/*
 * WxRadioAlwaysClick
 */
void MadReplaceDialog::WxRadioAlwaysClick(wxCommandEvent& event)
{
	// insert your code here
	if(m_EnableTransparency)
    {
        SetTransparent((wxByte)WxSliderTransDegree->GetValue());
    }
}

/*
 * MadSearchDialogKillFocus
 */
void MadReplaceDialog::SetTransparency()
{
	// insert your code here
	if(m_EnableTransparency && WxRadioLosingFocus->GetValue())
    {
		SetTransparent((wxByte)WxSliderTransDegree->GetValue());
    }
}

/*
 * MadReplaceDialogSetFocus
 */
void MadReplaceDialog::MadReplaceDialogSetFocus(wxFocusEvent& event)
{
	// insert your code here
	if(m_EnableTransparency && WxRadioLosingFocus->GetValue())
    {
        SetTransparent(wxIMAGE_ALPHA_OPAQUE);
    }
    this->SetFocus();
}

/*
 * WxSliderTransDegreeScroll
 */
void MadReplaceDialog::WxSliderTransDegreeScroll(wxScrollEvent& event)
{
	// insert your code here
	wxByte trans = wxIMAGE_ALPHA_OPAQUE;
	if(m_EnableTransparency && WxRadioAlways->GetValue())
    {
		trans = (wxByte)WxSliderTransDegree->GetValue();
    }
    SetTransparent(trans);
}
