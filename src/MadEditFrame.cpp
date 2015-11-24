///////////////////////////////////////////////////////////////////////////////
// Name:        MadEditFrame.cpp
// Description: main frame of MadEdit
// Author:		madedit@gmail.com
// Maintainer:	minggang.li@gmail.com
// Licence: 	GPL
///////////////////////////////////////////////////////////////////////////////

#include "MadEdit/MadEdit.h"
#include "MadEdit/MadEditCommand.h"
#include "MadEdit/MadEncoding.h"
#include "MadEdit/MadSyntax.h"
#include "MadEdit/TradSimp.h"
#include "MadEditFrame.h"
#include "MadSearchReplaceDialog.h"
#include "MadFindInFilesDialog.h"
#include "MadOptionsDialog.h"
#include "MadHighlightingDialog.h"
#ifdef __WXMSW__
	#include "MadFileAssociationDialog.h"
#endif
#include "MadPurgeHistoryDialog.h"
#include "MadMacroDlg.h"
#include "MadNumberDlg.h"
#include "MadConvEncDialog.h"
#include "MadWordCountDialog.h"
#include "MadSortDialog.h"
#include "MadAboutDialog.h"
#include "MadPrintout.h"
#include "MadUtils.h"
#include "MadCommand.h"
#include "MadRecentList.h"
#include "plugin.h"
#include <wx/config.h>
#include <wx/aui/auibook.h>

#include <wx/app.h>
//#include <wx/dynload.h>
#include <wx/tokenzr.h>
#include <wx/fontenum.h>
#include <wx/filename.h>
#include <wx/filefn.h>
#include <wx/dir.h>
#include <wx/fontdlg.h>
#include <wx/textdlg.h>
#include <wx/msgdlg.h>
#include <wx/dnd.h>
#include <wx/printdlg.h>
#include "wx/wxhtml.h"
#include <wx/xml/xml.h>
#include <wx/sstream.h>

#include <algorithm>

#include "EmbeddedPython.hpp"
#include "SpellCheckerManager.h"
#include "HunspellInterface.h"
#include "markdown.h"
#include "formattersettings.h"
#include "asstreamiterator.h"

#ifdef __WXMSW__
	#include <io.h>
#else
	#include <sys/stat.h>
#endif

//Do not add custom headers.
//wx-dvcpp designer will remove them
////Header Include Start
////Header Include End

#ifdef _DEBUG
	#include <crtdbg.h>
	#define new new(_NORMAL_BLOCK ,__FILE__, __LINE__)
#endif

#if !defined(__WXMSW__) && !defined(__WXPM__)
	#   include "../images/Mad.xpm"
	#   include "../images/Mad2.xpm"
#endif

#include "../images/null.xpm"
#define null_xpm_idx 0
#include "../images/new.xpm"
#define new_xpm_idx (null_xpm_idx+1)
#include "../images/fileopen.xpm"
#define fileopen_xpm_idx (new_xpm_idx+1)
#include "../images/filesave.xpm"
#define filesave_xpm_idx (fileopen_xpm_idx+1)
#include "../images/saveall.xpm"
#define saveall_xpm_idx (filesave_xpm_idx+1)
#include "../images/fileclose.xpm"
#define fileclose_xpm_idx (saveall_xpm_idx+1)
#include "../images/closeall.xpm"
#define closeall_xpm_idx (fileclose_xpm_idx+1)
#include "../images/preview.xpm"
#define preview_xpm_idx (closeall_xpm_idx+1)
#include "../images/print.xpm"
#define print_xpm_idx (preview_xpm_idx+1)
#include "../images/quit.xpm"
#define quit_xpm_idx (print_xpm_idx+1)

#include "../images/undo.xpm"
#define undo_xpm_idx (quit_xpm_idx+1)
#include "../images/redo.xpm"
#define redo_xpm_idx (undo_xpm_idx+1)
#include "../images/cut.xpm"
#define cut_xpm_idx (redo_xpm_idx+1)
#include "../images/copy.xpm"
#define copy_xpm_idx (cut_xpm_idx+1)
#include "../images/paste.xpm"
#define paste_xpm_idx (copy_xpm_idx+1)
#include "../images/indent.xpm"
#define indent_xpm_idx (paste_xpm_idx+1)
#include "../images/unindent.xpm"
#define unindent_xpm_idx (indent_xpm_idx+1)
#include "../images/comment.xpm"
#define comment_xpm_idx (unindent_xpm_idx+1)
#include "../images/uncomment.xpm"
#define uncomment_xpm_idx (comment_xpm_idx+1)

#include "../images/find.xpm"
#define find_xpm_idx (uncomment_xpm_idx+1)
#include "../images/findnext.xpm"
#define findnext_xpm_idx (find_xpm_idx+1)
#include "../images/findprev.xpm"
#define findprev_xpm_idx (findnext_xpm_idx+1)
#include "../images/replace.xpm"
#define replace_xpm_idx (findprev_xpm_idx+1)

#include "../images/fontname.xpm"
#define fontname_xpm_idx (replace_xpm_idx+1)
#include "../images/fontsize.xpm"
#define fontsize_xpm_idx (fontname_xpm_idx+1)
#include "../images/font.xpm"
#define font_xpm_idx (fontsize_xpm_idx+1)
#include "../images/nowrap.xpm"
#define nowrap_xpm_idx (font_xpm_idx+1)
#include "../images/wrapbywin.xpm"
#define wrapbywin_xpm_idx (nowrap_xpm_idx+1)
#include "../images/wrapbycol.xpm"
#define wrapbycol_xpm_idx (wrapbywin_xpm_idx+1)
#include "../images/textmode.xpm"
#define textmode_xpm_idx (wrapbycol_xpm_idx+1)
#include "../images/columnmode.xpm"
#define columnmode_xpm_idx (textmode_xpm_idx+1)
#include "../images/hexmode.xpm"
#define hexmode_xpm_idx (columnmode_xpm_idx+1)

#include "../images/Mad_16x15.xpm"
#define Mad_16x15_xpm_idx (hexmode_xpm_idx+1)

#include "../images/runscript.xpm"
#define runscript_xpm_idx (Mad_16x15_xpm_idx+1)
#include "../images/record.xpm"
#define record_xpm_idx (runscript_xpm_idx+1)
#include "../images/stop.xpm"
#define stop_xpm_idx (record_xpm_idx+1)
#include "../images/play.xpm"
#define play_xpm_idx (stop_xpm_idx+1)
#include "../images/saverec.xpm"
#define saverec_xpm_idx (play_xpm_idx+1)

#include "../images/bookmark_toggle.xpm"
#define bookmark_toggle_xpm_idx (saverec_xpm_idx+1)
#include "../images/bookmark_next.xpm"
#define bookmark_next_xpm_idx (bookmark_toggle_xpm_idx+1)
#include "../images/bookmark_prev.xpm"
#define bookmark_prev_xpm_idx (bookmark_next_xpm_idx+1)
#include "../images/bookmark_clear.xpm"
#define bookmark_clear_xpm_idx (bookmark_prev_xpm_idx+1)
#include "../images/spellchecker.xpm"
#define spellchecker_xpm_idx (bookmark_clear_xpm_idx+1)
#include "../images/showsymbol.xpm"
#define showsymbol_xpm_idx (spellchecker_xpm_idx+1)

#include "../images/down.xpm"
#define down_xpm_idx (showsymbol_xpm_idx+1)
#include "../images/up.xpm"
#define up_xpm_idx (down_xpm_idx+1)

#include "../images/alignleft.xpm"
#define alignleft_xpm_idx (up_xpm_idx+1)
#include "../images/alignright.xpm"
#define alignright_xpm_idx (alignleft_xpm_idx+1)
#include "../images/numbering.xpm"
#define numbering_xpm_idx (alignright_xpm_idx+1)
#include "../images/refresh.xpm"
#define refresh_xpm_idx (numbering_xpm_idx+1)
#include "../images/closepreview.xpm"
#define closepreview_xpm_idx (refresh_xpm_idx+1)

char ** g_MadIcons[] =
{
	&null_xpm[0], &new_xpm[0], &fileopen_xpm[0], &filesave_xpm[0], &saveall_xpm[0], &fileclose_xpm[0],
	&closeall_xpm[0], &preview_xpm[0], &print_xpm[0], &quit_xpm[0], &undo_xpm[0], &redo_xpm[0], &cut_xpm[0],
	&copy_xpm[0], &paste_xpm[0], &indent_xpm[0], &unindent_xpm[0], &comment_xpm[0], &uncomment_xpm[0],
	&find_xpm[0], &findnext_xpm[0], &findprev_xpm[0], &replace_xpm[0], &fontname_xpm[0], &fontsize_xpm[0],
	&font_xpm[0], &nowrap_xpm[0], &wrapbywin_xpm[0], &wrapbycol_xpm[0], &textmode_xpm[0], &columnmode_xpm[0],
	&hexmode_xpm[0], &Mad_16x15_xpm[0], &runscript_xpm[0], &record_xpm[0], &stop_xpm[0], &playback_xpm[0],
	&saverec_xpm[0], &bookmark_toggle_xpm[0], &bookmark_next_xpm[0], &bookmark_prev_xpm[0],
	&bookmark_clear_xpm[0], &spellchecker_xpm[0], &showsymbol_xpm[0], &down_xpm[0], &up_xpm[0],
	&alignleft_xpm[0], &alignright_xpm[0], &numbering_xpm[0], &refresh_xpm[0], &closepreview_xpm[0]
};

extern void ScanForLocales();
extern wxArrayString g_LanguageString;

#if wxCHECK_VERSION(2,7,0)
	#define GetAccelFromString(x) wxAcceleratorEntry::Create(x)
#else
	#define GetAccelFromString(x) wxGetAccelFromString(x)
#endif
extern wxString MadStrLower( const wxString & );

extern wxString g_MadEdit_Version, g_MadEditModLicense, g_MadEditModCredits;
extern wxString g_MadEdit_URL;
extern wxString g_MadEditMod_URL;
extern wxString MadEncodingGrpName[];

EmbeddedPython *g_EmbeddedPython = 0;
MadRecentList  *g_RecentFindText = NULL;
extern wxString g_MadEditAppDir, g_MadEditHomeDir;
wxHtmlWindow * g_MadToolHtmlWin = NULL;

MadEditFrame *g_MainFrame = NULL;
MadEdit *g_ActiveMadEdit = NULL;
int g_PrevPageID = -1;
wxStatusBar *g_StatusBar = NULL;
wxArrayString g_SpellSuggestions;
astyle::ASFormatter * g_ASFormatter = NULL;

bool g_CheckModTimeForReload = true;

wxMenu *g_Menu_File = NULL;
wxMenu *g_Menu_FilePop = NULL;
wxMenu *g_Menu_Edit = NULL;
wxMenu *g_Menu_EditPop = NULL;
wxMenu *g_Menu_EditSubAdv = NULL;
wxMenu *g_Menu_EditSubSort = NULL;
wxMenu *g_Menu_Search = NULL;
wxMenu *g_Menu_View = NULL;
wxMenu *g_Menu_Tools = NULL;
wxMenu *g_Menu_Window = NULL;
wxMenu *g_Menu_Help = NULL;
wxMenu *g_Menu_File_RecentFiles = NULL;
wxMenu *g_Menu_Edit_Bookmark = NULL;
wxMenu *g_Menu_Edit_Sort = NULL;
wxMenu *g_Menu_Edit_Advanced = NULL;
wxMenu *g_Menu_View_Encoding = NULL;
wxMenu *g_Menu_View_AllEncodings = NULL;
wxMenu *g_Menu_View_EncodingGrps[ENCG_MAX] = {NULL};
wxMenu *g_Menu_View_Syntax = NULL;
wxMenu *g_Menu_View_FontName = NULL;
wxMenu *g_Menu_View_Font0 = NULL;
wxMenu *g_Menu_View_Font1 = NULL;
wxMenu *g_Menu_View_Font2 = NULL;
wxMenu *g_Menu_View_Font3 = NULL;
wxMenu *g_Menu_View_Font4 = NULL;
wxMenu *g_Menu_View_Font5 = NULL;
wxMenu *g_Menu_View_Font6 = NULL;
wxMenu *g_Menu_View_FontSize = NULL;
wxMenu *g_Menu_View_TabColumn = NULL;
wxMenu *g_Menu_View_Preview = NULL;
wxMenu *g_Menu_View_LineSpacing = NULL;
wxMenu *g_Menu_Tools_BOM = NULL;
wxMenu *g_Menu_Tools_NewLineChar = NULL;
wxMenu *g_Menu_Tools_InsertNewLineChar = NULL;
wxMenu *g_Menu_Tools_ConvertChineseChar = NULL;
wxMenu *g_Menu_Tools_TextConvFormatter = NULL;
wxMenu *g_Menu_MadMacro = NULL;
wxMenu *g_Menu_MadMacro_Scripts = NULL;
wxMenu *g_Menu_Toolbars = NULL;
wxMenu *g_Menu_FrameContext = NULL;

// Add menus that needs initialized at startup in this array
wxMenu ** g_Menus[] =
{
	&g_Menu_File, &g_Menu_FilePop, &g_Menu_Edit, &g_Menu_EditPop, &g_Menu_EditSubAdv,
	&g_Menu_EditSubSort, &g_Menu_Search, &g_Menu_View, &g_Menu_Tools, &g_Menu_Window,
	&g_Menu_Help, &g_Menu_File_RecentFiles, &g_Menu_Edit_Bookmark, &g_Menu_Edit_Sort,
	&g_Menu_Edit_Advanced, &g_Menu_View_Encoding, &g_Menu_View_AllEncodings,
	&g_Menu_View_Syntax, &g_Menu_View_FontName, &g_Menu_View_Font0, &g_Menu_View_Font1,
	&g_Menu_View_Font2, &g_Menu_View_Font3, &g_Menu_View_Font4, &g_Menu_View_Font5,
	&g_Menu_View_Font6, &g_Menu_View_FontSize, &g_Menu_View_TabColumn, &g_Menu_View_Preview,
	&g_Menu_View_LineSpacing, &g_Menu_Tools_BOM, &g_Menu_Tools_NewLineChar,
	&g_Menu_Tools_InsertNewLineChar, &g_Menu_Tools_ConvertChineseChar,
	&g_Menu_Tools_TextConvFormatter, &g_Menu_MadMacro, &g_Menu_MadMacro_Scripts,
	&g_Menu_Toolbars
};

wxArrayString g_FontNames;

#ifdef __WXMSW__
int g_StatusWidth_1_6 = ( 215 + 215 + 135 + 121 + 60 + ( 40 + 18 ) );
int g_StatusWidths[7] = { 0, 215, 215, 135, 121, 60, ( 40 + 18 )};
#else
int g_StatusWidth_1_6 = ( 220 + 235 + 135 + 155 + 65 + ( 40 + 0 ) );
int g_StatusWidths[7] = { 0, 220, 235, 135, 155, 65, ( 40 + 0 )};
#endif

std::map<int, wxString>g_ToolbarNames;
std::map<int, wxString>g_PreviewTypeNames;

wxAcceleratorEntry g_AccelFindNext, g_AccelFindPrev;
int MadMessageBox( const wxString& message,
				   const wxString& caption = wxMessageBoxCaptionStr,
				   long style = wxOK | wxCENTRE,
				   wxWindow *parent = NULL,
				   int x = wxDefaultCoord, int y = wxDefaultCoord );
inline void RecordAsMadMacro( MadEdit * edit, const wxString& script )
{
	if( ( g_MainFrame != NULL ) && ( edit == g_ActiveMadEdit ) )
	{
		if( g_MainFrame->IsMacroRecording() )
		{
			g_MainFrame->AddMacroScript( script, ( int )g_ActiveMadEdit->GetCaretPosition(),
										 ( int )g_ActiveMadEdit->GetSelectionBeginPos(), ( int )g_ActiveMadEdit->GetSelectionEndPos() );
		}
	}
}

int MadMessageBox( const wxString& message, const wxString& caption, long style,
				   wxWindow *parent, int WXUNUSED( x ), int WXUNUSED( y ) )
{
	// add the appropriate icon unless this was explicitly disabled by use of
	// wxICON_NONE
	if( !( style & wxICON_NONE ) && !( style & wxICON_MASK ) )
	{
		style |= style & wxYES ? wxICON_QUESTION : wxICON_INFORMATION;
	}

	wxMessageDialog dialog( parent, message, caption, style );

	if( ( style & ( wxYES_NO | wxCANCEL ) ) == ( wxYES_NO | wxCANCEL ) )
	{
		dialog.SetYesNoCancelLabels( wxMessageDialog::ButtonLabel( _( "&Yes" ) ),
									 wxMessageDialog::ButtonLabel( _( "&No" ) ), wxMessageDialog::ButtonLabel( _( "&Cancel" ) ) );
	}
	else
		if( ( style & ( wxYES_NO ) ) == ( wxYES_NO ) )
		{
			dialog.SetYesNoLabels( wxMessageDialog::ButtonLabel( _( "&Yes" ) ), wxMessageDialog::ButtonLabel( _( "&No" ) ) );
		}
		else
			if( ( style & ( wxOK | wxCANCEL ) ) == ( wxOK | wxCANCEL ) )
			{
				dialog.SetOKCancelLabels( wxMessageDialog::ButtonLabel( _( "&Ok" ) ), wxMessageDialog::ButtonLabel( _( "&Cancel" ) ) );
			}
			else
				if( ( style & wxOK ) == wxOK )
				{
					dialog.SetOKLabel( wxMessageDialog::ButtonLabel( _( "&Ok" ) ) );
				}

	int ans = dialog.ShowModal();

	switch( ans )
	{
	case wxID_OK:
		return wxOK;

	case wxID_YES:
		return wxYES;

	case wxID_NO:
		return wxNO;

	case wxID_CANCEL:
		return wxCANCEL;

	case wxID_HELP:
		return wxHELP;
	}

	wxFAIL_MSG( wxT( "unexpected return code from wxMessageDialog" ) );
	return wxCANCEL;
}

//---------------------------------------------------------------------------

// for RestoreCaretPos
class FileCaretPosManager
{
	int max_count;

	struct FilePosData
	{
		wxString name;
		wxFileOffset pos;
		unsigned long hash; // hash value of filename
		wxString encoding;
		wxString fontname;
		int fontsize;

		FilePosData( const wxString &n, const wxLongLong_t &p, unsigned long h, const wxString &e, const wxString &fn, int fs )
			: name( n ), pos( p ), hash( h ), encoding( e ), fontname( fn ), fontsize( fs )
		{}
		FilePosData()
			: pos( 0 ), hash( 0 ), fontsize( 0 )
		{}
	};
	std::list<FilePosData> files;

public:
	FileCaretPosManager() : max_count( 40 ) {}

	void Add( const wxString &name, const wxFileOffset &pos, const wxString &encoding, const wxString &fontname, int fontsize ) {
#ifdef __WXMSW__
		wxString name0( name.Upper() );
#else
		const wxString &name0 = name;
#endif
		unsigned long hash = wxStringHash::wxCharStringHash( name0 );

		if( files.empty() ) {
			files.push_back( FilePosData( name0, pos, hash, encoding, fontname, fontsize ) );
		}
		else {
			std::list<FilePosData>::iterator it = files.begin();
			std::list<FilePosData>::iterator itend = files.end();

			do {
				if( it->hash == hash && it->name == name0 ) {
					break;
				}
			}
			while( ++it != itend );

			if( it == itend ) {
				files.push_front( FilePosData( name0, pos, hash, encoding, fontname, fontsize ) );
			}
			else {
				it->pos = pos;
				it->encoding = encoding;
				it->fontname = fontname;
				it->fontsize = fontsize;
				files.push_front( *it );
				files.erase( it );
			}
		}

		if( int( files.size() ) > max_count ) {
			files.pop_back();
		}
	}
	void Add( MadEdit *madedit ) {
		if( madedit == NULL ) { return; }

		wxString name = madedit->GetFileName();

		if( !name.IsEmpty() ) {
			wxString fontname;
			int fontsize;
			madedit->GetTextFont( fontname, fontsize );
			wxFileOffset pos = madedit->GetCaretPosition();
			Add( name, pos, madedit->GetEncodingName(), fontname, fontsize );
		}
	}
	void Save( wxConfigBase *cfg ) {
		cfg->Write( wxT( "MaxCount" ), max_count );
		std::list<FilePosData>::iterator it = files.begin();
		wxString entry( wxT( "file" ) ), text;
		int idx = 0, count = int( files.size() );

		while( idx < count ) {
			text = wxLongLong( it->pos ).ToString();
			text += wxT( "|" );
			text += it->name;
			text += wxT( "|" );
			text += it->encoding;
			text += wxT( "|" );
			text += it->fontname;
			text += wxT( "|" );
			text += wxLongLong( it->fontsize ).ToString();
			cfg->Write( entry + ( wxString() << ( idx + 1 ) ), text );
			++idx;
			++it;
		}
	}
	void Load( wxConfigBase *cfg ) {
		cfg->Read( wxT( "MaxCount" ), &max_count );
		FilePosData fpdata;
		wxString entry( wxT( "file" ) ), text;
		int idx = 1;

		while( idx <= max_count && cfg->Read( entry + ( wxString() << idx ), &text ) ) {
			int p = text.Find( wxT( "|" ) );

			if( p != wxNOT_FOUND ) {
				fpdata.pos = 0;
				fpdata.fontsize = 0;
				fpdata.encoding.Empty();
				wxInt64 i64;

				if( StrToInt64( text.Left( p ), i64 ) ) {
					fpdata.pos = i64;
					text = text.Right( text.Len() - ( p + 1 ) );
					p = text.Find( wxT( "|" ) );

					if( p != wxNOT_FOUND ) {
						fpdata.name = text.Left( p );
						text = text.Right( text.Len() - ( p + 1 ) );
						p = text.Find( wxT( "|" ) );

						if( p != wxNOT_FOUND ) {
							fpdata.encoding = text.Left( p );
							text = text.Right( text.Len() - ( p + 1 ) );
							p = text.Find( wxT( "|" ) );

							if( p != wxNOT_FOUND ) {
								fpdata.fontname = text.Left( p );
								text = text.Right( text.Len() - ( p + 1 ) );

								if( StrToInt64( text, i64 ) ) {
									fpdata.fontsize = i64;
								}
							}
							else {
								fpdata.fontname = text;
							}
						}
						else {
							fpdata.encoding = text;
						}
					}
					else { // old format
						fpdata.name = text;
					}

					fpdata.hash = wxStringHash::wxCharStringHash( fpdata.name );
					files.push_back( fpdata );
				}
			}

			++idx;
		}
	}
	wxFileOffset GetRestoreData( const wxString &name, wxString &encoding, wxString &fontname, int &fontsize ) {
#ifdef __WXMSW__
		wxString name0( name.Upper() );
#else
		const wxString &name0 = name;
#endif
		unsigned long hash = wxStringHash::wxCharStringHash( name0 );
		wxFileOffset pos = 0;
		fontsize = 0;

		if( !files.empty() ) {
			std::list<FilePosData>::iterator it = files.begin();
			std::list<FilePosData>::iterator itend = files.end();

			do {
				if( it->hash == hash && it->name == name0 ) {
					pos = it->pos;
					encoding = it->encoding;
					fontname = it->fontname;
					fontsize = it->fontsize;
					break;
				}
			}
			while( ++it != itend );
		}

		return pos;
	}
	void Clear( wxConfigBase *cfg ) {
		int idx = 1;
		wxString entry( wxT( "file" ) ), text;
		while( idx <= max_count) {
			cfg->DeleteEntry(entry + ( wxString() << idx ), false);
			++idx;
		}
		files.clear();
	}
};

FileCaretPosManager g_FileCaretPosManager;

//---------------------------------------------------------------------------

// for FindInFilesResults
class CaretPosData: public wxTreeItemData
{
public:
	wxString filename;
	int pageid; // >=0 for 'NoName'
	wxFileOffset bpos, epos;
	CaretPosData( const wxString &fn, int pid, const wxFileOffset &b, wxFileOffset &e )
		: filename( fn ), pageid( pid ), bpos( b ), epos( e ) {}
};

//---------------------------------------------------------------------------

#ifndef __WXMSW__   // for Linux filename checking/converting
MadConvFileName MadConvFileNameObj;

wxString FixFileNameEncoding( const wxString &filename )
{
	size_t len = filename.Len();
	wxByte *bbuf = new wxByte[len + 1];
	wxByte *ps = bbuf;
	const wxChar *pwcs = filename.c_str();

	for( size_t l = len; l > 0; --l, ++ps, ++pwcs )
	{
		if( *pwcs >= 0x100 )
		{
			delete []bbuf;
			return filename;
		}

		*ps = *pwcs;
	}

	*ps = 0;
	g_MB2WC_check_dir_filename = true;
	size_t wcslen = MadConvFileNameObj.MB2WC( NULL, ( const char* )bbuf, 0 );

	if( wcslen == size_t( -1 ) )
	{ return filename; }

	wxChar *str = new wxChar[wcslen + 1];
	MadConvFileNameObj.MB2WC( str, ( const char* )bbuf, wcslen + 1 );
	g_MB2WC_check_dir_filename = false;
	wxString newfn( str );
	delete []bbuf;
	delete []str;
	return newfn;
}
#endif

class DnDFile : public wxFileDropTarget
{
public:
	virtual bool OnDropFiles( wxCoord x, wxCoord y, const wxArrayString& filenames ) {
		size_t count = filenames.GetCount();

		for( size_t i = 0; i < count; ++i ) {
#ifdef __WXMSW__
			g_MainFrame->OpenFile( filenames[i], true );
#else
			wxString fn = FixFileNameEncoding( filenames[i] );
			g_MainFrame->OpenFile( fn, true );
#endif
		}

		return true;
	}
};

//---------------------------------------------------------------------------

class wxMadAuiNotebook : public wxAuiNotebook
{
public:
	wxMadAuiNotebook() : wxAuiNotebook() {}

	wxMadAuiNotebook( wxWindow* parent,
					  wxWindowID id = wxID_ANY,
					  const wxPoint& pos = wxDefaultPosition,
					  const wxSize& size = wxDefaultSize,
					  long style = wxAUI_NB_DEFAULT_STYLE )
		: wxAuiNotebook( parent, id, pos, size, style ) {
	}

	virtual ~wxMadAuiNotebook() {}

	struct PageData
	{
		int x, y, idx;
		MadEdit *madedit;
		PageData() {}
		PageData( int xx, int yy, int ii, MadEdit *mm )
			: x( xx ), y( yy ), idx( ii ), madedit( mm )
		{}
	};

	list<PageData> GetPagesList() {
		wxAuiNotebookPageArray& pages = m_tabs.GetPages();
		size_t i, page_count = pages.GetCount();
		list<PageData> pages_list;
		list<PageData>::iterator it;

		for( i = 0; i < page_count; ++i ) {
			wxAuiNotebookPage& page = pages.Item( i );
			MadEdit *madedit = ( MadEdit* )page.window;
			wxAuiTabCtrl *ctrl;
			int idx;

			if( FindTab( page.window, &ctrl, &idx ) ) {
				wxPoint pt = ctrl->GetPosition();
				pt = ctrl->ClientToScreen( pt );
				it = pages_list.begin();
				size_t j = 0;

				for( ; j < pages_list.size(); ++j, ++it ) {
					PageData &pd = *it;

					if( pt.y < pd.y ) {
						break;
					}
					else
						if( pt.y == pd.y ) {
							if( pt.x < pd.x ) {
								break;
							}
							else
								if( pt.x == pd.x ) {
									if( idx < pd.idx ) {
										break;
									}
								}
						}
				}

				pages_list.insert( it, PageData( pt.x, pt.y, idx, madedit ) );
			}
		}

		return pages_list;
	}

	int GetFilesList( wxString &files ) {
		int count = 0;
		list<PageData> pages_list = GetPagesList();
		size_t page_count = pages_list.size();
		list<PageData>::iterator it = pages_list.begin();

		for( size_t i = 0; i < page_count; ++i, ++it ) {
			wxString name( it->madedit->GetFileName() );

			if( !name.IsEmpty() ) {
				files += name;
				files += wxT( '|' );
				++count;
			}
		}

		return count;
	}

	struct FunctorA
	{
		MadEdit *madedit;
		bool operator()( PageData &pd ) {
			return madedit == pd.madedit;
		}
	};

	void AdvanceSelection( bool bForward ) {
		int count = ( int )GetPageCount();

		if( count <= 1 ) { return; }

		list<PageData> pages_list = GetPagesList();
		wxWindow* win = GetPage( GetSelection() );
		FunctorA fa;
		fa.madedit = ( MadEdit* )win;
		list<PageData>::iterator it = std::find_if( pages_list.begin(), pages_list.end(), fa );
		wxASSERT( it != pages_list.end() );

		if( bForward ) {
			if( ++it == pages_list.end() ) { it = pages_list.begin(); }
		}
		else {
			if( it == pages_list.begin() ) { it = pages_list.end(); }

			--it;
		}

		SetSelection( GetPageIndex( it->madedit ) );
	}

	void ConnectMouseClick() {
		if( GetPageCount() != 0 ) {
			wxAuiTabCtrl *ctrl = GetActiveTabCtrl();
			ctrl->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( wxMadAuiNotebook::OnMouseClick ) );
			ctrl->Connect( wxEVT_MIDDLE_UP, wxMouseEventHandler( wxMadAuiNotebook::OnMouseClick ) );
		}
	}

protected:
	void OnMouseClick( wxMouseEvent &evt ) {
		//wxString s;
		//s.Printf(L"%d %d", evt.m_x, evt.m_y);
		//((wxTopLevelWindow*)g_MainFrame)->SetLabel(s);
		wxAuiTabCtrl *ctrl = ( wxAuiTabCtrl* )evt.GetEventObject();
		wxWindow *win;

		if( ctrl->TabHitTest( evt.m_x, evt.m_y, &win ) ) {
			g_MainFrame->CloseFile( g_MainFrame->m_Notebook->GetPageIndex( win ) );
		}
	}

};


void OnReceiveMessage( const wchar_t *msg, size_t size )
{
#ifdef __WXMSW__
	WINDOWPLACEMENT wp;
	wp.length = sizeof( WINDOWPLACEMENT );
	GetWindowPlacement( ( HWND )g_MainFrame->GetHWND(), &wp );

	if( wp.showCmd == SW_SHOWMINIMIZED )
	{
		if( ( wp.flags & WPF_RESTORETOMAXIMIZED ) == 0 ) // show normal
		{
			wp.showCmd = SW_NORMAL;
		}
		else                                     // show maximized
		{
			wp.showCmd = SW_SHOWMAXIMIZED;
		}

		SetWindowPlacement( ( HWND )g_MainFrame->GetHWND(), &wp );
	}

#else
	//g_MainFrame->Show(true);
	g_MainFrame->Raise();
#if wxMAJOR_VERSION < 2 || (wxMAJOR_VERSION == 2 && wxMINOR_VERSION < 9)
	g_MainFrame->RequestUserAttention();//wxUSER_ATTENTION_ERROR);
#endif
	g_MainFrame->SetFocus();
#endif

	if( g_ActiveMadEdit ) { g_ActiveMadEdit->SetFocus(); }

	// open the files
	wxString files, file, args( msg ), arg, mpScript;
	bool use_script = false, forceEdit = false, silent = false, exitS = false;;
	/* filename1|filename2| *s *f *m mpython.mpy */
	files = args.BeforeLast( '|', &arg );
	args = arg;

	if( !args.IsEmpty() )
	{
		mpScript.Empty();
		wxString strDel = wxT( "*" );
		wxStringTokenizer tkz1( args, strDel );

		while( tkz1.HasMoreTokens() )
		{
			arg = tkz1.GetNextToken();

			// process token here
			if( !arg.IsEmpty() )
			{
				if( arg == wxT( "s" ) )
				{ silent = true; }
				else
					if( arg == wxT( "f" ) )
					{ forceEdit = true; }
					else
						if( arg == wxT( "x" ) )
						{ exitS = true; }
						else
							if( arg[0] == 'm' )
							{
								use_script = true;
								mpScript = arg.AfterFirst( 'm' );

								if( !mpScript.IsEmpty() )
								{
									mpScript.Trim( false );
									mpScript.Trim();
								}
							}
			}
		}
	}

	if( mpScript.IsEmpty() ) { use_script = false; }
	else
	{
		wxTextFile scriptfile( mpScript );
		scriptfile.Open( wxConvFile );
		use_script = false;

		if( scriptfile.IsOpened() )
		{
			arg = scriptfile.GetFirstLine() + wxT( "\n" );

			for( ; !scriptfile.Eof(); )
			{
				arg << scriptfile.GetNextLine() << wxT( "\n" );
			}

			if( arg.IsNull() == false )
			{ use_script = true;}

			scriptfile.Close();
		}
	}

	if( ( !silent ) || ( use_script == true ) )
	{
		wxString strDelimiters = wxT( "|" );
		wxStringTokenizer tkz2( files, strDelimiters );

		while( tkz2.HasMoreTokens() )
		{
			file = tkz2.GetNextToken();

			// process token here
			if( !use_script )
			{ g_MainFrame->OpenFile( file, false ); }
			else
			{ g_MainFrame->RunScriptWithFile( file, arg, false, silent, forceEdit ); }
		}
	}

	if( exitS )
	{ g_MainFrame->Close( false ); }
}


int GetIdByEdit( MadEdit *edit )
{
	return g_MainFrame->m_Notebook->GetPageIndex( edit );
}

// return true for name; false for title
bool GetActiveMadEditPathNameOrTitle( wxString &name )
{
	name = g_ActiveMadEdit->GetFileName();

	if( name.IsEmpty() )
	{
		name = g_MainFrame->m_Notebook->GetPageText( GetIdByEdit( g_ActiveMadEdit ) );

		if( name[name.Len() - 1] == wxT( '*' ) )
		{ name.Truncate( name.Len() - 1 ); }

		return false;
	}

	return true;
}

void ApplySyntaxAttributes( MadSyntax *syn )
{
	int count = int( g_MainFrame->m_Notebook->GetPageCount() );

	for( int id = 0; id < count; ++id )
	{
		MadEdit *me = ( MadEdit* )g_MainFrame->m_Notebook->GetPage( id );
		me->ApplySyntaxAttributes( syn, true );
	}
}

void OnEditSelectionChanged( MadEdit *madedit )
{
	g_MainFrame->m_Notebook->ConnectMouseClick();

	if( madedit == NULL )
	{
		g_StatusBar->SetStatusText( wxEmptyString, 1 );
		g_StatusBar->SetStatusText( wxEmptyString, 2 );
		g_StatusBar->SetStatusText( wxEmptyString, 3 );
	}
	else
	{
		if( madedit != g_ActiveMadEdit )
		{ return; }

		int line, subrow;
		wxFileOffset col;
		madedit->GetCaretPosition( line, subrow, col );

		if( madedit->GetEditMode() != emHexMode )
		{
			++line;
			++col;
		}

		wxString s1 = FormatThousands( wxString::Format( wxT( "%d" ), line ) );
		wxString s2 = FormatThousands( wxString::Format( wxT( "%u" ), madedit->GetLineCount() ) );
		wxString s4 = FormatThousands( wxLongLong( col ).ToString() );
		static wxString lnstr( _( "Ln:" ) );
		static wxString sepstr( wxT( " /" ) );
		static wxString sepstr1( wxT( " (" ) );
		static wxString substr( _( "Sub:" ) );
		static wxString sepstr2( wxT( ')' ) );
		static wxString sepstr3( wxT( ' ' ) );
		static wxString colstr( _( "Col:" ) );
		static wxString fpstr( _( "CharPos:" ) );
		static wxString ssstr( _( "SelSize:" ) );
		wxString text = lnstr + s1 + sepstr + s2;

		if( subrow > 0 )
		{
			wxString s3 = FormatThousands( wxString::Format( wxT( "%d" ), subrow + 1 ) );
			text += ( sepstr1 + substr + s3 + sepstr2 );
		}

		text += ( sepstr3 + colstr + s4 );
		g_StatusBar->SetStatusText( text, 1 );
		s1 = FormatThousands( wxLongLong( madedit->GetCaretPosition() ).ToString() );
		s2 = FormatThousands( wxLongLong( madedit->GetFileSize() ).ToString() );
		g_StatusBar->SetStatusText( fpstr + s1 + sepstr + s2, 2 );
		s1 = FormatThousands( wxLongLong( madedit->GetSelectionSize() ).ToString() );
		g_StatusBar->SetStatusText( ssstr + s1, 3 );
	}

	g_StatusBar->Update(); // repaint immediately
}

void OnEditStatusChanged( MadEdit *madedit )
{
	g_MainFrame->m_Notebook->ConnectMouseClick();

	if( madedit == NULL )
	{
		g_StatusBar->SetStatusText( wxEmptyString, 4 );
		g_StatusBar->SetStatusText( wxEmptyString, 5 );
		g_StatusBar->SetStatusText( wxEmptyString, 6 );
		g_StatusBar->Update(); // repaint immediately
	}
	else
	{
		// check the title is changed or not
		int selid = GetIdByEdit( madedit );
		wxString oldtitle = g_MainFrame->m_Notebook->GetPageText( selid );
		wxString filename = madedit->GetFileName(), title;

		if( !filename.IsEmpty() )
		{
			wxFileName fn( filename );
			title = fn.GetFullName();
		}
		else
		{
			title = oldtitle;
		}

		if( madedit->IsModified() )
		{
			if( title[title.Len() - 1] != wxT( '*' ) )
			{ title += wxT( '*' ); }

			if( filename.IsEmpty() )
			{ filename = title; }
			else
			{ filename += wxT( '*' ); }
		}
		else
		{
			if( title[title.Len() - 1] == wxT( '*' ) )
			{ title.Truncate( title.Len() - 1 ); }
		}

		if( title != oldtitle )
		{
			g_MainFrame->m_Notebook->SetPageText( selid, title );
		}

		if( madedit == g_ActiveMadEdit )
		{
			if( filename.IsEmpty() )
			{ filename = title; }

			g_MainFrame->SetTitle( wxString( wxT( "MadEdit-Mod - [" ) ) + filename + wxString( wxT( "] " ) ) );
			wxString enc = madedit->GetEncodingName();

			if( madedit->HasBOM() )
			{
				static wxString bom( wxT( ".BOM" ) );
				enc += bom;
			}

			switch( madedit->GetNewLineType() )
			{
			case nltDOS:
				{
					static wxString xdos( wxT( ".DOS" ) );
					enc += xdos;
				}
				break;

			case nltUNIX:
				{
					static wxString xunix( wxT( ".UNIX" ) );
					enc += xunix;
				}
				break;

			case nltMAC:
				{
					static wxString xmac( wxT( ".MAC" ) );
					enc += xmac;
				}
				break;

			default:
				break;
			}

			g_StatusBar->SetStatusText( enc, 4 );

			if( madedit->IsReadOnly() )
			{
				static wxString rostr( _( "ReadOnly" ) );
				g_StatusBar->SetStatusText( rostr, 5 );
			}
			else
			{
				g_StatusBar->SetStatusText( wxEmptyString, 5 );
			}

			if( madedit->GetInsertMode() )
			{
				static wxString insstr( _( "INS" ) );
				g_StatusBar->SetStatusText( insstr, 6 );
			}
			else
			{
				static wxString ovrstr( _( "OVR" ) );
				g_StatusBar->SetStatusText( ovrstr, 6 );
			}

			g_StatusBar->Update(); // repaint immediately
			/*if( g_SearchReplaceDialog != NULL )
			{
			    g_SearchReplaceDialog->UpdateCheckBoxByCBHex( g_SearchReplaceDialog->WxCheckBoxFindHex->GetValue() );
			}

			if( g_SearchReplaceDialog != NULL )
			{
			    g_SearchReplaceDialog->UpdateCheckBoxByCBHex( g_SearchReplaceDialog->WxCheckBoxFindHex->GetValue() );
			}*/
			g_ActiveMadEdit->Refresh( false );
		}
	}
}

void OnEditActivate( MadEdit *madedit )
{
	if( g_SearchReplaceDialog && g_SearchReplaceDialog->IsShown() )
	{
		g_SearchReplaceDialog->SetTransparency();
		return;
	}

	if( g_FindInFilesDialog && g_FindInFilesDialog->IsShown() )
	{
		return;
	}
}

void OnEditToggleWindow( MadEdit *madedit )
{
	wxCommandEvent e( 0, 0 );
	g_MainFrame->OnWindowToggleWindow( e );
}

void OnEditMouseRightUp( MadEdit *madedit )
{
	//wxPoint pt=wxGetMousePosition();
	//pt=g_MainFrame->m_Notebook->ScreenToClient(pt);
	//g_MainFrame->PopupMenu(g_Menu_Edit);//, pt);
	vector<wxMenuItem *> spellItems;

	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode && g_ActiveMadEdit->GetSpellCheckStatus() )
	{
		wxString misspelledStr;
		shared_ptr<wxSpellCheckEngineInterface> & spellChecker = g_ActiveMadEdit->GetSpellChecker();
		g_ActiveMadEdit->GetWordFromCaretPos( misspelledStr );
		size_t count = 0;

		if( !spellChecker->IsSpellingOk( misspelledStr ) )
		{
			g_SpellSuggestions.Clear();
			g_SpellSuggestions = spellChecker->GetSuggestions( misspelledStr );
			count = g_SpellSuggestions.GetCount();

			if( count )
			{
				for( size_t i = 0; i < count; ++i )
				{
					spellItems.push_back( g_Menu_EditPop->Insert( i, menuSpellOption1 + i, g_SpellSuggestions[i] ) );
				}

				spellItems.push_back( g_Menu_EditPop->InsertSeparator( count++ ) );
			}

			wxString label = _( "Ignore '" ) + misspelledStr + _( "' for this session" );
			spellItems.push_back( g_Menu_EditPop->Insert( count++, menuSpellIgnore, label ) );

			if( SpellCheckerManager::Instance().GetEnablePersonalDictionary() )
			{
				label = _( "Add '" ) + misspelledStr + _( "' to dictionary" );
				spellItems.push_back( g_Menu_EditPop->Insert( count++, menuSpellAdd2Dict, label ) );
			}

			spellItems.push_back( g_Menu_EditPop->InsertSeparator( count++ ) );
		}
		else
			if( spellChecker->IsWordInPersonalDictionary( misspelledStr ) )
			{
				wxString label = _( "Remove '" ) + misspelledStr + _( "' from dictionary" );
				spellItems.push_back( g_Menu_EditPop->Insert( count++, menuSpellRemoveFromDict, label ) );
				spellItems.push_back( g_Menu_EditPop->InsertSeparator( count++ ) );
			}
	}

	g_MainFrame->PopupMenu( g_Menu_EditPop ); //Fixe for the assertion in debug
	vector<wxMenuItem *>::iterator it = spellItems.begin();

	while( it != spellItems.end() )
	{
		g_Menu_EditPop->Delete( *it );
		++it;
	}
}


void UpdateMenus()
{
	g_Menu_File->UpdateUI();
	g_Menu_Edit->UpdateUI();
	g_Menu_Search->UpdateUI();
	g_Menu_View->UpdateUI();
	g_Menu_MadMacro->UpdateUI();
	g_Menu_Tools->UpdateUI();
	g_Menu_Window->UpdateUI();
	g_Menu_Help->UpdateUI();
}

void HideModalessDialogs()
{
	if( g_SearchReplaceDialog )
	{
		g_SearchReplaceDialog->Show( false );
	}

	if( g_FindInFilesDialog )
	{
		g_FindInFilesDialog->Show( false );
	}
}

//---------------------------------------------------------------------------

// enum & sort the facenames
class MadFontEnumerator : public wxFontEnumerator
{
	wxArrayString m_facenames_lowercase;
public:

	virtual bool OnFacename( const wxString& facename ) {
		size_t count = m_facenames_lowercase.Count();

		if( count == 0 ) {
			g_FontNames.Add( facename );
			m_facenames_lowercase.Add( facename.Lower() );
		}
		else {
			wxString lname;
			size_t i = 0;

			for( ; i < count; ++i ) {
				//lname=facename.Lower();
				lname = MadStrLower( facename );

				if( lname < m_facenames_lowercase[i] ) { break; }
			}

			g_FontNames.Insert( facename, i );
			m_facenames_lowercase.Insert( lname, i );
		}

		return true;
	}

};

//----------------------------------------------------------------------------
// MadEditFrame
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate Block.
// Code added in  other places will be removed by wx-dvcpp
////Event Table Start
BEGIN_EVENT_TABLE( MadEditFrame, wxFrame )
	////Manual Code Start
	//EVT_SIZE(MadEditFrame::OnSize)
	EVT_AUINOTEBOOK_PAGE_CHANGING( ID_NOTEBOOK, MadEditFrame::OnNotebookPageChanging )
	EVT_AUINOTEBOOK_PAGE_CHANGED( ID_NOTEBOOK, MadEditFrame::OnNotebookPageChanged )
	EVT_AUINOTEBOOK_PAGE_CLOSE( ID_NOTEBOOK, MadEditFrame::OnNotebookPageClosing )
	EVT_AUINOTEBOOK_TAB_RIGHT_UP( ID_NOTEBOOK, MadEditFrame::OnNotebookPageRightUp )
	//EVT_AUINOTEBOOK_PAGE_CLOSE(ID_NOTEBOOK, MadEditFrame::OnNotebookPageClosed)
	//EVT_CHAR(MadEditFrame::OnChar)
	// file
	EVT_ACTIVATE( MadEditFrame::OnActivate )
	EVT_UPDATE_UI( menuSave, MadEditFrame::OnUpdateUI_MenuCheckWritable )
	EVT_UPDATE_UI( menuSaveAs, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuSaveAll, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuReload, MadEditFrame::OnUpdateUI_MenuFileReload )
	EVT_UPDATE_UI( menuClose, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuCloseAll, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuCloseAllButThis, MadEditFrame::OnUpdateUI_MenuWindow_CheckCount )
	EVT_UPDATE_UI( menuCloseAllToTheLeft, MadEditFrame::OnUpdateUI_MenuWindow_CheckCount )
	EVT_UPDATE_UI( menuCloseAllToTheRight, MadEditFrame::OnUpdateUI_MenuWindow_CheckCount )
	EVT_UPDATE_UI( menuPrintPreview, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuPrint, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuRecentFiles, MadEditFrame::OnUpdateUI_MenuFileRecentFiles )
	EVT_UPDATE_UI( menuToggleReadOnly, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	// edit
	EVT_UPDATE_UI( menuUndo, MadEditFrame::OnUpdateUI_MenuEditUndo )
	EVT_UPDATE_UI( menuRedo, MadEditFrame::OnUpdateUI_MenuEditRedo )
	EVT_UPDATE_UI( menuCut, MadEditFrame::OnUpdateUI_MenuEditCut )
	EVT_UPDATE_UI( menuCopy, MadEditFrame::OnUpdateUI_MenuEditCopy )
	EVT_UPDATE_UI( menuPaste, MadEditFrame::OnUpdateUI_MenuEditPaste )
	EVT_UPDATE_UI( menuDelete, MadEditFrame::OnUpdateUI_MenuEditDelete )
	EVT_UPDATE_UI( menuCutLine, MadEditFrame::OnUpdateUI_Menu_CheckWritableTextFile )
	EVT_UPDATE_UI( menuDeleteLine, MadEditFrame::OnUpdateUI_Menu_CheckWritableTextFile )
	EVT_UPDATE_UI( menuSelectAll, MadEditFrame::OnUpdateUI_Menu_CheckSize )
	EVT_UPDATE_UI( menuStartEndSelction, MadEditFrame::OnUpdateUI_MenuEditStartEndSelction )
	EVT_UPDATE_UI( menuInsertTabChar, MadEditFrame::OnUpdateUI_Menu_CheckWritableTextFile )
	EVT_UPDATE_UI( menuInsertDateTime, MadEditFrame::OnUpdateUI_Menu_CheckWritableTextFile )
	EVT_UPDATE_UI( menuSortAscending, MadEditFrame::OnUpdateUI_Menu_CheckWritableTextFile )
	EVT_UPDATE_UI( menuSortDescending, MadEditFrame::OnUpdateUI_Menu_CheckWritableTextFile )
	EVT_UPDATE_UI( menuSortAscendingCase, MadEditFrame::OnUpdateUI_Menu_CheckWritableTextFile )
	EVT_UPDATE_UI( menuSortDescendingCase, MadEditFrame::OnUpdateUI_Menu_CheckWritableTextFile )
	EVT_UPDATE_UI( menuSortByOptions, MadEditFrame::OnUpdateUI_Menu_CheckWritableTextFile )
	EVT_UPDATE_UI( menuSortOptions, MadEditFrame::OnUpdateUI_Menu_CheckWritableTextFile )
	EVT_UPDATE_UI( menuSort, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuAdvanced, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuCopyAsHexString, MadEditFrame::OnUpdateUI_MenuEditCopyAsHexString )
	EVT_UPDATE_UI( menuCopyAsHexStringWithSpace, MadEditFrame::OnUpdateUI_MenuEditCopyAsHexString )
	EVT_UPDATE_UI( menuCopyRevertHex, MadEditFrame::OnUpdateUI_MenuEditCopyAsHexString )
	EVT_UPDATE_UI( menuIncreaseIndent, MadEditFrame::OnUpdateUI_MenuIndent )
	EVT_UPDATE_UI( menuDecreaseIndent, MadEditFrame::OnUpdateUI_MenuIndent )
	EVT_UPDATE_UI( menuComment, MadEditFrame::OnUpdateUI_MenuComment )
	EVT_UPDATE_UI( menuUncomment, MadEditFrame::OnUpdateUI_MenuComment )
	EVT_UPDATE_UI( menuWordWrapToNewLine, MadEditFrame::OnUpdateUI_Menu_CheckTextFileSize )
	EVT_UPDATE_UI( menuNewLineToWordWrap, MadEditFrame::OnUpdateUI_Menu_CheckTextFileSize )
	EVT_UPDATE_UI( menuToUpperCase, MadEditFrame::OnUpdateUI_MenuEdit_CheckSelSize )
	EVT_UPDATE_UI( menuToLowerCase, MadEditFrame::OnUpdateUI_MenuEdit_CheckSelSize )
	EVT_UPDATE_UI( menuInvertCase, MadEditFrame::OnUpdateUI_MenuEdit_CheckSelSize )
	EVT_UPDATE_UI( menuCapitalize, MadEditFrame::OnUpdateUI_MenuEdit_CheckSelSize )
	EVT_UPDATE_UI( menuToHalfWidth, MadEditFrame::OnUpdateUI_MenuEdit_CheckSelSize )
	EVT_UPDATE_UI( menuToHalfWidthByOptions, MadEditFrame::OnUpdateUI_MenuEdit_CheckSelSize )
	EVT_UPDATE_UI( menuToFullWidth, MadEditFrame::OnUpdateUI_MenuEdit_CheckSelSize )
	EVT_UPDATE_UI( menuToFullWidthByOptions, MadEditFrame::OnUpdateUI_MenuEdit_CheckSelSize )
	EVT_UPDATE_UI( menuTabToSpace, MadEditFrame::OnUpdateUI_MenuEdit_CheckSelSize )
	EVT_UPDATE_UI( menuSpaceToTab, MadEditFrame::OnUpdateUI_MenuEdit_CheckSelSize )
	EVT_UPDATE_UI( menuTrimTrailingSpaces, MadEditFrame::OnUpdateUI_Menu_CheckWritableTextFile )
	EVT_UPDATE_UI( menuTrimLeadingSpaces, MadEditFrame::OnUpdateUI_Menu_CheckWritableTextFile )
	EVT_UPDATE_UI( menuDeleteEmptyLines, MadEditFrame::OnUpdateUI_Menu_CheckWritableTextFile )
	EVT_UPDATE_UI( menuDeleteEmptyLinesWithSpaces, MadEditFrame::OnUpdateUI_Menu_CheckWritableTextFile )
	EVT_UPDATE_UI( menuJoinLines, MadEditFrame::OnUpdateUI_Menu_JoinLines )
	EVT_UPDATE_UI( menuInsertNumbers, MadEditFrame::OnUpdateUI_Menu_CheckColumnMode )
	EVT_UPDATE_UI( menuColumnAlignLeft, MadEditFrame::OnUpdateUI_Menu_CheckColumnMode )
	EVT_UPDATE_UI( menuColumnAlignRight, MadEditFrame::OnUpdateUI_Menu_CheckColumnMode )
	EVT_UPDATE_UI( menuBookmark, MadEditFrame::OnUpdateUI_MenuEditCheckBookmark )
	EVT_UPDATE_UI( menuBookmarkCopy, MadEditFrame::OnUpdateUI_MenuEditCheckBookmark )
	EVT_UPDATE_UI( menuBookmarkCut, MadEditFrame::OnUpdateUI_MenuEditCheckBookmarkWritable )
	EVT_UPDATE_UI( menuBookmarkDel, MadEditFrame::OnUpdateUI_MenuEditCheckBookmarkWritable )
	EVT_UPDATE_UI( menuBookmarkDelUnmarked, MadEditFrame::OnUpdateUI_MenuEditCheckBookmarkWritable )
	EVT_UPDATE_UI( menuBookmarkReplace, MadEditFrame::OnUpdateUI_MenuEditCheckBookmarkWritable )
	// search
	EVT_UPDATE_UI( menuFind, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuFindNext, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuFindPrevious, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuShowQuickFindBar, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuReplace, MadEditFrame::OnUpdateUI_MenuCheckWritable )
	EVT_UPDATE_UI( menuGoToLine, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuGoToPosition, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuLeftBrace, MadEditFrame::OnUpdateUI_MenuSearchGoToBrace )
	EVT_UPDATE_UI( menuRightBrace, MadEditFrame::OnUpdateUI_MenuSearchGoToBrace )
	EVT_UPDATE_UI( menuToggleBookmark, MadEditFrame::OnUpdateUI_Menu_CheckTextFile )
	EVT_UPDATE_UI( menuGotoNextBookmark, MadEditFrame::OnUpdateUI_MenuEditCheckBookmark )
	EVT_UPDATE_UI( menuGotoPreviousBookmark, MadEditFrame::OnUpdateUI_MenuEditCheckBookmark )
	EVT_UPDATE_UI( menuClearAllBookmarks, MadEditFrame::OnUpdateUI_MenuEditCheckBookmark )
	// view
	EVT_UPDATE_UI( menuEncoding, MadEditFrame::OnUpdateUI_MenuViewEncoding )
	EVT_UPDATE_UI( menuSyntax, MadEditFrame::OnUpdateUI_MenuViewSyntax )
	EVT_UPDATE_UI( menuFontName, MadEditFrame::OnUpdateUI_MenuViewFontName )
	EVT_UPDATE_UI( menuFontSize, MadEditFrame::OnUpdateUI_MenuViewFontSize )
	EVT_UPDATE_UI( menuSetFont, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuFixedWidthMode, MadEditFrame::OnUpdateUI_MenuViewFixedWidthMode )
	EVT_UPDATE_UI( menuTabColumn, MadEditFrame::OnUpdateUI_MenuViewTabColumn )
	EVT_UPDATE_UI( menuLineSpacing, MadEditFrame::OnUpdateUI_MenuViewLineSpacing )
	EVT_UPDATE_UI( menuNoWrap, MadEditFrame::OnUpdateUI_MenuViewNoWrap )
	EVT_UPDATE_UI( menuWrapByWindow, MadEditFrame::OnUpdateUI_MenuViewWrapByWindow )
	EVT_UPDATE_UI( menuWrapByColumn, MadEditFrame::OnUpdateUI_MenuViewWrapByColumn )
	EVT_UPDATE_UI( menuDisplayLineNumber, MadEditFrame::OnUpdateUI_MenuViewDisplayLineNumber )
	EVT_UPDATE_UI( menuDisplayBookmark, MadEditFrame::OnUpdateUI_MenuViewDisplayBookmark )
	EVT_UPDATE_UI( menuDisplay80ColHint, MadEditFrame::OnUpdateUI_MenuViewDisplay80ColHint )
	EVT_UPDATE_UI( menuShowEndOfLine, MadEditFrame::OnUpdateUI_MenuViewShowEndOfLine )
	EVT_UPDATE_UI( menuShowTabChar, MadEditFrame::OnUpdateUI_MenuViewShowTabChar )
	EVT_UPDATE_UI( menuShowSpaceChar, MadEditFrame::OnUpdateUI_MenuViewShowSpaceChar )
	EVT_UPDATE_UI( menuShowAllChars, MadEditFrame::OnUpdateUI_MenuViewShowAllChars )
	EVT_UPDATE_UI( menuViewRightToLeft, MadEditFrame::OnUpdateUI_MenuViewRightToLeft )
	EVT_UPDATE_UI( menuMarkActiveLine, MadEditFrame::OnUpdateUI_MenuViewMarkActiveLine )
	EVT_UPDATE_UI( menuMarkBracePair, MadEditFrame::OnUpdateUI_MenuViewMarkBracePair )
	EVT_UPDATE_UI( menuTextMode, MadEditFrame::OnUpdateUI_MenuViewTextMode )
	EVT_UPDATE_UI( menuColumnMode, MadEditFrame::OnUpdateUI_MenuViewColumnMode )
	EVT_UPDATE_UI( menuHexMode, MadEditFrame::OnUpdateUI_MenuViewHexMode )
	EVT_UPDATE_UI( menuPreview, MadEditFrame::OnUpdateUI_MenuViewPreview )
	EVT_UPDATE_UI_RANGE( menuPreview1, menuPreview16, MadEditFrame::OnUpdateUI_MenuViewPreviewList )
	EVT_UPDATE_UI( menuSpellChecker, MadEditFrame::OnUpdateUI_MenuViewSpellChecker )
	EVT_UPDATE_UI( menuSpellIgnore, MadEditFrame::OnUpdateUI_MenuSpellIgnore )
	EVT_UPDATE_UI( menuSpellAdd2Dict, MadEditFrame::OnUpdateUI_MenuSpellAdd2Dict )
	EVT_UPDATE_UI( menuSpellRemoveFromDict, MadEditFrame::OnUpdateUI_MenuSpellRemoveFromDict )
	EVT_UPDATE_UI( menuToolBars, MadEditFrame::OnUpdateUI_MenuViewToolbars )
	EVT_UPDATE_UI( menuToolBarsToggleAll, MadEditFrame::OnUpdateUI_MenuViewToolbarsToggleAll )
	EVT_UPDATE_UI_RANGE( menuToolBar1, menuToolBar99, MadEditFrame::OnUpdateUI_MenuViewToolbarList )
	// tools
	EVT_UPDATE_UI( menuByteOrderMark, MadEditFrame::OnUpdateUI_MenuToolsByteOrderMark )
	EVT_UPDATE_UI( menuMadMacro, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuRunTempMacro, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuRunMacroFile, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuEditMacroFile, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuStartRecMacro, MadEditFrame::OnUpdateUI_MenuToolsStartRecMacro )
	EVT_UPDATE_UI( menuStopRecMacro, MadEditFrame::OnUpdateUI_MenuToolsStopRecMacro )
	EVT_UPDATE_UI( menuPlayRecMacro, MadEditFrame::OnUpdateUI_MenuToolsPlayRecMacro )
	EVT_UPDATE_UI( menuSaveRecMacro, MadEditFrame::OnUpdateUI_MenuToolsSaveRecMacro )
	EVT_UPDATE_UI( menuMadScriptList, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	EVT_UPDATE_UI( menuInsertNewLineChar, MadEditFrame::OnUpdateUI_MenuToolsInsertNewLineChar )
	EVT_UPDATE_UI( menuNewLineChar, MadEditFrame::OnUpdateUI_MenuCheckWritable )
	EVT_UPDATE_UI( menuConvertToDOS, MadEditFrame::OnUpdateUI_MenuCheckWritable )
	EVT_UPDATE_UI( menuConvertToMAC, MadEditFrame::OnUpdateUI_MenuCheckWritable )
	EVT_UPDATE_UI( menuConvertToUNIX, MadEditFrame::OnUpdateUI_MenuCheckWritable )
	EVT_UPDATE_UI( menuConvertEncoding, MadEditFrame::OnUpdateUI_MenuToolsConvertEncoding )
	EVT_UPDATE_UI( menuSimp2TradChinese, MadEditFrame::OnUpdateUI_MenuToolsConvertEncoding )
	EVT_UPDATE_UI( menuTrad2SimpChinese, MadEditFrame::OnUpdateUI_MenuToolsConvertEncoding )
	EVT_UPDATE_UI( menuKanji2TradChinese, MadEditFrame::OnUpdateUI_MenuToolsConvertEncoding )
	EVT_UPDATE_UI( menuKanji2SimpChinese, MadEditFrame::OnUpdateUI_MenuToolsConvertEncoding )
	EVT_UPDATE_UI( menuChinese2Kanji, MadEditFrame::OnUpdateUI_MenuToolsConvertEncoding )
	EVT_UPDATE_UI( menuMarkdown2Html, MadEditFrame::OnUpdateUI_MenuCheckWritable )
	EVT_UPDATE_UI( menuHtml2PlainText, MadEditFrame::OnUpdateUI_MenuCheckWritable )
	EVT_UPDATE_UI( menuAstyleFormat, MadEditFrame::OnUpdateUI_MenuCheckWritable )
	EVT_UPDATE_UI( menuXMLFormat, MadEditFrame::OnUpdateUI_MenuCheckWritable )
	EVT_UPDATE_UI( menuWordCount, MadEditFrame::OnUpdateUI_MenuFile_CheckCount )
	// window
	EVT_UPDATE_UI( menuToggleWindow, MadEditFrame::OnUpdateUI_MenuWindow_CheckCount )
	EVT_UPDATE_UI( menuNextWindow, MadEditFrame::OnUpdateUI_MenuWindow_CheckCount )
	EVT_UPDATE_UI( menuPreviousWindow, MadEditFrame::OnUpdateUI_MenuWindow_CheckCount )
	// file
	EVT_MENU( menuNew, MadEditFrame::OnFileNew )
	EVT_MENU( menuOpen, MadEditFrame::OnFileOpen )
	EVT_MENU( menuSave, MadEditFrame::OnFileSave )
	EVT_MENU( menuSaveAs, MadEditFrame::OnFileSaveAs )
	EVT_MENU( menuSaveAll, MadEditFrame::OnFileSaveAll )
	EVT_MENU( menuReload, MadEditFrame::OnFileReload )
	EVT_MENU( menuClose, MadEditFrame::OnFileClose )
	EVT_MENU( menuCloseAll, MadEditFrame::OnFileCloseAll )
	EVT_MENU( menuCloseAllButThis, MadEditFrame::OnFileCloseAllButThis )
	EVT_MENU( menuCloseAllToTheLeft, MadEditFrame::OnFileCloseAllToTheLeft )
	EVT_MENU( menuCloseAllToTheRight, MadEditFrame::OnFileCloseAllToTheRight )
	EVT_MENU( menuPageSetup, MadEditFrame::OnFilePageSetup )
	EVT_MENU( menuPrintPreview, MadEditFrame::OnFilePrintPreview )
	EVT_MENU( menuPrint, MadEditFrame::OnFilePrint )
	EVT_MENU_RANGE( wxID_FILE1, wxID_FILE9, MadEditFrame::OnFileRecentFile )
	EVT_MENU( menuExit, MadEditFrame::OnFileExit )
	EVT_MENU( menuCopyFilePath, MadEditFrame::OnCopyFilePath )
	EVT_MENU( menuCopyFileName, MadEditFrame::OnCopyFileName )
	EVT_MENU( menuCopyFileDir, MadEditFrame::OnCopyFileDir )
	EVT_MENU( menuToggleReadOnly, MadEditFrame::OnFileToggleReadOnly )
	// edit
	EVT_MENU( menuUndo, MadEditFrame::OnEditUndo )
	EVT_MENU( menuRedo, MadEditFrame::OnEditRedo )
	EVT_MENU( menuCut, MadEditFrame::OnEditCut )
	EVT_MENU( menuCopy, MadEditFrame::OnEditCopy )
	EVT_MENU( menuPaste, MadEditFrame::OnEditPaste )
	EVT_MENU( menuDelete, MadEditFrame::OnEditDelete )
	EVT_MENU( menuCutLine, MadEditFrame::OnEditCutLine )
	EVT_MENU( menuDeleteLine, MadEditFrame::OnEditDeleteLine )
	EVT_MENU( menuSelectAll, MadEditFrame::OnEditSelectAll )
	EVT_MENU( menuStartEndSelction, MadEditFrame::OnEditStartEndSelction )
	EVT_MENU( menuInsertTabChar, MadEditFrame::OnEditInsertTabChar )
	EVT_MENU( menuInsertDateTime, MadEditFrame::OnEditInsertDateTime )
	EVT_MENU( menuSortAscending, MadEditFrame::OnEditSortAscending )
	EVT_MENU( menuSortDescending, MadEditFrame::OnEditSortDescending )
	EVT_MENU( menuSortAscendingCase, MadEditFrame::OnEditSortAscendingCase )
	EVT_MENU( menuSortDescendingCase, MadEditFrame::OnEditSortDescendingCase )
	EVT_MENU( menuSortByOptions, MadEditFrame::OnEditSortByOptions )
	EVT_MENU( menuSortOptions, MadEditFrame::OnEditSortOptions )
	EVT_MENU( menuCopyAsHexString, MadEditFrame::OnEditCopyAsHexString )
	EVT_MENU( menuCopyAsHexStringWithSpace, MadEditFrame::OnEditCopyAsHexStringWithSpace )
	EVT_MENU( menuCopyRevertHex, MadEditFrame::OnEditCopyRevertHex )
	EVT_MENU( menuIncreaseIndent, MadEditFrame::OnEditIncIndent )
	EVT_MENU( menuDecreaseIndent, MadEditFrame::OnEditDecIndent )
	EVT_MENU( menuComment, MadEditFrame::OnEditComment )
	EVT_MENU( menuUncomment, MadEditFrame::OnEditUncomment )
	EVT_MENU( menuWordWrapToNewLine, MadEditFrame::OnEditWordWrapToNewLine )
	EVT_MENU( menuNewLineToWordWrap, MadEditFrame::OnEditNewLineToWordWrap )
	EVT_MENU( menuToUpperCase, MadEditFrame::OnEditToUpperCase )
	EVT_MENU( menuToLowerCase, MadEditFrame::OnEditToLowerCase )
	EVT_MENU( menuInvertCase, MadEditFrame::OnEditInvertCase )
	EVT_MENU( menuCapitalize, MadEditFrame::OnEditCapitalize )
	EVT_MENU( menuToHalfWidth, MadEditFrame::OnEditToHalfWidth )
	EVT_MENU( menuToHalfWidthByOptions, MadEditFrame::OnEditToHalfWidthByOptions )
	EVT_MENU( menuToFullWidth, MadEditFrame::OnEditToFullWidth )
	EVT_MENU( menuToFullWidthByOptions, MadEditFrame::OnEditToFullWidthByOptions )
	EVT_MENU( menuTabToSpace, MadEditFrame::OnEditTabToSpace )
	EVT_MENU( menuSpaceToTab, MadEditFrame::OnEditSpaceToTab )
	EVT_MENU( menuTrimTrailingSpaces, MadEditFrame::OnEditTrimTrailingSpaces )
	EVT_MENU( menuTrimLeadingSpaces, MadEditFrame::OnEditTrimLeadingSpaces )
	EVT_MENU( menuDeleteEmptyLines, MadEditFrame::OnEditDeleteEmptyLines )
	EVT_MENU( menuDeleteEmptyLinesWithSpaces, MadEditFrame::OnEditDeleteEmptyLinesWithSpaces )
	EVT_MENU( menuJoinLines, MadEditFrame::OnEditJoinLines )
	EVT_MENU( menuInsertNumbers, MadEditFrame::OnEditInsertNumbers )
	EVT_MENU( menuColumnAlignLeft, MadEditFrame::OnEditColumnAlignLeft )
	EVT_MENU( menuColumnAlignRight, MadEditFrame::OnEditColumnAlignRight )
	EVT_MENU_RANGE( menuSpellOption1, menuSpellOption99, MadEditFrame::OnEditSpellCheck )
	EVT_MENU( menuBookmarkCopy, MadEditFrame::OnEditBookmarkCopy )
	EVT_MENU( menuBookmarkCut, MadEditFrame::OnEditBookmarkCut )
	EVT_MENU( menuBookmarkDel, MadEditFrame::OnEditBookmarkDel )
	EVT_MENU( menuBookmarkDelUnmarked, MadEditFrame::OnEditBookmarkDelUnmarked )
	EVT_MENU( menuBookmarkReplace, MadEditFrame::OnEditBookmarkReplace )
	// search
	EVT_MENU( menuFind, MadEditFrame::OnSearchFind )
	EVT_MENU( menuFindNext, MadEditFrame::OnSearchFindNext )
	EVT_MENU( menuFindPrevious, MadEditFrame::OnSearchFindPrevious )
	EVT_MENU( menuQuickFindNext, MadEditFrame::OnSearchQuickFindNext )
	EVT_MENU( menuQuickFindPrevious, MadEditFrame::OnSearchQuickFindPrevious )
	EVT_MENU( menuShowQuickFindBar, MadEditFrame::OnShowSearchQuickFindBar )
	EVT_MENU( menuReplace, MadEditFrame::OnSearchReplace )
	EVT_MENU( menuFindInFiles, MadEditFrame::OnSearchFindInFiles )
	EVT_MENU( menuShowFindInFilesResults, MadEditFrame::OnSearchShowFindInFilesResults )
	EVT_MENU( menuGoToLine, MadEditFrame::OnSearchGoToLine )
	EVT_MENU( menuGoToPosition, MadEditFrame::OnSearchGoToPosition )
	EVT_MENU( menuLeftBrace, MadEditFrame::OnSearchGoToLeftBrace )
	EVT_MENU( menuRightBrace, MadEditFrame::OnSearchGoToRightBrace )
	EVT_MENU( menuToggleBookmark, MadEditFrame::OnSearchToggleBookmark )
	EVT_MENU( menuGotoNextBookmark, MadEditFrame::OnSearchGotoNextBookmark )
	EVT_MENU( menuGotoPreviousBookmark, MadEditFrame::OnSearchGotoPreviousBookmark )
	EVT_MENU( menuClearAllBookmarks, MadEditFrame::OnSearchClearAllBookmarks )
	// view
	EVT_MENU_RANGE( menuEncoding1, menuEncoding99, MadEditFrame::OnViewEncoding )
	EVT_MENU_RANGE( menuRecentEncoding1, menuRecentEncoding9, MadEditFrame::OnViewRecentEncoding )
	EVT_MENU_RANGE( menuSyntax1, menuSyntax199, MadEditFrame::OnViewSyntax )
	EVT_MENU_RANGE( menuFontName1, menuFontName999, MadEditFrame::OnViewFontName )
	EVT_MENU_RANGE( menuRecentFont1, menuRecentFont9, MadEditFrame::OnViewRecentFont )
	EVT_MENU_RANGE( menuFontSize1, menuFontSize99, MadEditFrame::OnViewFontSize )
	EVT_MENU( menuSetFont, MadEditFrame::OnViewSetFont )
	EVT_MENU( menuFixedWidthMode, MadEditFrame::OnViewFixedWidthMode )
	EVT_MENU_RANGE( menuTabColumn1, menuTabColumn16, MadEditFrame::OnViewTabColumn )
	EVT_MENU_RANGE( menuPreview1, menuPreview16, MadEditFrame::OnViewPreview )
	EVT_MENU( menuRefreshPreview, MadEditFrame::OnRefreshPreview )
	EVT_MENU( menuClosePreview, MadEditFrame::OnClosePreview )
	EVT_MENU_RANGE( menuLineSpacing100, menuLineSpacing250, MadEditFrame::OnViewLineSpacing )
	EVT_MENU( menuNoWrap, MadEditFrame::OnViewNoWrap )
	EVT_MENU( menuWrapByWindow, MadEditFrame::OnViewWrapByWindow )
	EVT_MENU( menuWrapByColumn, MadEditFrame::OnViewWrapByColumn )
	EVT_MENU( menuDisplayLineNumber, MadEditFrame::OnViewDisplayLineNumber )
	EVT_MENU( menuDisplayBookmark, MadEditFrame::OnViewDisplayBookmark )
	EVT_MENU( menuDisplay80ColHint, MadEditFrame::OnViewDisplay80ColHint )
	EVT_MENU( menuShowEndOfLine, MadEditFrame::OnViewShowEndOfLine )
	EVT_MENU( menuShowTabChar, MadEditFrame::OnViewShowTabChar )
	EVT_MENU( menuShowSpaceChar, MadEditFrame::OnViewShowSpaceChar )
	EVT_MENU( menuShowAllChars, MadEditFrame::OnViewShowAllChars )
	EVT_MENU( menuViewRightToLeft, MadEditFrame::OnViewRightToLeft )
	EVT_MENU( menuMarkActiveLine, MadEditFrame::OnViewMarkActiveLine )
	EVT_MENU( menuMarkBracePair, MadEditFrame::OnViewMarkBracePair )
	EVT_MENU( menuTextMode, MadEditFrame::OnViewTextMode )
	EVT_MENU( menuColumnMode, MadEditFrame::OnViewColumnMode )
	EVT_MENU( menuHexMode, MadEditFrame::OnViewHexMode )
	EVT_MENU( menuSpellChecker, MadEditFrame::OnViewSpellChecker )
	EVT_MENU( menuSpellIgnore, MadEditFrame::OnSpellCheckIgnore )
	EVT_MENU( menuSpellAdd2Dict, MadEditFrame::OnSpellAdd2Dict )
	EVT_MENU( menuSpellRemoveFromDict, MadEditFrame::OnSpellCheckRemoveFromDict )
	EVT_MENU( menuToolBarsToggleAll, MadEditFrame::OnViewToolBarsToggleAll )
	EVT_MENU_RANGE( menuToolBar1, menuToolBar99, MadEditFrame::OnViewToolbars )
	// tools
	EVT_MENU( menuOptions, MadEditFrame::OnToolsOptions )
	EVT_MENU( menuHighlighting, MadEditFrame::OnToolsHighlighting )
#ifdef __WXMSW__
	EVT_MENU( menuFileAssociation, MadEditFrame::OnToolsFileAssociation )
#endif
	EVT_MENU( menuPurgeHistories, MadEditFrame::OnToolsPurgeHistories )
	EVT_MENU( menuRunTempMacro, MadEditFrame::OnToolsRunTempMacro )
	EVT_MENU( menuRunMacroFile, MadEditFrame::OnToolsRunMacroFile )
	EVT_MENU( menuStartRecMacro, MadEditFrame::OnToolsStartRecMacro )
	EVT_MENU( menuStopRecMacro, MadEditFrame::OnToolsStopRecMacro )
	EVT_MENU( menuPlayRecMacro, MadEditFrame::OnToolsPlayRecMacro )
	EVT_MENU( menuSaveRecMacro, MadEditFrame::OnToolsSaveRecMacro )
	EVT_MENU( menuEditMacroFile, MadEditFrame::OnToolsEditMacroFile )
	EVT_MENU_RANGE( menuMadScrip1, menuMadScrip1000, MadEditFrame::OnToolsMadScriptList )
	EVT_MENU( menuToggleBOM, MadEditFrame::OnToolsToggleBOM )
	EVT_MENU( menuConvertToDOS, MadEditFrame::OnToolsConvertToDOS )
	EVT_MENU( menuConvertToMAC, MadEditFrame::OnToolsConvertToMAC )
	EVT_MENU( menuConvertToUNIX, MadEditFrame::OnToolsConvertToUNIX )
	EVT_MENU( menuInsertDOS, MadEditFrame::OnToolsInsertDOS )
	EVT_MENU( menuInsertMAC, MadEditFrame::OnToolsInsertMAC )
	EVT_MENU( menuInsertUNIX, MadEditFrame::OnToolsInsertUNIX )
	EVT_MENU( menuConvertEncoding, MadEditFrame::OnToolsConvertEncoding )
	EVT_MENU( menuSimp2TradChinese, MadEditFrame::OnToolsSimp2TradChinese )
	EVT_MENU( menuTrad2SimpChinese, MadEditFrame::OnToolsTrad2SimpChinese )
	EVT_MENU( menuKanji2TradChinese, MadEditFrame::OnToolsKanji2TradChinese )
	EVT_MENU( menuKanji2SimpChinese, MadEditFrame::OnToolsKanji2SimpChinese )
	EVT_MENU( menuChinese2Kanji, MadEditFrame::OnToolsChinese2Kanji )
	EVT_MENU( menuSimp2TradClipboard, MadEditFrame::OnToolsSimp2TradClipboard )
	EVT_MENU( menuTrad2SimpClipboard, MadEditFrame::OnToolsTrad2SimpClipboard )
	EVT_MENU( menuKanji2TradClipboard, MadEditFrame::OnToolsKanji2TradClipboard )
	EVT_MENU( menuKanji2SimpClipboard, MadEditFrame::OnToolsKanji2SimpClipboard )
	EVT_MENU( menuChinese2KanjiClipboard, MadEditFrame::OnToolsChinese2KanjiClipboard )
	EVT_MENU( menuMarkdown2Html, MadEditFrame::OnToolsMarkdown2Html )
	EVT_MENU( menuHtml2PlainText, MadEditFrame::OnToolsHtml2PlainText )
	EVT_MENU( menuAstyleFormat, MadEditFrame::OnToolsAstyleFormat )
	EVT_MENU( menuXMLFormat, MadEditFrame::OnToolsXMLFormat )
	EVT_MENU( menuWordCount, MadEditFrame::OnToolsWordCount )
	// window
	EVT_MENU( menuToggleWindow, MadEditFrame::OnWindowToggleWindow )
	EVT_MENU( menuNextWindow, MadEditFrame::OnWindowNextWindow )
	EVT_MENU( menuPreviousWindow, MadEditFrame::OnWindowPreviousWindow )
	// help
	EVT_MENU( menuAbout, MadEditFrame::OnHelpAbout )
	////Manual Code End

	EVT_CLOSE( MadEditFrame::MadEditFrameClose )
	EVT_KEY_DOWN( MadEditFrame::MadEditFrameKeyDown )

	EVT_MENU( menuCopyCurResult, MadEditFrame::OnCopyCurrResult )
	EVT_MENU( menuCopyAllResults, MadEditFrame::OnCopyAllResults )
	EVT_MENU( menuResetCurResult, MadEditFrame::OnResetCurrResult )
	EVT_TEXT( ID_QUICKSEARCH, MadEditFrame::OnSearchQuickFind )
	EVT_TEXT_ENTER( ID_QUICKSEARCH, MadEditFrame::OnSearchQuickFind )
END_EVENT_TABLE()
////Event Table End



//==========================================================
// do not use wxGetTranslation() now
#undef _
#define _(s)    wxT(s)

wxAuiToolBar * g_tbSTANDARD_ptr = 0;
wxAuiToolBar * g_tbEDITOR_ptr = 0;
wxAuiToolBar * g_tbSEARCHREPLACE_ptr = 0;
wxAuiToolBar * g_tbTEXTVIEW_ptr = 0;
wxAuiToolBar * g_tbEDITMODE_ptr = 0;
wxAuiToolBar * g_tbMACRO_ptr = 0;

CommandData CommandTable[] =
{
	// file
	{ 0, 0, 0, 0, _( "&File" ), 0, wxITEM_NORMAL, 0, &g_Menu_File, 0, 0, 0, 0, false},
	{ 0, 1, menuNew,          wxT( "menuNew" ),          _( "&New File" ),         wxT( "Ctrl-N" ),       wxITEM_NORMAL,    new_xpm_idx,       0,                        _( "Create a new file" ), 0, &g_tbSTANDARD_ptr, _( "New File" ), false},
	{ 0, 1, menuOpen,         wxT( "menuOpen" ),         _( "&Open File..." ),     wxT( "Ctrl-O" ),       wxITEM_NORMAL,    fileopen_xpm_idx,  0,                        _( "Open an existing file" ), 0, &g_tbSTANDARD_ptr, _( "Open File" ), false},
	{ 0, 1, 0,                0,                       0,                      0,                   wxITEM_SEPARATOR, -1,                0,                        0, 0, 0, 0, false},
	{ 0, 1, menuSave,         wxT( "menuSave" ),         _( "&Save File" ),        wxT( "Ctrl-S" ),       wxITEM_NORMAL,    filesave_xpm_idx,  0,                        _( "Save the file" ), &g_Menu_FilePop, &g_tbSTANDARD_ptr, _( "Save File" ), false},
	{ 0, 1, menuSaveAs,       wxT( "menuSaveAs" ),       _( "Save &As..." ),       wxT( "" ),             wxITEM_NORMAL,    -1,                0,                        _( "Save the file with a new name" ), &g_Menu_FilePop, 0, 0, false},
	{ 0, 1, menuSaveAll,      wxT( "menuSaveAll" ),      _( "Sa&ve All" ),         wxT( "Ctrl-Shift-S" ), wxITEM_NORMAL,    saveall_xpm_idx,   0,                        _( "Save all files" ), &g_Menu_FilePop, &g_tbSTANDARD_ptr, _( "Save All" ), false},
	{ 0, 1, 0,                0,                       0,                      0,                   wxITEM_SEPARATOR, -1,                0,                        0, &g_Menu_FilePop, 0, 0, false},
	{ 0, 1, menuReload,       wxT( "menuReload" ),       _( "&Reload File" ),      wxT( "Ctrl-R" ),       wxITEM_NORMAL,    -1,                0,                        _( "Reload the file" ), &g_Menu_FilePop, 0, 0, false},
	{ 0, 1, 0,                0,                       0,                      0,                   wxITEM_SEPARATOR, -1,                0,                        0, &g_Menu_FilePop, 0, 0, false},
	{ 0, 1, menuClose,        wxT( "menuClose" ),        _( "&Close File" ),       wxT( "Ctrl-F4" ),      wxITEM_NORMAL,    fileclose_xpm_idx, 0,                        _( "Close the file" ), &g_Menu_FilePop, &g_tbSTANDARD_ptr, _( "Close File" ), false},
	{ 0, 1, menuCloseAll,     wxT( "menuCloseAll" ),     _( "C&lose All" ),        wxT( "" ),             wxITEM_NORMAL,    closeall_xpm_idx,  0,                        _( "Close all files" ), &g_Menu_FilePop, &g_tbSTANDARD_ptr, _( "Close All" ), true},
	{ 0, 1, menuCloseAllButThis,     wxT( "menuCloseAllButThis" ),    _( "Close All But This" ),     wxT( "" ),  wxITEM_NORMAL,    -1,         0,                        _( "Close all files but this" ), &g_Menu_FilePop, 0, 0, false},
	{ 0, 1, menuCloseAllToTheLeft,   wxT( "menuCloseAllToTheLeft" ),  _( "Close All To The Left" ),  wxT( "" ),  wxITEM_NORMAL,    -1,         0,                        _( "Close all files to the left" ), &g_Menu_FilePop, 0, 0, false},
	{ 0, 1, menuCloseAllToTheRight,  wxT( "menuCloseAllToTheRight" ), _( "Close All To The Right" ), wxT( "" ),  wxITEM_NORMAL,    -1,         0,                        _( "Close all files to the right" ), &g_Menu_FilePop, 0, 0, false},
	{ 0, 1, 0,                            0,                                   0,                                            0,                   wxITEM_SEPARATOR, -1,                0,                     0, &g_Menu_FilePop, 0, 0, false},
	{ 0, 1, menuToggleReadOnly,           wxT( "menuToggleReadOnly" ),           _( "Set/Clear ReadOnly Flag" ),                 0,                   wxITEM_NORMAL,    -1,                0,                     _( "Set/Clear ReadOnly flag of the file" ), &g_Menu_FilePop, 0, 0, false},
	{ 0, 1, 0,                0,                       0,                      0,                   wxITEM_SEPARATOR, -1,                0,                        0, &g_Menu_FilePop, 0, 0, false},
	{ 0, 1, menuPageSetup,    wxT( "menuPageSetup" ),    _( "Page Set&up..." ),    wxT( "" ),             wxITEM_NORMAL,    -1,                0,                        _( "Setup the pages for printing" ), &g_Menu_FilePop, 0, 0, false},
	{ 0, 1, menuPrintPreview, wxT( "menuPrintPreview" ), _( "Print Previe&w..." ), wxT( "" ),             wxITEM_NORMAL,    preview_xpm_idx,   0,                        _( "Preview the result of printing" ), &g_Menu_FilePop, 0, 0, false},
	{ 0, 1, menuPrint,        wxT( "menuPrint" ),        _( "&Print..." ),         wxT( "Ctrl-P" ),       wxITEM_NORMAL,    print_xpm_idx,     0,                        _( "Print the file" ), &g_Menu_FilePop, &g_tbSTANDARD_ptr, _( "Print" ), true},
	{ 0, 1, 0,                0,                       0,                      0,                   wxITEM_SEPARATOR, -1,                0,                        0, 0, 0, 0, false},
	{ 0, 1, menuRecentFiles,  wxT( "menuRecentFiles" ),  _( "Recent Files" ),      wxT( "" ),             wxITEM_NORMAL,    -1,                &g_Menu_File_RecentFiles, 0, 0, 0, 0, false},
	{ 0, 1, 0,                0,                       0,                      0,                   wxITEM_SEPARATOR, -1,                0,                        0, 0, 0, 0, false},
	{ 0, 1, menuExit,         wxT( "menuExit" ),         _( "E&xit" ),             wxT( "" ),             wxITEM_NORMAL,    quit_xpm_idx,      0,                        _( "Quit MadEdit" ), 0, 0, 0, false},

	// Edit
	{ 0, 0, 0, 0, _( "&Edit" ), 0, wxITEM_NORMAL, 0, &g_Menu_Edit, 0, 0, 0, 0, false},
	{ ecUndo,           1, menuUndo,                     wxT( "menuUndo" ),                     _( "&Undo" ),                                   wxT( "Ctrl-Z" ),       wxITEM_NORMAL,    undo_xpm_idx,      0,                     _( "Undo the last action" ), 0, &g_tbSTANDARD_ptr, _( "Undo" ), false},

	{
		ecRedo,           1, menuRedo,                     wxT( "menuRedo" ),                     _( "&Redo" ),
#ifdef __WXMSW__
		wxT( "Ctrl-Y" ),
#else
		wxT( "Ctrl-Shift-Z" ),
#endif
		wxITEM_NORMAL,    redo_xpm_idx,      0,                     _( "Redo the previously undone action" ), 0, &g_tbSTANDARD_ptr, _( "Redo" ), true
	},

	{ 0,                1, 0,                            0,                                   0,                                            0,                   wxITEM_SEPARATOR, -1,                0,                     0, 0, 0, 0, false},
	{ ecCut,            1, menuCut,                      wxT( "menuCut" ),                      _( "Cu&t" ),                                    wxT( "Ctrl-X" ),       wxITEM_NORMAL,    cut_xpm_idx,       0,                     _( "Cut the selection and put it on the Clipboard" ), &g_Menu_EditPop, &g_tbSTANDARD_ptr, _( "Cut" ), false},
	{ ecCopy,           1, menuCopy,                     wxT( "menuCopy" ),                     _( "&Copy" ),                                   wxT( "Ctrl-C" ),       wxITEM_NORMAL,    copy_xpm_idx,      0,                     _( "Copy the selection and put it on the Clipboard" ), &g_Menu_EditPop, &g_tbSTANDARD_ptr, _( "Copy" ), false},
	{ ecPaste,          1, menuPaste,                    wxT( "menuPaste" ),                    _( "&Paste" ),                                  wxT( "Ctrl-V" ),       wxITEM_NORMAL,    paste_xpm_idx,     0,                     _( "Insert data from the Clipboard" ), &g_Menu_EditPop, &g_tbSTANDARD_ptr, _( "Paste" ), false},
	{ ecDelete,         1, menuDelete,                   wxT( "menuDelete" ),                   _( "&Delete" ),                                 wxT( "DEL" ),          wxITEM_NORMAL,    -1,                0,                     _( "Delete data" ), &g_Menu_EditPop, 0, 0, false},
	{ 0,                1, 0,                            0,                                   0,                                            0,                   wxITEM_SEPARATOR, -1,                0,                     0, &g_Menu_EditPop, 0, 0, false},
	{ ecCutLine,        1, menuCutLine,                  wxT( "menuCutLine" ),                  _( "Cut L&ine" ),                               wxT( "Ctrl-Shift-L" ), wxITEM_NORMAL,    -1,                0,                     _( "Cut the selected lines and put it on the Clipboard" ), &g_Menu_EditPop, 0, 0, false},

	{
		ecDeleteLine,     1, menuDeleteLine,               wxT( "menuDeleteLine" ),               _( "Delete &Line" ),
#ifdef __WXMSW__
		wxT( "Ctrl-L" ),
#else
		wxT( "Ctrl-Y" ),
#endif
		wxITEM_NORMAL,    -1,                0,                     _( "Delete the selected lines" ), &g_Menu_EditPop, 0, 0, false
	},

	{ 0,                1, menuDeleteEmptyLines,         wxT( "menuDeleteEmptyLines" ),         _( "Delete Empty Lines" ),                      wxT( "Ctrl-Alt-L" ),   wxITEM_NORMAL,    -1,                0,                     _( "Delete empty lines" ), &g_Menu_EditPop, 0, 0, false},
	{ 0,                1, menuDeleteEmptyLinesWithSpaces, wxT( "menuDeleteEmptyLinesWithSpaces" ), _( "Delete Empty Lines With Spaces" ),      wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Delete empty lines with spaces" ), &g_Menu_EditPop, 0, 0, false},
	{ 0,                1, menuJoinLines,                wxT( "menuJoinLines" ),                _( "Join Lines" ),                              wxT( "Ctrl-J" ),       wxITEM_NORMAL,    -1,                0,                     _( "Join selected lines into one" ), &g_Menu_EditPop, 0, 0, false},
	{ 0,                1, menuTrimTrailingSpaces,       wxT( "menuTrimTrailingSpaces" ),       _( "Tri&m Trailing Spaces" ),                   wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Trim trailing spaces at the end of lines" ), &g_Menu_EditPop, 0, 0, false},
	{ 0,                1, menuTrimLeadingSpaces,        wxT( "menuTrimLeadingSpaces" ),        _( "Tri&m Leading Spaces" ),                    wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Trim leading spaces at the beginning of lines" ), &g_Menu_EditPop, 0, 0, false},
	{ 0,                1, 0,                            0,                                   0,                                            0,                   wxITEM_SEPARATOR, -1,                0,                     0, &g_Menu_EditPop, 0, 0, false},
	{ ecSelectAll,      1, menuSelectAll,                wxT( "menuSelectAll" ),                _( "Select &All" ),                             wxT( "Ctrl-A" ),       wxITEM_NORMAL,    -1,                0,                     _( "Select all data" ), &g_Menu_EditPop, 0, 0, false},
	{ 0,                1, menuStartEndSelction,         wxT( "menuStartEndSelction" ),         _( "Begin/End Select" ),                        0,                     wxITEM_CHECK,     -1,                0,                     _( "Begin/End to select text" ), &g_Menu_EditPop, 0, 0, false},
	{ 0,                1, 0,                            0,                                   0,                                            0,                   wxITEM_SEPARATOR, -1,                0,                     0, &g_Menu_EditPop, 0, 0, false},

	{
		ecInsertTabChar,  1, menuInsertTabChar,            wxT( "menuInsertTabChar" ),            _( "Insert Ta&b Char" ),
#ifdef __WXMSW__
		wxT( "Ctrl-~" ),
#else
		wxT( "Ctrl-`" ),
#endif
		wxITEM_NORMAL,    -1,                0,                     _( "Insert a Tab char at current position" ), &g_Menu_EditPop, 0, 0, false
	},

	{ ecInsertDateTime, 1, menuInsertDateTime,           wxT( "menuInsertDateTime" ),           _( "Insert Dat&e and Time" ),                   wxT( "F7" ),           wxITEM_NORMAL,    -1,                0,                     _( "Insert date and time at current position" ), &g_Menu_EditPop, 0, 0, false},

	// add: gogo, 21.09.2009
	{ 0,                1, 0,                            0,                                   0,                                            0,                   wxITEM_SEPARATOR, -1,                0,                     0, 0, 0, 0, false},
	{ 0,                1, menuBookmark,                 wxT( "menuBookmark" ),                 _( "Bookmark" ),                                0,                   wxITEM_NORMAL,    -1,                &g_Menu_Edit_Bookmark, 0, 0, 0, 0, false},
	{ 0,                2, menuBookmarkCopy,             wxT( "menuBookmarkCopy" ),             _( "Copy Bookmarked Lines" ),                   0,                   wxITEM_NORMAL,    -1,                0,                     _( "Copy Bookmarked Lines" ), 0, 0, 0, false},
	{ 0,                2, menuBookmarkCut,              wxT( "menuBookmarkCut" ),              _( "Cut Bookmarked Lines" ),                    0,                   wxITEM_NORMAL,    -1,                0,                     _( "Cut Bookmarked Lines" ), 0, 0, 0, false},
	{ 0,                2, menuBookmarkDel,              wxT( "menuBookmarkDel" ),              _( "Delete Bookmarked Lines" ),                 0,                   wxITEM_NORMAL,    -1,                0,                     _( "Delete Bookmarked Lines" ), 0, 0, 0, false},
	{ 0,                2, menuBookmarkDelUnmarked,      wxT( "menuBookmarkDelUnmarked" ),      _( "Delete Unmarked Lines" ),                   0,                   wxITEM_NORMAL,    -1,                0,                     _( "Delete Unmarked Lines" ), 0, 0, 0, false},
	{ 0,                2, menuBookmarkReplace,          wxT( "menuBookmarkReplace" ),          _( "Replace Bookmarked Lines" ),                0,                   wxITEM_NORMAL,    -1,                0,                     _( "Replace Bookmarked Lines" ), 0, 0, 0, false},
	{ 0,                1, 0,                            0,                                   0,                                            0,                   wxITEM_SEPARATOR, -1,                0,                     0, 0, 0, 0, false},
	{ 0,                1, menuAdvanced,                 wxT( "menuAdvanced" ),                 _( "Ad&vanced" ),                               0,                   wxITEM_NORMAL,    -1,                &g_Menu_Edit_Advanced, 0, 0, 0, 0, false},
	{ 0,                2, menuCopyAsHexString,          wxT( "menuCopyAsHexString" ),          _( "Copy As &Hex String" ),                     wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Copy the selection as hex-string" ), &g_Menu_EditSubAdv, 0, 0, false},
	{ 0,                2, menuCopyAsHexStringWithSpace, wxT( "menuCopyAsHexStringWithSpace" ), _( "Copy As He&x String with Space" ),          wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Copy the selection as hex-string with space" ), &g_Menu_EditSubAdv, 0, 0, false},
	{ 0,                2, menuCopyRevertHex,            wxT( "menuCopyRevertHex" ),            _( "Copy Value &Reverted from Hex String" ),    wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Copy the selection reverted from hex-string" ), &g_Menu_EditSubAdv, 0, 0, false},
	{ 0,                2, 0,                            0,                                   0,                                            0,                   wxITEM_SEPARATOR, -1,                0,                     0, &g_Menu_EditSubAdv, 0, 0, false},
	{ ecIncreaseIndent, 2, menuIncreaseIndent,           wxT( "menuIncreaseIndent" ),           _( "&Increase Indent" ),                        wxT( "" ),             wxITEM_NORMAL,    indent_xpm_idx,    0,                     _( "Increase the indent of seleted lines" ), &g_Menu_EditSubAdv, &g_tbEDITOR_ptr, _( "Increase Indent" ), false},
	{ ecDecreaseIndent, 2, menuDecreaseIndent,           wxT( "menuDecreaseIndent" ),           _( "&Decrease Indent" ),                        wxT( "Shift-TAB" ),    wxITEM_NORMAL,    unindent_xpm_idx,  0,                     _( "Decrease the indent of seleted lines" ), &g_Menu_EditSubAdv, &g_tbEDITOR_ptr, _( "Decrease Indent" ), true},
	{ 0,                2, 0,                            0,                                   0,                                            0,                   wxITEM_SEPARATOR, -1,                0,                     0, &g_Menu_EditSubAdv, 0, 0, false},
	{ ecComment,        2, menuComment,                  wxT( "menuComment" ),                  _( "&Comment" ),                                wxT( "Ctrl-M" ),       wxITEM_NORMAL,    comment_xpm_idx,   0,                     _( "Comment out the selected lines" ), &g_Menu_EditSubAdv, &g_tbEDITOR_ptr, _( "Comment" ), false},
	{ ecUncomment,      2, menuUncomment,                wxT( "menuUncomment" ),                _( "&Uncomment" ),                              wxT( "Ctrl-Shift-M" ), wxITEM_NORMAL,    uncomment_xpm_idx, 0,                     _( "Uncomment the selected lines" ), &g_Menu_EditSubAdv, &g_tbEDITOR_ptr, _( "Uncomment" ), true},
	{ 0,                2, 0,                            0,                                   0,                                            0,                   wxITEM_SEPARATOR, -1,                0,                     0, &g_Menu_EditSubAdv, 0, 0, false},
	{ 0,                2, menuWordWrapToNewLine,        wxT( "menuWordWrapToNewLine" ),        _( "WordWraps To NewLine Chars" ),              wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Convert WordWraps to NewLine chars in the file or selection" ), &g_Menu_EditSubAdv, 0, 0, false},
	{ 0,                2, menuNewLineToWordWrap,        wxT( "menuNewLineToWordWrap" ),        _( "NewLine Chars To WordWraps" ),              wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Convert NewLine chars to WordWraps in the selection" ), &g_Menu_EditSubAdv, 0, 0, false},
	{ 0,                2, 0,                            0,                                   0,                                            0,                   wxITEM_SEPARATOR, -1,                0,                     0, &g_Menu_EditSubAdv, 0, 0, false},
	{ ecToUpperCase,    2, menuToUpperCase,              wxT( "menuToUpperCase" ),              _( "To U&PPERCASE" ),                           wxT( "Ctrl-U" ),       wxITEM_NORMAL,    -1,                0,                     _( "Convert the selection to uppercase" ), &g_Menu_EditSubAdv, 0, 0, false},
	{ ecToLowerCase,    2, menuToLowerCase,              wxT( "menuToLowerCase" ),              _( "To l&owerCase" ),                           wxT( "Ctrl-Shift-U" ), wxITEM_NORMAL,    -1,                0,                     _( "Convert the selection to lowercase" ), &g_Menu_EditSubAdv, 0, 0, false},
	{ ecInvertCase,     2, menuInvertCase,               wxT( "menuInvertCase" ),               _( "Inver&t Case" ),                            wxT( "Ctrl-Alt-U" ),   wxITEM_NORMAL,    -1,                0,                     _( "Invert the case of the selection" ), &g_Menu_EditSubAdv, 0, 0, false},
	{ 0,                2, menuCapitalize,               wxT( "menuCapitalize" ),               _( "Capitalize" ),                              0,                     wxITEM_NORMAL,    -1,                0,                     _( "Capitalize words of the selection" ), &g_Menu_EditSubAdv, 0, 0, false},
	{ 0,                2, 0,                            0,                                   0,                                            0,                   wxITEM_SEPARATOR, -1,                0,                     0, &g_Menu_EditSubAdv, 0, 0, false},
	{ ecToHalfWidth,    2, menuToHalfWidth,              wxT( "menuToHalfWidth" ),              _( "To H&alfwidth" ),                           wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Convert the selection to halfwidth" ), &g_Menu_EditSubAdv, 0, 0, false},
	{ 0,                2, menuToHalfWidthByOptions,     wxT( "menuToHalfWidthByOptions" ),     _( "To Halfwidth by Options..." ),              wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Convert the selection to halfwidth by options" ), &g_Menu_EditSubAdv, 0, 0, false},
	{ ecToFullWidth,    2, menuToFullWidth,              wxT( "menuToFullWidth" ),              _( "To &Fullwidth" ),                           wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Convert the selection to fullwidth" ), &g_Menu_EditSubAdv, 0, 0, false},
	{ 0,                2, menuToFullWidthByOptions,     wxT( "menuToFullWidthByOptions" ),     _( "To Fullwidth by Options..." ),              wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Convert the selection to fullwidth by options" ), &g_Menu_EditSubAdv, 0, 0, false},
	{ 0,                2, 0,                            0,                                   0,                                            0,                   wxITEM_SEPARATOR, -1,                0,                     0, &g_Menu_EditSubAdv, 0, 0, false},
	{ 0,                2, menuTabToSpace,               wxT( "menuTabToSpace" ),               _( "Tab Chars To Space Chars" ),                wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Convert Tab chars to Space chars in the selection" ), &g_Menu_EditSubAdv, 0, 0, false},
	{ 0,                2, menuSpaceToTab,               wxT( "menuSpaceToTab" ),               _( "Space Chars To Tab Chars" ),                wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Convert Space chars to Tab chars in the selection" ), &g_Menu_EditSubAdv, 0, 0, false},
	{ 0,                2, 0,                            0,                                   0,                                            0,                   wxITEM_SEPARATOR, -1,                0,                     0, &g_Menu_EditSubAdv, 0, 0, false},
	{ 0,                2, menuInsertNumbers,            wxT( "menuInsertNumbers" ),            _( "Insert Incremental numbers..." ),           wxT( "Ctrl-Shift-N" ), wxITEM_NORMAL,    numbering_xpm_idx, 0,                     _( "Insert incremental numbers with step and padding at current caret" ), &g_Menu_EditSubAdv, &g_tbEDITOR_ptr, _( "Numbering and Bullets" ), false},
	{ 0,                2, menuColumnAlignLeft,          wxT( "menuColumnAlignLeft" ),          _( "Column Align Left" ),                       wxT( "" ),             wxITEM_NORMAL,    alignleft_xpm_idx, 0,                     _( "Align selection to the left" ), &g_Menu_EditSubAdv, &g_tbEDITOR_ptr, _( "Align Left" ), false},
	{ 0,                2, menuColumnAlignRight,         wxT( "menuColumnAlignRight" ),         _( "Column Align Right" ),                      wxT( "" ),             wxITEM_NORMAL,    alignright_xpm_idx, 0,                     _( "Align selection to the right" ), &g_Menu_EditSubAdv, &g_tbEDITOR_ptr, _( "Align Right" ), true},
	{ 0,                1, 0,                            0,                                   0,                                            0,                   wxITEM_SEPARATOR, -1,                0,                     0, 0, 0, 0, false},
	{ 0,                1, menuSort,                     wxT( "menuSort" ),                     _( "&Sort" ),                                   0,                     wxITEM_NORMAL,    -1,                &g_Menu_Edit_Sort,     0, 0, 0, 0, false},
	{ 0,                2, menuSortAscending,            wxT( "menuSortAscending" ),            _( "Sort Lines (&Ascending)" ),                 wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Sort the selected or all lines in ascending order" ), &g_Menu_EditSubSort, 0, 0, false},
	{ 0,                2, menuSortDescending,           wxT( "menuSortDescending" ),           _( "Sort Lines (&Descending)" ),                wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Sort the selected or all lines in descending order" ), &g_Menu_EditSubSort, 0, 0, false},
	{ 0,                2, 0,                            0,                                   0,                                            0,                   wxITEM_SEPARATOR, -1,                0,                     0, &g_Menu_EditSubSort, 0, 0, false},
	{ 0,                2, menuSortAscendingCase,        wxT( "menuSortAscendingCase" ),        _( "Sort Lines (A&scending, CaseSensitive)" ),  wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Sort lines in ascending order and with case-sensitive" ), &g_Menu_EditSubSort, 0, 0, false},
	{ 0,                2, menuSortDescendingCase,       wxT( "menuSortDescendingCase" ),       _( "Sort Lines (D&escending, CaseSensitive)" ), wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Sort lines in descending order and with case-sensitive" ), &g_Menu_EditSubSort, 0, 0, false},
	{ 0,                2, 0,                            0,                                   0,                                            0,                   wxITEM_SEPARATOR, -1,                0,                     0, &g_Menu_EditSubSort, 0, 0, false},
	{ 0,                2, menuSortByOptions,            wxT( "menuSortByOptions" ),            _( "Sort Lines by &Current Options" ),          wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Sort the selected or all lines by using current options" ), &g_Menu_EditSubSort, 0, 0, false},
	{ 0,                2, menuSortOptions,              wxT( "menuSortOptions" ),              _( "Sort &Options..." ),                        wxT( "" ),             wxITEM_NORMAL,    -1,                0,                     _( "Set the sort options" ), &g_Menu_EditSubSort, 0, 0, false},

	// Search
	{ 0, 0, 0, 0, _( "&Search" ), 0, wxITEM_NORMAL, 0, &g_Menu_Search, 0, 0, 0, 0, false},
	{ 0,            1, menuFind,                   wxT( "menuFind" ),                   _( "&Find..." ),                                        wxT( "Ctrl-F" ),       wxITEM_NORMAL,    find_xpm_idx,     0, _( "Find a string" ), 0, &g_tbSEARCHREPLACE_ptr, _( "Find" ), false},
	{ 0,            1, menuFindNext,               wxT( "menuFindNext" ),               _( "Find &Next" ),                                      wxT( "F3" ),           wxITEM_NORMAL,    findnext_xpm_idx, 0, _( "Find next occurrence" ), 0, &g_tbSEARCHREPLACE_ptr, _( "Find Next" ), false},
	{ 0,            1, menuFindPrevious,           wxT( "menuFindPrevious" ),           _( "Find &Previous" ),                                  wxT( "Ctrl-F3" ),      wxITEM_NORMAL,    findprev_xpm_idx, 0, _( "Find previous occurrence" ), 0, &g_tbSEARCHREPLACE_ptr, _( "Find Previous" ), false},
	{ 0,            1, menuShowQuickFindBar,       wxT( "menuShowQuickFindBar" ),       _( "&Quick Find" ),                                     wxT( "F8" ),           wxITEM_NORMAL,    -1,               0, _( "Find a string" ), 0, 0, 0, false},
	{ 0,            1, 0,                          0,                                 0,                                                    0,                   wxITEM_SEPARATOR, -1,               0, 0, 0, 0, 0, false},
	{ 0,            1, menuReplace,                wxT( "menuReplace" ),                _( "&Replace..." ),                                     wxT( "Ctrl-H" ),       wxITEM_NORMAL,    replace_xpm_idx,  0, _( "Replace a string" ), 0, &g_tbSEARCHREPLACE_ptr, _( "Replace" ), false},
	{ 0,            1, 0,                          0,                                 0,                                                    0,                   wxITEM_SEPARATOR, -1,               0, 0, 0, 0, 0, false},
	{ 0,            1, menuFindInFiles,            wxT( "menuFindInFiles" ),            _( "Fin&d/Replace in Files..." ),                       wxT( "Ctrl-Shift-F" ), wxITEM_NORMAL,    -1,               0, _( "Find or replace a string in files" ), 0, 0, 0, false},
	{ 0,            1, menuShowFindInFilesResults, wxT( "menuShowFindInFilesResults" ), _( "&Show/Hide the Results of Find/Replace in Files" ), wxT( "Ctrl-Shift-R" ), wxITEM_NORMAL,    -1,               0, _( "Show or hide the results of find or replace a string in files" ), 0, 0, 0, false},
	{ 0,            1, 0,                          0,                                 0,                                                    0,                   wxITEM_SEPARATOR, -1,               0, 0, 0, 0, 0, false},
	{ 0,            1, menuGoToLine,               wxT( "menuGoToLine" ),               _( "&Go To Line..." ),                                  wxT( "Ctrl-G" ),       wxITEM_NORMAL,    -1,               0, _( "Go to the specified line" ), 0, 0, 0, false},
	{ 0,            1, menuGoToPosition,           wxT( "menuGoToPosition" ),           _( "G&o To Position..." ),                              wxT( "Ctrl-Shift-G" ), wxITEM_NORMAL,    -1,               0, _( "Go to the specified position" ), 0, 0, 0, false},
	{ 0,            1, 0,                          0,                                 0,                                                    0,                   wxITEM_SEPARATOR, -1,               0, 0, 0, 0, 0, false},
	{ ecLeftBrace,  1, menuLeftBrace,              wxT( "menuLeftBrace" ),              _( "Go To L&eft Brace" ),                               wxT( "Ctrl-[" ),       wxITEM_NORMAL,    -1,               0, _( "Go to left brace" ), 0, 0, 0, false},
	{ ecRightBrace, 1, menuRightBrace,             wxT( "menuRightBrace" ),             _( "Go To R&ight Brace" ),                              wxT( "Ctrl-]" ),       wxITEM_NORMAL,    -1,               0, _( "Go to right brace" ), 0, 0, 0, false},
	{ 0,            1, 0,                          0,                                 0,                                                    0,                   wxITEM_SEPARATOR, -1,               0, 0, 0, 0, 0, false},
	{ 0,            1, menuToggleBookmark,         wxT( "menuToggleBookmark" ),         _( "Toggle/Remove Bookmark" ),                          wxT( "Ctrl-F2" ),      wxITEM_NORMAL,    bookmark_toggle_xpm_idx, 0,               _( "Toggle Bookmark at current line" ), 0, &g_tbEDITOR_ptr, _( "Toggle/Remove Bookmark" ), false},
	{ 0,            1, menuGotoNextBookmark,       wxT( "menuGotoNextBookmark" ),       _( "Go To Next Bookmark" ),                             wxT( "F2" ),           wxITEM_NORMAL,    bookmark_next_xpm_idx,   0,               _( "Go to the next bookmark" ), 0, &g_tbEDITOR_ptr, _( "Go To Next Bookmark" ), false},
	{ 0,            1, menuGotoPreviousBookmark,   wxT( "menuGotoPreviousBookmark" ),   _( "Go To Previous Bookmark" ),                         wxT( "Shift-F2" ),     wxITEM_NORMAL,    bookmark_prev_xpm_idx,   0,               _( "Go to the previous bookmark" ), 0, &g_tbEDITOR_ptr, _( "Go To Previous Bookmark" ), false},
	{ 0,            1, menuClearAllBookmarks,      wxT( "menuClearAllBookmarks" ),      _( "Clear All Bookmarks" ),                             wxT( "" ),             wxITEM_NORMAL,    bookmark_clear_xpm_idx,  0,               _( "Clear All Bookmarks" ), 0, &g_tbEDITOR_ptr, _( "Clear All Bookmarks" ), false},

	// View
	{ 0, 0, 0, 0, _( "&View" ), 0, wxITEM_NORMAL, 0, &g_Menu_View, 0, 0, 0, 0, false},
	{ 0,            1, menuEncoding,          wxT( "menuEncoding" ),          _( "Encoding: " ),           0,                   wxITEM_NORMAL,    -1,                 &g_Menu_View_Encoding,     0, 0, 0, 0, false},
	{ 0,            2, menuAllEncodings,      wxT( "menuAllEncodings" ),      _( "All Encodings" ),        0,                   wxITEM_NORMAL,    -1,                 &g_Menu_View_AllEncodings, 0, 0, 0, 0, false},
	{ 0,            1, 0,                     0,                            0,                         0,                   wxITEM_SEPARATOR, -1,                 0,                         0, 0, 0, 0, false},
	{ 0,            1, menuSyntax,            wxT( "menuSyntax" ),            _( "Syntax Type: " ),        0,                   wxITEM_NORMAL,    -1,                 &g_Menu_View_Syntax,       0, 0, 0, 0, false},
	{ 0,            1, 0,                     0,                            0,                         0,                   wxITEM_SEPARATOR, -1,                 0,                         0, 0, 0, 0, false},
	{ 0,            1, menuFontName,          wxT( "menuFontName" ),          _( "Font Name: " ),          0,                   wxITEM_NORMAL,    fontname_xpm_idx,   &g_Menu_View_FontName,     0, 0, 0, 0, false},
	{ 0,            2, menuFont0,             wxT( "menuFont0" ),             wxT( "[@]" ),                0,                   wxITEM_NORMAL,    -1,                 &g_Menu_View_Font0,        0, 0, 0, 0, false},
	{ 0,            2, menuFont1,             wxT( "menuFont1" ),             wxT( "[ABCDE]" ),            0,                   wxITEM_NORMAL,    -1,                 &g_Menu_View_Font1,        0, 0, 0, 0, false},
	{ 0,            2, menuFont2,             wxT( "menuFont2" ),             wxT( "[FGHIJ]" ),            0,                   wxITEM_NORMAL,    -1,                 &g_Menu_View_Font2,        0, 0, 0, 0, false},
	{ 0,            2, menuFont3,             wxT( "menuFont3" ),             wxT( "[KLMNO]" ),            0,                   wxITEM_NORMAL,    -1,                 &g_Menu_View_Font3,        0, 0, 0, 0, false},
	{ 0,            2, menuFont4,             wxT( "menuFont4" ),             wxT( "[PQRST]" ),            0,                   wxITEM_NORMAL,    -1,                 &g_Menu_View_Font4,        0, 0, 0, 0, false},
	{ 0,            2, menuFont5,             wxT( "menuFont5" ),             wxT( "[UVWXYZ]" ),           0,                   wxITEM_NORMAL,    -1,                 &g_Menu_View_Font5,        0, 0, 0, 0, false},
	{ 0,            2, menuFont6,             wxT( "menuFont6" ),             _( "[other]" ),              0,                   wxITEM_NORMAL,    -1,                 &g_Menu_View_Font6,        0, 0, 0, 0, false},

	{ 0,            1, menuFontSize,          wxT( "menuFontSize" ),          _( "Font Size: " ),          0,                   wxITEM_NORMAL,    fontsize_xpm_idx,   &g_Menu_View_FontSize,     0, 0, 0, 0, false},
	{ 0,            2, menuFontSize1,         wxT( "menuFontSize1" ),         wxT( " 1 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         _( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 1,      wxT( "menuFontSize2" ),         wxT( " 2 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 2,      wxT( "menuFontSize3" ),         wxT( " 3 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 3,      wxT( "menuFontSize4" ),         wxT( " 4 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 4,      wxT( "menuFontSize5" ),         wxT( " 5 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 5,      wxT( "menuFontSize6" ),         wxT( " 6 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 6,      wxT( "menuFontSize7" ),         wxT( " 7 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 7,      wxT( "menuFontSize8" ),         wxT( " 8 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 8,      wxT( "menuFontSize9" ),         wxT( " 9 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 9,      wxT( "menuFontSize10" ),        wxT( " 10 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 10,      wxT( "menuFontSize11" ),        wxT( " 11 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 11,      wxT( "menuFontSize12" ),        wxT( " 12 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 12,      wxT( "menuFontSize13" ),        wxT( " 13 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 13,      wxT( "menuFontSize14" ),        wxT( " 14 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 14,      wxT( "menuFontSize15" ),        wxT( " 15 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 15,      wxT( "menuFontSize16" ),        wxT( " 16 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 16,      wxT( "menuFontSize17" ),        wxT( " 17 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 17,      wxT( "menuFontSize18" ),        wxT( " 18 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 18,      wxT( "menuFontSize19" ),        wxT( " 19 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 19,      wxT( "menuFontSize20" ),        wxT( " 20 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 20,      wxT( "menuFontSize21" ),        wxT( " 21 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 21,      wxT( "menuFontSize22" ),        wxT( " 22 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 22,      wxT( "menuFontSize23" ),        wxT( " 23 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 23,      wxT( "menuFontSize24" ),        wxT( " 24 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 24,      wxT( "menuFontSize25" ),        wxT( " 25 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 25,      wxT( "menuFontSize26" ),        wxT( " 26 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 26,      wxT( "menuFontSize27" ),        wxT( " 27 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 27,      wxT( "menuFontSize28" ),        wxT( " 28 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 28,      wxT( "menuFontSize29" ),        wxT( " 29 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 29,      wxT( "menuFontSize30" ),        wxT( " 30 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 30,      wxT( "menuFontSize31" ),        wxT( " 31 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 31,      wxT( "menuFontSize32" ),        wxT( " 32 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 32,      wxT( "menuFontSize33" ),        wxT( " 33 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 33,      wxT( "menuFontSize34" ),        wxT( " 34 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 34,      wxT( "menuFontSize35" ),        wxT( " 35 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 35,      wxT( "menuFontSize36" ),        wxT( " 36 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 36,      wxT( "menuFontSize37" ),        wxT( " 37 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 37,      wxT( "menuFontSize38" ),        wxT( " 38 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 38,      wxT( "menuFontSize39" ),        wxT( " 39 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 39,      wxT( "menuFontSize40" ),        wxT( " 40 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 40,      wxT( "menuFontSize41" ),        wxT( " 41 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 41,      wxT( "menuFontSize42" ),        wxT( " 42 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 42,      wxT( "menuFontSize43" ),        wxT( " 43 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 43,      wxT( "menuFontSize44" ),        wxT( " 44 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 44,      wxT( "menuFontSize45" ),        wxT( " 45 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 45,      wxT( "menuFontSize46" ),        wxT( " 46 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 46,      wxT( "menuFontSize47" ),        wxT( " 47 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 47,      wxT( "menuFontSize48" ),        wxT( " 48 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 48,      wxT( "menuFontSize49" ),        wxT( " 49 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 49,      wxT( "menuFontSize50" ),        wxT( " 50 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 50,      wxT( "menuFontSize51" ),        wxT( " 51 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 51,      wxT( "menuFontSize52" ),        wxT( " 52 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 52,      wxT( "menuFontSize53" ),        wxT( " 53 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 53,      wxT( "menuFontSize54" ),        wxT( " 54 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 54,      wxT( "menuFontSize55" ),        wxT( " 55 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 55,      wxT( "menuFontSize56" ),        wxT( " 56 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 56,      wxT( "menuFontSize57" ),        wxT( " 57 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 57,      wxT( "menuFontSize58" ),        wxT( " 58 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 58,      wxT( "menuFontSize59" ),        wxT( " 59 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 59,      wxT( "menuFontSize60" ),        wxT( " 60 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 60,      wxT( "menuFontSize61" ),        wxT( " 61 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 61,      wxT( "menuFontSize62" ),        wxT( " 62 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 62,      wxT( "menuFontSize63" ),        wxT( " 63 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 63,      wxT( "menuFontSize64" ),        wxT( " 64 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 64,      wxT( "menuFontSize65" ),        wxT( " 65 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 65,      wxT( "menuFontSize66" ),        wxT( " 66 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 66,      wxT( "menuFontSize67" ),        wxT( " 67 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 67,      wxT( "menuFontSize68" ),        wxT( " 68 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 68,      wxT( "menuFontSize69" ),        wxT( " 69 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 69,      wxT( "menuFontSize70" ),        wxT( " 70 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 70,      wxT( "menuFontSize71" ),        wxT( " 71 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},
	{ 0,            2, menuFontSize1 + 71,      wxT( "menuFontSize72" ),        wxT( " 72 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set font point-size" ), 0, 0, 0, false},

	{ 0,            1, menuSetFont,           wxT( "menuSetFont" ),           _( "Set Font..." ),          wxT( "" ),             wxITEM_NORMAL,    font_xpm_idx,       0,                         _( "Change font settings" ), 0, 0, 0, false},
	{ 0,            1, menuFixedWidthMode,    wxT( "menuFixedWidthMode" ),    _( "&Fixed Width Mode" ),    wxT( "Ctrl-Alt-F" ),   wxITEM_CHECK,     -1,                 0,                         _( "Set/Unset the font with Fixed Width" ), 0, 0, 0, false},

	{ 0,            1, 0,                     0,                            0,                         0,                   wxITEM_SEPARATOR, -1,                 0,                         0, 0, 0, 0, false},
	{ 0,            1, menuTabColumn,         wxT( "menuTabColumn" ),         _( "Tab Column: " ),         0,                   wxITEM_NORMAL,    -1,                 &g_Menu_View_TabColumn,    0, 0, 0, 0, false},
	{ 0,            2, menuTabColumn1,        wxT( "menuTabColumn1" ),        wxT( " 1 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         _( "Set column of Tab char" ), 0, 0, 0, false},
	{ 0,            2, menuTabColumn1 + 1,     wxT( "menuTabColumn2" ),        wxT( " 2 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set column of Tab char" ), 0, 0, 0, false},
	{ 0,            2, menuTabColumn1 + 2,     wxT( "menuTabColumn3" ),        wxT( " 3 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set column of Tab char" ), 0, 0, 0, false},
	{ 0,            2, menuTabColumn1 + 3,     wxT( "menuTabColumn4" ),        wxT( " 4 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set column of Tab char" ), 0, 0, 0, false},
	{ 0,            2, menuTabColumn1 + 4,     wxT( "menuTabColumn5" ),        wxT( " 5 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set column of Tab char" ), 0, 0, 0, false},
	{ 0,            2, menuTabColumn1 + 5,     wxT( "menuTabColumn6" ),        wxT( " 6 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set column of Tab char" ), 0, 0, 0, false},
	{ 0,            2, menuTabColumn1 + 6,     wxT( "menuTabColumn7" ),        wxT( " 7 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set column of Tab char" ), 0, 0, 0, false},
	{ 0,            2, menuTabColumn1 + 7,     wxT( "menuTabColumn8" ),        wxT( " 8 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set column of Tab char" ), 0, 0, 0, false},
	{ 0,            2, menuTabColumn1 + 8,     wxT( "menuTabColumn9" ),        wxT( " 9 " ),                0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set column of Tab char" ), 0, 0, 0, false},
	{ 0,            2, menuTabColumn1 + 9,     wxT( "menuTabColumn10" ),       wxT( " 10 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set column of Tab char" ), 0, 0, 0, false},
	{ 0,            2, menuTabColumn1 + 10,     wxT( "menuTabColumn11" ),       wxT( " 11 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set column of Tab char" ), 0, 0, 0, false},
	{ 0,            2, menuTabColumn1 + 11,     wxT( "menuTabColumn12" ),       wxT( " 12 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set column of Tab char" ), 0, 0, 0, false},
	{ 0,            2, menuTabColumn1 + 12,     wxT( "menuTabColumn13" ),       wxT( " 13 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set column of Tab char" ), 0, 0, 0, false},
	{ 0,            2, menuTabColumn1 + 13,     wxT( "menuTabColumn14" ),       wxT( " 14 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set column of Tab char" ), 0, 0, 0, false},
	{ 0,            2, menuTabColumn1 + 14,     wxT( "menuTabColumn15" ),       wxT( " 15 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set column of Tab char" ), 0, 0, 0, false},
	{ 0,            2, menuTabColumn1 + 15,     wxT( "menuTabColumn16" ),       wxT( " 16 " ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set column of Tab char" ), 0, 0, 0, false},

	{ 0,            1, 0,                     0,                            0,                         0,                   wxITEM_SEPARATOR, -1,                 0,                         0, 0, 0, 0, false},
	{ 0,            1, menuLineSpacing,       wxT( "menuLineSpacing" ),       _( "Line Spacing: " ),       0,                   wxITEM_NORMAL,    -1,                 &g_Menu_View_LineSpacing,  0, 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100,    wxT( "menuLineSpacing100" ),    wxT( "100%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         _( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 1, wxT( "menuLineSpacing105" ),    wxT( "105%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 2, wxT( "menuLineSpacing110" ),    wxT( "110%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 3, wxT( "menuLineSpacing115" ),    wxT( "115%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 4, wxT( "menuLineSpacing120" ),    wxT( "120%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 5, wxT( "menuLineSpacing125" ),    wxT( "125%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 6, wxT( "menuLineSpacing130" ),    wxT( "130%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 7, wxT( "menuLineSpacing135" ),    wxT( "135%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 8, wxT( "menuLineSpacing140" ),    wxT( "140%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 9, wxT( "menuLineSpacing145" ),    wxT( "145%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 10, wxT( "menuLineSpacing150" ),    wxT( "150%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 11, wxT( "menuLineSpacing155" ),    wxT( "155%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 12, wxT( "menuLineSpacing160" ),    wxT( "160%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 13, wxT( "menuLineSpacing165" ),    wxT( "165%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 14, wxT( "menuLineSpacing170" ),    wxT( "170%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 15, wxT( "menuLineSpacing175" ),    wxT( "175%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 16, wxT( "menuLineSpacing180" ),    wxT( "180%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 17, wxT( "menuLineSpacing185" ),    wxT( "185%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 18, wxT( "menuLineSpacing190" ),    wxT( "190%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 19, wxT( "menuLineSpacing195" ),    wxT( "195%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 20, wxT( "menuLineSpacing200" ),    wxT( "200%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 21, wxT( "menuLineSpacing205" ),    wxT( "205%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 22, wxT( "menuLineSpacing210" ),    wxT( "210%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 23, wxT( "menuLineSpacing215" ),    wxT( "215%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 24, wxT( "menuLineSpacing220" ),    wxT( "220%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 25, wxT( "menuLineSpacing225" ),    wxT( "225%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 26, wxT( "menuLineSpacing230" ),    wxT( "230%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 27, wxT( "menuLineSpacing235" ),    wxT( "235%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 28, wxT( "menuLineSpacing240" ),    wxT( "240%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 29, wxT( "menuLineSpacing245" ),    wxT( "245%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},
	{ 0,            2, menuLineSpacing100 + 30, wxT( "menuLineSpacing250" ),    wxT( "250%" ),               0,                   wxITEM_NORMAL,    -1,                 0,                         wxT( "Set line spacing" ), 0, 0, 0, false},

	{ 0,              1, 0,                     0,                            0,                         0,                   wxITEM_SEPARATOR, -1,                 0,                         0, 0, 0, 0, false},
	{ ecNoWrap,       1, menuNoWrap,            wxT( "menuNoWrap" ),            _( "&No Wrap" ),             wxT( "Ctrl-Q" ),       wxITEM_CHECK,     nowrap_xpm_idx,     0,                         _( "Do not wrap lines" ), 0, &g_tbTEXTVIEW_ptr, _( "No Wrap" ), false},
	{ ecWrapByWindow, 1, menuWrapByWindow,      wxT( "menuWrapByWindow" ),      _( "Wrap By &Window" ),      wxT( "Ctrl-W" ),       wxITEM_CHECK,     wrapbywin_xpm_idx,  0,                         _( "Wrap the lines by the window width" ), 0, &g_tbTEXTVIEW_ptr, _( "Wrap By Window" ), false},
	{ ecWrapByColumn, 1, menuWrapByColumn,      wxT( "menuWrapByColumn" ),      _( "Wrap By Column" ),       wxT( "Ctrl-E" ),       wxITEM_CHECK,     wrapbycol_xpm_idx,  0,                         _( "Wrap the lines by the specified Max Columns" ), 0, &g_tbTEXTVIEW_ptr, _( "Wrap By Column" ), false},
	{ 0,              1, 0,                     0,                            0,                         0,                   wxITEM_SEPARATOR, -1,                 0,                         0, 0, 0, 0, false},
	{ 0,              1, menuDisplayLineNumber, wxT( "menuDisplayLineNumber" ), _( "&Display Line Number" ), wxT( "Ctrl-Alt-D" ),   wxITEM_CHECK,     -1,                 0,                         _( "Display the Line Numbers" ), 0, 0, 0, false},
	{ 0,              1, menuDisplayBookmark,   wxT( "menuDisplayBookmark" ),   _( "Display &Bookmark" ),    wxT( "Ctrl-Alt-B" ),   wxITEM_CHECK,     -1,                 0,                         _( "Display the Bookmark sign" ), 0, 0, 0, false},
	{ 0,              1, menuDisplay80ColHint,  wxT( "menuDisplay80ColHint" ),  _( "Display 80th Cols &Hint" ), wxT( "" ),          wxITEM_CHECK,     -1,                 0,                         _( "Display the 80th columns hint" ), 0, 0, 0, false},
	{ 0,              1, menuShowEndOfLine,     wxT( "menuShowEndOfLine" ),     _( "Show End Of Line" ),     wxT( "Ctrl-Alt-L" ),   wxITEM_CHECK,     -1,                 0,                         _( "Show the sign of EndOfLine" ), 0, 0, 0, false},
	{ 0,              1, menuShowTabChar,       wxT( "menuShowTabChar" ),       _( "Show Tab Char" ),        wxT( "Ctrl-Alt-T" ),   wxITEM_CHECK,     -1,                 0,                         _( "Show the sign of Tab char" ), 0, 0, 0, false},
	{ 0,              1, menuShowSpaceChar,     wxT( "menuShowSpaceChar" ),     _( "Show Space Char" ),      wxT( "Ctrl-Alt-S" ),   wxITEM_CHECK,     -1,                 0,                         _( "Show the sign of Space char" ), 0, 0, 0, false},
	{ 0,              1, menuShowAllChars,      wxT( "menuShowAllChar" ),       _( "Show All Chars" ),       wxT( "Ctrl-Alt-A" ),   wxITEM_CHECK,     showsymbol_xpm_idx, 0,                         _( "Show the sign of all characters" ), 0, &g_tbTEXTVIEW_ptr, _( "Show All Chars" ), false},
	{ 0,              1, menuViewRightToLeft,   wxT( "menuViewRightToLeft" ),   _( "Right-to-left" ),        wxT( "Ctrl-Alt-R" ),   wxITEM_CHECK,     -1,                 0,                         _( "View text from Right-to-left" ), 0, 0, 0, false},
	{ 0,              1, menuMarkActiveLine,    wxT( "menuMarkActiveLine" ),    _( "Mark Active Line" ),     wxT( "" ),             wxITEM_CHECK,     -1,                 0,                         _( "Mark the current line" ), 0, 0, 0, false},
	{ 0,              1, menuMarkBracePair,     wxT( "menuMarkBracePair" ),     _( "Mark Brace Pair" ),      wxT( "" ),             wxITEM_CHECK,     -1,                 0,                         _( "Mark the BracePair under the caret" ), 0, 0, 0, false},
	{ 0,              1, menuSpellChecker,      wxT( "menuSpellChecker" ),      _( "Spell Check" ),        wxT( "Ctrl-K" ),       wxITEM_CHECK,     spellchecker_xpm_idx,                 0,       _( "Turn on spell checker" ), 0, &g_tbTEXTVIEW_ptr, _( "Spell Check" ), false},
	{ 0,              1, 0,                     0,                            0,                         0,                   wxITEM_SEPARATOR, -1,                 0,                         0, 0, 0, 0, false},
	{ 0,              1, menuToolBars,          wxT( "menuToolBar" ),           _( "Toolbars" ),             0,                   wxITEM_NORMAL,    -1,                 &g_Menu_Toolbars,          0, 0, 0, 0, false},
	{ 0,              2, menuToolBarsToggleAll, wxT( "menuToolBarsToggleAll" ), _( "Toggle Main Toolbar" ),  0,                   wxITEM_CHECK,     -1,                 0,                         _( "Show/Hide Main Toolbar" ), 0, 0, 0, false},
	{ 0,              2, 0,                     0,                            0,                         0,                   wxITEM_SEPARATOR, -1,                 0,                         0, 0, 0, 0, false},
	{ 0,              1, 0,                     0,                            0,                         0,                   wxITEM_SEPARATOR, -1,                 0,                         0, 0, 0, 0, false},
	{ ecTextMode,     1, menuTextMode,          wxT( "menuTextMode" ),          _( "&Text Mode" ),           wxT( "Alt-1" ),        wxITEM_CHECK,     textmode_xpm_idx,   0,                         _( "Change the editing mode to Text-Mode" ), 0, &g_tbEDITMODE_ptr, _( "Text Mode" ), false},
	{ ecColumnMode,   1, menuColumnMode,        wxT( "menuColumnMode" ),        _( "&Column Mode" ),         wxT( "Alt-2" ),        wxITEM_CHECK,     columnmode_xpm_idx, 0,                         _( "Change the editing mode to Column-Mode" ), 0, &g_tbEDITMODE_ptr, _( "Column Mode" ), false},
	{ ecHexMode,      1, menuHexMode,           wxT( "menuHexMode" ),           _( "&Hex Mode" ),            wxT( "Alt-3" ),        wxITEM_CHECK,     hexmode_xpm_idx,    0,                         _( "Change the editing mode to Hex-Mode" ), 0, &g_tbEDITMODE_ptr, _( "Hex Mode" ), false},
	{ 0,              1, 0,                     0,                            0,                         0,                   wxITEM_SEPARATOR, -1,                 0,                         0, 0, 0, 0, false},
	{ 0,              1, menuPreview,           wxT( "menuPreview" ),           _( "Preview as: " ),         0,                   wxITEM_NORMAL,    -1,                 &g_Menu_View_Preview,      0, 0, 0, 0, false},

	// Macro
	{ 0, 0, 0, 0, _( "&Macro" ), 0, wxITEM_NORMAL, 0, &g_Menu_MadMacro, 0, 0, 0, 0, false},
	{ 0,               1, menuRunTempMacro,       wxT( "menuRunTempMacro" ),       _( "Run TemporayMacro" ),                             wxT( "" ),       wxITEM_NORMAL,    runscript_xpm_idx, 0,                 _( "Run temporary macro" ), 0, &g_tbMACRO_ptr, _( "Run temporary macro" ), false},
	{ 0,               1, menuRunMacroFile,       wxT( "menuRunMacroFile" ),       _( "Load Saved MacroScript..." ),                     wxT( "" ),       wxITEM_NORMAL,    -1, 0,                                _( "Load saved macro script" ), 0, 0, 0, false},
	{ 0,               1, menuStartRecMacro,      wxT( "menuStartRecMacro" ),      _( "Start Recording" ),                               wxT( "" ),       wxITEM_NORMAL,    record_xpm_idx,  0,                   _( "Start Recording" ), 0, &g_tbMACRO_ptr, _( "Start Recording" ), false},
	{ 0,               1, menuStopRecMacro,       wxT( "menuStopRecMacro" ),       _( "Stop Recording" ),                                wxT( "" ),       wxITEM_NORMAL,    stop_xpm_idx,    0,                   _( "Stop Recording" ), 0, &g_tbMACRO_ptr, _( "Stop Recording" ), false},
	{ 0,               1, menuPlayRecMacro,       wxT( "menuPlayRecMacro" ),       _( "Playback" ),                                      wxT( "" ),       wxITEM_NORMAL,    play_xpm_idx,    0,                   _( "Playback" ), 0, &g_tbMACRO_ptr, _( "Playback" ), false},
	{ 0,               1, menuSaveRecMacro,       wxT( "menuSaveRecMacro" ),       _( "Save Currently Recorded Macro..." ),              wxT( "" ),       wxITEM_NORMAL,    saverec_xpm_idx, 0,                   _( "Save Currently Recorded Macro" ), 0, &g_tbMACRO_ptr, _( "Save Recorded Macro" ), false},
	{ 0,               1, menuMadScriptList,      wxT( "menuMadScriptList" ),      _( "Local Script List" ),                             wxT( "" ),       wxITEM_NORMAL,    -1, &g_Menu_MadMacro_Scripts,    0, 0, 0, 0, false},
	{ 0,               2, menuEditMacroFile,      wxT( "menuEditMacroFile" ),      _( "Edit Saved MacroScript..." ),                     wxT( "" ),       wxITEM_NORMAL,    -1, 0,                                _( "Edit saved macro script" ), 0, 0, 0, false},

	// Tools
	{ 0, 0, 0, 0, _( "&Tools" ), 0, wxITEM_NORMAL, 0, &g_Menu_Tools, 0, 0, 0, 0, false},
	{ 0,               1, menuOptions,            wxT( "menuOptions" ),            _( "&Options..." ),                                   wxT( "" ),       wxITEM_NORMAL,    -1, 0,                                _( "Change the configuration" ), 0, 0, 0, false},
	{ 0,               1, menuHighlighting,       wxT( "menuHighlighting" ),       _( "&Syntax Highlighting Settings..." ),              wxT( "" ),       wxITEM_NORMAL,    -1, 0,                                _( "Change syntax highlighting settings" ), 0, 0, 0, false},
#ifdef __WXMSW__
	{ 0,               1, menuFileAssociation,    wxT( "menuFileAssociation" ),    _( "&File Type Associations..." ),                    wxT( "" ),       wxITEM_NORMAL,    -1, 0,                                _( "Change file type associations" ), 0, 0, 0, false},
#endif
	{ 0,               1, menuPurgeHistories,     wxT( "menuPurgeHistories" ),     _( "&Purge Histories..." ),                           wxT( "" ),       wxITEM_NORMAL,    -1, 0,                                _( "Clearing out your history" ), 0, 0, 0, false},
	{ 0,               1, 0,                      0,                             0,                                                  0,             wxITEM_SEPARATOR, -1, 0,                                0, 0, 0, 0, false},
	{ 0,               1, menuByteOrderMark,      wxT( "menuByteOrderMark" ),      _( "Has Unicode BOM (Byte-Order Mark)" ),             0,             wxITEM_NORMAL,    -1, &g_Menu_Tools_BOM,                0, 0, 0, 0, false},
	{ 0,               2, menuToggleBOM,          wxT( "menuToggleBOM" ),          _( "Add/Remove BOM" ),                                wxT( "" ),       wxITEM_NORMAL,    -1, 0,                                _( "Add/Remove Unicode BOM" ), 0, 0, 0, false},
	{ 0,               1, 0,                      0,                             0,                                                  0,             wxITEM_SEPARATOR, -1, 0,                                0, 0, 0, 0, false},
	{ 0,               1, menuNewLineChar,        wxT( "menuNewLineChar" ),        _( "NewLine Char (File Format): " ),                  0,             wxITEM_NORMAL,    -1, &g_Menu_Tools_NewLineChar,        0, 0, 0, 0, false},
	{ 0,               2, menuConvertToDOS,       wxT( "menuConvertToDOS" ),       _( "Convert To CRLF/0D0A (&DOS)" ),                   wxT( "" ),       wxITEM_NORMAL,    -1, 0,                                _( "Convert the file format to DOS format" ), 0, 0, 0, false},
	{ 0,               2, menuConvertToMAC,       wxT( "menuConvertToMAC" ),       _( "Convert To CR/0D (Old &MAC)" ),                   wxT( "" ),       wxITEM_NORMAL,    -1, 0,                                _( "Convert the file format to MAC format" ), 0, 0, 0, false},
	{ 0,               2, menuConvertToUNIX,      wxT( "menuConvertToUNIX" ),      _( "Convert To LF/0A (&UNIX/OSX)" ),                  wxT( "" ),       wxITEM_NORMAL,    -1, 0,                                _( "Convert the file format to UNIX format" ), 0, 0, 0, false},
	{ 0,               1, menuInsertNewLineChar,  wxT( "menuInsertNewLineChar" ),  _( "Press Enter to Insert NewLine Char: " ),          0,             wxITEM_NORMAL,    -1, &g_Menu_Tools_InsertNewLineChar,  0, 0, 0, 0, false},
	{ 0,               2, menuInsertDOS,          wxT( "menuInsertDOS" ),          _( "Insert CRLF/0D0A (&DOS)" ),                       wxT( "" ),       wxITEM_NORMAL,    -1, 0,                                _( "Insert CR&LF chars when pressing Enter key" ), 0, 0, 0, false},
	{ 0,               2, menuInsertMAC,          wxT( "menuInsertMAC" ),          _( "Insert CR/0D (Old &MAC)" ),                       wxT( "" ),       wxITEM_NORMAL,    -1, 0,                                _( "Insert CR char when pressing Enter key" ), 0, 0, 0, false},
	{ 0,               2, menuInsertUNIX,         wxT( "menuInsertUNIX" ),         _( "Insert LF/0A (&UNIX/OSX)" ),                      wxT( "" ),       wxITEM_NORMAL,    -1, 0,                                _( "Insert LF char when pressing Enter key" ), 0, 0, 0, false},
	{ 0,               1, 0,                      0,                             0,                                                  0,             wxITEM_SEPARATOR, -1, 0,                                0, 0, 0, 0, false},
	{ 0,               1, menuConvertEncoding,    wxT( "menuConvertEncoding" ),    _( "Convert File &Encoding..." ),                     0,               wxITEM_NORMAL,    -1, 0,                                _( "Convert to the specified encoding" ), 0, 0, 0, false},
	{ 0,               1, 0,                      0,                             0,                                                  0,             wxITEM_SEPARATOR, -1, 0,                                0, 0, 0, 0, false},
	{ 0,               1, menuConvertChineseChar,     wxT( "menuConvertChineseChar" ),     _( "Convert &Chinese Char" ),                                 0,             wxITEM_NORMAL,    -1, &g_Menu_Tools_ConvertChineseChar, 0, 0, 0, 0, false},
	{ 0,               2, menuSimp2TradChinese,       wxT( "menuSimp2TradChinese" ),       _( "File: Simplified Chinese to &Traditional Chinese" ),      0,             wxITEM_NORMAL,    -1, 0,                                _( "Convert simplified Chinese chars to traditional Chinese chars in the file" ), 0, 0, 0, false},
	{ 0,               2, menuTrad2SimpChinese,       wxT( "menuTrad2SimpChinese" ),       _( "File: Traditional Chinese to &Simplified Chinese" ),      0,             wxITEM_NORMAL,    -1, 0,                                _( "Convert traditional Chinese chars to simplified Chinese chars in the file" ), 0, 0, 0, false},
	{ 0,               2, menuKanji2TradChinese,      wxT( "menuKanji2TradChinese" ),      _( "File: Japanese Kanji to Tr&aditional Chinese" ),          0,             wxITEM_NORMAL,    -1, 0,                                _( "Convert Japanese Kanji to traditional Chinese chars in the file" ), 0, 0, 0, false},
	{ 0,               2, menuKanji2SimpChinese,      wxT( "menuKanji2SimpChinese" ),      _( "File: Japanese Kanji to Si&mplified Chinese" ),           0,             wxITEM_NORMAL,    -1, 0,                                _( "Convert Japanese Kanji to simplified Chinese chars in the file" ), 0, 0, 0, false},
	{ 0,               2, menuChinese2Kanji,          wxT( "menuChinese2Kanji" ),          _( "File: Chinese to &Japanese Kanji" ),                      0,             wxITEM_NORMAL,    -1, 0,                                _( "Convert Chinese chars to Japanese Kanji in the file" ), 0, 0, 0, false},
	{ 0,               2, 0,                          0,                                 0,                                                          0,             wxITEM_SEPARATOR, -1, 0,                                0, 0, 0, 0, false},
	{ 0,               2, menuSimp2TradClipboard,     wxT( "menuSimp2TradClipboard" ),     _( "Clipboard: Simplified Chinese to T&raditional Chinese" ), 0,             wxITEM_NORMAL,    -1, 0,                                _( "Convert simplified Chinese chars to traditional Chinese chars in the clipboard" ), 0, 0, 0, false},
	{ 0,               2, menuTrad2SimpClipboard,     wxT( "menuTrad2SimpClipboard" ),     _( "Clipboard: Traditional Chinese to S&implified Chinese" ), 0,             wxITEM_NORMAL,    -1, 0,                                _( "Convert traditional Chinese chars to simplified Chinese chars in the clipboard" ), 0, 0, 0, false},
	{ 0,               2, menuKanji2TradClipboard,    wxT( "menuKanji2TradClipboard" ),    _( "Clipboard: Japanese Kanji to Tra&ditional Chinese" ),     0,             wxITEM_NORMAL,    -1, 0,                                _( "Convert Japanese Kanji to traditional Chinese chars in the clipboard" ), 0, 0, 0, false},
	{ 0,               2, menuKanji2SimpClipboard,    wxT( "menuKanji2SimpClipboard" ),    _( "Clipboard: Japanese Kanji to Sim&plified Chinese" ),      0,             wxITEM_NORMAL,    -1, 0,                                _( "Convert Japanese Kanji to simplified Chinese chars in the clipboard" ), 0, 0, 0, false},
	{ 0,               2, menuChinese2KanjiClipboard, wxT( "menuChinese2KanjiClipboard" ), _( "Clipboard: Chinese to Japanese &Kanji" ),                 0,             wxITEM_NORMAL,    -1, 0,                                _( "Convert Chinese chars to Japanese Kanji in the clipboard" ), 0, 0, 0, false},
	{ 0,               1, 0,                          0,                                 0,                                                          0,             wxITEM_SEPARATOR, -1, 0,                                0, 0, 0, 0, false},
	{ 0,               1, menuTextConvFormatter,      wxT( "menuTextConvFormatter" ),      _( "Text Converter/Formatter" ),                              0,             wxITEM_NORMAL,    -1, &g_Menu_Tools_TextConvFormatter, 0, 0, 0, 0, false},
	{ 0,               2, menuMarkdown2Html,          wxT( "menuMarkdown2Html" ),          _( "&Markdown to HTML" ),                                     0,             wxITEM_NORMAL,    -1, 0,                                _( "Convert Markdown to HTML" ), 0, 0, 0, false},
	{ 0,               2, menuHtml2PlainText,         wxT( "menuHtml2PlainText" ),         _( "&HTML to Plain Text" ),                                   0,             wxITEM_NORMAL,    -1, 0,                                _( "Convert HTML to Plain Text" ), 0, 0, 0, false},
	{ 0,               2, 0,                          0,                                 0,                                                          0,             wxITEM_SEPARATOR, -1, 0,                                0, 0, 0, 0, false},
	{ 0,               2, menuAstyleFormat,           wxT( "menuAstyleFormat" ),           _( "&Astyle(C++/C#/Java/ObjC)" ),         wxT( "Ctrl-Shift-K" ),             wxITEM_NORMAL,    -1, 0,                                _( "Format selection or whole file(C++/C#/Java)" ), 0, 0, 0, false},
	{ 0,               2, menuXMLFormat,              wxT( "menuXMLFormat" ),              _( "&XML Formatter" ),                                        0,             wxITEM_NORMAL,    -1, 0,                                _( "Format XML(whole file)" ), 0, 0, 0, false},
	{ 0,               1, 0,                          0,                                 0,                                                          0,             wxITEM_SEPARATOR, -1, 0,                                0, 0, 0, 0, false},
	{ 0,               1, menuWordCount,              wxT( "menuWordCount" ),              _( "&Word Count..." ),                                        0,             wxITEM_NORMAL,    -1, 0,                                _( "Count the words and chars of the file or selection" ), 0, 0, 0, false},

	// Window
	{ 0, 0, 0, 0, _( "&Window" ), 0, wxITEM_NORMAL, 0, &g_Menu_Window, 0, 0, 0, 0, false},
	{ ecToggleWindow, 1, menuToggleWindow,   wxT( "menuToggleWindow" ),   _( "&Toggle Window" ),   wxT( "Ctrl-TAB" ), wxITEM_NORMAL, -1, 0, _( "Switch to the previous active window" ), 0, 0, 0, false},
	{ 0,              1, menuPreviousWindow, wxT( "menuPreviousWindow" ), _( "&Previous Window" ), wxT( "F5" ),       wxITEM_NORMAL, -1, 0, _( "Activate the previous window" ), 0, 0, 0, false},
	{ 0,              1, menuNextWindow,     wxT( "menuNextWindow" ),     _( "&Next Window" ),     wxT( "F6" ),       wxITEM_NORMAL, -1, 0, _( "Activate the next window" ), 0, 0, 0, false},

	// Help
	{ 0, 0, 0, 0, _( "&Help" ), 0, wxITEM_NORMAL, 0, &g_Menu_Help, 0, 0, 0, 0, false},
	{ 0, 1, menuAbout, wxT( "menuAbout" ), _( "&About MadEdit-Mod..." ), wxT( "" ),       wxITEM_NORMAL, Mad_16x15_xpm_idx, 0, wxT( "" ), 0, 0, 0, false},
	// end menu

	// begin editor
	{ ecLeft,      -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Move caret left one char" ), 0, 0, 0, false},
	{ ecRight,     -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Move caret right one char" ), 0, 0, 0, false},
	{ ecUp,        -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Move caret up one line" ), 0, 0, 0, false},
	{ ecDown,      -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Move caret down one line" ), 0, 0, 0, false},
	{ ecBeginLine, -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to begin of line" ), 0, 0, 0, false},
	{ ecEndLine,   -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to end of line" ), 0, 0, 0, false},
	{ ecBeginDoc,  -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to begin of document" ), 0, 0, 0, false},
	{ ecEndDoc,    -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to end of document" ), 0, 0, 0, false},
	{ ecPrevPage,  -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to previous page" ), 0, 0, 0, false},
	{ ecNextPage,  -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to next page" ), 0, 0, 0, false},
	{ ecPrevWord,  -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to previous word" ), 0, 0, 0, false},
	{ ecNextWord,  -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to next word" ), 0, 0, 0, false},

	{ ecSelLeft,       -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Move caret left one char and select" ), 0, 0, 0, false},
	{ ecSelRight,      -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Move caret right one char and select" ), 0, 0, 0, false},
	{ ecSelUp,         -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Move caret up one line and select" ), 0, 0, 0, false},
	{ ecSelDown,       -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Move caret down one line and select" ), 0, 0, 0, false},
	{ ecSelBeginLine,  -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to begin of line and select" ), 0, 0, 0, false},
	{ ecSelEndLine,    -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to end of line and select" ), 0, 0, 0, false},
	{ ecSelBeginDoc,   -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to begin of document and select" ), 0, 0, 0, false},
	{ ecSelEndDoc,     -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to end of document and select" ), 0, 0, 0, false},
	{ ecSelPrevPage,   -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to previous page and select" ), 0, 0, 0, false},
	{ ecSelNextPage,   -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to next page and select" ), 0, 0, 0, false},
	{ ecSelPrevWord,   -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to previous word and select" ), 0, 0, 0, false},
	{ ecSelNextWord,   -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to next word and select" ), 0, 0, 0, false},
	{ ecSelLeftBrace,  -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to left brace and select" ), 0, 0, 0, false},
	{ ecSelRightBrace, -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Go to right brace and select" ), 0, 0, 0, false},

	{ ecScrollLineUp,   -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Scroll text up one line" ), 0, 0, 0, false},
	{ ecScrollLineDown, -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Scroll text down one line" ), 0, 0, 0, false},
	{ ecScrollPageUp,   -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Scroll text up one page" ), 0, 0, 0, false},
	{ ecScrollPageDown, -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Scroll text down one page" ), 0, 0, 0, false},
	{ ecScrollLeft,     -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Scroll text left" ), 0, 0, 0, false},
	{ ecScrollRight,    -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Scroll text right" ), 0, 0, 0, false},

	{ ecReturn,         -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Insert one NewLine char" ), 0, 0, 0, false},
	{ ecReturnNoIndent, -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Insert one NewLine char without indentation" ), 0, 0, 0, false},
	{ ecTab,            -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Insert one Tab char or indent lines" ), 0, 0, 0, false},
	{ ecBackSpace,      -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Delete one char to the left of the caret" ), 0, 0, 0, false},

	// add: gogo, 30.08.2009
	{ ecDelPrevWord,    -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Delete a word left from the caret" ), 0, 0, 0, false},
	{ ecDelNextWord,    -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Delete a word right from the caret" ), 0, 0, 0, false},

	{ ecToggleInsertMode, -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, _( "Toggle Insert/Overwrite Mode" ), 0, 0, 0, false},

	// end editor
	{ -1, -1, 0, 0, 0, 0, wxITEM_NORMAL, -1, 0, 0, 0, 0, 0, false},
};

// restore the definition of _(s)
#undef _
#define _(s)    wxGetTranslation(_T(s))
//==========================================================

void LoadDefaultSettings( wxConfigBase *madConfig )
{
	madConfig->SetPath( wxT( "/MadEdit" ) );
	long templong, x, y;
	bool tempbool;
	wxString tempstr;
	long orien;
	madConfig->Read( wxT( "PageOrientation" ), &orien, wxPORTRAIT );
#if (wxMAJOR_VERSION < 3)
	g_PageSetupData->GetPrintData().SetOrientation( orien );
#else
	g_PageSetupData->GetPrintData().SetOrientation( ( wxPrintOrientation )orien );
#endif
	wxSize psize = g_PageSetupData->GetPaperSize();
	madConfig->Read( wxT( "PagePaperSizeW" ), &psize.x );
	madConfig->Read( wxT( "PagePaperSizeH" ), &psize.y );

	if( orien != wxPORTRAIT )
	{
		long tmp = psize.x;
		psize.x = psize.y;
		psize.y = tmp;
	}

	g_PageSetupData->SetPaperSize( psize );
	madConfig->Read( wxT( "PageLeftMargin" ), &x, 20 );
	madConfig->Read( wxT( "PageTopMargin" ), &y, 30 );
	g_PageSetupData->SetMarginTopLeft( wxPoint( x, y ) );
	madConfig->Read( wxT( "PageRightMargin" ), &x, 20 );
	madConfig->Read( wxT( "PageBottomMargin" ), &y, 30 );
	g_PageSetupData->SetMarginBottomRight( wxPoint( x, y ) );
	madConfig->Read( wxT( "PrintSyntax" ), &tempbool, false );
	madConfig->Read( wxT( "PrintLineNumber" ), &tempbool, true );
	madConfig->Read( wxT( "PrintBookmark" ), &tempbool, false );
	madConfig->Read( wxT( "PrintEndOfLine" ), &tempbool, false );
	madConfig->Read( wxT( "PrintTabChar" ), &tempbool, false );
	madConfig->Read( wxT( "PrintSpaceChar" ), &tempbool, false );
	madConfig->Read( wxT( "PrintOffsetHeader" ), &templong, 2 );
	madConfig->Read( wxT( "PrintPageHeader" ), &tempbool, true );
	madConfig->Read( wxT( "PageHeaderLeft" ), &tempstr, wxT( "%f" ) );
	madConfig->Read( wxT( "PageHeaderCenter" ), &tempstr, wxEmptyString );
	madConfig->Read( wxT( "PageHeaderRight" ), &tempstr, wxT( "%n/%s" ) );
	madConfig->Read( wxT( "PrintPageFooter" ), &tempbool, true );
	madConfig->Read( wxT( "PageFooterLeft" ), &tempstr, wxEmptyString );
	madConfig->Read( wxT( "PageFooterCenter" ), &tempstr, wxEmptyString );
	madConfig->Read( wxT( "PageFooterRight" ), &tempstr, wxT( "%d %t" ) );
	madConfig->SetPath( wxT( "/FileCaretPos" ) );
	g_FileCaretPosManager.Load( madConfig );
}


MadEditFrame::MadEditFrame( wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style )
	: wxFrame( parent, id, title, position, size, style )
{
#ifndef __WXMSW__
	wxConvFileName = &MadConvFileNameObj;
#endif
	this->SetWindowStyleFlag( this->GetWindowStyleFlag() & ~wxTAB_TRAVERSAL );
	/*
	#if !defined(__WXMSW__) && !defined(__WXPM__)
	SetIcon(wxIcon(Mad_xpm));
	#else // __MSW__
	SetIcon(wxIcon(wxT("appicon")));
	#endif
	*/
	m_NewFileCount = 0;
	m_Config = wxConfigBase::Get( false );
	MadEncoding::InitEncodings();
	MadSyntax::SetAttributeFilePath( g_MadEditHomeDir + wxT( "syntax" ) + wxFILE_SEP_PATH );
#if defined(__WXMSW__)
	MadSyntax::AddSyntaxFilesPath( g_MadEditAppDir + wxT( "syntax" ) + wxFILE_SEP_PATH );
#elif defined(__WXGTK__) // linux
	MadSyntax::AddSyntaxFilesPath( g_MadEditAppDir + wxT( "syntax" ) + wxFILE_SEP_PATH );
	MadSyntax::AddSyntaxFilesPath( g_MadEditHomeDir + wxT( "syntax" ) + wxFILE_SEP_PATH );
#if defined (DATA_DIR)
	MadSyntax::AddSyntaxFilesPath( wxT( DATA_DIR"/madedit-mod/syntax/" ) );
#else
	MadSyntax::AddSyntaxFilesPath( wxT( "/usr/share/madedit-mod/syntax/" ) );
#endif
#else // other platform
	MadSyntax::AddSyntaxFilesPath( g_MadEditAppDir + wxT( "syntax" ) + wxFILE_SEP_PATH );
#endif
	CreateGUIControls();
	//g_PrintData = new wxPrintData;
	g_PageSetupData = new wxPageSetupDialogData;
	LoadDefaultSettings( m_Config );
	m_ReloadFiles  = m_Config->ReadBool( wxT( "/MadEdit/ReloadFiles" ), true );
	m_PurgeHistory = m_Config->ReadBool( wxT( "/MadEdit/PurgeHistory" ), false );
	SetDropTarget( new DnDFile() );
	m_PageClosing = false;
	m_MadMacroStatus = emMacroStopped;
	m_LastSelBeg = -1;
	m_LastSelEnd = -1;
	m_SearchDirectionNext = true;
	m_HtmlPreview = 0;
	m_PreviewType = ptPREVIEW_NONE;
	g_MainFrame = this;
}

MadEditFrame::~MadEditFrame()
{}

// not all ports have support for EVT_CONTEXT_MENU yet, don't define
// USE_CONTEXT_MENU for those which don't
#if defined(__WXMOTIF__) || defined(__WXPM__) || defined(__WXX11__)
	#define USE_CONTEXT_MENU 0
#else
	#define USE_CONTEXT_MENU 1
#endif

void MadEditFrame::CreateGUIControls( void )
{
	WxStatusBar1 = new wxStatusBar( this, ID_WXSTATUSBAR1 );
	g_StatusBar = WxStatusBar1;
#if defined(__WXGTK__)
	const wxFont &font = WxStatusBar1->GetFont();
	int pt = font.GetPointSize();

	if( pt > 10 ) { pt = 10; }

	wxFont *pf = wxTheFontList->FindOrCreateFont( pt, font.GetFamily(), font.GetStyle(), font.GetWeight(), font.GetUnderlined(), wxT( "Serif" ) );
	WxStatusBar1->SetFont( *pf );
#endif
#define MADTOOBAR_STYLE_NO_OVERFLOW (wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_HORIZONTAL)
	WxToolBar[tbSTANDARD] = new wxAuiToolBar( this, ID_WXTOOLBAR1 + tbSTANDARD, wxPoint( 0, 0 ), wxSize( 392, 29 ), MADTOOBAR_STYLE_NO_OVERFLOW );
	WxToolBar[tbSTANDARD]->Connect( wxEVT_AUITOOLBAR_RIGHT_CLICK, wxAuiToolBarEventHandler( MadEditFrame::OnRightClickToolBar ) );
	g_ToolbarNames[tbSTANDARD] = _( "Standard" );
	WxToolBar[tbEDITOR] = new wxAuiToolBar( this, ID_WXTOOLBAR1 + tbEDITOR, wxPoint( 0, 0 ), wxSize( 392, 29 ), MADTOOBAR_STYLE_NO_OVERFLOW );
	WxToolBar[tbEDITOR]->Connect( wxEVT_AUITOOLBAR_RIGHT_CLICK, wxAuiToolBarEventHandler( MadEditFrame::OnRightClickToolBar ) );
	g_ToolbarNames[tbEDITOR] = _( "Editor" );
	WxToolBar[tbSEARCHREPLACE] = new wxAuiToolBar( this, ID_WXTOOLBAR1 + tbSEARCHREPLACE, wxPoint( 0, 0 ), wxSize( 392, 29 ), MADTOOBAR_STYLE_NO_OVERFLOW );
	WxToolBar[tbSEARCHREPLACE]->Connect( wxEVT_AUITOOLBAR_RIGHT_CLICK, wxAuiToolBarEventHandler( MadEditFrame::OnRightClickToolBar ) );
	g_ToolbarNames[tbSEARCHREPLACE] = _( "Search/Replace" );
	WxToolBar[tbTEXTVIEW] = new wxAuiToolBar( this, ID_WXTOOLBAR1 + tbTEXTVIEW, wxPoint( 0, 0 ), wxSize( 392, 29 ), MADTOOBAR_STYLE_NO_OVERFLOW );
	WxToolBar[tbTEXTVIEW]->Connect( wxEVT_AUITOOLBAR_RIGHT_CLICK, wxAuiToolBarEventHandler( MadEditFrame::OnRightClickToolBar ) );
	g_ToolbarNames[tbTEXTVIEW] = _( "Text View" );
	WxToolBar[tbEDITMODE] = new wxAuiToolBar( this, ID_WXTOOLBAR1 + tbEDITMODE, wxPoint( 0, 0 ), wxSize( 392, 29 ), MADTOOBAR_STYLE_NO_OVERFLOW );
	WxToolBar[tbEDITMODE]->Connect( wxEVT_AUITOOLBAR_RIGHT_CLICK, wxAuiToolBarEventHandler( MadEditFrame::OnRightClickToolBar ) );
	g_ToolbarNames[tbEDITMODE] = _( "Edit Mode" );
	WxToolBar[tbMACRO] = new wxAuiToolBar( this, ID_WXTOOLBAR1 + tbMACRO, wxPoint( 0, 0 ), wxSize( 392, 29 ), MADTOOBAR_STYLE_NO_OVERFLOW | wxAUI_TB_OVERFLOW );
	WxToolBar[tbMACRO]->Connect( wxEVT_AUITOOLBAR_RIGHT_CLICK, wxAuiToolBarEventHandler( MadEditFrame::OnRightClickToolBar ) );
	g_ToolbarNames[tbMACRO] = _( "Macro" );
	m_QuickSeachBar = new wxAuiToolBar( this, ID_WXTOOLBAR1 + tbQSEARCH, wxPoint( 0, 0 ), wxSize( 392, 29 ), MADTOOBAR_STYLE_NO_OVERFLOW );
	m_QuickSeachBar->Connect( wxEVT_AUITOOLBAR_RIGHT_CLICK, wxAuiToolBarEventHandler( MadEditFrame::OnRightClickToolBar ) );
	g_ToolbarNames[tbQSEARCH] = _( "Quick Search" );
	WxToolBar[tbQSEARCH] = m_QuickSeachBar;
	m_Notebook = new wxMadAuiNotebook( this, ID_NOTEBOOK, wxPoint( 0, 29 ), wxSize( 392, 320 ), wxWANTS_CHARS | wxAUI_NB_TOP | wxAUI_NB_TAB_SPLIT | wxAUI_NB_TAB_MOVE | wxAUI_NB_SCROLL_BUTTONS | wxAUI_NB_WINDOWLIST_BUTTON | wxAUI_NB_CLOSE_ON_ACTIVE_TAB );
	m_Notebook->wxControl::SetWindowStyleFlag( m_Notebook->wxControl::GetWindowStyleFlag() & ~wxTAB_TRAVERSAL );
	m_Notebook->SetDropTarget( new DnDFile() );
	m_Notebook->SetArtProvider( new wxAuiSimpleTabArt );
	g_PreviewTypeNames[ptPREVIEW_HTML] = _( "HTML" );
	g_PreviewTypeNames[ptPREVIEW_MARKDOWN] = _( "Markdown" );
	g_tbSTANDARD_ptr      = WxToolBar[tbSTANDARD];
	g_tbEDITOR_ptr        = WxToolBar[tbEDITOR];
	g_tbSEARCHREPLACE_ptr = WxToolBar[tbSEARCHREPLACE];
	g_tbTEXTVIEW_ptr      = WxToolBar[tbTEXTVIEW];
	g_tbEDITMODE_ptr      = WxToolBar[tbEDITMODE];
	g_tbMACRO_ptr         = WxToolBar[tbMACRO];
	WxMenuBar1 = new wxMenuBar();
	this->SetMenuBar( WxMenuBar1 );
#if USE_CONTEXT_MENU && !defined(__WXGTK__) /*GTK+3 will show this while right clicking on editing erea*/
	Connect( wxEVT_CONTEXT_MENU, wxContextMenuEventHandler( MadEditFrame::OnContextMenu ) );
#endif
	//this->SetToolBar(WxToolBar[tbSTANDARD]);
	this->SetStatusBar( WxStatusBar1 );
	this->SetTitle( wxT( "MadEdit-Mod " ) );
#if !defined(__WXMSW__) //&& !defined(__WXPM__)
	SetIcon( wxIcon( Mad2_xpm ) );
#else // __MSW__
	SetIcon( wxIcon( wxT( "appicon" ) ) );
#endif
	// load MenuText
	{
		CommandData *cd = &CommandTable[0];

		do
		{
			if( cd->menuid_name != 0 )
			{
				MadKeyBindings::AddMenuTextCommand( cd->menu_id, wxString( cd->menuid_name ), cd->command );
			}

			++cd;
		}
		while( cd->menu_level >= 0 );
	}

	// load keybindings
	if( m_Config->Exists( wxT( "/KeyBindings" ) ) )
	{
		m_Config->SetPath( wxT( "/KeyBindings" ) );
		MadEdit::ms_KeyBindings.LoadFromConfig_New( m_Config );
		MadEdit::ms_KeyBindings.AddDefaultBindings( false );
	}
	else
		if( m_Config->Exists( wxT( "/MenuKeys" ) ) )
		{
			m_Config->SetPath( wxT( "/MenuKeys" ) );
			LoadMenuKeys( m_Config );
		}

	// add keybinding of ecToggleWindow
	wxString str = GetMenuKey( wxT( "menuToggleWindow" ), wxEmptyString );

	if( !str.IsEmpty() )
	{
		if( str[0] == wxT( '\t' ) )
		{
			str = str.Right( str.Len() - 1 );
		}

		MadEdit::ms_KeyBindings.Add( StringToShortCut( str ), ecToggleWindow, true );
	}

	//m_ImageList
	m_ImageList = new wxImageList( 16, 15 );

	for( int i = 0; i < ( sizeof( g_MadIcons ) / sizeof( g_MadIcons[0] ) ); ++i )
	{ m_ImageList->Add( wxBitmap( g_MadIcons[i] ) ); }

	// add menuitems
	for( int i = 0; i < ( sizeof( g_Menus ) / sizeof( g_Menus[0] ) ); ++i )
	{ ( *g_Menus[i] ) = new wxMenu( ( long )0 ); }

	list<wxMenu*> menu_stack;
	CommandData *cd = &CommandTable[0];
#define OUTPUT_MENU 0
#if OUTPUT_MENU
#if defined(_DEBUG) && defined(__WXMSW__) //Output all accel key to text file
	wxTextFile KeyTable( g_MadEditAppDir + wxT( "key_table.csv" ) );
	KeyTable.Create();
	KeyTable.Open( wxConvFile );

	if( KeyTable.IsOpened() )
	{
		wxString mapStr, col1( wxT( "			  " ) ), col2( wxT( "								  " ) );
		wxString tTitle( wxT( "  Shortcut	|			   Menu 			  | 		  Function" ) );
		wxString tSep( wxT( "-------------|---------------------------------|-------------------------------------------------" ) );
		wxArrayString keymap;
		KeyTable.Clear();
		KeyTable.AddLine( tTitle );
		KeyTable.AddLine( tSep );

		for( int i  = 0; i < sizeof( CommandTable ) / sizeof( CommandData ); ++i )
		{
			if( CommandTable[i].menu_id != 0/* && *(CommandTable[i].key) != 0*/ )
			{
				wxString tKey( CommandTable[i].key ), tMenu( CommandTable[i].text ), tHint( CommandTable[i].hint );

				if( tKey.Length() < col1.Length() ) { tKey += col1.Left( col1.Length() - tKey.Length() ); }

				if( tMenu.Length() < col2.Length() ) { tMenu += col2.Left( col2.Length() - tMenu.Length() ); }

				mapStr = tKey + wxT( '|' ) + tMenu + wxT( '|' ) + tHint;
				keymap.Add( mapStr );
				KeyTable.AddLine( mapStr );
			}
		}

		KeyTable.AddLine( wxString( wxT( "\n" ) ) );
		KeyTable.AddLine( wxString( wxT( "\n" ) ) );
		KeyTable.AddLine( tTitle );
		KeyTable.AddLine( tSep );
		keymap.Sort();

		for( int j = 0; j < keymap.GetCount(); ++j )
		{
			KeyTable.AddLine( keymap[j] );
		}

#ifdef __WXMAC__
		KeyTable.Write( wxTextFileType_Mac );
#else
		KeyTable.Write( wxTextFileType_Unix );
#endif
		KeyTable.Close();
	}

#endif
#endif
#ifdef __WXMSW__
	bool bHasMenuIcon = ( wxGetOsVersion() != wxOS_WINDOWS_9X ); // fixed win98 will crash if menuitem has icon
#endif
#if OUTPUT_MENU //Output all accel key to text file
	wxTextFile MenuTable( g_MadEditHomeDir + wxT( "MenuTable.txt" ) );
	MenuTable.Create();
	MenuTable.Open( wxConvFile );

	if( MenuTable.IsOpened() )
	{
		wxString tSep = wxT( "Normal:" );
		tSep << wxITEM_NORMAL;
		tSep << wxT( " " );
		tSep << wxT( "Seperator:" );
		tSep << wxITEM_SEPARATOR;
		tSep << wxT( " " );
		tSep << wxT( "Check:" );
		tSep << wxITEM_CHECK;
		MenuTable.AddLine( tSep );
	}

#endif

	do
	{
		if( cd->menu_level == 0 )
		{
			menu_stack.clear();
			menu_stack.push_back( *cd->menu_ptr );
			WxMenuBar1->Append( *cd->menu_ptr, wxGetTranslation( cd->text ) );
			++cd;
			continue;
		}
		else
		{
			if( cd->menu_level < int( menu_stack.size() ) )
			{
				do
				{
					menu_stack.pop_back();
				}
				while( cd->menu_level < int( menu_stack.size() ) );
			}
		}

		if( cd->menu_ptr != 0 )
		{
			menu_stack.back()->Append( cd->menu_id, wxGetTranslation( cd->text ), *cd->menu_ptr );
			menu_stack.push_back( *cd->menu_ptr );
		}
		else
		{
			if( cd->kind == wxITEM_SEPARATOR )
			{
				menu_stack.back()->AppendSeparator();

				if( cd->popmenu_ptr )
				{
					( *( cd->popmenu_ptr ) )->AppendSeparator();
				}
			}
			else
			{
				wxString memLabel( wxGetTranslation( cd->text ) );

				if( memLabel == wxString( wxEmptyString ) )
				{
					memLabel = cd->text;
				}

#if OUTPUT_MENU //Output all accel key to text file

				if( MenuTable.IsOpened() )
				{
					wxString tSep = wxT( "MenuId:" );
					tSep << cd->menu_id;
					tSep << wxT( " " );
					tSep << wxT( "Kind:" );
					tSep << cd->kind;
					tSep << wxT( " " );
					tSep += memLabel;
					MenuTable.AddLine( tSep );
				}

#endif
				wxMenuItem *mit = new wxMenuItem( menu_stack.back(), cd->menu_id, memLabel + GetMenuKey( cd->menuid_name, cd->key ), wxGetTranslation( cd->hint ), cd->kind );
#ifdef __WXMSW__

				if( bHasMenuIcon )
#endif
					if( cd->image_idx >= 0 && cd->kind == wxITEM_NORMAL )
					{
						mit->SetBitmap( m_ImageList->GetBitmap( cd->image_idx ) );
					}

				menu_stack.back()->Append( mit );

				if( cd->popmenu_ptr )
				{
					mit = new wxMenuItem( ( *( cd->popmenu_ptr ) ), cd->menu_id, memLabel + GetMenuKey( cd->menuid_name, cd->key ), wxGetTranslation( cd->hint ), cd->kind );

					if( cd->image_idx >= 0 && cd->kind == wxITEM_NORMAL )
					{
						mit->SetBitmap( m_ImageList->GetBitmap( cd->image_idx ) );
					}

					( *( cd->popmenu_ptr ) )->Append( mit );

					if( cd->menu_id == menuToggleReadOnly )
					{
						( *( cd->popmenu_ptr ) )->AppendSeparator();
						( *( cd->popmenu_ptr ) )->Append( menuCopyFilePath,       _( "Copy full path name" ) );
						( *( cd->popmenu_ptr ) )->Append( menuCopyFileName,       _( "Copy full file name" ) );
						( *( cd->popmenu_ptr ) )->Append( menuCopyFileDir,        _( "Copy directory name" ) );
					}
				}

				if( cd->toolbar_ptr && *( cd->toolbar_ptr ) )
				{
					( *( cd->toolbar_ptr ) )->AddTool( cd->menu_id, memLabel, m_ImageList->GetBitmap( cd->image_idx ), wxNullBitmap, cd->kind, wxGetTranslation( cd->short_help ), wxGetTranslation( cd->hint ), NULL );

					if( cd->apd_toolbar_spr )
					{ ( *( cd->toolbar_ptr ) )->AddSeparator(); }
				}
			}
		}

		++cd;
	}
	while( cd->menu_level >= 0 );

	g_Menu_EditPop->AppendSeparator();
	g_Menu_EditPop->AppendSubMenu( g_Menu_EditSubAdv, _( "Ad&vanced" ) );
	g_Menu_EditPop->AppendSeparator();
	g_Menu_EditPop->AppendSubMenu( g_Menu_EditSubSort, _( "&Sort" ) );
#if OUTPUT_MENU //Output all accel key to text file

	if( MenuTable.IsOpened() )
	{
#ifdef __WXMAC__
		MenuTable.Write( wxTextFileType_Mac );
#else
		MenuTable.Write( wxTextFileType_Unix );
#endif
		MenuTable.Close();
	}

#endif
	// set FindNext/FindPrev keys for search/replace dialog
	g_AccelFindNext.Set( 0, 0, 0, 0 );
	g_AccelFindPrev.Set( 0, 0, 0, 0 );
	wxAcceleratorEntry *ent = GetAccelFromString( g_Menu_Search->GetLabel( menuFindNext ) );

	if( ent != NULL )
	{
		g_AccelFindNext = *ent;
		delete ent;
	}

	ent = GetAccelFromString( g_Menu_Search->GetLabel( menuFindPrevious ) );

	if( ent != NULL )
	{
		g_AccelFindPrev = *ent;
		delete ent;
	}

	{
		size_t cnt = MadEncoding::GetEncodingsCount();

		for( size_t i = 0; i < cnt; ++i )
		{
			wxString enc = wxString( wxT( '[' ) ) + MadEncoding::GetEncodingName( i ) + wxT( "] " );
			wxString des = wxGetTranslation( MadEncoding::GetEncodingDescription( i ).c_str() );
			g_Menu_View_AllEncodings->Append( menuEncoding1 + int( i ), enc + des );
			const std::vector<int>& encGrps = MadEncoding::GetEncodingGrps( i );

			for( size_t j = 0; j < encGrps.size(); ++j )
			{
				wxASSERT( encGrps[j] < ENCG_MAX );

				if( g_Menu_View_EncodingGrps[encGrps[j]] == NULL )
				{ g_Menu_View_EncodingGrps[encGrps[j]] = new wxMenu( ( long )0 ); }

				g_Menu_View_EncodingGrps[encGrps[j]]->Append( menuEncoding1 + int( i ), enc + des );
			}
		}

		g_Menu_View_Encoding->AppendSeparator();

		for( int encgid = 0; encgid < ENCG_MAX; ++encgid )
		{
			if( g_Menu_View_EncodingGrps[encgid] )
			{ g_Menu_View_Encoding->Append( menuEncodingGroup1 + encgid, MadEncoding::GetGroupNameById( encgid ), g_Menu_View_EncodingGrps[encgid] ); }
		}
	}

	{
		size_t cnt = MadSyntax::GetSyntaxCount();

		for( size_t i = 0; i < cnt; ++i )
		{
			g_Menu_View_Syntax->Append( menuSyntax1 + int( i ), MadSyntax::GetSyntaxTitle( i ) );
		}
	}

	{
		MadFontEnumerator fontenumerator;
		fontenumerator.EnumerateFacenames(); // get all fontnames
		size_t count = g_FontNames.Count();

		for( size_t i = 0; i < count; ++i )
		{
			wxString &name = g_FontNames[i];
			wxChar firstchar = name[0];

			if( firstchar <= 'Z' && firstchar >= 'A' )
			{
				firstchar |= 0x20; // to lower case
			}

			wxMenu *menu = g_Menu_View_Font6;

			if( firstchar == wxT( '@' ) )
			{
				menu = g_Menu_View_Font0;
			}
			else
				if( firstchar <= 'z' && firstchar >= 'a' )
				{
					if( firstchar <= 'e' ) { menu = g_Menu_View_Font1; }
					else
						if( firstchar <= 'j' ) { menu = g_Menu_View_Font2; }
						else
							if( firstchar <= 'o' ) { menu = g_Menu_View_Font3; }
							else
								if( firstchar <= 't' ) { menu = g_Menu_View_Font4; }
								else
									if( firstchar <= 'z' ) { menu = g_Menu_View_Font5; }
				}

			menu->Append( menuFontName1 + int( i ), name );
		}
	}

	{
		for( int i = 0; i < tbMAX; ++i )
		{
			g_Menu_Toolbars->Append( menuToolBar1 + i, g_ToolbarNames[i], wxEmptyString, wxITEM_CHECK );
		}
	}

	{
		for( int i = ptPREVIEW_HTML; i < ptPREVIEW_MAXTYPE; ++i )
		{
			g_Menu_View_Preview->Append( i, g_PreviewTypeNames[i], wxEmptyString, wxITEM_CHECK );
		}
	}

	if( !m_Config->Exists( wxT( "/KeyBindings" ) ) )
	{
		if( m_Config->Exists( wxT( "/EditKeys" ) ) )
		{
			m_Config->SetPath( wxT( "/EditKeys" ) );
			MadEdit::ms_KeyBindings.LoadFromConfig( m_Config );
		}
		else
		{
			MadEdit::ms_KeyBindings.AddDefaultBindings( true );
		}
	}

	ResetAcceleratorTable();
	/***/
	m_RecentFiles = new MadRecentList();
	m_RecentFiles->UseMenu( g_Menu_File_RecentFiles );
	m_Config->SetPath( wxT( "/RecentFiles" ) );
	m_RecentFiles->Load( *m_Config );
	m_RecentEncodings = new MadRecentList( 9, menuRecentEncoding1 );
	m_RecentEncodings->UseMenu( g_Menu_View_Encoding );
	m_Config->SetPath( wxT( "/RecentEncodings" ) );
	m_RecentEncodings->Load( *m_Config );
	m_RecentFonts = new MadRecentList( 9, menuRecentFont1 );
	m_RecentFonts->UseMenu( g_Menu_View_FontName );
	m_Config->SetPath( wxT( "/RecentFonts" ) );
	m_RecentFonts->Load( *m_Config );
	// status bar field widths
#if (wxMAJOR_VERSION < 3)
	int width0 = GetClientSize().GetWidth() - g_StatusWidth_1_6;

	if( width0 < 0 ) { width0 = 0; }

	g_StatusWidths[0] = width0;
#else
	g_StatusWidths[0] = -1;
#endif
	WxStatusBar1->SetFieldsCount( 7, g_StatusWidths );

	//WxStatusBar1->SetFieldsCount(7, g_StatusWidths);
	//int styles[7]={wxSB_RAISED, wxSB_RAISED, wxSB_RAISED, wxSB_RAISED, wxSB_RAISED, wxSB_RAISED, wxSB_RAISED};
	//WxStatusBar1->SetStatusStyles(7, styles);
	/*
	// load plugins
	wxPluginLibrary *lib = wxPluginManager::LoadLibrary(wxT("./plugin"));
	if(lib)
	{
	    wxLogWarning(wxString::Format(wxT("Loaded [ %s ]\n"), wxT("plugin")));
	                      //wxString(path + filename).c_str()));

	    if(lib->HasSymbol(wxT("PluginProc")))
	    {
	        //typedef const wchar_t* (*GetNameProc)();
	        typedef int (*PluginProc_Proc)(int PluginID, int nMsg, void* pParam);
	        PluginProc_Proc PluginProc=(PluginProc_Proc)lib->GetSymbol(wxT("PluginProc"));

	        if(PluginProc)
	        {
	            wchar_t *name;

	            PluginProc(0, PL_GET_NAME, (void*)&name);
	            wxLogWarning(wxString::Format(wxT("GetName: [%s]\n"), name));

	            char **xpm;
	            PluginProc(0, PL_GET_XPM, (void*)&xpm);
	            m_ImageList->Add(wxBitmap(xpm));

	        }
	    }
	}
	*/
	for( int tbId = tbSTANDARD; tbId <= tbMACRO; ++tbId )
	{ WxToolBar[tbId]->Realize(); }

	m_AuiManager.AddPane( WxToolBar[tbSTANDARD],      wxAuiPaneInfo().Name( wxT( "WxToolBar1" ) ).CloseButton( false ).Caption( wxT( "Starndard" ) ).Floatable().ToolbarPane().Top().Position( 0 ) );
	m_AuiManager.AddPane( WxToolBar[tbEDITOR],        wxAuiPaneInfo().Name( wxT( "WxToolBar2" ) ).CloseButton( false ).Caption( wxT( "Editor" ) ).Floatable().ToolbarPane().Top().Position( 1 ) );
	m_AuiManager.AddPane( WxToolBar[tbSEARCHREPLACE], wxAuiPaneInfo().Name( wxT( "WxToolBar3" ) ).CloseButton( false ).Caption( wxT( "Search/Replace" ) ).Floatable().ToolbarPane().Top().Position( 2 ) );
	m_AuiManager.AddPane( WxToolBar[tbTEXTVIEW],      wxAuiPaneInfo().Name( wxT( "WxToolBar4" ) ).CloseButton( false ).Caption( wxT( "Text View" ) ).Floatable().ToolbarPane().Top().Position( 3 ) );
	m_AuiManager.AddPane( WxToolBar[tbEDITMODE],      wxAuiPaneInfo().Name( wxT( "WxToolBar5" ) ).CloseButton( false ).Caption( wxT( "Edit Mode" ) ).Floatable().ToolbarPane().Top().Position( 4 ) );
	m_AuiManager.AddPane( WxToolBar[tbMACRO],         wxAuiPaneInfo().Name( wxT( "WxToolBar6" ) ).CloseButton( false ).Caption( wxT( "Macro" ) ).Floatable().ToolbarPane().Top().Position( 5 ) );
	bool bb;
	m_ToolbarStatus[tbMAX] = false;
	m_Config->Read( wxT( "/MadEdit/ShowToolbarStandard" ), &bb, true );
	m_ToolbarStatus[tbSTANDARD] = bb;
	m_ToolbarStatus[tbMAX] = ( m_ToolbarStatus[tbMAX] | bb );

	if( !bb )
	{ m_AuiManager.GetPane( WxToolBar[tbSTANDARD] ).Hide(); }

	m_Config->Read( wxT( "/MadEdit/ShowToolbarEditor" ), &bb, true );
	m_ToolbarStatus[tbEDITOR] = bb;
	m_ToolbarStatus[tbMAX] = ( m_ToolbarStatus[tbMAX] | bb );

	if( !bb )
	{ m_AuiManager.GetPane( WxToolBar[tbEDITOR] ).Hide(); }

	m_Config->Read( wxT( "/MadEdit/ShowToolbarSearchReplace" ), &bb, true );
	m_ToolbarStatus[tbSEARCHREPLACE] = bb;
	m_ToolbarStatus[tbMAX] = ( m_ToolbarStatus[tbMAX] | bb );

	if( !bb )
	{ m_AuiManager.GetPane( WxToolBar[tbSEARCHREPLACE] ).Hide(); }

	m_Config->Read( wxT( "/MadEdit/ShowToolbarTextview" ), &bb, true );
	m_ToolbarStatus[tbTEXTVIEW] = bb;
	m_ToolbarStatus[tbMAX] = ( m_ToolbarStatus[tbMAX] | bb );

	if( !bb )
	{ m_AuiManager.GetPane( WxToolBar[tbTEXTVIEW] ).Hide(); }

	m_Config->Read( wxT( "/MadEdit/ShowToolbarEditMode" ), &bb, true );
	m_ToolbarStatus[tbEDITMODE] = bb;
	m_ToolbarStatus[tbMAX] = ( m_ToolbarStatus[tbMAX] | bb );

	if( !bb )
	{ m_AuiManager.GetPane( WxToolBar[tbEDITMODE] ).Hide(); }

	m_Config->Read( wxT( "/MadEdit/ShowToolbarMacro" ), &bb, true );
	m_ToolbarStatus[tbMACRO] = bb;
	m_ToolbarStatus[tbMAX] = ( m_ToolbarStatus[tbMAX] | bb );

	if( !bb )
	{ m_AuiManager.GetPane( WxToolBar[tbMACRO] ).Hide(); }

	{
		// enum all madpython files under scripts
		wxString scriptsLibDir = g_MadEditHomeDir + wxT( "scripts" ) + wxFILE_SEP_PATH, filename;

		if( wxDirExists( scriptsLibDir ) )
		{
			wxDir dir( scriptsLibDir );
			static wxString hlp_prefix( wxT( "####" ) );
			size_t i = 0;
			//bool hasHelp = false;
			bool cont = dir.GetFirst( &filename, wxT( "*.mpy" ), wxDIR_FILES );

			if( cont )
			{
				g_Menu_MadMacro_Scripts->AppendSeparator();
				g_tbMACRO_ptr->AddSeparator();
			}

			while( cont )
			{
				filename = scriptsLibDir + filename;
				wxString help, firstLine;
				wxFileName fn( filename );
				wxTextFile scriptfile( filename );
				scriptfile.Open( wxConvFile );
				//hasHelp = false;

				if( scriptfile.IsOpened() )
				{
					firstLine = scriptfile.GetFirstLine();

					if( !firstLine.StartsWith( hlp_prefix, &help ) )
					{
						help.Empty();
					}

					g_Menu_MadMacro_Scripts->Append( menuMadScrip1 + int( i ), fn.GetName(), help );
					g_tbMACRO_ptr->AddTool( menuMadScrip1 + int( i ), _T( "Macro" ), m_ImageList->GetBitmap( saverec_xpm_idx ), wxNullBitmap, wxITEM_NORMAL, fn.GetName(), help, NULL );
					++i;
				}

				cont = dir.GetNext( &filename );
			}
		}
	}

	m_QuickSearch = new wxComboBox( m_QuickSeachBar, ID_QUICKSEARCH, wxEmptyString, wxDefaultPosition, wxSize( 200, 21 ) );
	g_RecentFindText = new MadRecentList( 20, ID_RECENTFINDTEXT1, true ); //Should be freed in SearchDialog
	wxString oldpath = m_Config->GetPath();
	m_Config->SetPath( wxT( "/RecentFindText" ) );
	g_RecentFindText->Load( *m_Config );
	m_Config->SetPath( oldpath );
	size_t count = g_RecentFindText->GetCount();

	if( count > 0 )
	{
		wxString text = g_RecentFindText->GetHistoryFile( 0 );
		m_QuickSearch->SetValue( text );
		m_QuickSearch->Append( text );

		for( size_t i = 1; i < count; ++i ) { m_QuickSearch->Append( g_RecentFindText->GetHistoryFile( i ) ); }
	}

	m_QuickSearch->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MadEditFrame::MadEditFrameKeyDown ) );
	m_QuickSeachBar->AddControl( m_QuickSearch );
	m_QuickSeachBar->AddTool( menuQuickFindNext, wxT( "QuickFindNext" ), m_ImageList->GetBitmap( down_xpm_idx ), wxNullBitmap, wxITEM_NORMAL, _( "Find Next" ), _( "Find matched text next to caret" ), NULL );
	m_QuickSeachBar->AddTool( menuQuickFindPrevious, wxT( "QuickFindPrevious" ), m_ImageList->GetBitmap( up_xpm_idx ), wxNullBitmap, wxITEM_NORMAL, _( "Find Previous" ), _( "Find matched text previous from caret" ), NULL );
	m_CheckboxWholeWord = new wxCheckBox( m_QuickSeachBar, ID_QUICKSEARCHWHOLEWORD, _( "Whole Word" ) );
	m_CheckboxWholeWord->SetValue( false );
	m_CheckboxWholeWord->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MadEditFrame::MadEditFrameKeyDown ) );
	m_QuickSeachBar->AddControl( m_CheckboxWholeWord );
	m_CheckboxCaseSensitive = new wxCheckBox( m_QuickSeachBar, ID_QUICKSEARCHCASESENSITIVE, _( "Case Sensitive" ) );
	m_CheckboxCaseSensitive->SetValue( false );
	m_QuickSeachBar->AddControl( m_CheckboxCaseSensitive );
	m_CheckboxRegEx = new wxCheckBox( m_QuickSeachBar, ID_QUICKSEARCHREGEX, _( "Regular Expression" ) );
	m_CheckboxRegEx->SetValue( false );
	m_CheckboxCaseSensitive->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MadEditFrame::MadEditFrameKeyDown ) );
	m_QuickSeachBar->AddControl( m_CheckboxRegEx );
	m_QuickSeachBar->Realize();
	m_AuiManager.AddPane( m_QuickSeachBar, wxAuiPaneInfo().Name( wxT( "QuickSeachBar" ) ).CloseButton( false ).Caption( _( "Quick Search" ) ).Floatable( true ).ToolbarPane().Top().Row( 2 ) );
	bool showQsBar = m_Config->ReadBool( wxT( "/MadEdit/ShowQSearchBarOnStart" ), true );

	if( !showQsBar )
	{ m_AuiManager.GetPane( m_QuickSeachBar ).Hide(); }

	m_ToolbarStatus[tbQSEARCH] = showQsBar;
	// information window
	int infoW = 300, infoH = 130;
	m_Config->Read( wxT( "/MadEdit/InfoWindowWidth" ), &infoW );
	m_Config->Read( wxT( "/MadEdit/InfoWindowHeight" ), &infoH );
	wxSize nbsize( infoW, infoH );
	m_InfoNotebook = new wxAuiNotebook( this, ID_OUTPUTNOTEBOOK, wxDefaultPosition, nbsize, wxAUI_NB_TOP | wxAUI_NB_SCROLL_BUTTONS );
	m_FindInFilesResults = new MadTreeCtrl( m_InfoNotebook, ID_FINDINFILESRESULTS, wxDefaultPosition, wxSize( infoW, 4 ), wxTR_DEFAULT_STYLE | wxTR_HIDE_ROOT );
	m_FindInFilesResults->AddRoot( wxT( "Root" ) );
	m_FindInFilesResults->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( MadEditFrame::OnFindInFilesResultsDClick ) );
	m_InfoNotebook->AddPage( m_FindInFilesResults, _( "Search Results" ) );
	m_InfoNotebook->Connect( wxEVT_SIZE, wxSizeEventHandler( MadEditFrame::OnInfoNotebookSize ) );
	// wxAUI
	m_AuiManager.SetManagedWindow( this );
	m_AuiManager.SetFlags( m_AuiManager.GetFlags() | wxAUI_MGR_ALLOW_ACTIVE_PANE );
	m_AuiManager.SetDockSizeConstraint( 0.75, 0.75 );
	m_AuiManager.AddPane( m_Notebook, wxCENTER );
	m_AuiManager.AddPane( m_InfoNotebook, wxBOTTOM, _( "Information Window" ) );
	m_AuiManager.GetPane( m_InfoNotebook ).Show( false ).FloatingSize( nbsize );
	m_AuiManager.Update();

	if( g_tbMACRO_ptr->GetToolCount() <= 5 )
	{
		g_tbMACRO_ptr->SetOverflowVisible( false );
		g_tbMACRO_ptr->Realize();
	}

	// fixed for using wxAUI
	WxStatusBar1->Connect( wxEVT_SIZE, wxSizeEventHandler( MadEditFrame::OnSize ) );
}

void MadEditFrame::MadEditFrameClose( wxCloseEvent& event )
{
	// --> Don't use Close with a Frame,
	// use Destroy instead.
	if( event.CanVeto() )
	{
		if( QueryCloseAllFiles() == false )
		{
			event.Veto( true );
			return;
		}
	}

	// save ReloadFilesList
	wxString files;
	int count = int( m_Notebook->GetPageCount() );
	bool bb = m_ReloadFiles;

	//m_Config->Read(wxT("ReloadFiles"), &bb);
	if( bb && count > 0 )
	{
		count = m_Notebook->GetFilesList( files );
		wxString selname = g_ActiveMadEdit->GetFileName();

		if( count != 1 && !selname.IsEmpty() )
		{
			files += selname; // append selname to activate it
			files += wxT( '|' );
		}
	}

	m_Config->Write( wxT( "/MadEdit/ReloadFilesList" ), files );
	bb = m_PurgeHistory;

	//m_Config->Read(wxT("/MadEdit/PurgeHistory"), &bb);
	if( bb )
	{
		PurgeRecentFiles();
		PurgeRecentFonts();
		PurgeRecentEncodings();
		extern bool g_ForcePurgeThisTime;

		if( g_ForcePurgeThisTime )
		{
			if( g_SearchReplaceDialog == NULL )
			{
				g_SearchReplaceDialog = new MadSearchReplaceDialog( this, -1 );
			}

			if( g_FindInFilesDialog == NULL )
			{
				g_FindInFilesDialog = new MadFindInFilesDialog( this, -1 );
			}
		}

		if( g_SearchReplaceDialog != NULL )
		{
			if( g_SearchReplaceDialog->IsShown() )
			{ g_SearchReplaceDialog->Show( false ); }

			g_SearchReplaceDialog->PurgeRecentFindTexts();
			g_SearchReplaceDialog->PurgeRecentReplaceTexts();
		}

		if( g_FindInFilesDialog != NULL )
		{
			if( g_FindInFilesDialog->IsShown() )
			{ g_FindInFilesDialog->Show( false ); }

			g_FindInFilesDialog->PurgeRecentFindDirs();
			g_FindInFilesDialog->PurgeRecentFindFilters();
			g_FindInFilesDialog->PurgeRecentFindExcludes();
		}

		m_QuickSearch->Clear();
	}

	m_Config->SetPath( wxT( "/FileCaretPos" ) );
	g_FileCaretPosManager.Save( m_Config );
	// changed: gogo, 30.08.2009 ---
	int x, y;
#ifdef __WXMSW__
	//int style=::GetWindowLong((HWND)GetHWND(), GWL_STYLE);
	//m_Config->Write(wxT("/MadEdit/WindowMaximize"), (style&WS_MAXIMIZE)!=0 );
	WINDOWPLACEMENT wp;
	wp.length = sizeof( WINDOWPLACEMENT );
	GetWindowPlacement( ( HWND ) GetHWND(), &wp );
	m_Config->Write( wxT( "/MadEdit/WindowMaximize" ), wp.showCmd == SW_SHOWMAXIMIZED );
	m_Config->Write( wxT( "/MadEdit/WindowLeft" ),  wp.rcNormalPosition.left );
	m_Config->Write( wxT( "/MadEdit/WindowTop" ),   wp.rcNormalPosition.top );
	m_Config->Write( wxT( "/MadEdit/WindowWidth" ), wp.rcNormalPosition.right - wp.rcNormalPosition.left );
	m_Config->Write( wxT( "/MadEdit/WindowHeight" ), wp.rcNormalPosition.bottom - wp.rcNormalPosition.top );
	//#endif
#else
	GetPosition( &x, &y );
	m_Config->Write( wxT( "/MadEdit/WindowLeft" ), x );
	m_Config->Write( wxT( "/MadEdit/WindowTop" ), y );
	GetSize( &x, &y );
	m_Config->Write( wxT( "/MadEdit/WindowWidth" ), x );
	m_Config->Write( wxT( "/MadEdit/WindowHeight" ), y );
#endif
	//------------------
	m_Config->SetPath( wxT( "/RecentFiles" ) );
	m_RecentFiles->Save( *m_Config );
	m_Config->SetPath( wxT( "/RecentEncodings" ) );
	m_RecentEncodings->Save( *m_Config );
	m_Config->SetPath( wxT( "/RecentFonts" ) );
	m_RecentFonts->Save( *m_Config );

	if( g_SearchReplaceDialog != NULL )
	{
		if( g_SearchReplaceDialog->IsShown() )
		{ g_SearchReplaceDialog->Show( false ); }

		m_Config->SetPath( wxT( "/RecentFindText" ) );
		g_SearchReplaceDialog->m_RecentFindText->Save( *m_Config );
		m_Config->SetPath( wxT( "/RecentReplaceText" ) );
		g_SearchReplaceDialog->m_RecentReplaceText->Save( *m_Config );
		// add: gogo, 19.09.2009
		g_SearchReplaceDialog->GetPosition( &x, &y );
		m_Config->Write( wxT( "/MadEdit/SearchWinLeft" ), x );
		m_Config->Write( wxT( "/MadEdit/SearchWinTop" ), y );
		m_Config->Write( wxT( "/MadEdit/SearchThrEndOfFile" ), g_SearchReplaceDialog->WxCheckBoxSearchThrEndOfFile->GetValue() );

		if( CanSetTransparent() )
		{
			m_Config->Write( wxT( "/MadEdit/AlwaysTransparent" ), g_SearchReplaceDialog->WxRadioAlways->GetValue() );
			long trans = 25;
			m_Config->Read( wxT( "/MadEdit/Transparency" ), &trans );
		}

		//----------
	}

	if( g_FindInFilesDialog != NULL )
	{
		if( g_FindInFilesDialog->IsShown() )
		{ g_FindInFilesDialog->Show( false ); }

		m_Config->SetPath( wxT( "/RecentFindDir" ) );
		g_FindInFilesDialog->m_RecentFindDir->Save( *m_Config );
		m_Config->SetPath( wxT( "/RecentFindFilter" ) );
		g_FindInFilesDialog->m_RecentFindFilter->Save( *m_Config );
		m_Config->SetPath( wxT( "/RecentFindExcludeFilter" ) );
		g_FindInFilesDialog->m_RecentFindExclude->Save( *m_Config );
	}

	// reset SearchInSelection
	m_Config->Write( wxT( "/MadEdit/SearchInSelection" ), false );
	m_Config->Write( wxT( "/MadEdit/SearchFrom" ), wxEmptyString );
	m_Config->Write( wxT( "/MadEdit/SearchTo" ), wxEmptyString );
	m_Config->Write( wxT( "/MadEdit/ShowToolbarStandard" ), m_ToolbarStatus[tbSTANDARD] );
	m_Config->Write( wxT( "/MadEdit/ShowToolbarEditor" ), m_ToolbarStatus[tbEDITOR] );
	m_Config->Write( wxT( "/MadEdit/ShowToolbarSearchReplace" ), m_ToolbarStatus[tbSEARCHREPLACE] );
	m_Config->Write( wxT( "/MadEdit/ShowToolbarTextview" ), m_ToolbarStatus[tbTEXTVIEW] );
	m_Config->Write( wxT( "/MadEdit/ShowToolbarEditMode" ), m_ToolbarStatus[tbEDITMODE] );
	m_Config->Write( wxT( "/MadEdit/ShowToolbarMacro" ), m_ToolbarStatus[tbMACRO] );
	delete m_RecentFiles;
	m_RecentFiles = NULL;
	delete m_RecentEncodings;
	m_RecentEncodings = NULL;
	delete m_RecentFonts;
	m_RecentFonts = NULL;
	delete m_ImageList;
	MadEncoding::FreeEncodings();
	FreeConvertChineseTable();
	//delete g_PrintData;
	delete g_PageSetupData;
	g_PageSetupData = NULL;
	extern void DeleteConfig();
	DeleteConfig();
	m_AuiManager.UnInit();

	if( g_ASFormatter != NULL )
	{
		delete g_ASFormatter;
	}

	if( g_MadToolHtmlWin ) { delete g_MadToolHtmlWin; }

	g_MainFrame = 0;
#ifndef __WXMSW__
	// it will crash randomly under linux.
	// so we must call exit() to quit the app.
	exit( 0 );
#else
	Destroy(); // quit app normally.
#endif
}

/*
 * MadEditFrameKeyDown
 */
void MadEditFrame::MadEditFrameKeyDown( wxKeyEvent& event )
{
	int key = event.GetKeyCode();

	switch( key )
	{
	case WXK_ESCAPE:
		if( g_SearchReplaceDialog )
		{
			g_SearchReplaceDialog->Show( false );
		}

		if( g_FindInFilesDialog )
		{
			g_FindInFilesDialog->Show( false );
		}

		if( g_MainFrame->m_ToolbarStatus[tbQSEARCH] )
		{
			g_MainFrame->HideQuickFindBar();

			if( g_ActiveMadEdit )
			{
				g_ActiveMadEdit->SetFocus();
				g_ActiveMadEdit->Refresh( false );
			}
		}

		break;
	}

	event.Skip();
}

void MadEditFrame::SetPageFocus( int pageId )
{
	int selid = m_Notebook->GetSelection();

	if( pageId != selid && pageId >= 0 && pageId < int( m_Notebook->GetPageCount() ) )
	{
		m_Notebook->SetSelection( pageId );
		MadEdit *cme = ( MadEdit* )m_Notebook->GetPage( m_Notebook->GetSelection() );

		if( cme != g_ActiveMadEdit )
		{
			wxAuiNotebookEvent event( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, m_Notebook->GetId() );
			event.SetSelection( pageId );
			event.SetOldSelection( selid );
			event.SetEventObject( this );
			OnNotebookPageChanged( event );
		}
	}
}

MadEdit *MadEditFrame::GetEditByFileName( const wxString &filename, int &id )
{
	int count = int( m_Notebook->GetPageCount() );
	wxString fn;

	for( id = 0; id < count; ++id )
	{
		MadEdit *me = ( MadEdit* )m_Notebook->GetPage( id );
		fn = me->GetFileName();
#ifdef __WXMSW__

		if( MadStrLower( fn ) == MadStrLower( filename ) )
			//if(fn.Lower()==filename.Lower())
#else
		if( fn == filename )
#endif
		{
			return me;
		}
	}

	id = -1;
	return NULL;
}

void MadEditFrame::ResetAcceleratorTable()
{
	vector<wxAcceleratorEntry> entries;
	MadEdit::ms_KeyBindings.BuildAccelEntries( true, entries );

	if( entries.size() > 0 )
	{
		wxAcceleratorTable accel( int( entries.size() ), &entries[0] );
		this->SetAcceleratorTable( accel );
	}
}

#ifdef __WXMSW__
WXLRESULT MadEditFrame::MSWWindowProc( WXUINT message, WXWPARAM wParam, WXLPARAM lParam )
{
	switch( message )
	{
	case WM_COPYDATA:
		{
			COPYDATASTRUCT *pcds = *( ( COPYDATASTRUCT** )&lParam );
			OnReceiveMessage( ( wxChar* )pcds->lpData, pcds->cbData );
		}

		return TRUE;
	}

	return wxFrame::MSWWindowProc( message, wParam, lParam );
}
#endif


void MadEditFrame::OnNotebookPageChanging( wxAuiNotebookEvent& event )
{
	g_PrevPageID = event.GetOldSelection();
}

void MadEditFrame::OnNotebookPageChanged( wxAuiNotebookEvent& event )
{
	g_ActiveMadEdit = ( MadEdit* )m_Notebook->GetPage( m_Notebook->GetSelection() );
	int now = event.GetSelection();
	int old = event.GetOldSelection();

	if( event.GetEventObject() == this )
	{
		old = event.GetOldSelection();
	}

	//wxLogDebug(wxT("curr :%d,  prev: %d"), now, old);

	if( old != now && old >= 0 )
	{
		g_PrevPageID = old;
	}

	//wxLogMessage( wxString()<<int(g_ActiveMadEdit));
	if( g_ActiveMadEdit != NULL )
	{
		g_ActiveMadEdit->SetFocus();
		wxString title = g_ActiveMadEdit->GetFileName();

		if( title.IsEmpty() )
		{
			title = m_Notebook->GetPageText( event.GetSelection() );
		}

		if( g_ActiveMadEdit->IsModified() && title[title.Len() - 1] != wxT( '*' ) )
		{ title += wxT( '*' ); }

		SetTitle( wxString( wxT( "MadEdit-Mod - [" ) ) + title + wxString( wxT( "] " ) ) );
		OnEditSelectionChanged( g_ActiveMadEdit );
		OnEditStatusChanged( g_ActiveMadEdit );

		if( g_CheckModTimeForReload )
		{
			g_ActiveMadEdit->ReloadByModificationTime();
		}

		if( m_PreviewType != ptPREVIEW_NONE )
		{
			wxString text;
			g_ActiveMadEdit->GetText( text, false );

			if( m_PreviewType == ptPREVIEW_MARKDOWN )
			{
				std::wstring src = text.ToStdWstring();
				std::wostringstream out;
				markdown::Document doc;
				doc.read( src );
				doc.write( out );
				text = out.str();
			}

			m_HtmlPreview->SetPage( text );
			g_ActiveMadEdit->Synced();
		}
	}
	else
	{
		SetTitle( wxString( wxT( "MadEdit-Mod " ) ) );
	}
}

void MadEditFrame::OnNotebookPageClosing( wxAuiNotebookEvent& event )
{
	if( m_PageClosing )
	{
		return;
	}

	m_PageClosing = true;

	if( QueryCloseFile( event.GetSelection() ) == false )
	{
		event.Veto();
	}
	else
	{
		if( m_Notebook->GetPageCount() == 1 ) //close last file
		{
			OnNotebookPageClosed( true );
		}
	}

	m_PageClosing = false;
}

void MadEditFrame::OnNotebookPageClosed( bool bZeroPage )
{
	if( bZeroPage || m_Notebook->GetPageCount() == 0 )
	{
		g_ActiveMadEdit = NULL;
		SetTitle( wxString( wxT( "MadEdit " ) ) );
		OnEditSelectionChanged( NULL );
		OnEditStatusChanged( NULL );
	}
	else
	{
		MadEdit *madedit = ( MadEdit* )m_Notebook->GetPage( m_Notebook->GetSelection() );

		if( g_ActiveMadEdit != madedit )
		{
			g_ActiveMadEdit = madedit;
			OnEditSelectionChanged( g_ActiveMadEdit );
			OnEditStatusChanged( g_ActiveMadEdit );
			wxString title = g_ActiveMadEdit->GetFileName();

			if( title.IsEmpty() )
			{
				title = m_Notebook->GetPageText( m_Notebook->GetSelection() );
			}

			if( g_ActiveMadEdit->IsModified() && title[title.Len() - 1] != wxT( '*' ) )
			{ title += wxT( '*' ); }

			SetTitle( wxString( wxT( "MadEdit-Mod - [" ) ) + title + wxString( wxT( "] " ) ) );
		}

		g_ActiveMadEdit->ReloadByModificationTime();
	}
}

void MadEditFrame::OnNotebookPageRightUp( wxAuiNotebookEvent& event )
{
	int now = event.GetSelection();
	SetPageFocus( now );
	PopupMenu( g_Menu_FilePop );
}

void MadEditFrame::OnSize( wxSizeEvent &evt )
{
	evt.Skip();
#if (wxMAJOR_VERSION < 3)
	int width0 = g_MainFrame->GetClientSize().GetWidth() - g_StatusWidth_1_6;

	if( width0 < 0 ) { width0 = 0; }

	g_StatusWidths[0] = width0;
#else
	g_StatusWidths[0] = -1;
#endif
	g_MainFrame->WxStatusBar1->SetFieldsCount( 7, g_StatusWidths );
	//static int n=0;
	//g_MainFrame->SetTitle(wxString::Format(wxT("%d %d %d"), n++, g_MainFrame->GetClientSize().GetWidth(), width0));
}

//void MadEditFrame::OnChar(wxKeyEvent& evt)
//{
//wxLogDebug(wxT("frame OnChar"));
//evt.Skip();
//}

void MadEditFrame::OnActivate( wxActivateEvent &evt )
{
	DBOUT( "MadEditFrame::OnActivate\n" );

	if( evt.GetActive() && g_ActiveMadEdit )
	{
		//g_ActiveMadEdit->SetFocus();
		g_ActiveMadEdit->ReloadByModificationTime( true );
	}

	evt.Skip();
}

//---------------------------------------------------------------------------

void MadEditFrame::LoadMenuKeys( wxConfigBase *config )
{
	wxString key, menu;
	long idx = 0;
	bool kcont = config->GetNextEntry( key, idx );

	while( kcont )
	{
		config->Read( key, &menu );
		int menuid = MadKeyBindings::TextToMenuId( menu );
		MadEditShortCut sc = StringToShortCut( key );

		if( menuid != 0 && sc != 0 )
		{
			MadEdit::ms_KeyBindings.Add( sc, true, menuid, true );
		}

		kcont = config->GetNextEntry( key, idx );
	}
}

wxString MadEditFrame::GetMenuKey( const wxString &menu, const wxString &defaultkey )
{
	wxString key = MadEdit::ms_KeyBindings.GetKeyByMenuText( menu );

	if( !key.IsEmpty() )
	{
		return wxString( wxT( "\t" ) ) + key;
	}

	// defaultkey is empty
	if( defaultkey.IsEmpty() )
	{
		return wxEmptyString;
	}

	// check the defaultkey is applied to other menuitem or not
	if( MadEdit::ms_KeyBindings.KeyIsAssigned( defaultkey ) )
	{
		return wxEmptyString;
	}

	// the defaultkey doesn't apply yet, add it
	int menuid = MadKeyBindings::TextToMenuId( menu );
	MadEditShortCut sc = StringToShortCut( defaultkey );

	if( menuid != 0 && sc != 0 )
	{
		MadEdit::ms_KeyBindings.Add( sc, true, menuid, true );
	}

	return wxString( wxT( "\t" ) ) + defaultkey;
}

void MadEditFrame::OnInfoNotebookSize( wxSizeEvent &evt )
{
	wxAuiPaneInfo &pinfo = g_MainFrame->m_AuiManager.GetPane( g_MainFrame->m_InfoNotebook );

	if( pinfo.IsOk() ) // && pinfo.IsShown())
	{
		wxSize size;

		if( pinfo.IsDocked() )
		{
			size = g_MainFrame->m_InfoNotebook->GetSize();
		}
		else
		{
			if( pinfo.frame != NULL )
			{
				size = pinfo.frame->GetSize();
			}
			else
			{
				size.x = 0;
			}
		}

		if( size.x > 16 && size.y > 16 )
		{
			if( pinfo.IsDocked() )
			{
				if( pinfo.dock_direction == wxAUI_DOCK_TOP || pinfo.dock_direction == wxAUI_DOCK_BOTTOM )
				{
					pinfo.floating_size.y = size.y;
					pinfo.best_size.y = size.y;
					g_MainFrame->m_Config->Write( wxT( "/MadEdit/InfoWindowHeight" ), size.y );
				}
				else
				{
					pinfo.floating_size.x = size.x;
					pinfo.best_size.x = size.x;
					g_MainFrame->m_Config->Write( wxT( "/MadEdit/InfoWindowWidth" ), size.x );
				}
			}
			else //IsFloating()
			{
				pinfo.BestSize( size );
				g_MainFrame->m_Config->Write( wxT( "/MadEdit/InfoWindowWidth" ), size.x );
				g_MainFrame->m_Config->Write( wxT( "/MadEdit/InfoWindowHeight" ), size.y );
			}
		}
	}

	evt.Skip();
}

void MadEditFrame::OnFindInFilesResultsDClick( wxMouseEvent& event )
{
	MadEdit *madedit = NULL;
	int flags;
	wxTreeItemId id = g_MainFrame->m_FindInFilesResults->HitTest( event.GetPosition(), flags );

	if( id.IsOk() )
	{
		CaretPosData *cpdata = ( CaretPosData* )g_MainFrame->m_FindInFilesResults->GetItemData( id );

		if( cpdata )
		{
			int count = int( g_MainFrame->m_Notebook->GetPageCount() );

			if( cpdata->pageid >= 0 && cpdata->pageid < count )
			{
				wxString title = g_MainFrame->m_Notebook->GetPageText( cpdata->pageid );

				if( title[title.Len() - 1] == wxT( '*' ) )
				{ title.Truncate( title.Len() - 1 ); }

				wxFileName fname( cpdata->filename );

				if( title == fname.GetFullName() )
				{
					g_MainFrame->SetPageFocus( cpdata->pageid );
					madedit = g_ActiveMadEdit;
				}
			}

			if( madedit == NULL && wxFileExists( cpdata->filename ) )
			{
				g_MainFrame->OpenFile( cpdata->filename, true );
#ifdef __WXMSW__

				if( MadStrLower( g_ActiveMadEdit->GetFileName() ) == MadStrLower( cpdata->filename ) )
					//if(g_ActiveMadEdit->GetFileName().Lower()==cpdata->filename.Lower())
#else
				if( g_ActiveMadEdit->GetFileName() == cpdata->filename )
#endif
				{
					madedit = g_ActiveMadEdit;
				}
			}

			if( madedit )
			{
				madedit->SetCaretPosition( cpdata->epos, cpdata->bpos, cpdata->epos );
				madedit->SetFocus();
			}
		}
	}

	if( madedit == NULL ) { event.Skip(); }
}

void MadEditFrame::ResetFindInFilesResults()
{
	m_FindInFilesResults->DeleteAllItems();
	m_FindInFilesResults->AddRoot( wxT( "Root" ) );
}

void MadEditFrame::AddItemToFindInFilesResults( const wxString &text, size_t index, const wxString &filename, int pageid, const wxFileOffset &begpos, wxFileOffset &endpos )
{
	static wxTreeItemId fileid;

	if( index == 0 )
	{
		if( m_FindInFilesResults->GetChildrenCount( m_FindInFilesResults->GetRootItem(), false ) == 0 )
		{
			fileid = m_FindInFilesResults->AppendItem( m_FindInFilesResults->GetRootItem(), filename );
		}
		else
		{
			// sort the results
			wxTreeItemIdValue cookie;
			wxTreeItemId id = m_FindInFilesResults->GetFirstChild( m_FindInFilesResults->GetRootItem(), cookie );
			size_t before = 0;

			while( id.IsOk() )
			{
				wxString idname = m_FindInFilesResults->GetItemText( id );
#ifdef __WXMSW__

				if( MadStrLower( filename ) < MadStrLower( idname ) )
					//if(filename.Lower() < idname.Lower())
#else
				if( filename < idname )
#endif
				{
					break;
				}

				id = m_FindInFilesResults->GetNextChild( m_FindInFilesResults->GetRootItem(), cookie );
				++before;
			}

			if( !id.IsOk() ) // append item
			{
				fileid = m_FindInFilesResults->AppendItem( m_FindInFilesResults->GetRootItem(), filename );
			}
			else // insert item
			{
				fileid = m_FindInFilesResults->InsertItem( m_FindInFilesResults->GetRootItem(), before, filename );
			}
		}
	}

	m_FindInFilesResults->AppendItem( fileid, text, -1, -1, new CaretPosData( filename, pageid, begpos, endpos ) );
}

//---------------------------------------------------------------------------

int MadEditFrame::OpenedFileCount()
{
	return ( int )m_Notebook->GetPageCount();
}

void MadEditFrame::OpenFile( const wxString &fname, bool mustExist )
{
	wxString title, filename( fname ), linenumstr;
	long linenum = -1;

	if( filename.IsEmpty() )
	{
		int count = int( m_Notebook->GetPageCount() );
		wxArrayString fnames;
		wxString fname;

		for( int id = 0; id < count; ++id )
		{
			fname = m_Notebook->GetPageText( id );

			if( fname[fname.Len() - 1] == wxT( '*' ) )
			{ fname.Truncate( fname.Len() - 1 ); }

			fnames.Add( fname );
		}

		bool nameNotOk = true;

		do
		{
			title.Printf( _( "NoName%d" ), ++m_NewFileCount );

			if( wxNOT_FOUND == fnames.Index( title ) )
			{ nameNotOk = false; }
		}
		while( nameNotOk );
	}
	else
	{
		int npos = filename.Find( '*', true );

		if( npos != wxNOT_FOUND )
		{
			filename = filename.Remove( npos );
			linenumstr = fname;
			linenumstr.Remove( 0, npos + 1 );

			if( !linenumstr.ToLong( &linenum ) ) { linenum = -1; }
		}

		int selid = m_Notebook->GetSelection();
		// check this file is opened or not
		int count = int( m_Notebook->GetPageCount() );

		for( int id = 0; id < count; ++id )
		{
			MadEdit *me = ( MadEdit* )m_Notebook->GetPage( id );
#ifdef __WXMSW__

			if( MadStrLower( me->GetFileName() ) == MadStrLower( filename ) )
				//if(me->GetFileName().Lower()==filename.Lower())
#else
			if( me->GetFileName() == filename )
#endif
			{
				// YES, it's opened. Activate it.
				if( linenum != -1 )
				{ me->GoToLine( linenum ); }

				g_CheckModTimeForReload = false;
				m_Notebook->SetSelection( id );
				MadEdit *madedit = ( MadEdit* )m_Notebook->GetPage( m_Notebook->GetSelection() );

				if( madedit != g_ActiveMadEdit )
				{
					wxAuiNotebookEvent event( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, m_Notebook->GetId() );
					event.SetSelection( m_Notebook->GetSelection() );
					event.SetOldSelection( selid );
					event.SetEventObject( this );
					OnNotebookPageChanged( event );
				}

				g_CheckModTimeForReload = true;
				g_ActiveMadEdit->ReloadByModificationTime();
				m_RecentFiles->AddFileToHistory( filename ); // bring the filename to top of list
				g_ActiveMadEdit->SetFocus();
				return;
			}
		}

		if( MadDirExists( filename ) != 0 )
		{
			wxLogError( wxString( _( "This is a Directory:" ) ) + wxT( "\n\n" ) + filename );
			return;
		}

		int utf8test = MadFileNameIsUTF8( filename );
		bool exists = ( wxFileExists( filename ) || ( utf8test != 0 ) );

		if( mustExist && !exists )
		{
			wxLogError( wxString( _( "This file does not exist:" ) ) + wxT( "\n\n" ) + filename );
			return;
		}

		wxFileName fn( filename );
		title = fn.GetFullName();

		// test parent dir
		if( MadDirExists( fn.GetPath( wxPATH_GET_VOLUME ) ) == 0 )
		{
			wxLogError( wxString( _( "The Parent Directory of this file does not exist:" ) ) + wxT( "\n\n" ) + filename );
			return;
		}

		// test access mode
		MadConvFileName_WC2MB_UseLibc uselibc( utf8test < 0 );

		if( exists && wxFile::Access( filename.c_str(), wxFile::read ) == false )
		{
			wxLogError( wxString( _( "Cannot access this file:" ) ) + wxT( "\n\n" ) + filename );
			return;
		}
	}

	MadEdit *madedit = g_ActiveMadEdit;

	if( !filename.IsEmpty() && madedit != NULL
			&& !madedit->IsModified() && madedit->GetFileName().IsEmpty() )
	{
		// load file in g_ActiveMadEdit
	}
	else
	{
		// create a new MadEdit
		madedit = new MadEdit( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, /*wxSIMPLE_BORDER|*/wxWANTS_CHARS );
		madedit->SetWindowStyleFlag( madedit->GetWindowStyleFlag() & ~wxTAB_TRAVERSAL );
		//madedit->SetDropTarget(new DnDFile());
		madedit->SetOnSelectionChanged( &OnEditSelectionChanged );
		madedit->SetOnStatusChanged( &OnEditStatusChanged );
		madedit->SetOnActivate( &OnEditActivate );
		madedit->SetOnToggleWindow( &OnEditToggleWindow );
		madedit->SetOnMouseRightUp( &OnEditMouseRightUp );
		madedit->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MadEditFrame::MadEditFrameKeyDown ) );
		g_PrevPageID = m_Notebook->GetSelection();
		m_Notebook->AddPage( madedit, title, true );
		m_Notebook->SetSelection( m_Notebook->GetPageCount() - 1 );
	}

	if( !filename.IsEmpty() )
	{
		wxString enc, fn;
		wxFileOffset pos;
		int fs;
		pos = g_FileCaretPosManager.GetRestoreData( filename, enc, fn, fs );

		if( !fn.IsEmpty() && fs > 0 )
		{
			madedit->SetTextFont( fn, fs, false );
		}

		if( !madedit->LoadFromFile( filename, enc ) && mustExist )
		{
			wxLogError( wxString( _( "Cannot load this file:" ) ) + wxT( "\n\n" ) + filename );
		}
		else
		{
			// add filename, fontname, and encoding to recentlist
			m_RecentFiles->AddFileToHistory( filename );
			bool rcp;
			m_Config->Read( wxT( "/MadEdit/RestoreCaretPos" ), &rcp, true );

			if( rcp )
			{
				madedit->SetCaretPosition( pos );
			}
		}
	}

	wxString str;
	int size;
	madedit->GetFont( str, size );
	m_RecentFonts->AddFileToHistory( str );
	str = wxString( wxT( '[' ) ) + madedit->GetEncodingName() + wxT( "] " ) + wxGetTranslation( madedit->GetEncodingDescription().c_str() );
	m_RecentEncodings->AddFileToHistory( str );
	madedit->SetFocus();

	if( g_ActiveMadEdit != madedit )
	{
		g_ActiveMadEdit = madedit;
		OnEditSelectionChanged( g_ActiveMadEdit );
		OnEditStatusChanged( g_ActiveMadEdit );
	}

	title = g_ActiveMadEdit->GetFileName();

	if( title.IsEmpty() )
	{
		title = m_Notebook->GetPageText( GetIdByEdit( g_ActiveMadEdit ) );
	}

	if( g_ActiveMadEdit->IsModified() && title[title.Len() - 1] != wxT( '*' ) )
	{ title += wxT( '*' ); }

	SetTitle( wxString( wxT( "MadEdit-Mod - [" ) ) + title + wxString( wxT( "] " ) ) );

	if( linenum != -1 )
	{ g_ActiveMadEdit->GoToLine( linenum ); }
}

void MadEditFrame::RunScriptWithFile( const wxString &filename, const wxString &script, bool mustExist, bool closeafterdone, bool ignorereadonly )
{
	if( !filename.IsEmpty() )
	{
		int utf8test = MadFileNameIsUTF8( filename );
		bool exists = ( wxFileExists( filename ) || ( utf8test != 0 ) );

		if( mustExist && !exists )
		{
			return;
		}

		OpenFile( filename, mustExist );

		if( g_ActiveMadEdit != NULL )
		{
			int idx = m_Notebook->GetSelection();

			if( ( ignorereadonly || ( !g_ActiveMadEdit->IsReadOnly() ) ) && ( ( !mustExist ) || ( filename == g_ActiveMadEdit->GetFileName() ) ) )
			{
				if( g_ActiveMadEdit->IsReadOnly() )
				{
					wxCommandEvent event;
					OnFileToggleReadOnly( event );
				}

				if( !g_EmbeddedPython )
				{
					try
					{
						g_EmbeddedPython = new EmbeddedPython();
					}
					catch( std::bad_alloc & )
					{
						MadMessageBox( _( "Memory allocation failed" ), wxT( "Error" ),  wxOK | wxICON_ERROR );
					}
				}

				if( g_EmbeddedPython )
				{
					g_EmbeddedPython->exec( std::string( script.mb_str() ) );
				}

				wxString name = m_Notebook->GetPageText( idx );

				if( name[name.Len() - 1] == wxT( '*' ) )
				{ name.Truncate( name.Len() - 1 ); }

				if( g_ActiveMadEdit->Save( false, name, false ) == wxID_YES )
				{
					m_RecentFiles->AddFileToHistory( g_ActiveMadEdit->GetFileName() );
				}
			}

			if( closeafterdone )
			{
				CloseFile( idx );
			}
		}
	}
}

void MadEditFrame::CloseFile( int pageId )
{
	if( QueryCloseFile( pageId ) )
	{
		m_PageClosing = true;
		g_CheckModTimeForReload = false;
		m_Notebook->DeletePage( pageId );

		if( m_Notebook->GetPageCount() == 0 ) { OnNotebookPageClosed(); }

		g_CheckModTimeForReload = true;
		m_PageClosing = false;
	}
}

bool MadEditFrame::QueryCloseFile( int idx )
{
	MadEdit *madedit = ( MadEdit* )m_Notebook->GetPage( idx );

	if( madedit == NULL )
	{ return false; }

	wxString name = m_Notebook->GetPageText( idx );

	if( name[name.Len() - 1] == wxT( '*' ) )
	{ name.Truncate( name.Len() - 1 ); }

	if( madedit->Save( true, name, false ) == wxID_CANCEL )
	{ return false; }

	g_FileCaretPosManager.Add( madedit );
	return true;
}

bool MadEditFrame::QueryCloseAllFiles()
{
	if( m_Notebook->GetPageCount() == 0 ) { return true; }

	int selid = m_Notebook->GetSelection();

	if( selid == -1 ) { return true; }

	MadEdit *madedit = ( MadEdit* )m_Notebook->GetPage( selid );
	wxString name;

	if( madedit->IsModified() )
	{
		name = m_Notebook->GetPageText( selid );

		if( name[name.Len() - 1] == wxT( '*' ) )
		{ name.Truncate( name.Len() - 1 ); }

		if( madedit->Save( true, name, false ) == wxID_CANCEL )
		{ return false; }
	}

	g_FileCaretPosManager.Add( madedit );
	int count = int( m_Notebook->GetPageCount() );
	int id = 0, sid = selid;

	do
	{
		if( id != selid )
		{
			madedit = ( MadEdit* )m_Notebook->GetPage( id );

			if( madedit->IsModified() )
			{
				m_Notebook->SetSelection( id );
				MadEdit *cme = ( MadEdit* )m_Notebook->GetPage( m_Notebook->GetSelection() );

				if( cme != g_ActiveMadEdit )
				{
					wxAuiNotebookEvent event( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, m_Notebook->GetId() );
					event.SetSelection( id );
					event.SetOldSelection( sid );
					event.SetEventObject( this );
					OnNotebookPageChanged( event );
				}

				name = m_Notebook->GetPageText( id );

				if( name[name.Len() - 1] == wxT( '*' ) )
				{ name.Truncate( name.Len() - 1 ); }

				if( madedit->Save( true, name, false ) == wxID_CANCEL )
				{ return false; }

				sid = id;
			}

			g_FileCaretPosManager.Add( madedit );
		}
	}
	while( ++id < count );

	return true;
}

//---------------------------------------------------------------------------

void MadEditFrame::OnUpdateUI_MenuFile_CheckCount( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL );
}

void MadEditFrame::OnUpdateUI_MenuFileReload( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL &&
				  !g_ActiveMadEdit->GetFileName().IsEmpty() );
}

void MadEditFrame::OnUpdateUI_MenuFileRecentFiles( wxUpdateUIEvent& event )
{
	event.Enable( m_RecentFiles->GetCount() != 0 );
}

void MadEditFrame::OnUpdateUI_MenuEditUndo( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit && ( !g_ActiveMadEdit->IsReadOnly() ) && g_ActiveMadEdit->CanUndo() );
}

void MadEditFrame::OnUpdateUI_MenuEditRedo( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit && ( !g_ActiveMadEdit->IsReadOnly() ) && g_ActiveMadEdit->CanRedo() );
}

void MadEditFrame::OnUpdateUI_MenuEditCopy( wxUpdateUIEvent& event )
{
	bool enabled = ( g_ActiveMadEdit && g_ActiveMadEdit->IsSelected() );

	if( ( enabled ) && g_ActiveMadEdit->GetEditMode() == emColumnMode )
	{ enabled = ( g_ActiveMadEdit->GetSelectionSize() > 0 ); }

	event.Enable( enabled );
}

void MadEditFrame::OnUpdateUI_MenuEditDelete( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit && !g_ActiveMadEdit->IsReadOnly() && g_ActiveMadEdit->GetFileSize() );
}

void MadEditFrame::OnUpdateUI_MenuEditCut( wxUpdateUIEvent& event )
{
	bool enabled = ( g_ActiveMadEdit && g_ActiveMadEdit->IsSelected() && !g_ActiveMadEdit->IsReadOnly() );

	if( ( enabled ) && g_ActiveMadEdit->GetEditMode() == emColumnMode )
	{ enabled = ( g_ActiveMadEdit->GetSelectionSize() > 0 ); }

	event.Enable( enabled );
}

void MadEditFrame::OnUpdateUI_MenuEdit_CheckSelSize( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit && !g_ActiveMadEdit->IsReadOnly() && g_ActiveMadEdit->GetSelectionSize() > 0 );
}

void MadEditFrame::OnUpdateUI_MenuEditPaste( wxUpdateUIEvent& event )
{
#ifdef __WXMSW__
	event.Enable( g_ActiveMadEdit && !g_ActiveMadEdit->IsReadOnly() && g_ActiveMadEdit->CanPaste() );
#else
	event.Enable( g_ActiveMadEdit && !g_ActiveMadEdit->IsReadOnly() ); // workaround for high CPU loading in Linux
#endif
}

void MadEditFrame::OnUpdateUI_Menu_CheckSize( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit && g_ActiveMadEdit->GetFileSize() );
}

void MadEditFrame::OnUpdateUI_Menu_CheckTextFileSize( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit && !g_ActiveMadEdit->IsReadOnly() && g_ActiveMadEdit->GetEditMode() != emHexMode && g_ActiveMadEdit->GetFileSize() );
}

void MadEditFrame::OnUpdateUI_MenuEditStartEndSelction( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->IsSelecting() );
}

// add: gogo, 21.09.2009
//----------
void MadEditFrame::OnUpdateUI_MenuEditCheckBookmark( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode && g_ActiveMadEdit->HasBookMark() );
}
void MadEditFrame::OnUpdateUI_MenuEditCheckBookmarkWritable( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && !g_ActiveMadEdit->IsReadOnly() && g_ActiveMadEdit->GetEditMode() != emHexMode && g_ActiveMadEdit->HasBookMark() );
}
//----------

void MadEditFrame::OnUpdateUI_Menu_CheckTextFile( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode );
}

void MadEditFrame::OnUpdateUI_Menu_CheckWritableTextFile( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && !g_ActiveMadEdit->IsReadOnly() && g_ActiveMadEdit->GetEditMode() != emHexMode );
}

void MadEditFrame::OnUpdateUI_Menu_CheckColumnMode( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() == emColumnMode && g_ActiveMadEdit->IsSelected() );
}

void MadEditFrame::OnUpdateUI_Menu_JoinLines( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && !g_ActiveMadEdit->IsReadOnly() && g_ActiveMadEdit->GetEditMode() != emHexMode && g_ActiveMadEdit->IsSelected() );
}

void MadEditFrame::OnUpdateUI_MenuEditCopyAsHexString( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit && //g_ActiveMadEdit->GetEditMode()==emHexMode &&
				  g_ActiveMadEdit->IsSelected() );
}

void MadEditFrame::OnUpdateUI_MenuIndent( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit && !g_ActiveMadEdit->IsReadOnly() &&
				  g_ActiveMadEdit->GetEditMode() != emHexMode );
}

void MadEditFrame::OnUpdateUI_MenuComment( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit && !g_ActiveMadEdit->IsReadOnly() && g_ActiveMadEdit->GetEditMode() != emHexMode
				  && g_ActiveMadEdit->HasLineComment() );
}

void MadEditFrame::OnUpdateUI_MenuSearchGoToBrace( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode && g_ActiveMadEdit->HasBracePair() );
}

void MadEditFrame::OnUpdateUI_MenuViewEncoding( wxUpdateUIEvent& event )
{
	if( g_ActiveMadEdit )
	{
		event.Enable( true );
		wxString str = wxString( wxT( '[' ) ) + g_ActiveMadEdit->GetEncodingName() + wxT( "] " ) + wxGetTranslation( g_ActiveMadEdit->GetEncodingDescription().c_str() );
		event.SetText( wxString( _( "Encoding: " ) ) + str );
		//m_RecentEncodings->AddFileToHistory(str);
	}
	else
	{
		event.Enable( false );
		event.SetText( wxString( _( "Encoding: " ) ) + _( "None" ) );
	}
}

void MadEditFrame::OnUpdateUI_MenuViewSyntax( wxUpdateUIEvent& event )
{
	if( g_ActiveMadEdit )
	{
		event.Enable( g_ActiveMadEdit->GetEditMode() != emHexMode );
		event.SetText( wxString( _( "Syntax Type: " ) ) + g_ActiveMadEdit->GetSyntaxTitle() );
	}
	else
	{
		event.Enable( false );
		event.SetText( wxString( _( "Syntax Type: " ) ) + _( "None" ) );
	}
}

void MadEditFrame::OnUpdateUI_MenuViewFontName( wxUpdateUIEvent& event )
{
	if( g_ActiveMadEdit )
	{
		event.Enable( true );
		wxString name;
		int size;
		g_ActiveMadEdit->GetFont( name, size );
		event.SetText( wxString( _( "Font Name: " ) ) + name );
	}
	else
	{
		event.Enable( false );
		event.SetText( wxString( _( "Font Name: " ) ) + _( "None" ) );
	}
}
void MadEditFrame::OnUpdateUI_MenuViewFontSize( wxUpdateUIEvent& event )
{
	if( g_ActiveMadEdit )
	{
		event.Enable( true );
		wxString name;
		int size;
		g_ActiveMadEdit->GetFont( name, size );
		event.SetText( wxString( _( "Font Size: " ) ) << size );
	}
	else
	{
		event.Enable( false );
		event.SetText( wxString( _( "Font Size: " ) ) + _( "None" ) );
	}
}

void MadEditFrame::OnUpdateUI_MenuViewFixedWidthMode( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->GetFixedWidthMode() );
}

void MadEditFrame::OnUpdateUI_MenuViewTabColumn( wxUpdateUIEvent& event )
{
	if( g_ActiveMadEdit != NULL )
	{
		event.Enable( g_ActiveMadEdit->GetEditMode() != emHexMode );
		event.SetText( wxString( _( "Tab Column: " ) ) << g_ActiveMadEdit->GetTabColumns() );
	}
	else
	{
		event.Enable( false );
		event.SetText( wxString( _( "Tab Column: " ) ) + _( "None" ) );
	}
}

void MadEditFrame::OnUpdateUI_MenuViewPreview( wxUpdateUIEvent& event )
{
	wxString viewType( _( "None" ) );

	if( g_ActiveMadEdit != NULL )
	{
		switch( m_PreviewType )
		{
		case ptPREVIEW_HTML:
			viewType = _( "HTML" );
			break;

		case ptPREVIEW_MARKDOWN:
			viewType = _( "Markdown" );
			break;

		default:
			break;
		}

		event.Enable( true );
	}
	else
	{
		event.Enable( false );
	}

	event.SetText( wxString( _( "Preview as: " ) ) + viewType );
}

void MadEditFrame::OnUpdateUI_MenuViewPreviewList( wxUpdateUIEvent& event )
{
	for( int menuId = ptPREVIEW_HTML; menuId < ptPREVIEW_MAXTYPE; ++menuId )
	{
		if( menuId != m_PreviewType )
		{
			g_Menu_View_Preview->Check( menuId, false );
		}
		else
		{
			g_Menu_View_Preview->Check( menuId, true );
		}

		if( g_ActiveMadEdit != NULL )
		{
			g_Menu_View_Preview->Enable( menuId, true );
		}
		else
		{
			g_Menu_View_Preview->Enable( menuId, false );
		}
	}
}

void MadEditFrame::OnUpdateUI_MenuViewLineSpacing( wxUpdateUIEvent& event )
{
	if( g_ActiveMadEdit != NULL )
	{
		event.Enable( g_ActiveMadEdit->GetEditMode() != emHexMode );
		event.SetText( wxString( _( "Line Spacing: " ) ) << g_ActiveMadEdit->GetLineSpacing() << wxT( '%' ) );
	}
	else
	{
		event.Enable( false );
		event.SetText( wxString( _( "Line Spacing: " ) ) + _( "None" ) );
	}
}

void MadEditFrame::OnUpdateUI_MenuViewNoWrap( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->GetWordWrapMode() == wwmNoWrap );
}
void MadEditFrame::OnUpdateUI_MenuViewWrapByWindow( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->GetWordWrapMode() == wwmWrapByWindow );
}
void MadEditFrame::OnUpdateUI_MenuViewWrapByColumn( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->GetWordWrapMode() == wwmWrapByColumn );
}
void MadEditFrame::OnUpdateUI_MenuViewDisplayLineNumber( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->GetDisplayLineNumber() );
}
void MadEditFrame::OnUpdateUI_MenuViewDisplayBookmark( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->GetDisplayBookmark() );
}
void MadEditFrame::OnUpdateUI_MenuViewDisplay80ColHint( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->GetDisplay80ColHint() );
}
void MadEditFrame::OnUpdateUI_MenuViewShowEndOfLine( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->GetShowEndOfLine() );
}
void MadEditFrame::OnUpdateUI_MenuViewShowTabChar( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->GetShowTabChar() );
}
void MadEditFrame::OnUpdateUI_MenuViewShowSpaceChar( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->GetShowSpaceChar() );
}
void MadEditFrame::OnUpdateUI_MenuViewShowAllChars( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->GetShowSpaceChar() && g_ActiveMadEdit->GetShowTabChar()
				 && g_ActiveMadEdit->GetShowEndOfLine() );
}
void MadEditFrame::OnUpdateUI_MenuViewRightToLeft( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode );
	event.Check( g_ActiveMadEdit && ( g_ActiveMadEdit->GetLayoutDirection() == wxLayout_RightToLeft ) );
}
void MadEditFrame::OnUpdateUI_MenuViewMarkActiveLine( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->GetMarkActiveLine() );
}
void MadEditFrame::OnUpdateUI_MenuViewMarkBracePair( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->GetMarkBracePair() );
}
void MadEditFrame::OnUpdateUI_MenuViewSpellChecker( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode
				  && SpellCheckerManager::Instance().GetSelectedDictionaryNumber() != -1 );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->GetSpellCheckStatus() );
}
void MadEditFrame::OnUpdateUI_MenuSpellIgnore( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode
				  && SpellCheckerManager::Instance().GetSelectedDictionaryNumber() != -1 );
}

void MadEditFrame::OnUpdateUI_MenuSpellRemoveFromDict( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode
				  && SpellCheckerManager::Instance().GetEnablePersonalDictionary() );
}

void MadEditFrame::OnUpdateUI_MenuSpellAdd2Dict( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && g_ActiveMadEdit->GetEditMode() != emHexMode
				  && SpellCheckerManager::Instance().GetEnablePersonalDictionary() );
}
void MadEditFrame::OnUpdateUI_MenuViewTextMode( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() == emTextMode );
}
void MadEditFrame::OnUpdateUI_MenuViewColumnMode( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() == emColumnMode );
}
void MadEditFrame::OnUpdateUI_MenuViewHexMode( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL );
	event.Check( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() == emHexMode );
}
void MadEditFrame::OnUpdateUI_MenuViewToolbars( wxUpdateUIEvent& event )
{
	event.Enable( tbMAX != 0 );
}
void MadEditFrame::OnUpdateUI_MenuViewToolbarsToggleAll( wxUpdateUIEvent& event )
{
	event.Enable( tbMAX != 0 );
	event.Check( m_ToolbarStatus[tbMAX] );
}
void MadEditFrame::OnUpdateUI_MenuViewToolbarList( wxUpdateUIEvent& event )
{
	int menuItemId = event.GetId();
	int toolbarId = menuItemId - menuToolBar1;

	if( toolbarId < tbMAX )
	{
		if( m_ToolbarStatus[tbMAX] )
		{
			g_Menu_Toolbars->Enable( menuItemId, true );

			if( m_ToolbarStatus[toolbarId] )
			{
				if( !m_AuiManager.GetPane( WxToolBar[toolbarId] ).IsShown() )
				{
					m_ToolbarStatus[toolbarId] = false;
				}

				g_Menu_Toolbars->Check( menuItemId, m_ToolbarStatus[toolbarId] );
			}
			else
			{
				g_Menu_Toolbars->Check( menuItemId, false );
			}
		}
		else
		{ g_Menu_Toolbars->Enable( menuItemId, false ); }
	}
}

void MadEditFrame::OnUpdateUI_MenuToolsByteOrderMark( wxUpdateUIEvent& event )
{
	MadEncodingType type;

	if( g_ActiveMadEdit && g_ActiveMadEdit->IsTextFile()
			&& ( type = g_ActiveMadEdit->GetEncodingType() ) != etSingleByte
			&& type != etDoubleByte )   // unicode format
	{
		event.Enable( true );

		if( g_ActiveMadEdit->HasBOM() )
		{
			event.SetText( _( "Has Unicode BOM (Byte-Order Mark)" ) );
		}
		else
		{
			event.SetText( _( "Has No Unicode BOM (Byte-Order Mark)" ) );
		}
	}
	else
	{
		event.Enable( false );
		event.SetText( _( "Has No Unicode BOM (Byte-Order Mark)" ) );
	}
}
void MadEditFrame::OnUpdateUI_MenuToolsNewLineChar( wxUpdateUIEvent& event )
{
	wxString text( _( "NewLine Char (File Format): " ) );

	if( g_ActiveMadEdit && g_ActiveMadEdit->IsTextFile() )
	{
		event.Enable( !g_ActiveMadEdit->IsReadOnly() );

		switch( g_ActiveMadEdit->GetNewLineType() )
		{
		case nltDOS:  text += wxT( "CRLF/0D0A (DOS)" ); break;

		case nltUNIX: text += wxT( "LF/0A (UNIX)" ); break;

		case nltMAC:  text += wxT( "CR/0D (MAC)" ); break;

		default: break;
		}

		event.SetText( text );
	}
	else
	{
		event.Enable( false );
		event.SetText( text + _( "None" ) );
	}
}
void MadEditFrame::OnUpdateUI_MenuToolsInsertNewLineChar( wxUpdateUIEvent& event )
{
	wxString text( _( "Press Enter to Insert NewLine Char: " ) );

	if( g_ActiveMadEdit && g_ActiveMadEdit->IsTextFile() )
	{
		event.Enable( !g_ActiveMadEdit->IsReadOnly() );

		switch( g_ActiveMadEdit->GetInsertNewLineType() )
		{
		case nltDOS:  text += wxT( "CRLF/0D0A (DOS)" ); break;

		case nltUNIX: text += wxT( "LF/0A (UNIX)" ); break;

		case nltMAC:  text += wxT( "CR/0D (MAC)" ); break;

		default: break;
		}

		event.SetText( text );
	}
	else
	{
		event.Enable( false );
		event.SetText( text + _( "None" ) );
	}
}

void MadEditFrame::OnUpdateUI_MenuCheckWritable( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && !g_ActiveMadEdit->IsReadOnly() );
}

void MadEditFrame::OnUpdateUI_MenuToolsConvertEncoding( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL &&
				  !g_ActiveMadEdit->IsReadOnly() && g_ActiveMadEdit->IsTextFile() );
}

void MadEditFrame::OnUpdateUI_MenuWindow_CheckCount( wxUpdateUIEvent& event )
{
	event.Enable( m_Notebook->GetPageCount() >= 2 );
}

void MadEditFrame::OnUpdateUI_MenuToolsStartRecMacro( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && IsMacroStopped() );
}

void MadEditFrame::OnUpdateUI_MenuToolsStopRecMacro( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && IsMacroRecording() );
}

void MadEditFrame::OnUpdateUI_MenuToolsPlayRecMacro( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit && IsMacroStopped() && HasRecordedScript() );
}

void MadEditFrame::OnUpdateUI_MenuToolsSaveRecMacro( wxUpdateUIEvent& event )
{
	event.Enable( g_ActiveMadEdit != NULL && IsMacroStopped() && HasRecordedScript() );
}

//---------------------------------------------------------------------------

void MadEditFrame::OnFileNew( wxCommandEvent& event )
{
	OpenFile( wxEmptyString, false );
}

void MadEditFrame::OnFileOpen( wxCommandEvent& event )
{
	wxString dir;

	if( m_RecentFiles->GetCount() )
	{
		wxFileName filename( m_RecentFiles->GetHistoryFile( 0 ) );
		dir = filename.GetPath( wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR );
	}

	static int filterIndex = 0;
	wxString fileFilter = wxString( wxT( "All files(*;*.*)|" ) ) + wxFileSelectorDefaultWildcardStr + wxT( "|68k Assembly (*.68k)|*.68k|" )
						  wxT( "ActionScript (*.as;*.asc;*.mx)|*.as;*.asc;*.mx|Ada (*.a;*.ada;*.adb;*.ads)|*.a;*.ada;*.adb;*.ads|Apache Conf (*.conf;*.htaccess)|" )
						  wxT( "*.conf;*.htaccess|Bash Shell Script (*.bsh;*.configure;*.sh)|*.bsh;*.configure;*.sh|Boo (*.boo)|*.boo|C (*.c;*.h)|*.c;*.h|" )
						  wxT( "C# (*.cs)|*.cs|C-Shell Script (*.csh)|*.csh|Caml (*.ml;*.mli)|*.ml;*.mli|Cascading Style Sheet (*.css)|*.css|" )
						  wxT( "Cilk (*.cilk;*.cilkh)|*.cilk;*.cilkh|Cobra (*.cobra)|*.cobra|ColdFusion (*.cfc;*.cfm;*.cfml;*.dbm)|*.cfc;*.cfm;*.cfml;*.dbm|" )
						  wxT( "CPP (*.c++;*.cc;*.cpp;*.cxx;*.h++;*.hh;*.hpp;*.hxx)|*.c++;*.cc;*.cpp;*.cxx;*.h++;*.hh;*.hpp;*.hxx|D (*.d)|*.d|" )
						  wxT( "Diff File (*.diff;*.patch)|*.diff;*.patch|Django (*.django)|*.django|DOS Batch Script (*.bat;*.cmd)|*.bat;*.cmd|DOT (*.dot)|" )
						  wxT( "*.dot|DSP56K Assembly (*.56k)|*.56k|Editra Style Sheet (*.ess)|*.ess|Edje (*.edc)|*.edc|Eiffel (*.e)|*.e|Erlang (*.erl)|*.erl|" )
						  wxT( "Ferite (*.fe)|*.fe|FlagShip (*.prg)|*.prg|Forth (*.4th;*.fs;*.fth;*.seq)|*.4th;*.fs;*.fth;*.seq|Fortran 77 (*.f;*.for)|*.f;*.for|" )
						  wxT( "Fortran 95 (*.f2k;*.f90;*.f95;*.fpp)|*.f2k;*.f90;*.f95;*.fpp|GLSL (*.frag;*.glsl;*.vert)|*.frag;*.glsl;*.vert|" )
						  wxT( "GNU Assembly (*.gasm)|*.gasm|Groovy (*.groovy)|*.groovy|Gui4Cli (*.gc;*.gui)|*.gc;*.gui|Haskell (*.hs)|*.hs|HaXe (*.hx;*.hxml)|" )
						  wxT( "*.hx;*.hxml|HTML (*.htm;*.html;*.shtm;*.shtml;*.xhtml)|*.htm;*.html;*.shtm;*.shtml;*.xhtml|Inno Setup Script (*.iss)|*.iss|" )
						  wxT( "IssueList (*.isl)|*.isl|Java (*.java)|*.java|JavaScript (*.js)|*.js|Kix (*.kix)|*.kix|Korn Shell Script (*.ksh)|*.ksh|" )
						  wxT( "LaTeX (*.aux;*.sty;*.tex)|*.aux;*.sty;*.tex|Lisp (*.cl;*.lisp)|*.cl;*.lisp|Lout (*.lt)|*.lt|Lua (*.lua)|*.lua|Mako (*.mako;*.mao)|" )
						  wxT( "*.mako;*.mao|MASM (*.asm;*.masm)|*.asm;*.masm|Matlab (*.matlab)|*.matlab|Microsoft SQL (*.mssql)|*.mssql|Netwide Assembler (*.nasm)|" )
						  wxT( "*.nasm|newLISP (*.lsp)|*.lsp|NONMEM Control Stream (*.ctl)|*.ctl|Nullsoft Installer Script (*.nsh;*.nsi)|*.nsh;*.nsi|" )
						  wxT( "Objective C (*.m;*.mm)|*.m;*.mm|Octave (*.oct;*.octave)|*.oct;*.octave|OOC (*.ooc)|*.ooc|Pascal (*.dfm;*.dpk;*.dpr;*.inc;*.p;*.pas;*.pp)|" )
						  wxT( "*.dfm;*.dpk;*.dpr;*.inc;*.p;*.pas;*.pp|Perl (*.cgi;*.pl;*.pm;*.pod)|*.cgi;*.pl;*.pm;*.pod|PHP (*.php;*.php3;*.phtm;*.phtml)|" )
						  wxT( "*.php;*.php3;*.phtm;*.phtml|Pike (*.pike)|*.pike|PL/SQL (*.plsql)|*.plsql|Plain Text (*.txt)|*.txt|Postscript (*.ai;*.ps)|" )
						  wxT( "*.ai;*.ps|Progress 4GL (*.4gl)|*.4gl|Properties (*.cfg;*.cnf;*.inf;*.ini;*.reg;*.url)|*.cfg;*.cnf;*.inf;*.ini;*.reg;*.url|" )
						  wxT( "Python (*.py;*.python;*.pyw)|*.py;*.python;*.pyw|R (*.r)|*.r|Ruby (*.gemspec;*.rake;*.rb;*.rbw;*.rbx)|*.gemspec;*.rake;*.rb;*.rbw;*.rbx|" )
						  wxT( "S (*.s)|*.s|Scheme (*.scm;*.smd;*.ss)|*.scm;*.smd;*.ss|Smalltalk (*.st)|*.st|SQL (*.sql)|*.sql|Squirrel (*.nut)|*.nut|Stata (*.ado;*.do)|" )
						  wxT( "*.ado;*.do|System Verilog (*.sv;*.svh)|*.sv;*.svh|Tcl/Tk (*.itcl;*.tcl;*.tk)|*.itcl;*.tcl;*.tk|Vala (*.vala)|*.vala|" )
						  wxT( "VBScript (*.dsm;*.vbs)|*.dsm;*.vbs|Verilog (*.v)|*.v|VHDL (*.vh;*.vhd;*.vhdl)|*.vh;*.vhd;*.vhdl|Visual Basic (*.bas;*.cls;*.frm;*.vb)|" )
						  wxT( "*.bas;*.cls;*.frm;*.vb|XML (*.axl;*.dtd;*.plist;*.rdf;*.svg;*.xml;*.xrc;*.xsd;*.xsl;*.xslt;*.xul)|*.axl;*.dtd;*.plist;*.rdf;*.svg;*.xml;" )
						  wxT( "*.xrc;*.xsd;*.xsl;*.xslt;*.xul|Xtext (*.xtext)|*.xtext|YAML (*.yaml;*.yml)|*.yaml;*.yml" );
	wxFileDialog dlg( this, _( "Open File" ), dir, wxEmptyString, fileFilter,
#if wxCHECK_VERSION(2,8,0)
					  wxFD_OPEN | wxFD_MULTIPLE );
#else
					  wxOPEN | wxMULTIPLE );
#endif
	// Hide Modaless Dialog
	HideModalessDialogs();
	dlg.SetFilterIndex( filterIndex );

	if( dlg.ShowModal() == wxID_OK )
	{
		wxArrayString filenames;
		g_MB2WC_check_dir_filename = true;
		dlg.GetPaths( filenames );
		g_MB2WC_check_dir_filename = false;
		size_t count = filenames.GetCount();

		for( size_t i = 0; i < count; ++i )
		{
			OpenFile( filenames[i], false );
		}
	}

	filterIndex = dlg.GetFilterIndex();
}

void MadEditFrame::OnFileSave( wxCommandEvent& event )
{
	if( g_ActiveMadEdit != NULL )
	{
		wxString name = m_Notebook->GetPageText( m_Notebook->GetSelection() );

		if( name[name.Len() - 1] == wxT( '*' ) )
		{ name.Truncate( name.Len() - 1 ); }

		if( g_ActiveMadEdit->Save( false, name, false ) == wxID_YES )
		{
			m_RecentFiles->AddFileToHistory( g_ActiveMadEdit->GetFileName() );
		}
	}
}

void MadEditFrame::OnFileSaveAs( wxCommandEvent& event )
{
	if( g_ActiveMadEdit != NULL )
	{
		wxString name = m_Notebook->GetPageText( m_Notebook->GetSelection() );

		if( name[name.Len() - 1] == wxT( '*' ) )
		{ name.Truncate( name.Len() - 1 ); }

		// Hide Modaless Dialog
		HideModalessDialogs();

		if( g_ActiveMadEdit->Save( false, name, true ) == wxID_YES )
		{
			m_RecentFiles->AddFileToHistory( g_ActiveMadEdit->GetFileName() );
		}
	}
}

void MadEditFrame::OnFileSaveAll( wxCommandEvent& event )
{
	int selid = m_Notebook->GetSelection();

	if( selid == -1 ) { return; } // no file was opened

	MadEdit *madedit = ( MadEdit* )m_Notebook->GetPage( selid );
	wxString name;

	if( madedit->IsModified() )
	{
		name = m_Notebook->GetPageText( selid );

		if( name[name.Len() - 1] == wxT( '*' ) )
		{ name.Truncate( name.Len() - 1 ); }

		if( madedit->Save( false, name, false ) == wxID_CANCEL )
		{ return; }
	}

	int count = int( m_Notebook->GetPageCount() );
	int id = 0, sid = selid;

	do
	{
		if( id != selid )
		{
			madedit = ( MadEdit* )m_Notebook->GetPage( id );

			if( madedit->IsModified() )
			{
				if( madedit->GetFileName().IsEmpty() )
				{
					m_Notebook->SetSelection( id );
					MadEdit *cme = ( MadEdit* )m_Notebook->GetPage( m_Notebook->GetSelection() );

					if( cme != g_ActiveMadEdit )
					{
						wxAuiNotebookEvent event( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, m_Notebook->GetId() );
						event.SetSelection( id );
						event.SetOldSelection( sid );
						event.SetEventObject( this );
						OnNotebookPageChanged( event );
					}
				}

				name = m_Notebook->GetPageText( id );

				if( name[name.Len() - 1] == wxT( '*' ) )
				{ name.Truncate( name.Len() - 1 ); }

				if( madedit->Save( false, name, false ) == wxID_CANCEL )
				{ return; }

				sid = id;
			}
		}
	}
	while( ++id < count );
}

void MadEditFrame::OnFileReload( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->Reload();
	}
}

void MadEditFrame::OnFileClose( wxCommandEvent& event )
{
	int idx = m_Notebook->GetSelection();
	CloseFile( idx );
}

void MadEditFrame::OnFileCloseAll( wxCommandEvent& event )
{
	if( QueryCloseAllFiles() )
	{
		m_PageClosing = true;

		//m_Notebook->DeleteAllPages();
		while( m_Notebook->GetPageCount() != 0 )
		{
			m_Notebook->DeletePage( 0 );
		}

		m_PageClosing = false;
		g_ActiveMadEdit = NULL;
		SetTitle( wxString( wxT( "MadEdit " ) ) );
		OnEditSelectionChanged( NULL );
		OnEditStatusChanged( NULL );
	}
}

void MadEditFrame::OnFileCloseAllButThis( wxCommandEvent& event )
{
	wxWindow * thisWin = m_Notebook->GetPage( m_Notebook->GetSelection() );
	m_Notebook->SetSelection( 0 );

	while( m_Notebook->GetPageCount() > 1 )
	{
		int idx = m_Notebook->GetSelection();

		if( thisWin != m_Notebook->GetPage( idx ) )
		{
			CloseFile( idx );
		}
		else
		{ m_Notebook->AdvanceSelection( true ); }
	}
}

void MadEditFrame::OnFileCloseAllToTheLeft( wxCommandEvent& event )
{
	wxWindow * thisWin = m_Notebook->GetPage( m_Notebook->GetSelection() );
	m_Notebook->SetSelection( 0 );

	while( m_Notebook->GetPageCount() > 1 )
	{
		int idx = m_Notebook->GetSelection();

		if( thisWin == m_Notebook->GetPage( idx ) ) { break; }

		CloseFile( idx );
	}
}

void MadEditFrame::OnFileCloseAllToTheRight( wxCommandEvent& event )
{
	wxWindow * thisWin = m_Notebook->GetPage( m_Notebook->GetSelection() );
	m_Notebook->AdvanceSelection( true );
	int idx = m_Notebook->GetSelection();

	while( m_Notebook->GetPage( idx ) != thisWin )
	{
		CloseFile( idx );
		idx = m_Notebook->GetSelection();
	}
}

void MadEditFrame::OnFilePageSetup( wxCommandEvent& event )
{
	//(*g_PageSetupData) = *g_PrintData;
	// Hide Modaless Dialog
	HideModalessDialogs();
	wxPageSetupDialog pageSetupDialog( this, g_PageSetupData );

	if( pageSetupDialog.ShowModal() == wxID_OK )
		//pageSetupDialog.ShowModal();
	{
		//(*g_PrintData) = pageSetupDialog.GetPageSetupData().GetPrintData();
		( *g_PageSetupData ) = pageSetupDialog.GetPageSetupData();
		//g_PageSetupData->SetPrintData( pageSetupDialog.GetPageSetupData().GetPrintData() );
		wxString oldpath = m_Config->GetPath();
		m_Config->SetPath( wxT( "/MadEdit" ) );
		m_Config->Write( wxT( "PageOrientation" ), ( long )g_PageSetupData->GetPrintData().GetOrientation() );
		//((wxFrame*)wxTheApp->GetTopWindow())->SetTitle(wxString::Format(wxT("%d"), g_PageSetupData->GetPaperId()));
		wxSize size = g_PageSetupData->GetPaperSize();
		m_Config->Write( wxT( "PagePaperSizeW" ), size.x );
		m_Config->Write( wxT( "PagePaperSizeH" ), size.y );
		wxPoint p = g_PageSetupData->GetMarginTopLeft();
		m_Config->Write( wxT( "PageLeftMargin" ), p.x );
		m_Config->Write( wxT( "PageTopMargin" ), p.y );
		p = g_PageSetupData->GetMarginBottomRight();
		m_Config->Write( wxT( "PageRightMargin" ), p.x );
		m_Config->Write( wxT( "PageBottomMargin" ), p.y );
		m_Config->SetPath( oldpath );
	}
}

void MadEditFrame::OnFilePrintPreview( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	// Pass two printout objects: for preview, and possible printing.
	wxPrintDialogData printDialogData( g_PageSetupData->GetPrintData() ); //*g_PrintData);
	wxPrintPreview *preview = new wxPrintPreview( new MadPrintout, new MadPrintout, &printDialogData );
	//#ifdef __WXMSW__
	//preview->SetZoom(30);
	//#endif
	// Hide Modaless Dialog
	HideModalessDialogs();

	if( !preview->Ok() )
	{
		delete preview;
		MadMessageBox( _( "There was a problem previewing.\nPerhaps your current printer is not set correctly?" ), _( "Previewing" ), wxOK );
	}
	else
	{
		wxPreviewFrame *frame = new wxPreviewFrame( preview, this, _( "MadEdit Print Preview" ),
				wxPoint( 0, 0 ),
#ifdef __WXMSW__
				wxSize( 600, 720 )
#else
				wxSize( 600, 620 )
#endif
												  );
		frame->Centre( wxBOTH );
		frame->Initialize();
		frame->Show();
	}
}


void PrintOut( wxWindow *parentWin )
{
	wxPrintDialogData printDialogData( g_PageSetupData->GetPrintData() ); //*g_PrintData);
	wxPrinter printer( &printDialogData );
	MadPrintout printout;

	if( !printer.Print( parentWin, &printout, true /*prompt*/ ) )
	{
		if( wxPrinter::GetLastError() == wxPRINTER_ERROR )
		{ MadMessageBox( _( "There was a problem printing.\nPerhaps your current printer is not set correctly?" ), _( "Printing" ), wxOK ); }
	}
	else
	{
		//(*g_PrintData) = printer.GetPrintDialogData().GetPrintData();
		g_PageSetupData->SetPrintData( printer.GetPrintDialogData().GetPrintData() );
	}
}

#if defined(__WXMSW__)
/* temp modal-dialog for printing */
class TempPrintDialog : public wxDialog
{
private:
	DECLARE_EVENT_TABLE()
public:
	TempPrintDialog( wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT( "TopPrintDialog" ),
					 const wxPoint& pos = wxPoint( 10, 10 ), //wxDefaultPosition,
					 const wxSize& size = wxSize( 1, 1 ), //wxDefaultSize,
					 long style = wxDIALOG_NO_PARENT )
		: wxDialog( parent, id, title, pos, size, style ), m_Printed( false ) { }
	virtual ~TempPrintDialog() { }

	void OnPaint( wxPaintEvent &evt );

	bool m_Printed;
};

BEGIN_EVENT_TABLE( TempPrintDialog, wxDialog )
	EVT_PAINT( TempPrintDialog::OnPaint )
END_EVENT_TABLE()

void TempPrintDialog::OnPaint( wxPaintEvent &evt )
{
	if( !m_Printed )
	{
		m_Printed = true;
		PrintOut( this );
		Close(); //EndModal(wxID_OK);
	}

	evt.Skip();
}
#endif

void MadEditFrame::OnFilePrint( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	// Hide Modaless Dialog
	HideModalessDialogs();
#if defined(__WXMSW__)
	// using a temp modal-dialog to avoid the user change the contents of Edit
	TempPrintDialog *dlg = new TempPrintDialog( this );
	dlg->ShowModal();
	delete dlg;
#else
	PrintOut( this );
#endif
}


void MadEditFrame::OnFileRecentFile( wxCommandEvent& event )
{
	int idx = event.GetId() - wxID_FILE1;
	wxString file = m_RecentFiles->GetHistoryFile( idx );

	if( !file.IsEmpty() )
	{
		OpenFile( file, true );
	}
}

void MadEditFrame::OnFileExit( wxCommandEvent& event )
{
	Close( false );
}

void MadEditFrame::OnCopyFilePath( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		wxString fullPath = g_ActiveMadEdit->GetFileName();
		g_ActiveMadEdit->CopyToClipboard( fullPath );
	}
}

void MadEditFrame::OnCopyFileName( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		wxFileName fileName( g_ActiveMadEdit->GetFileName() );
		g_ActiveMadEdit->CopyToClipboard( fileName.GetFullName() );
	}
}

void MadEditFrame::OnCopyFileDir( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		wxFileName fileName( g_ActiveMadEdit->GetFileName() );
		g_ActiveMadEdit->CopyToClipboard( fileName.GetPath() );
	}
}

void MadEditFrame::OnEditUndo( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && ( !g_ActiveMadEdit->IsReadOnly() ) )
	{
		g_ActiveMadEdit->Undo();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "Undo()" ) ) );
	}
}

void MadEditFrame::OnEditRedo( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && ( !g_ActiveMadEdit->IsReadOnly() ) )
	{
		g_ActiveMadEdit->Redo();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "Redo()" ) ) );
	}
}

void MadEditFrame::OnEditCut( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->CutToClipboard();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "CutToClipboard()" ) ) );
	}
}

void MadEditFrame::OnEditCopy( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->CopyToClipboard();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "CopyToClipboard()" ) ) );
	}
}

void MadEditFrame::OnEditPaste( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->PasteFromClipboard();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "PasteFromClipboard()" ) ) );
	}
}

void MadEditFrame::OnEditDelete( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->Delete();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "Delete()" ) ) );
	}
}

void MadEditFrame::OnEditCutLine( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->CutLine();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "CutLine()" ) ) );
	}
}

void MadEditFrame::OnEditDeleteLine( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->DeleteLine();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "DeleteLine()" ) ) );
	}
}

void MadEditFrame::OnEditSelectAll( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->SelectAll();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "DeleteLine()" ) ) );
	}
}

void MadEditFrame::OnEditStartEndSelction( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->StartEndSelction();
	}
}

void MadEditFrame::OnEditInsertTabChar( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->InsertTabChar();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "InsertTabChar()" ) ) );
	}
}

void MadEditFrame::OnEditInsertDateTime( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->InsertDateTime();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "InsertDateTime()" ) ) );
	}
}

void MadEditFrame::OnFileToggleReadOnly( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		if( g_ActiveMadEdit->IsReadOnly() )
		{
#if wxMAJOR_VERSION <3
#ifdef __WXMSW__
			_wchmod( g_ActiveMadEdit->GetFileName().fn_str(), _S_IREAD | _S_IWRITE );
#else
			chmod( g_ActiveMadEdit->GetFileName().fn_str(), S_IRUSR | S_IWUSR )
#endif
#else
			wxFileName fname( g_ActiveMadEdit->GetFileName() );
			fname.SetPermissions( wxPOSIX_USER_READ | wxPOSIX_USER_WRITE );
#endif
			g_ActiveMadEdit->SetReadOnly( false );
		}
		else
		{
#if wxMAJOR_VERSION <3
#ifdef __WXMSW__
			_wchmod( g_ActiveMadEdit->GetFileName().fn_str(), _S_IREAD );
#else
			chmod( g_ActiveMadEdit->GetFileName().fn_str(), S_IRUSR )
#endif
#else
			wxFileName fname( g_ActiveMadEdit->GetFileName() );
			fname.SetPermissions( wxPOSIX_USER_READ );
#endif
			g_ActiveMadEdit->SetReadOnly( true );
		}

		OnEditStatusChanged( g_ActiveMadEdit );
	}
}

// add: gogo, 21.09.2009
//
void MadEditFrame::OnSearchToggleBookmark( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->SetBookmark();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetBookmark()" ) ) );
	}
}

void MadEditFrame::OnSearchGotoNextBookmark( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->GotoNextBookmark();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "GotoNextBookmark()" ) ) );
	}
}

void MadEditFrame::OnSearchGotoPreviousBookmark( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->GotoPreviousBookmark();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "GotoPreviousBookmark()" ) ) );
	}
}

void MadEditFrame::OnSearchClearAllBookmarks( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->ClearAllBookmarks();
		//RecordAsMadMacro(g_ActiveMadEdit, wxString(wxT("ClearAllBookmarks()")));
	}
}

//----------

void MadEditFrame::OnEditSortAscending( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		int begin, end;
		g_ActiveMadEdit->GetSelectionLineId( begin, end );
		g_ActiveMadEdit->SortLines( sfAscending, begin, end );
		RecordAsMadMacro( g_ActiveMadEdit, wxString::Format( wxT( "SortLines(%d, %d, %d)" ), ( int )sfAscending, begin, end ) );
	}
}

void MadEditFrame::OnEditSortDescending( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		int begin, end;
		g_ActiveMadEdit->GetSelectionLineId( begin, end );
		g_ActiveMadEdit->SortLines( sfDescending, begin, end );
		RecordAsMadMacro( g_ActiveMadEdit, wxString::Format( wxT( "SortLines(%d, %d, %d)" ), ( int )sfDescending, begin, end ) );
	}
}

void MadEditFrame::OnEditSortAscendingCase( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		int begin, end;
		g_ActiveMadEdit->GetSelectionLineId( begin, end );
		g_ActiveMadEdit->SortLines( sfAscending | sfCaseSensitive, begin, end );
		RecordAsMadMacro( g_ActiveMadEdit, wxString::Format( wxT( "SortLines(%d, %d, %d)" ), ( int )sfAscending | sfCaseSensitive, begin, end ) );
	}
}

void MadEditFrame::OnEditSortDescendingCase( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		int begin, end;
		g_ActiveMadEdit->GetSelectionLineId( begin, end );
		g_ActiveMadEdit->SortLines( sfDescending | sfCaseSensitive, begin, end );
		RecordAsMadMacro( g_ActiveMadEdit, wxString::Format( wxT( "SortLines(%d, %d, %d)" ), ( int )sfDescending | sfCaseSensitive, begin, end ) );
	}
}

void MadEditFrame::OnEditSortByOptions( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		wxString oldpath = m_Config->GetPath();
		m_Config->SetPath( wxT( "/MadEdit" ) );
		int order;
		bool cs, num, rem;
		m_Config->Read( wxT( "SortOrder" ), &order, sfAscending );
		m_Config->Read( wxT( "SortCaseSensitive" ), &cs, false );
		m_Config->Read( wxT( "SortNumeric" ), &num, false );
		m_Config->Read( wxT( "SortRemoveDup" ), &rem, false );
		m_Config->SetPath( oldpath );
		MadSortFlags flags = order |
							 ( cs ? sfCaseSensitive : 0 ) |
							 ( num ? sfNumericSort : 0 ) |
							 ( rem ? sfRemoveDuplicate : 0 ) ;
		int begin, end;
		g_ActiveMadEdit->GetSelectionLineId( begin, end );
		g_ActiveMadEdit->SortLines( flags, begin, end );
		RecordAsMadMacro( g_ActiveMadEdit, wxString::Format( wxT( "SortLines(%d, %d, %d)" ), flags, begin, end ) );
	}
}

void MadEditFrame::OnEditSortOptions( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL || g_ActiveMadEdit->GetEditMode() == emHexMode )
	{ return; }

	MadSortDialog dialog( this, -1 );
	wxString oldpath = m_Config->GetPath();
	m_Config->SetPath( wxT( "/MadEdit" ) );
	int order;
	bool cs, num, rem;
	m_Config->Read( wxT( "SortOrder" ), &order, sfAscending );
	dialog.WxRadioBoxOrder->SetSelection( order );
	m_Config->Read( wxT( "SortCaseSensitive" ), &cs, false );
	dialog.WxCheckBoxCase->SetValue( cs );
	m_Config->Read( wxT( "SortNumeric" ), &num, false );
	dialog.WxCheckBoxNumeric->SetValue( num );
	m_Config->Read( wxT( "SortRemoveDup" ), &rem, false );
	dialog.WxCheckBoxRemoveDup->SetValue( rem );
	// Hide Modaless Dialog
	HideModalessDialogs();

	if( dialog.ShowModal() == wxID_OK )
	{
		order = dialog.WxRadioBoxOrder->GetSelection();
		cs = dialog.WxCheckBoxCase->GetValue();
		num = dialog.WxCheckBoxNumeric->GetValue();
		rem = dialog.WxCheckBoxRemoveDup->GetValue();
		m_Config->Write( wxT( "SortOrder" ), order );
		m_Config->Write( wxT( "SortCaseSensitive" ), cs );
		m_Config->Write( wxT( "SortNumeric" ), num );
		m_Config->Write( wxT( "SortRemoveDup" ), rem );
		int flags = order |
					( cs ? sfCaseSensitive : 0 ) |
					( num ? sfNumericSort : 0 ) |
					( rem ? sfRemoveDuplicate : 0 ) ;
		int begin, end;
		g_ActiveMadEdit->GetSelectionLineId( begin, end );
		g_ActiveMadEdit->SortLines( flags, begin, end );
		RecordAsMadMacro( g_ActiveMadEdit, wxString::Format( wxT( "SortLines(%d, %d, %d)" ), flags, begin, end ) );
	}

	m_Config->SetPath( oldpath );
}

void MadEditFrame::OnEditCopyAsHexString( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->CopyAsHexString( false );
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "CopyAsHexString(False)" ) ) );
	}
}

void MadEditFrame::OnEditCopyAsHexStringWithSpace( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->CopyAsHexString( true );
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "CopyAsHexString(True)" ) ) );
	}
}

void MadEditFrame::OnEditCopyRevertHex( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		static wxString strDelimiters = wxT( " .,?!@#\t$%^&*()-=_+[]{}\\|;:\"'`<>/~" );
		wxString str = wxGetTextFromUser( _( "Delimiters:" ), _( "Revert Hex String" ), strDelimiters );

		if( !str.IsEmpty() )
		{
			strDelimiters = str;
		}

		g_ActiveMadEdit->CopyRevertHex( str );
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxString::Format( wxT( "CopyRevertHex(%s)" ), str.c_str() ) ) );
	}
}

void MadEditFrame::OnEditIncIndent( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->IncreaseDecreaseIndent( true );
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "IncreaseDecreaseIndent(True)" ) ) );
	}
}
void MadEditFrame::OnEditDecIndent( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->IncreaseDecreaseIndent( false );
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "IncreaseDecreaseIndent(False)" ) ) );
	}
}

void MadEditFrame::OnEditComment( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->CommentUncomment( true );
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "CommentUncomment(True)" ) ) );
	}
}

void MadEditFrame::OnEditUncomment( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->CommentUncomment( false );
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "CommentUncomment(False)" ) ) );
	}
}

void MadEditFrame::OnEditWordWrapToNewLine( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->ConvertWordWrapToNewLine();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ConvertWordWrapToNewLine()" ) ) );
	}
}
void MadEditFrame::OnEditNewLineToWordWrap( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->ConvertNewLineToWordWrap();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ConvertNewLineToWordWrap()" ) ) );
	}
}

void MadEditFrame::OnEditToUpperCase( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->ToUpperCase();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ToUpperCase()" ) ) );
	}
}

void MadEditFrame::OnEditToLowerCase( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->ToLowerCase();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ToLowerCase()" ) ) );
	}
}

void MadEditFrame::OnEditInvertCase( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->InvertCase();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "InvertCase()" ) ) );
	}
}

void MadEditFrame::OnEditCapitalize( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->Capitalize();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "Capitalize()" ) ) );
	}
}

void MadEditFrame::OnEditToHalfWidth( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->ToHalfWidth();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ToHalfWidth()" ) ) );
	}
}

void MadEditFrame::OnEditToHalfWidthByOptions( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	static wxArrayInt selections;
	static bool inited = false;

	if( !inited )
	{
		selections.Add( 0 );
		selections.Add( 1 );
		selections.Add( 2 );
		selections.Add( 3 );
		inited = true;
	}

	wxString choices[4] = { _( "ASCII characters" ), _( "Japanese characters" ),
							_( "Korean characters" ), _( "other characters" )
						  };
#if (wxMAJOR_VERSION == 2)
	size_t sels = wxGetSelectedChoices( selections,
										_( "Choose the characters you want to convert:" ), _( "To Halfwidth by Options..." ),
										4, choices, this );
#else
	int sels = wxGetSelectedChoices( selections,
									 _( "Choose the characters you want to convert:" ), _( "To Halfwidth by Options..." ),
									 4, choices, this );
#endif

	if( sels > 0 )
	{
		bool ascii = false, japanese = false, korean = false, other = false;

		for( size_t i = 0; i < sels; ++i )
		{
			switch( selections[i] )
			{
			case 0: ascii = true; break;

			case 1: japanese = true; break;

			case 2: korean = true; break;

			case 3: other = true; break;
			}
		}

		g_ActiveMadEdit->ToHalfWidth( ascii, japanese, korean, other );
		RecordAsMadMacro( g_ActiveMadEdit, wxString::Format( wxT( "ToHalfWidth(%s, %s, %s)" ), ascii ? wxT( "True" ) : wxT( "False" ),
						  japanese ? wxT( "True" ) : wxT( "False" ), korean ? wxT( "True" ) : wxT( "False" ), other ? wxT( "True" ) : wxT( "False" ) ) );
	}
}

void MadEditFrame::OnEditToFullWidth( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->ToFullWidth();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ToFullWidth()" ) ) );
	}
}

void MadEditFrame::OnEditToFullWidthByOptions( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	static wxArrayInt selections;
	static bool inited = false;

	if( !inited )
	{
		selections.Add( 0 );
		selections.Add( 1 );
		selections.Add( 2 );
		selections.Add( 3 );
		inited = true;
	}

	wxString choices[4] = { _( "ASCII characters" ), _( "Japanese characters" ),
							_( "Korean characters" ), _( "other characters" )
						  };
#if (wxMAJOR_VERSION == 2)
	size_t sels = wxGetSelectedChoices( selections,
										_( "Choose the characters you want to convert:" ), _( "To Fullwidth by Options..." ),
										4, choices, this );
#else
	int sels = wxGetSelectedChoices( selections,
									 _( "Choose the characters you want to convert:" ), _( "To Fullwidth by Options..." ),
									 4, choices, this );
#endif

	if( sels > 0 )
	{
		bool ascii = false, japanese = false, korean = false, other = false;

		for( size_t i = 0; i < sels; ++i )
		{
			switch( selections[i] )
			{
			case 0: ascii = true; break;

			case 1: japanese = true; break;

			case 2: korean = true; break;

			case 3: other = true; break;
			}
		}

		g_ActiveMadEdit->ToFullWidth( ascii, japanese, korean, other );
		RecordAsMadMacro( g_ActiveMadEdit, wxString::Format( wxT( "ToFullWidth(%s, %s, %s)" ), ascii ? wxT( "True" ) : wxT( "False" ),
						  japanese ? wxT( "True" ) : wxT( "False" ), korean ? wxT( "True" ) : wxT( "False" ), other ? wxT( "True" ) : wxT( "False" ) ) );
	}
}

void MadEditFrame::OnEditTabToSpace( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->ConvertTabToSpace();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ConvertTabToSpace()" ) ) );
	}
}
void MadEditFrame::OnEditSpaceToTab( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->ConvertSpaceToTab();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ConvertSpaceToTab()" ) ) );
	}
}

void MadEditFrame::OnEditTrimTrailingSpaces( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		g_ActiveMadEdit->TrimTrailingSpaces();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "TrimTrailingSpaces()" ) ) );
	}
}

void MadEditFrame::OnEditTrimLeadingSpaces( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		g_ActiveMadEdit->TrimLeadingSpaces();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "TrimLeadingSpaces()" ) ) );
	}
}

void MadEditFrame::OnEditDeleteEmptyLines( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		g_ActiveMadEdit->DeleteEmptyLines();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "DeleteEmptyLines()" ) ) );
	}
}

void MadEditFrame::OnEditDeleteEmptyLinesWithSpaces( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		g_ActiveMadEdit->DeleteEmptyLinesWithSpaces();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "DeleteEmptyLinesWithSpaces()" ) ) );
	}
}

void MadEditFrame::OnEditJoinLines( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		g_ActiveMadEdit->JoinLines();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "JoinLines()" ) ) );
	}
}

void MadEditFrame::OnEditInsertNumbers( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() == emColumnMode )
	{
		// Hide Modaless Dialog
		HideModalessDialogs();

		if( g_MadNumberDlg == NULL ) { g_MadNumberDlg = new MadNumberDlg( this ); }

		if( g_MadNumberDlg->ShowModal() == wxID_OK )
		{
			MadNumberingStepType numStepType = nstLinear;
			MadNumberFormat numFormat = nfDEC;
			MadNumberAlign numAlign = naLeft;
			wxString strStepType( wxT( "MadNumberingStepType.Linear" ) ),
					 strFormat( wxT( "MadNumberFormat.DEC" ) ),
					 strAlign( wxT( "MadNumberAlign.Left" ) );
			int sel = g_MadNumberDlg->WxChoiceNumberStepType->GetSelection();

			switch( sel )
			{
			case 1: numStepType = nstExponential; break;

			default: break;
			}

			sel = g_MadNumberDlg->WxChoiceFormat->GetSelection();

			switch( sel )
			{
			case 1:
				{
					numFormat = nfHEX;
					strFormat = wxT( "MadNumberFormat.HEX" );
				}
				break;

			case 2:
				{
					numFormat = nfBIN;
					strFormat = wxT( "MadNumberFormat.BIN" );
				}
				break;

			case 3:
				{
					numFormat = nfOCT;
					strFormat = wxT( "MadNumberFormat.OCT" );
				}
				break;

			default:
				break;
			}

			sel = g_MadNumberDlg->WxChoiceAlign->GetSelection();

			switch( sel )
			{
			case 1:
				{
					numAlign = naRight;
					strAlign = wxT( "MadNumberAlign.Right" );
				}
				break;

			default:
				break;
			}

			long initialNum = 0, numStep = 0, totalChar = 0;
			g_MadNumberDlg->WxEditNumberOfChars->GetValue().ToLong( &totalChar );
			g_MadNumberDlg->WxEditNumberingStep->GetValue().ToLong( &numStep );
			g_MadNumberDlg->WxEditInitialNumber->GetValue().ToLong( &initialNum );
			wxString prefix, postfix;

			if( g_MadNumberDlg->WxCheckPrefix->GetValue() )
			{ prefix = g_MadNumberDlg->WxEditPrefix->GetValue(); }

			if( g_MadNumberDlg->WxCheckPostfix->GetValue() )
			{ postfix = g_MadNumberDlg->WxEditPostfix->GetValue(); }

			g_ActiveMadEdit->InsertIncrementalNumber( initialNum, numStep, totalChar, numStepType, numFormat, numAlign, g_MadNumberDlg->WxPadChar->GetValue(), prefix, postfix );
			g_ActiveMadEdit->Refresh( false );
			RecordAsMadMacro( g_ActiveMadEdit, wxString::Format( wxT( "InsertIncrementalNumber(%s, %s, %s, %s, %s, %s, %s, \"%s\", \"%s\")" ),
							  wxLongLong( initialNum ).ToString().c_str(), wxLongLong( numStep ).ToString().c_str(), wxLongLong( totalChar ).ToString().c_str(), strStepType.c_str(), strFormat.c_str(), strAlign.c_str(),
							  g_MadNumberDlg->WxPadChar->GetValue() ? wxT( "True" ) : wxT( "False" ), prefix.c_str(), postfix.c_str() ) );
		}
	}
}

void MadEditFrame::OnEditColumnAlignLeft( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		g_ActiveMadEdit->ColumnAlignLeft();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ColumnAlignLeft()" ) ) );
	}
}

void MadEditFrame::OnEditColumnAlignRight( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		g_ActiveMadEdit->ColumnAlignRight();
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ColumnAlignRight()" ) ) );
	}
}

void MadEditFrame::OnEditSpellCheck( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		g_ActiveMadEdit->ReplaceWordFromCaretPos( g_SpellSuggestions[event.GetId() - menuSpellOption1] );
	}
}

void MadEditFrame::OnEditBookmarkCopy( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		g_ActiveMadEdit->CopyBookmarkedLines();
	}
}

void MadEditFrame::OnEditBookmarkCut( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		g_ActiveMadEdit->CutDelBookmarkedLines( true );
	}
}

void MadEditFrame::OnEditBookmarkDel( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		g_ActiveMadEdit->CutDelBookmarkedLines();
	}
}

void MadEditFrame::OnEditBookmarkDelUnmarked( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		g_ActiveMadEdit->DeleteUnmarkedLines();
	}
}

void MadEditFrame::OnEditBookmarkReplace( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		g_ActiveMadEdit->ReplaceBookmarkedLines();
	}
}

void MadEditFrame::OnSearchFind( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	if( g_SearchReplaceDialog == NULL )
	{
		g_SearchReplaceDialog = new MadSearchReplaceDialog( this, -1 );
	}

	if( g_FindInFilesDialog )
	{
		g_FindInFilesDialog->Show( false );
	}

	g_SearchReplaceDialog->ShowFindUI();

	if( g_ActiveMadEdit->IsSelected() )
	{
		if( g_ActiveMadEdit->GetSelectionSize() <= 10240 )
		{
			wxString ws;

			if( g_SearchReplaceDialog->WxCheckBoxFindHex->GetValue() )
			{
				wxString ws;
				g_ActiveMadEdit->GetSelHexString( ws, true );
				g_SearchReplaceDialog->m_FindText->SetText( ws );
			}
			else
			{
				g_ActiveMadEdit->GetSelText( ws );
				g_SearchReplaceDialog->m_FindText->SetText( ws );
			}
		}
		else
		{
			wxString ws;
			g_ActiveMadEdit->GetWordFromCaretPos( ws );

			if( !ws.IsEmpty() && ws[0] > wxChar( 0x20 ) )
			{
				g_SearchReplaceDialog->m_FindText->SetText( ws );
			}
		}
	}
	else
	{
		if( !( g_SearchReplaceDialog->WxCheckBoxFindHex->GetValue() ) )
		{
			wxString ws;
			g_ActiveMadEdit->GetWordFromCaretPos( ws );

			if( !ws.IsEmpty() && ws[0] > wxChar( 0x20 ) )
			{
				g_SearchReplaceDialog->m_FindText->SetText( ws );
			}
		}
	}

	g_SearchReplaceDialog->m_FindText->SelectAll();
	g_SearchReplaceDialog->m_FindText->SetFocus();
}

void MadEditFrame::OnSearchFindNext( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	if( g_SearchReplaceDialog == NULL )
	{
		g_SearchReplaceDialog = new MadSearchReplaceDialog( this, -1 );
	}

	if( g_FindInFilesDialog != NULL && g_FindInFilesDialog->IsShown() )
	{ g_FindInFilesDialog->Show( false ); }

	//g_SearchReplaceDialog->m_FindText->SetEncoding( g_ActiveMadEdit->GetEncodingName() );
	//g_SearchReplaceDialog->UpdateCheckBoxByCBHex( g_SearchReplaceDialog->WxCheckBoxFindHex->GetValue() );

	if( g_ActiveMadEdit->IsSelected() )
	{
		if( g_ActiveMadEdit->GetSelectionSize() <= 10240 )
		{
			if( g_SearchReplaceDialog->WxCheckBoxFindHex->GetValue() )
			{
				wxString ws;
				g_ActiveMadEdit->GetSelHexString( ws, true );
				g_SearchReplaceDialog->m_FindText->SetText( ws );
			}
			else
			{
				wxString ws;
				g_ActiveMadEdit->GetSelText( ws );
				g_SearchReplaceDialog->m_FindText->SetText( ws );
			}
		}
		else
		{
			wxString ws;
			g_ActiveMadEdit->GetWordFromCaretPos( ws );

			if( !ws.IsEmpty() && ws[0] > wxChar( 0x20 ) )
			{
				g_SearchReplaceDialog->m_FindText->SetText( ws );
			}
		}
	}

	wxCommandEvent e;
	g_SearchReplaceDialog->WxButtonFindNextClick( e );
}

void MadEditFrame::OnSearchFindPrevious( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	if( g_SearchReplaceDialog == NULL )
	{
		g_SearchReplaceDialog = new MadSearchReplaceDialog( this, -1 );
	}

	if( g_FindInFilesDialog != NULL && g_FindInFilesDialog->IsShown() )
	{ g_FindInFilesDialog->Show( false ); }

	//g_SearchReplaceDialog->m_FindText->SetEncoding( g_ActiveMadEdit->GetEncodingName() );
	//g_SearchReplaceDialog->UpdateCheckBoxByCBHex( g_SearchReplaceDialog->WxCheckBoxFindHex->GetValue() );

	if( g_ActiveMadEdit->IsSelected() )
	{
		wxString ws;

		if( g_ActiveMadEdit->GetSelectionSize() <= 10240 )
		{
			if( g_SearchReplaceDialog->WxCheckBoxFindHex->GetValue() )
			{
				g_ActiveMadEdit->GetSelHexString( ws, true );
				g_SearchReplaceDialog->m_FindText->SetText( ws );
			}
			else
			{
				g_ActiveMadEdit->GetSelText( ws );
				g_SearchReplaceDialog->m_FindText->SetText( ws );
			}
		}
		else
		{
			g_ActiveMadEdit->GetWordFromCaretPos( ws );

			if( !ws.IsEmpty() && ws[0] > wxChar( 0x20 ) )
			{
				g_SearchReplaceDialog->m_FindText->SetText( ws );
			}
		}
	}

	wxCommandEvent e;
	g_SearchReplaceDialog->WxButtonFindPrevClick( e );
}

void MadEditFrame::OnSearchReplace( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	if( g_SearchReplaceDialog == NULL )
	{
		g_SearchReplaceDialog = new MadSearchReplaceDialog( this, -1 );
	}

	if( g_FindInFilesDialog != NULL )
	{ g_FindInFilesDialog->Show( false ); }

	//g_SearchReplaceDialog->m_FindText->SetEncoding( g_ActiveMadEdit->GetEncodingName() );
	//g_SearchReplaceDialog->m_ReplaceText->SetEncoding( g_ActiveMadEdit->GetEncodingName() );
	g_SearchReplaceDialog->ShowReplaceUI();
	//wxString fname;
	//int fsize;
	//g_SearchReplaceDialog->UpdateCheckBoxByCBHex( g_SearchReplaceDialog->WxCheckBoxFindHex->GetValue() );
	//g_ActiveMadEdit->GetFont( fname, fsize );
	//g_SearchReplaceDialog->m_FindText->SetFont( fname, 14 );
	//g_SearchReplaceDialog->m_ReplaceText->SetFont( fname, 14 );

	if( g_ActiveMadEdit->IsSelected() )
	{
		if( g_ActiveMadEdit->GetSelectionSize() <= 10240 )
		{
			if( g_SearchReplaceDialog->WxCheckBoxFindHex->GetValue() )
			{
				wxString ws;
				g_ActiveMadEdit->GetSelHexString( ws, true );
				g_SearchReplaceDialog->m_FindText->SetText( ws );
			}
			else
			{
				wxString ws;
				g_ActiveMadEdit->GetSelText( ws );
				g_SearchReplaceDialog->m_FindText->SetText( ws );
			}
		}
		else
		{
			wxString ws;
			g_ActiveMadEdit->GetWordFromCaretPos( ws );

			if( !ws.IsEmpty() && ws[0] > wxChar( 0x20 ) )
			{
				g_SearchReplaceDialog->m_FindText->SetText( ws );
			}
		}
	}
	else
	{
		if( !( g_SearchReplaceDialog->WxCheckBoxFindHex->GetValue() ) )
		{
			wxString ws;
			g_ActiveMadEdit->GetWordFromCaretPos( ws );

			if( !ws.IsEmpty() && ws[0] > wxChar( 0x20 ) )
			{
				g_SearchReplaceDialog->m_FindText->SetText( ws );
			}
		}
	}

	g_SearchReplaceDialog->m_FindText->SelectAll();
	g_SearchReplaceDialog->m_FindText->SetFocus();
}

void MadEditFrame::OnSearchFindInFiles( wxCommandEvent& event )
{
	if( g_SearchReplaceDialog == NULL )
	{
		g_SearchReplaceDialog = new MadSearchReplaceDialog( this, -1 );
	}

	if( g_FindInFilesDialog == NULL )
	{
		g_FindInFilesDialog = new MadFindInFilesDialog( this, -1 );
	}

	// Hide Modaless Dialog
	g_SearchReplaceDialog->Show( false );
	static wxString text( _( "Find/Replace in Files Results" ) );
	int pid = m_InfoNotebook->GetPageIndex( m_FindInFilesResults );
	m_InfoNotebook->SetPageText( pid, text );
	g_FindInFilesDialog->Show();
	g_FindInFilesDialog->SetFocus();
	g_FindInFilesDialog->Raise();
	wxString fname;
	int fsize;

	if( g_ActiveMadEdit ) { g_ActiveMadEdit->GetFont( fname, fsize ); }
	else { g_FindInFilesDialog->m_FindText->GetFont( fname, fsize ); }

	g_FindInFilesDialog->m_FindText->SetFont( fname, 14 );
	g_FindInFilesDialog->m_ReplaceText->SetFont( fname, 14 );

	if( g_ActiveMadEdit && g_ActiveMadEdit->IsSelected() )
	{
		if( g_ActiveMadEdit->GetSelectionSize() <= 10240 )
		{
			if( g_FindInFilesDialog->WxCheckBoxFindHex->GetValue() )
			{
				wxString ws;
				g_ActiveMadEdit->GetSelHexString( ws, true );
				g_FindInFilesDialog->m_FindText->SetText( ws );
			}
			else
			{
				wxString ws;
				g_ActiveMadEdit->GetSelText( ws );
				g_FindInFilesDialog->m_FindText->SetText( ws );
			}
		}
		else
		{
			wxString ws;
			g_ActiveMadEdit->GetWordFromCaretPos( ws );

			if( !ws.IsEmpty() && ws[0] > wxChar( 0x20 ) )
			{
				g_FindInFilesDialog->m_FindText->SetText( ws );
			}
		}
	}

	g_FindInFilesDialog->m_FindText->SelectAll();
	g_FindInFilesDialog->m_FindText->SetFocus();
}

void MadEditFrame::OnSearchShowFindInFilesResults( wxCommandEvent& event )
{
	if( m_AuiManager.GetPane( m_InfoNotebook ).IsShown() )
	{
		m_AuiManager.GetPane( m_InfoNotebook ).Hide();
	}
	else
	{
		m_AuiManager.GetPane( m_InfoNotebook ).Show();
	}

	m_AuiManager.Update();
}

void MadEditFrame::OnSearchGoToLine( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	// Hide Modaless Dialog
	HideModalessDialogs();
	static wxString defstr;
	int lineCount = g_ActiveMadEdit->GetLineCount();
	wxString str = wxGetTextFromUser( wxString::Format( _( "Line Number(1~%d): (you can input HexNumber(0x1~0x%X): 0xNNN)" ), lineCount, lineCount ), _( "Go To Line" ), defstr );

	if( !str.IsEmpty() )
	{
		defstr = str;
	}

	str.Trim( false );
	str.Trim( true );
	long line;
	int base = 10;

	if( str.Left( 2 ).Lower() == wxT( "0x" ) ) { base = 16; }

	if( !str.IsEmpty() && str.ToLong( &line, base ) )
	{
		g_ActiveMadEdit->GoToLine( line );

		if( base == 16 )
		{ RecordAsMadMacro( g_ActiveMadEdit, wxString::Format( wxT( "GoToLine(0x%X)" ), line ) ); }
		else
		{ RecordAsMadMacro( g_ActiveMadEdit, wxString::Format( wxT( "GoToLine(%d)" ), line ) ); }
	}
}

void MadEditFrame::OnSearchGoToPosition( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	// Hide Modaless Dialog
	HideModalessDialogs();
	static wxString defstr;
	wxLongLong wxPos( g_ActiveMadEdit->GetFileSize() );
	wxString str = wxGetTextFromUser( wxString::Format( _( "Position(0~%s): (you can input HexNumber: 0xNNN)" ), ( wxPos.ToString() ).c_str() ), _( "Go To Position" ), defstr );

	if( !str.IsEmpty() )
	{
		defstr = str;
		wxInt64 pos;

		if( StrToInt64( str, pos ) )
		{
			g_ActiveMadEdit->SetCaretPosition( pos );
			wxLongLong wxPos1( pos );
			RecordAsMadMacro( g_ActiveMadEdit, wxString::Format( wxT( "SetCaretPosition(%s)" ), ( wxPos1.ToString() ).c_str() ) );
		}
	}
}

void MadEditFrame::OnSearchGoToLeftBrace( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->GoToLeftBrace();
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "GoToLeftBrace()" ) ) );
}
void MadEditFrame::OnSearchGoToRightBrace( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->GoToRightBrace();
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "GoToWriteBrace()" ) ) );
}


void MadEditFrame::OnViewEncoding( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	int idx = event.GetId() - menuEncoding1;
	wxString enc = MadEncoding::GetEncodingName( idx );
	g_ActiveMadEdit->SetEncoding( enc );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetEncoding(" ) ) + enc + wxT( ")" ) );
	wxString str = wxString( wxT( '[' ) ) + enc + wxT( "] " ) + wxGetTranslation( MadEncoding::GetEncodingDescription( idx ).c_str() );
	m_RecentEncodings->AddFileToHistory( str );
	int size;
	g_ActiveMadEdit->GetFont( str, size );
	m_RecentFonts->AddFileToHistory( str );
}

void MadEditFrame::OnViewRecentEncoding( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	int idx = event.GetId() - menuRecentEncoding1;
	wxString str = m_RecentEncodings->GetHistoryFile( idx );

	if( !str.IsEmpty() )
	{
		// get encname from str
		wxStringTokenizer tkz( str, wxT( "[]" ), wxTOKEN_STRTOK );

		if( tkz.HasMoreTokens() )
		{
			wxString enc = tkz.GetNextToken();
			g_ActiveMadEdit->SetEncoding( enc );
			RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetEncoding(" ) ) + enc + wxT( ")" ) );
			m_RecentEncodings->AddFileToHistory( str );
			wxString str;
			int size;
			g_ActiveMadEdit->GetFont( str, size );
			m_RecentFonts->AddFileToHistory( str );
		}
	}
}

void MadEditFrame::OnViewSyntax( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	int idx = event.GetId() - menuSyntax1;
	wxString title = MadSyntax::GetSyntaxTitle( idx );
	g_ActiveMadEdit->SetSyntax( title );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetSyntax(" ) ) + title + wxT( ")" ) );
}

void MadEditFrame::OnViewFontName( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	int idx = event.GetId() - menuFontName1;
	wxString fn;
	int fs;
	g_ActiveMadEdit->GetFont( fn, fs );
	wxString &fontname = g_FontNames[idx];
	g_ActiveMadEdit->SetFont( fontname, fs );
	m_RecentFonts->AddFileToHistory( fontname );
}

void MadEditFrame::OnViewRecentFont( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	int idx = event.GetId() - menuRecentFont1;
	wxString fontname = m_RecentFonts->GetHistoryFile( idx );

	if( !fontname.IsEmpty() )
	{
		wxString fn;
		int fs;
		g_ActiveMadEdit->GetFont( fn, fs );
		g_ActiveMadEdit->SetFont( fontname, fs );
		m_RecentFonts->AddFileToHistory( fontname );
	}
}

void MadEditFrame::OnViewFontSize( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	wxString fn;
	int fs;
	g_ActiveMadEdit->GetFont( fn, fs );
	fs = event.GetId() - menuFontSize1 + 1;
	g_ActiveMadEdit->SetFont( fn, fs );
}

void MadEditFrame::OnViewSetFont( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	wxFontData data;
	wxFont font = g_ActiveMadEdit->GetFont();
	MadSyntax* syn = g_ActiveMadEdit->GetSyntax();
	MadAttributes* attr = syn->GetAttributes( aeText );
	data.SetColour( attr->color );

	if( ( attr->style & fsItalic ) != 0 ) { font.SetStyle( wxFONTSTYLE_ITALIC ); }

	if( ( attr->style & fsBold ) != 0 ) { font.SetWeight( wxFONTWEIGHT_BOLD ); }

	font.SetUnderlined( ( attr->style & fsUnderline ) != 0 );

	if( font.Ok() )
	{
		data.SetInitialFont( font );
	}

	// Hide Modaless Dialog
	HideModalessDialogs();
	wxFontDialog dialog( this, data );

	if( dialog.ShowModal() == wxID_OK )
	{
		font = dialog.GetFontData().GetChosenFont();

		if( font.Ok() )
		{
			wxString fn = FixUTF8ToWCS( font.GetFaceName() );
			g_ActiveMadEdit->SetFont( fn, font.GetPointSize() );
			m_RecentFonts->AddFileToHistory( fn );
		}

		attr->color = dialog.GetFontData().GetColour();
		MadFontStyles style = fsNone;

		if( font.GetWeight() == wxFONTWEIGHT_BOLD ) { style |= fsBold; }

		if( font.GetStyle() == wxFONTSTYLE_ITALIC ) { style |= fsItalic; }

		if( font.GetUnderlined() ) { style |= fsUnderline; }

		attr->style = style;
		ApplySyntaxAttributes( syn );
		syn->SaveAttributes();
	}
}

void MadEditFrame::OnViewFixedWidthMode( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->SetFixedWidthMode( event.IsChecked() );

	if( event.IsChecked() )
	{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetFixedWidthMode(True)" ) ) ); }
	else
	{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetFixedWidthMode(False)" ) ) ); }
}

void MadEditFrame::OnViewTabColumn( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	int col = event.GetId() - menuTabColumn1 + 1;
	g_ActiveMadEdit->SetTabColumns( col );
	RecordAsMadMacro( g_ActiveMadEdit, wxString::Format( wxT( "SetTabColumns(%d)" ), col ) );
}

void MadEditFrame::OnViewPreview( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	int menuItemId = event.GetId();

	if( menuItemId != m_PreviewType )
	{
		m_PreviewType = menuItemId;

		if( m_HtmlPreview )
		{
			m_AuiManager.GetPane( m_HtmlPreview ).Show();
		}
		else
		{
			m_HtmlPreview = new wxHtmlWindow( this, wxID_ANY,
											  wxDefaultPosition,
											  wxSize( 400, 300 ) );
			m_AuiManager.AddPane( m_HtmlPreview, wxAuiPaneInfo().Name( wxT( "Markdown/HTML Preview" ) ).Caption( _( "Markdown/HTML Preview" ) ).Floatable( false ).Right().CloseButton( false ) );
			long style = wxAUI_TB_NO_TOOLTIPS;
			m_RefreshView = new wxAuiToolBar( this, ID_WXTOOLBAR1 + tbMAX + 1, wxPoint( 0, 0 ), wxSize( 392, 29 ), style );
			m_RefreshView->AddTool( menuRefreshPreview, wxT( "RefreshPreview" ), m_ImageList->GetBitmap( refresh_xpm_idx ), wxNullBitmap, wxITEM_NORMAL, _( "Refresh" ), _( "Refresh prviewed text" ), NULL );
			m_RefreshView->AddTool( menuClosePreview, wxT( "ClosePreview" ), m_ImageList->GetBitmap( closepreview_xpm_idx ), wxNullBitmap, wxITEM_NORMAL, _( "Close Preveiw" ), _( "Close preveiw windows" ), NULL );
			m_RefreshView->Realize();
			m_AuiManager.AddPane( m_RefreshView, wxAuiPaneInfo().Name( wxT( "RefreshBar" ) ).CaptionVisible( false ).CloseButton( false ).Dockable( false ).DockFixed().Resizable( false ).Top().Position( 6 ).Float() );
		}

		wxString text;
		g_ActiveMadEdit->GetText( text, false );

		if( m_PreviewType == ptPREVIEW_MARKDOWN )
		{
			std::wstring src = text.ToStdWstring();
			std::wostringstream out;
			markdown::Document doc;
			doc.read( src );
			doc.write( out );
			text = out.str();
		}

		m_AuiManager.GetPane( m_RefreshView ).Show();
		m_HtmlPreview->SetPage( text );
		g_ActiveMadEdit->Synced();
	}
	else
	{
		m_PreviewType = ptPREVIEW_NONE;

		if( m_HtmlPreview )
		{
			m_AuiManager.GetPane( m_HtmlPreview ).Hide();
		}

		m_AuiManager.GetPane( m_RefreshView ).Hide();
	}

	m_AuiManager.Update();
}

void MadEditFrame::OnRefreshPreview( wxCommandEvent& event )
{
	if( m_HtmlPreview )
	{
		m_AuiManager.GetPane( m_HtmlPreview ).Show();
		wxString text;
		g_ActiveMadEdit->GetText( text, false );

		if( m_PreviewType == ptPREVIEW_MARKDOWN )
		{
			std::wstring src = text.ToStdWstring();
			std::wostringstream out;
			markdown::Document doc;
			doc.read( src );
			doc.write( out );
			text = out.str();
		}

		m_HtmlPreview->SetPage( text );
	}
}

void MadEditFrame::OnClosePreview( wxCommandEvent& event )
{
	m_PreviewType = ptPREVIEW_NONE;

	if( m_HtmlPreview )
	{
		m_AuiManager.GetPane( m_HtmlPreview ).Hide();
	}

	m_AuiManager.GetPane( m_RefreshView ).Hide();
	m_AuiManager.Update();
}

void MadEditFrame::OnViewLineSpacing( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	int ls = ( event.GetId() - menuLineSpacing100 ) * 5 + 100;
	g_ActiveMadEdit->SetLineSpacing( ls );
	RecordAsMadMacro( g_ActiveMadEdit, wxString::Format( wxT( "SetLineSpacing(%d)" ), ls ) );
}

void MadEditFrame::OnViewNoWrap( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->SetWordWrapMode( wwmNoWrap );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetWordWrapMode(MadWordWrapMode.NoWrap)" ) ) );
}
void MadEditFrame::OnViewWrapByWindow( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->SetWordWrapMode( wwmWrapByWindow );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetWordWrapMode(MadWordWrapMode.WrapByWindow)" ) ) );
}
void MadEditFrame::OnViewWrapByColumn( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->SetWordWrapMode( wwmWrapByColumn );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetWordWrapMode(MadWordWrapMode.WrapByColumn)" ) ) );
}

void MadEditFrame::OnViewDisplayLineNumber( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->SetDisplayLineNumber( event.IsChecked() );

	if( event.IsChecked() )
	{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetDisplayLineNumber(True)" ) ) ); }
	else
	{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetDisplayLineNumber(False)" ) ) ); }
}

void MadEditFrame::OnViewDisplayBookmark( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->SetDisplayBookmark( event.IsChecked() );

	if( event.IsChecked() )
	{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetDisplayBookmark(True)" ) ) ); }
	else
	{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetDisplayBookmark(False)" ) ) ); }
}

void MadEditFrame::OnViewDisplay80ColHint( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->SetDisplay80ColHint( event.IsChecked() );

	if( event.IsChecked() )
	{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetDisplay80ColHint(True)" ) ) ); }
	else
	{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetDisplay80ColHint(False)" ) ) ); }
}

void MadEditFrame::OnViewShowEndOfLine( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->SetShowEndOfLine( event.IsChecked() );

	if( event.IsChecked() )
	{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetShowEndOfLine(True)" ) ) ); }
	else
	{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetShowEndOfLine(False)" ) ) ); }
}

void MadEditFrame::OnViewShowTabChar( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->SetShowTabChar( event.IsChecked() );

	if( event.IsChecked() )
	{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetShowTabChar(True)" ) ) ); }
	else
	{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetShowTabChar(False)" ) ) ); }
}

void MadEditFrame::OnViewShowSpaceChar( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->SetShowSpaceChar( event.IsChecked() );

	if( event.IsChecked() )
	{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetShowSpaceChar(True)" ) ) ); }
	else
	{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetShowSpaceChar(False)" ) ) ); }
}

void MadEditFrame::OnViewShowAllChars( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->SetShowTabChar( event.IsChecked() );
	g_ActiveMadEdit->SetShowEndOfLine( event.IsChecked() );
	g_ActiveMadEdit->SetShowSpaceChar( event.IsChecked() );

	if( event.IsChecked() )
	{
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetShowTabChar(True)" ) ) );
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetShowSpaceChar(True)" ) ) );
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetShowEndOfLine(True)" ) ) );
	}
	else
	{
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetShowTabChar(False)" ) ) );
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetShowSpaceChar(False)" ) ) );
		RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetShowEndOfLine(False)" ) ) );
	}
}

void MadEditFrame::OnViewRightToLeft( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		wxLayoutDirection dir = wxLayout_LeftToRight;

		if( event.IsChecked() ) { dir = wxLayout_RightToLeft; }

		g_ActiveMadEdit->SetLayoutDirection( dir );
	}
}

void MadEditFrame::OnViewMarkActiveLine( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->SetMarkActiveLine( event.IsChecked() );

		if( event.IsChecked() )
		{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetMarkActiveLine(True)" ) ) ); }
		else
		{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetMarkActiveLine(False)" ) ) ); }
	}
}

void MadEditFrame::OnViewMarkBracePair( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->SetMarkBracePair( event.IsChecked() );

		if( event.IsChecked() )
		{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetMarkBracePair(True)" ) ) ); }
		else
		{ RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetMarkBracePair(False)" ) ) ); }
	}
}

void MadEditFrame::OnViewSpellChecker( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{ g_ActiveMadEdit->SetSpellCheck( event.IsChecked() ); }
}

void MadEditFrame::OnSpellCheckIgnore( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		wxString str;
		shared_ptr<wxSpellCheckEngineInterface> & spellChecker = g_ActiveMadEdit->GetSpellChecker();
		g_ActiveMadEdit->GetWordFromCaretPos( str );
		spellChecker->GetUserCorrection( str );
		g_ActiveMadEdit->SetSpellCheck( true );
	}
}

void MadEditFrame::OnSpellCheckRemoveFromDict( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		wxString str;
		shared_ptr<wxSpellCheckEngineInterface> & spellChecker = g_ActiveMadEdit->GetSpellChecker();
		g_ActiveMadEdit->GetWordFromCaretPos( str );
		spellChecker->RemoveWordFromDictionary( str );
		g_ActiveMadEdit->SetSpellCheck( true );
	}
}

void MadEditFrame::OnSpellAdd2Dict( wxCommandEvent& event )
{
	if( g_ActiveMadEdit && g_ActiveMadEdit->GetEditMode() != emHexMode )
	{
		wxString str;
		g_ActiveMadEdit->GetWordFromCaretPos( str );
		g_ActiveMadEdit->AddtoDictionary( str );
	}
}

void MadEditFrame::OnViewTextMode( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->SetEditMode( emTextMode );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetEditMode(MadEditMode.TextMode)" ) ) );
}
void MadEditFrame::OnViewColumnMode( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->SetEditMode( emColumnMode );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetEditMode(MadEditMode.ColumnMode)" ) ) );
}
void MadEditFrame::OnViewHexMode( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->SetEditMode( emHexMode );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetEditMode(MadEditMode.HexMode)" ) ) );
}

void MadEditFrame::OnViewToolbars( wxCommandEvent& event )
{
	int menuId = event.GetId();
	int toolbarId = menuId - menuToolBar1;

	if( toolbarId < tbMAX )
	{
		if( m_ToolbarStatus[toolbarId] )
		{
			m_ToolbarStatus[toolbarId] = false;
			int i = tbSTANDARD;

			for( ; i < tbMAX; ++i )
			{
				if( m_ToolbarStatus[i] )
				{
					m_ToolbarStatus[tbMAX] = true;
					break;
				}
			}

			if( i == tbMAX )
			{ m_ToolbarStatus[tbMAX] = false; }

			m_AuiManager.GetPane( WxToolBar[toolbarId] ).Hide();

			for( int i = toolbarId + 1; i < tbMAX; ++i )
			{
				m_AuiManager.GetPane( WxToolBar[i] ).Position( i - 1 );
			}
		}
		else
		{
			m_AuiManager.GetPane( WxToolBar[toolbarId] ).Show( true );
			m_ToolbarStatus[toolbarId] = true;

			if( !m_ToolbarStatus[tbMAX] )
			{ m_ToolbarStatus[tbMAX] = true; }
		}

		m_AuiManager.Update();
	}
}
void MadEditFrame::OnViewToolBarsToggleAll( wxCommandEvent& event )
{
	if( event.IsChecked() || event.GetInt() == -1 )
	{
		for( int toolbarId = tbSTANDARD; toolbarId < tbMAX; ++toolbarId )
		{
			if( m_ToolbarStatus[toolbarId] )
			{
				m_AuiManager.GetPane( WxToolBar[toolbarId] ).Show();
			}
		}

		m_ToolbarStatus[tbMAX] = true;
	}
	else
	{
		for( int toolbarId = tbSTANDARD; toolbarId < tbMAX; ++toolbarId )
		{
			if( m_ToolbarStatus[toolbarId] )
			{ m_AuiManager.GetPane( WxToolBar[toolbarId] ).Hide(); }
		}

		m_ToolbarStatus[tbMAX] = false;
	}

	m_AuiManager.Update();
}

void MadEditFrame::OnToolsOptions( wxCommandEvent& event )
{
	size_t lang_count = g_LanguageString.GetCount();
	ScanForLocales();

	if( g_OptionsDialog == NULL ) { g_OptionsDialog = new MadOptionsDialog( this ); }
	else
	{
		// update languages
		wxString lang = g_OptionsDialog->WxComboBoxLanguage->GetValue();
		g_OptionsDialog->WxComboBoxLanguage->Clear();
		g_OptionsDialog->WxComboBoxLanguage->Append(g_LanguageString);
		if(wxNOT_FOUND == g_LanguageString.Index(lang)) g_OptionsDialog->WxComboBoxLanguage->SetValue(g_LanguageString[0]);
		else g_OptionsDialog->WxComboBoxLanguage->SetValue(lang);
	}

	// Hide Modaless Dialog
	HideModalessDialogs();
	g_OptionsDialog->LoadOptions();

	if( g_OptionsDialog->ShowModal() == wxID_OK )
	{
		// save options
		wxString oldpath = m_Config->GetPath();
		m_Config->SetPath( wxT( "/MadEdit" ) );
		bool rcm, isiot, ai, acp, msc, mscck, mmp, afcp;
		wxString mc, tc, ic;
		m_Config->Write( wxT( "Language" ), g_OptionsDialog->WxComboBoxLanguage->GetValue() );
		m_Config->Write( wxT( "SingleInstance" ), g_OptionsDialog->WxCheckBoxSingleInstance->GetValue() );
		rcm = g_OptionsDialog->WxCheckBoxRecordCaretMovements->GetValue();
		m_Config->Write( wxT( "RecordCaretMovements" ), rcm );
		m_Config->Write( wxT( "MaxSizeToLoad" ), g_OptionsDialog->WxEditMaxSizeToLoad->GetValue() );
		m_Config->Write( wxT( "MaxTextFileSize" ), g_OptionsDialog->WxEditMaxTextFileSize->GetValue() );
		m_Config->Write( wxT( "DefaultEncoding" ), g_OptionsDialog->WxComboBoxEncoding->GetValue() );
#ifdef __WXMSW__

		if( g_OptionsDialog->WxCheckBoxRightClickMenu->GetValue() )
		{
			wxRegKey *pRegKeyMad = new wxRegKey( g_MadEditRegkeyPath + wxT( "*\\shell\\MadEdit-Mod" ) );
			pRegKeyMad->Create();
			pRegKeyMad->SetValue( wxEmptyString, wxT( "MadEdit-Mod" ) );
			wxRegKey *pRegKey = new wxRegKey( *pRegKeyMad, wxT( "\\command" ) );
			pRegKey->Create();
			wxString exepath = GetExecutablePath();
			pRegKey->SetValue( wxEmptyString, wxString( wxT( '"' ) ) + exepath + wxString( wxT( "\" \"%1\"" ) ) );
			delete pRegKey;
			delete pRegKeyMad;
		}
		else
		{
			wxRegKey *pRegKey = new wxRegKey( g_MadEditRegkeyPath + wxT( "*\\shell\\MadEdit-Mod" ) );
			pRegKey->DeleteSelf();
			delete pRegKey;
		}

#endif
		m_Config->Write( wxT( "MaxLineLength" ), g_OptionsDialog->WxEditMaxLineLength->GetValue() );
		mc = g_OptionsDialog->WxEditMaxColumns->GetValue();
		m_Config->Write( wxT( "MaxColumns" ), mc );
		tc = g_OptionsDialog->WxEditTabColumns->GetValue();
		m_Config->Write( wxT( "TabColumns" ), tc );
		ic = g_OptionsDialog->WxEditIndentColumns->GetValue();
		m_Config->Write( wxT( "IndentColumns" ), ic );
		m_Config->Write( wxT( "DateTimeFormat" ), g_OptionsDialog->WxEditDateTime->GetValue() );
		m_Config->Write( wxT( "DateTimeInEnglish" ), g_OptionsDialog->WxCheckBoxDateTimeInEnglish->GetValue() );
		isiot = g_OptionsDialog->WxCheckBoxTabOrSpaces->GetValue();
		m_Config->Write( wxT( "InsertSpacesInsteadOfTab" ), isiot );
		ai = g_OptionsDialog->WxCheckBoxAutoIndent->GetValue();
		m_Config->Write( wxT( "AutoIndent" ), ai );
		acp = g_OptionsDialog->WxCheckBoxAutoCompletePair->GetValue();
		m_Config->Write( wxT( "AutoCompletePair" ), acp );
		msc = g_OptionsDialog->WxCheckBoxMouseSelectToCopy->GetValue();
		m_Config->Write( wxT( "MouseSelectToCopy" ), msc );
		mscck = g_OptionsDialog->WxCheckBoxCtrlWithMouseToSelect->GetValue();
		m_Config->Write( wxT( "MouseSelectToCopyWithCtrlKey" ), mscck );
		mmp = g_OptionsDialog->WxCheckBoxMiddleMouseToPaste->GetValue();
		m_Config->Write( wxT( "MiddleMouseToPaste" ), mmp );
		afcp = g_OptionsDialog->WxCheckBoxAutoFillColumnPaste->GetValue();
		m_Config->Write( wxT( "AutoFillColumnPaste" ), afcp );
		extern bool g_DoNotSaveSettings;
		g_DoNotSaveSettings = g_OptionsDialog->WxCheckBoxDoNotSaveSettings->GetValue();
		m_Config->Write( wxT( "ReloadFiles" ), g_OptionsDialog->WxCheckBoxReloadFiles->GetValue() );
		m_ReloadFiles  = g_OptionsDialog->WxCheckBoxReloadFiles->GetValue();
		m_Config->Write( wxT( "RestoreCaretPos" ), g_OptionsDialog->WxCheckBoxRestoreCaretPos->GetValue() );
		extern bool g_ForcePurgeThisTime;
		m_Config->Read( wxT( "PurgeHistory" ), g_ForcePurgeThisTime );
		m_PurgeHistory = g_OptionsDialog->WxCheckBoxPurgeHistory->GetValue();
		m_Config->Write( wxT( "PurgeHistory" ), g_OptionsDialog->WxCheckBoxPurgeHistory->GetValue() );
		m_Config->Write( wxT( "ShowQSearchBarOnStart" ), g_OptionsDialog->WxCheckBoxShowQSearchBar->GetValue() );

		if( !g_ForcePurgeThisTime ) { g_ForcePurgeThisTime = g_OptionsDialog->WxCheckBoxPurgeHistory->GetValue(); }
		else { g_ForcePurgeThisTime = false; }

		bool bb;
		long ll;
		wxString ss;
		bb = g_OptionsDialog->WxCheckBoxPrintSyntax->GetValue();
		m_Config->Write( wxT( "PrintSyntax" ), bb );
		bb = g_OptionsDialog->WxCheckBoxPrintLineNumber->GetValue();
		m_Config->Write( wxT( "PrintLineNumber" ), bb );
		bb = g_OptionsDialog->WxCheckBoxPrintBookmark->GetValue();
		m_Config->Write( wxT( "PrintBookmark" ), bb );
		bb = g_OptionsDialog->WxCheckBoxPrintEndOfLine->GetValue();
		m_Config->Write( wxT( "PrintEndOfLine" ), bb );
		bb = g_OptionsDialog->WxCheckBoxPrintTabChar->GetValue();
		m_Config->Write( wxT( "PrintTabChar" ), bb );
		bb = g_OptionsDialog->WxCheckBoxPrintSpaceChar->GetValue();
		m_Config->Write( wxT( "PrintSpaceChar" ), bb );
		ll = g_OptionsDialog->WxRadioBoxPrintOffset->GetSelection();
		m_Config->Write( wxT( "PrintOffsetHeader" ), ll );
		bb = g_OptionsDialog->WxCheckBoxPrintPageHeader->GetValue();
		m_Config->Write( wxT( "PrintPageHeader" ), bb );
		ss = g_OptionsDialog->WxEditHeaderLeft->GetValue();
		m_Config->Write( wxT( "PageHeaderLeft" ), ss );
		ss = g_OptionsDialog->WxEditHeaderCenter->GetValue();
		m_Config->Write( wxT( "PageHeaderCenter" ), ss );
		ss = g_OptionsDialog->WxEditHeaderRight->GetValue();
		m_Config->Write( wxT( "PageHeaderRight" ), ss );
		bb = g_OptionsDialog->WxCheckBoxPrintPageFooter->GetValue();
		m_Config->Write( wxT( "PrintPageFooter" ), bb );
		ss = g_OptionsDialog->WxEditFooterLeft->GetValue();
		m_Config->Write( wxT( "PageFooterLeft" ), ss );
		ss = g_OptionsDialog->WxEditFooterCenter->GetValue();
		m_Config->Write( wxT( "PageFooterCenter" ), ss );
		ss = g_OptionsDialog->WxEditFooterRight->GetValue();
		m_Config->Write( wxT( "PageFooterRight" ), ss );
		wxString path = g_OptionsDialog->WxEditDictionaryDir->GetValue();

		if( wxDir::Exists( path ) )
		{
			SpellCheckerManager::Instance().SetDictionaryPath( path );
			SpellCheckerManager::Instance().ScanForDictionaries();
		}

		wxString dictDesc = g_OptionsDialog->WxChoiceDictionary->GetString( g_OptionsDialog->WxChoiceDictionary->GetSelection() );
		wxString dictName = SpellCheckerManager::Instance().GetDictionaryName( dictDesc );

		if( !dictName.IsEmpty() )
		{
			SpellCheckerManager::Instance().SetDictionaryName( dictName );
		}

		if( SpellCheckerManager::Instance().GetEnablePersonalDictionary()
				!= g_OptionsDialog->WxCheckBoxPersonalDict->GetValue() )
		{
			SpellCheckerManager::Instance().SetEnablePersonalDictionary( g_OptionsDialog->WxCheckBoxPersonalDict->GetValue() );
		}

		// SpellChecker
		SpellCheckerManager::Instance().Save();
		int count = int( m_Notebook->GetPageCount() );

		for( int i = 0; i < count; ++i )
		{
			MadEdit *madedit = ( MadEdit* )m_Notebook->GetPage( i );
			madedit->SetRecordCaretMovements( rcm );
			madedit->SetInsertSpacesInsteadOfTab( isiot );
			madedit->SetAutoIndent( ai );
			madedit->SetAutoCompletePair( acp );
			madedit->SetMouseSelectToCopy( msc );
			madedit->SetMouseSelectToCopyWithCtrlKey( mscck );
			madedit->SetMiddleMouseToPaste( mmp );
			madedit->SetAutoFillColumnPaste( afcp );
			long lo;

			if( mc.ToLong( &lo ) ) { madedit->SetMaxColumns( lo ); }

			if( tc.ToLong( &lo ) ) { madedit->SetTabColumns( lo ); }

			if( ic.ToLong( &lo ) ) { madedit->SetIndentColumns( lo ); }
		}

		extern bool g_ResetAllKeys;
		g_ResetAllKeys = g_OptionsDialog->WxCheckBoxResetAllKeys->GetValue();

		// apply the changed keybindings
		if( g_OptionsDialog->ChangedTreeItemDataList.size() != 0 )
		{
			list<TreeItemData*> ChangedMenuList;
			list<TreeItemData*>::iterator tidit = g_OptionsDialog->ChangedTreeItemDataList.begin();
			list<TreeItemData*>::iterator tiditend = g_OptionsDialog->ChangedTreeItemDataList.end();

			while( tidit != tiditend )
			{
				TreeItemData *tid = *tidit;
				CommandData *cd = tid->cmddata;

				// remove key of changed menu
				if( cd->menu_id > 0 )
				{
					wxString menukey, newkey;
					menukey = MadEdit::ms_KeyBindings.GetKeyByMenuText( cd->menuid_name );

					if( !tid->keys.IsEmpty() )
					{
						newkey = tid->keys[0];
					}

					if( menukey.Lower() != newkey.Lower() )
					{
						// add it to ChangedMenuList for modifying menukey later
						ChangedMenuList.push_back( tid );
					}

					MadEdit::ms_KeyBindings.RemoveByMenuId( cd->menu_id );
				}
				else
					if( cd->command > 0 ) // delete the keys of changed comnnad
					{
						MadEdit::ms_KeyBindings.RemoveByCommand( cd->command );
					}

				++tidit;
			}

			// add the keys of changed comnnad
			tidit = g_OptionsDialog->ChangedTreeItemDataList.begin();

			while( tidit != tiditend )
			{
				TreeItemData *tid = *tidit;
				CommandData *cd = tid->cmddata;

				if( cd->menu_id > 0 )
				{
					size_t idx = 0, count = tid->keys.GetCount();

					for( ; idx < count; ++idx )
					{
						MadEdit::ms_KeyBindings.Add( StringToShortCut( tid->keys[idx] ), idx == 0, cd->menu_id, true );
					}
				}
				else
					if( cd->command > 0 )
					{
						size_t idx = 0, count = tid->keys.GetCount();

						for( ; idx < count; ++idx )
						{
							MadEdit::ms_KeyBindings.Add( StringToShortCut( tid->keys[idx] ), cd->command, true );
						}
					}

				++tidit;
			}

			// change the menukey
			tidit = ChangedMenuList.begin();
			tiditend = ChangedMenuList.end();
#ifdef __WXMSW__
			bool bHasMenuIcon = ( wxGetOsVersion() != wxOS_WINDOWS_9X ); // fixed win98 will crash if menuitem has icon
#endif

			while( tidit != tiditend )
			{
				TreeItemData *tid = *tidit;
				CommandData *cd = tid->cmddata;
				wxString newkey;

				if( !tid->keys.IsEmpty() )
				{
					newkey = tid->keys[0];
					newkey = wxString( wxT( '\t' ) ) + newkey;
				}

				// change the menu key
				wxMenuItem *mit = WxMenuBar1->FindItem( cd->menu_id );
#if wxCHECK_VERSION(2,9,0)
				mit->SetItemLabel( mit->GetItemLabelText() + newkey );
#else
				mit->SetText( mit->GetLabel() + newkey );
#endif
#ifdef __WXMSW__

				if( bHasMenuIcon )
#endif
					if( cd->image_idx >= 0 && cd->kind == wxITEM_NORMAL )
					{
						mit->SetBitmap( m_ImageList->GetBitmap( cd->image_idx ) );
					}

				++tidit;
			}

			ResetAcceleratorTable();
		}

		//Write config for Astyle
		m_Config->SetPath( wxT( "/astyle" ) );
		ll = g_OptionsDialog->WxRadioBoxBracketStyle->GetSelection();
		m_Config->Write( wxT( "style" ), ll );
		bb = g_OptionsDialog->WxCheckAttachClasses->GetValue();
		m_Config->Write( wxT( "attach_classes" ), bb );
		bb = g_OptionsDialog->WxCheckAttachExternC->GetValue();
		m_Config->Write( wxT( "attach_extern_c" ), bb );
		bb = g_OptionsDialog->WxCheckAttachNamespaces->GetValue();
		m_Config->Write( wxT( "attach_namespaces" ), bb );
		bb = g_OptionsDialog->WxCheckAttachInlines->GetValue();
		m_Config->Write( wxT( "attach_inlines" ), bb );
		bb = g_OptionsDialog->WxCheckForceUseTabs->GetValue();
		m_Config->Write( wxT( "force_tabs" ), bb );
		ll = g_OptionsDialog->WxSpinIndentation->GetValue();
		m_Config->Write( wxT( "indentation" ), ll );
		bb = g_OptionsDialog->WxCheckUseTab->GetValue();
		m_Config->Write( wxT( "use_tabs" ), bb );
		bb = g_OptionsDialog->WxCheckIndentCase->GetValue();
		m_Config->Write( wxT( "indent_case" ), bb );
		bb = g_OptionsDialog->WxCheckIndentClasses->GetValue();
		m_Config->Write( wxT( "indent_classes" ), bb );
		bb = g_OptionsDialog->WxCheckIndentLabels->GetValue();
		m_Config->Write( wxT( "indent_labels" ), bb );
		bb = g_OptionsDialog->WxCheckIndentModifiers->GetValue();
		m_Config->Write( wxT( "indent_modifiers" ), bb );
		bb = g_OptionsDialog->WxCheckIndentNamespaces->GetValue();
		m_Config->Write( wxT( "indent_namespaces" ), bb );
		bb = g_OptionsDialog->WxCheckIndentSwitches->GetValue();
		m_Config->Write( wxT( "indent_switches" ), bb );
		bb = g_OptionsDialog->WxCheckIndentPreprocBlock->GetValue();
		m_Config->Write( wxT( "indent_preproc_block" ), bb );
		bb = g_OptionsDialog->WxCheckIndentPreprocDefine->GetValue();
		m_Config->Write( wxT( "indent_preproc_define" ), bb );
		bb = g_OptionsDialog->WxCheckIndentPreprocCond->GetValue();
		m_Config->Write( wxT( "indent_preproc_cond" ), bb );
		bb = g_OptionsDialog->WxCheckIndentCol1Comments->GetValue();
		m_Config->Write( wxT( "indent_col1_comments" ), bb );
		ll = g_OptionsDialog->WxSpinMinConditionalEvent->GetValue();
		m_Config->Write( wxT( "min_conditional_indent" ), ll );
		g_OptionsDialog->WxEditMaxInStatementIndent->GetValue().ToLong( &ll );
		m_Config->Write( wxT( "max_instatement_indent" ), ll );
		bb = g_OptionsDialog->WxCheckBreakClosing->GetValue();
		m_Config->Write( wxT( "break_closing" ), bb );
		bb = g_OptionsDialog->WxCheckBreakElseIfs->GetValue();
		m_Config->Write( wxT( "break_elseifs" ), bb );
		bb = g_OptionsDialog->WxCheckAddBrackets->GetValue();
		m_Config->Write( wxT( "add_brackets" ), bb );
		bb = g_OptionsDialog->WxCheckAddOneLineBrackets->GetValue();
		m_Config->Write( wxT( "add_one_line_brackets" ), bb );
		bb = g_OptionsDialog->WxCheckKeepComplex->GetValue();
		m_Config->Write( wxT( "keep_complex" ), bb );
		bb = g_OptionsDialog->WxCheckRemoveBrackets->GetValue();
		m_Config->Write( wxT( "remove_brackets" ), bb );
		bb = g_OptionsDialog->WxCheckKeepBlocks->GetValue();
		m_Config->Write( wxT( "keep_blocks" ), bb );
		bb = g_OptionsDialog->WxCheckConvertTabs->GetValue();
		m_Config->Write( wxT( "convert_tabs" ), bb );
		bb = g_OptionsDialog->WxCheckCloseTemplates->GetValue();
		m_Config->Write( wxT( "closewxTemplates" ), bb );
		bb = g_OptionsDialog->WxCheckRemoveCommentPrefix->GetValue();
		m_Config->Write( wxT( "remove_comment_prefix" ), bb );
		bb = g_OptionsDialog->WxCheckBreakLines->GetValue();
		bb = m_Config->Write( wxT( "break_lines" ), bb );

		if( bb )
		{
			wxString maxLine = g_OptionsDialog->WxEditSFMaxLineLength->GetValue();
			m_Config->Read( wxT( "max_line_length" ), maxLine );
			bb = g_OptionsDialog->WxCheckBreakAfterLogical->GetValue();
			m_Config->Write( wxT( "break_after_mode" ), bb );
		}

		bb = g_OptionsDialog->WxCheckBreakBlocks->GetValue();
		m_Config->Write( wxT( "break_blocks" ), bb );
		bb = g_OptionsDialog->WxCheckBreakBlocksAll->GetValue();
		m_Config->Write( wxT( "break_blocks_all" ), bb );
		bb = g_OptionsDialog->WxCheckPadOperators->GetValue();
		m_Config->Write( wxT( "pad_operators" ), bb );
		bb = g_OptionsDialog->WxCheckPadParensOut->GetValue();
		m_Config->Write( wxT( "pad_parentheses_out" ), bb );
		bb = g_OptionsDialog->WxCheckPadParensIn->GetValue();
		m_Config->Write( wxT( "pad_parentheses_in" ), bb );
		bb = g_OptionsDialog->WxCheckPadHeader->GetValue();
		m_Config->Write( wxT( "pad_header" ), bb );
		bb = g_OptionsDialog->WxCheckUnpadParens ->GetValue();
		m_Config->Write( wxT( "unpad_parentheses" ), bb );
		bb = g_OptionsDialog->WxCheckDelEmptyLine->GetValue();
		m_Config->Write( wxT( "delete_empty_lines" ), bb );
		bb = g_OptionsDialog->WxCheckFillEmptyLines->GetValue();
		m_Config->Write( wxT( "fill_empty_lines" ), bb );
		wxString pointerAlign( wxT( "None" ) );

		switch( g_OptionsDialog->WxChoicePointerAlign->GetSelection() )
		{
		case astyle::PTR_ALIGN_TYPE:
			pointerAlign = wxString( wxT( "Type" ) );
			break;

		case astyle::PTR_ALIGN_MIDDLE:
			pointerAlign = wxString( wxT( "Middle" ) );
			break;

		case astyle::PTR_ALIGN_NAME:
			pointerAlign = wxString( wxT( "Name" ) );
			break;

		default :
			break;
		}

		m_Config->Write( wxT( "pointer_align" ), pointerAlign );
		wxString referenceAlign( wxT( "None" ) );

		switch( g_OptionsDialog->WxChoiceReferenceAlign->GetSelection() )
		{
		case astyle::REF_ALIGN_TYPE:
			referenceAlign = wxString( wxT( "Type" ) );
			break;

		case astyle::REF_ALIGN_MIDDLE:
			referenceAlign = wxString( wxT( "Middle" ) );
			break;

		case astyle::REF_ALIGN_NAME:
			referenceAlign = wxString( wxT( "Name" ) );
			break;

		default :
			break;
		}

		m_Config->Write( wxT( "reference_align" ), referenceAlign );
		m_Config->SetPath( wxT( "/xml" ) );
		m_Config->Write( wxT( "indentation" ), g_OptionsDialog->WxEditXmlIndentSize->GetValue() );
		m_Config->Write( wxT( "version" ), g_OptionsDialog->WxEditXMLversion->GetValue() );
		m_Config->SetPath( oldpath );
	}
}

void MadEditFrame::OnToolsHighlighting( wxCommandEvent& event )
{
	if( g_HighlightingDialog == NULL ) { g_HighlightingDialog = new MadHighlightingDialog( this, -1 ); }

	if( g_ActiveMadEdit )
	{
		g_HighlightingDialog->m_InitSetting = g_ActiveMadEdit->GetSyntaxTitle();
	}
	else
	{
		g_HighlightingDialog->m_InitSetting = wxT( "XXX" );
	}

	// Hide Modaless Dialog
	HideModalessDialogs();
	int id = g_HighlightingDialog->ShowModal();
	g_HighlightingDialog->FreeSyntax( id != wxID_OK ); // press cancel to restore the syntax

	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->SetFocus();
	}
}

#ifdef __WXMSW__
void MadEditFrame::OnToolsFileAssociation( wxCommandEvent& event )
{
	// Hide Modaless Dialog
	HideModalessDialogs();
	MadFileAssociationDialog fadialog( this, -1 );
	fadialog.ShowModal();
}
#endif

void MadEditFrame::OnToolsPurgeHistories( wxCommandEvent& event )
{
	MadPurgeHistoryDialog dlg( this );

	if( dlg.ShowModal() == wxID_OK )
	{
		// insert your code here
		if( dlg.wxCheckBoxRecentFiles->IsChecked() )
		{ PurgeRecentFiles(); }

		if( dlg.wxCheckBoxRecentFonts->IsChecked() )
		{ PurgeRecentFonts(); }

		if( dlg.wxCheckBoxRecentEncodings->IsChecked() )
		{ PurgeRecentEncodings(); }

		if( dlg.wxCheckBoxRecentSearchedTexts->IsChecked() )
		{
			if( g_SearchReplaceDialog == NULL )
			{
				g_SearchReplaceDialog = new MadSearchReplaceDialog( this, -1 );
			}

			g_SearchReplaceDialog->PurgeRecentFindTexts();
		}

		if( dlg.wxCheckBoxRecentReplacedTexts->IsChecked() )
		{
			if( g_SearchReplaceDialog == NULL )
			{
				g_SearchReplaceDialog = new MadSearchReplaceDialog( this, -1 );
			}

			g_SearchReplaceDialog->PurgeRecentReplaceTexts();
		}

		if( dlg.wxCheckBoxRecentSearchedDirectories->IsChecked() )
		{
			if( g_FindInFilesDialog == NULL )
			{
				g_FindInFilesDialog = new MadFindInFilesDialog( this, -1 );
			}

			g_FindInFilesDialog->PurgeRecentFindDirs();
		}

		if( dlg.wxRecentSearchedFileFilters->IsChecked() )
		{
			if( g_FindInFilesDialog == NULL )
			{
				g_FindInFilesDialog = new MadFindInFilesDialog( this, -1 );
			}

			g_FindInFilesDialog->PurgeRecentFindFilters();
		}

		if( dlg.wxCheckBoxRecentSearchedExcludeFilters->IsChecked() )
		{
			if( g_FindInFilesDialog == NULL )
			{
				g_FindInFilesDialog = new MadFindInFilesDialog( this, -1 );
			}

			g_FindInFilesDialog->PurgeRecentFindExcludes();
		}

		if( dlg.WxCheckBoxCaretPos->IsChecked() )
		{
			m_Config->SetPath( wxT( "/FileCaretPos" ) );
			g_FileCaretPosManager.Clear( m_Config );
		}

		m_QuickSearch->Clear();
	}
}

void MadEditFrame::OnToolsRunTempMacro( wxCommandEvent& event )
{
	if( g_MadMacroDlg == NULL )
	{
		g_MadMacroDlg = new MadMacroDlg( this );
	}

	if( g_SearchReplaceDialog != NULL )
	{ g_SearchReplaceDialog->Show( false ); }

	if( g_FindInFilesDialog != NULL )
	{ g_FindInFilesDialog->Show( false ); }

	g_MadMacroDlg->ShowModal();

	if( g_ActiveMadEdit )
	{
		g_ActiveMadEdit->Refresh( false );
	}
}

void MadEditFrame::OnToolsRunMacroFile( wxCommandEvent& event )
{
	wxString dir = g_MadEditHomeDir + wxT( "scripts" );

	if( !wxDir::Exists( dir ) )
	{
		if( m_RecentFiles->GetCount() )
		{
			wxFileName filename( m_RecentFiles->GetHistoryFile( 0 ) );
			dir = filename.GetPath( wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR );

			if( !wxDir::Exists( dir ) ) { dir = wxGetCwd(); }
		}
		else
		{
			dir = wxGetCwd();
		}
	}

	// Hide Modaless Dialog
	if( g_SearchReplaceDialog )
	{
		g_SearchReplaceDialog->Show( false );
	}

	if( g_FindInFilesDialog )
	{
		g_FindInFilesDialog->Show( false );
	}

	static int filterIndex = 0;
	wxString fileFilter = wxString( wxT( "Mad Macro(*.mpy)|*.mpy|" ) ) + wxFileSelectorDefaultWildcardStr + wxT( "|All files(*;*.*)" );
	wxFileDialog dlg( this, _( "Open Mad Macro File" ), dir, wxEmptyString, fileFilter,
#if wxCHECK_VERSION(2,8,0)
					  wxFD_OPEN | wxFD_FILE_MUST_EXIST );
#else
					  wxOPEN );
#endif
	dlg.SetFilterIndex( filterIndex );

	if( dlg.ShowModal() == wxID_OK )
	{
		wxString filename = dlg.GetPath();
		wxTextFile scriptfile( filename );
		scriptfile.Open( wxConvFile );

		if( scriptfile.IsOpened() )
		{
			wxString str = scriptfile.GetFirstLine() + wxT( "\n" );

			for( ; !scriptfile.Eof(); )
			{
				str << scriptfile.GetNextLine() << wxT( "\n" );
			}

			if( str.IsNull() == false )
			{
				if( g_MadMacroDlg == NULL )
				{
					g_MadMacroDlg = new MadMacroDlg( this );
				}

				g_MadMacroDlg->SetPyScript( str );
				g_MadMacroDlg->ShowModal();

				if( g_ActiveMadEdit )
				{
					g_ActiveMadEdit->Refresh( false );
				}
			}

			scriptfile.Close();
		}
	}
}

void MadEditFrame::OnToolsStartRecMacro( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		SetMacroRecording();
		m_MadMacroScripts.Empty();
		{
			int caretPos = ( int )g_ActiveMadEdit->GetCaretPosition();
			AddMacroScript( wxString::Format( wxT( "#Restore caret position" ) ) );
			AddMacroScript( wxString::Format( wxT( "SetCaretPosition(%d)" ), caretPos ) );
		}
	}
}

void MadEditFrame::OnToolsStopRecMacro( wxCommandEvent& event )
{
	SetMacroStopped();
}

void MadEditFrame::OnToolsPlayRecMacro( wxCommandEvent& event )
{
	if( g_ActiveMadEdit != NULL )
	{
		size_t total = m_MadMacroScripts.GetCount();
		wxString medit( wxT( "medit." ) ), pyscript;

		if( total > 2 ) // Ignore the restore caret line and the comments
		{
			if( g_SearchReplaceDialog )
			{ g_SearchReplaceDialog->Show( false ); }

			if( g_FindInFilesDialog )
			{ g_FindInFilesDialog->Show( false ); }

			if( g_MadMacroDlg == NULL )
			{
				g_MadMacroDlg = new MadMacroDlg( this );
			}

			wxString endline( wxT( "\r" ) );

			if( g_ActiveMadEdit->GetInsertNewLineType() == nltDOS ) { endline += wxT( "\n" ); }
			else
				if( g_ActiveMadEdit->GetInsertNewLineType() == nltUNIX ) { endline = wxT( "\n" ); }

			pyscript = wxString( wxT( "#Create MadEdit Object for active edit" ) ) + endline + wxT( "medit = MadEdit()" ) + endline + endline;
			pyscript += m_MadMacroScripts[0] + endline;

			for( size_t i = 1; i < total; ++i )
			{ pyscript += ( medit + m_MadMacroScripts[i] + endline ); }

			g_MadMacroDlg->SetPyScript( pyscript );
			g_MadMacroDlg->ShowModal();

			if( g_ActiveMadEdit )
			{
				g_ActiveMadEdit->Refresh( false );
			}
		}
	}
}

void MadEditFrame::OnToolsSaveRecMacro( wxCommandEvent& event )
{
	wxString dir( g_MadEditHomeDir + wxT( "scripts" ) );

	if( !wxDir::Exists( dir ) )
	{
		if( !::wxMkdir( dir ) )
		{
			if( m_RecentFiles->GetCount() )
			{
				wxFileName filename( m_RecentFiles->GetHistoryFile( 0 ) );
				dir = filename.GetPath( wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR );

				if( !wxDir::Exists( dir ) ) { dir = wxGetCwd(); }
			}
			else
			{
				dir = wxGetCwd();
			}
		}
	}

	wxString fileFilter = wxString( wxT( "Mad Macro(*.mpy)|*.mpy|" ) ) + wxFileSelectorDefaultWildcardStr + wxT( "|All files(*;*.*)" );
	wxString filename = wxSaveFileSelector( _( "Mad Macro" ), fileFilter );

	if( !filename.IsEmpty() )
	{
		wxTextFile scriptfile( filename );

		if( scriptfile.Exists() )
		{
			if( wxNO == MadMessageBox( wxString::Format( _( "Do you want to overwrite %s" ), filename.c_str() ), _( "Warning" ), wxICON_WARNING | wxYES_NO ) )
			{ return; }

			scriptfile.Open( wxConvFile );
		}
		else
		{
			scriptfile.Create();
			scriptfile.Open();
		}

		if( scriptfile.IsOpened() )
		{
			scriptfile.Clear();
			size_t total = m_MadMacroScripts.GetCount();
			wxString medit( wxT( "medit." ) );

			if( total )
			{
				scriptfile.AddLine( wxT( "#Create MadEdit Object for active edit" ) );
				scriptfile.AddLine( wxT( "medit = MadEdit()" ) );
				scriptfile.AddLine( wxT( "" ) );
				scriptfile.AddLine( m_MadMacroScripts[0] );
				scriptfile.AddLine( wxT( "" ) );

				for( size_t i = 1; i < total; ++i )
				{ scriptfile.AddLine( medit + m_MadMacroScripts[i] ); }

#ifdef __WXMAC__
				scriptfile.Write( wxTextFileType_Mac );
#else
				scriptfile.Write( wxTextFileType_Unix );
#endif
			}

			wxFileName fn( filename );
			wxString saveDir( fn.GetPath() );

			if( dir == saveDir )
			{
				static wxString hlp_prefix( wxT( "####" ) );
				wxString help, firstLine;
				firstLine = scriptfile.GetFirstLine();

				if( !firstLine.StartsWith( hlp_prefix, &help ) )
				{
					help.Empty();
				}

				if( !g_tbMACRO_ptr->GetOverflowVisible() )
				{
					g_tbMACRO_ptr->SetOverflowVisible( true );
					g_tbMACRO_ptr->Realize();
					m_AuiManager.Update();
				}

				g_Menu_MadMacro_Scripts->Append( menuMadScrip1 + int( g_Menu_MadMacro_Scripts->GetMenuItemCount() ), fn.GetName(), help );
				g_tbMACRO_ptr->AddTool( menuMadScrip1 + int( g_Menu_MadMacro_Scripts->GetMenuItemCount() ), _T( "Macro" ), m_ImageList->GetBitmap( saverec_xpm_idx ), wxNullBitmap, wxITEM_NORMAL, fn.GetName(), help, NULL );
			}

			scriptfile.Close();
		}
	}
}

void MadEditFrame::OnToolsEditMacroFile( wxCommandEvent& event )
{
	wxString dir = g_MadEditHomeDir + wxT( "scripts" );

	if( !wxDir::Exists( dir ) )
	{
		if( m_RecentFiles->GetCount() )
		{
			wxFileName filename( m_RecentFiles->GetHistoryFile( 0 ) );
			dir = filename.GetPath( wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR );

			if( !wxDir::Exists( dir ) ) { dir = wxGetCwd(); }
		}
		else
		{
			dir = wxGetCwd();
		}
	}

	// Hide Modaless Dialog
	HideModalessDialogs();
	static int filterIndex = 0;
	wxString fileFilter = wxString( wxT( "Mad Macro(*.mpy)|*.mpy|" ) ) + wxFileSelectorDefaultWildcardStr + wxT( "|All files(*;*.*)" );
	wxFileDialog dlg( this, _( "Edit Mad Macro File" ), dir, wxEmptyString, fileFilter,
#if wxCHECK_VERSION(2,8,0)
					  wxFD_OPEN | wxFD_FILE_MUST_EXIST );
#else
					  wxOPEN );
#endif
	dlg.SetFilterIndex( filterIndex );

	if( dlg.ShowModal() == wxID_OK )
	{
		wxArrayString filenames;
		g_MB2WC_check_dir_filename = true;
		dlg.GetPaths( filenames );
		g_MB2WC_check_dir_filename = false;
		size_t count = filenames.GetCount();

		for( size_t i = 0; i < count; ++i )
		{
			OpenFile( filenames[i], false );
		}
	}
}


void MadEditFrame::OnToolsMadScriptList( wxCommandEvent& event )
{
	wxString filename = g_MadEditAppDir + wxT( "scripts" ) + wxFILE_SEP_PATH;
	int menuId = event.GetId();
	filename += g_Menu_MadMacro_Scripts->GetLabelText( menuId ) + wxT( ".mpy" );
	wxTextFile scriptfile( filename );
	scriptfile.Open( wxConvFile );

	if( scriptfile.IsOpened() )
	{
		if( !g_EmbeddedPython )
		{
			try
			{
				g_EmbeddedPython = new EmbeddedPython();
			}
			catch( std::bad_alloc & )
			{
				MadMessageBox( _( "Memory allocation failed" ), wxT( "Error" ),  wxOK | wxICON_ERROR );
			}
		}

		if( g_EmbeddedPython )
		{
			wxString str = scriptfile.GetFirstLine() + wxT( "\n" );

			for( ; !scriptfile.Eof(); )
			{
				str << scriptfile.GetNextLine() << wxT( "\n" );
			}

			if( str.IsNull() == false )
			{
				g_EmbeddedPython->exec( std::string( str.mb_str() ) );
			}
		}

		scriptfile.Close();
	}
}

void MadEditFrame::OnToolsToggleBOM( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->ToggleBOM();
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ToggleBOM()" ) ) );
}
void MadEditFrame::OnToolsConvertToDOS( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->ConvertNewLineType( nltDOS );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ConvertNewLineType(MadNewLineType.Dos)" ) ) );
}
void MadEditFrame::OnToolsConvertToMAC( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->ConvertNewLineType( nltMAC );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ConvertNewLineType(MadNewLineType.MAC)" ) ) );
}
void MadEditFrame::OnToolsConvertToUNIX( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->ConvertNewLineType( nltUNIX );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ConvertNewLineType(MadNewLineType.UNIX)" ) ) );
}

void MadEditFrame::OnToolsInsertDOS( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->SetInsertNewLineType( nltDOS );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetInsertNewLineType(MadNewLineType.DOS)" ) ) );
}
void MadEditFrame::OnToolsInsertMAC( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->SetInsertNewLineType( nltMAC );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetInsertNewLineType(MadNewLineType.MAC)" ) ) );
}
void MadEditFrame::OnToolsInsertUNIX( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->SetInsertNewLineType( nltUNIX );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "SetInsertNewLineType(MadNewLineType.UNIX)" ) ) );
}


void MadEditFrame::OnToolsConvertEncoding( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	if( g_ConvEncDialog == NULL ) { g_ConvEncDialog = new MadConvEncDialog( this, -1 ); }

	// Hide Modaless Dialog
	HideModalessDialogs();

	if( g_ConvEncDialog->ShowModal() == wxID_OK )
	{
		g_ActiveMadEdit->ConvertEncoding( g_ConvEncDialog->WxComboBoxEncoding->GetValue(),
										  MadConvertEncodingFlag( g_ConvEncDialog->WxRadioBoxOption->GetSelection() ) );
		RecordAsMadMacro( g_ActiveMadEdit, wxString::Format( wxT( "ConvertEncoding(%s, %d)" ), g_ConvEncDialog->WxComboBoxEncoding->GetValue().c_str(),
						  MadConvertEncodingFlag( g_ConvEncDialog->WxRadioBoxOption->GetSelection() ) ) );
		wxString oldpath = m_Config->GetPath();
		m_Config->SetPath( wxT( "/MadEdit" ) );
		m_Config->Write( wxT( "/MadEdit/ConvertEncoding" ), g_ConvEncDialog->WxComboBoxEncoding->GetValue() );
		m_Config->SetPath( oldpath );
		wxString str = wxString( wxT( '[' ) ) + g_ActiveMadEdit->GetEncodingName() + wxT( "] " ) +
					   wxGetTranslation( g_ActiveMadEdit->GetEncodingDescription().c_str() );
		m_RecentEncodings->AddFileToHistory( str );
		int size;
		g_ActiveMadEdit->GetFont( str, size );
		m_RecentFonts->AddFileToHistory( str );
	}
}

void MadEditFrame::OnToolsSimp2TradChinese( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->ConvertChinese( cefSC2TC );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ConvertChineseA(MadConvertEncodingFlag.SC2TC)" ) ) );
}

void MadEditFrame::OnToolsTrad2SimpChinese( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->ConvertChinese( cefTC2SC );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ConvertChineseA(MadConvertEncodingFlag.TC2SC)" ) ) );
}

void MadEditFrame::OnToolsKanji2TradChinese( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->ConvertChinese( cefJK2TC );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ConvertChineseA(MadConvertEncodingFlag.JK2TC)" ) ) );
}

void MadEditFrame::OnToolsKanji2SimpChinese( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->ConvertChinese( cefJK2SC );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ConvertChineseA(MadConvertEncodingFlag.JK2SC)" ) ) );
}

void MadEditFrame::OnToolsChinese2Kanji( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	g_ActiveMadEdit->ConvertChinese( cefC2JK );
	RecordAsMadMacro( g_ActiveMadEdit, wxString( wxT( "ConvertChineseA(MadConvertEncodingFlag.C2JK)" ) ) );
}

void MadEditFrame::OnToolsSimp2TradClipboard( wxCommandEvent& event )
{
	ConvertChineseInClipboard( ccfSimp2Trad );
	//RecordAsMadMacro(g_ActiveMadEdit, wxString::Format(wxT("ConvertChineseInClipboard(%d)"), ccfSimp2Trad));
}

void MadEditFrame::OnToolsTrad2SimpClipboard( wxCommandEvent& event )
{
	ConvertChineseInClipboard( ccfTrad2Simp );
	//RecordAsMadMacro(g_ActiveMadEdit, wxString::Format(wxT("ConvertChineseInClipboard(%d)"), ccfTrad2Simp));
}

void MadEditFrame::OnToolsKanji2TradClipboard( wxCommandEvent& event )
{
	ConvertChineseInClipboard( ccfKanji2Trad );
	//RecordAsMadMacro(g_ActiveMadEdit, wxString::Format(wxT("ConvertChineseInClipboard(%d)"), ccfKanji2Trad));
}

void MadEditFrame::OnToolsKanji2SimpClipboard( wxCommandEvent& event )
{
	ConvertChineseInClipboard( ccfKanji2Simp );
	//RecordAsMadMacro(g_ActiveMadEdit, wxString::Format(wxT("ConvertChineseInClipboard(%d)"), ccfKanji2Simp));
}

void MadEditFrame::OnToolsChinese2KanjiClipboard( wxCommandEvent& event )
{
	ConvertChineseInClipboard( ccfChinese2Kanji );
	//RecordAsMadMacro(g_ActiveMadEdit, wxString::Format(wxT("ConvertChineseInClipboard(%d)"), ccfChinese2Kanji));
}

void MadEditFrame::OnToolsWordCount( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	// Hide Modaless Dialog
	HideModalessDialogs();
	MadWordCountDialog dialog( this, -1 );
	dialog.ShowModal();
}

void MadEditFrame::OnToolsMarkdown2Html( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	wxString text;
	g_ActiveMadEdit->GetText( text, false );
	std::wstring src = text.ToStdWstring();
	std::wostringstream out;
	markdown::Document doc;
	doc.read( src );
	doc.write( out );
	text = out.str();
	g_ActiveMadEdit->SetText( text );
}

void MadEditFrame::OnToolsHtml2PlainText( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	if( g_MadToolHtmlWin == NULL )
	{
		try
		{
			g_MadToolHtmlWin = new wxHtmlWindow( this, wxID_ANY );
		}
		catch( ... )
		{
			return;
		}
	}

	wxString text;
	g_ActiveMadEdit->GetText( text, false );
	g_MadToolHtmlWin->SetPage( text );
	text = g_MadToolHtmlWin->ToText();
	g_ActiveMadEdit->SetText( text );
}

// Special code to compare strings which doesn't care
// about spaces leading up to the EOL.
static bool BuffersDiffer( const wxString &a, const wxString &b )
{
	const wxChar *aCurrent = a.c_str();
	const wxChar *bCurrent = b.c_str();
	const wxChar * const aEnd = aCurrent + a.Len();
	const wxChar * const bEnd = bCurrent + b.Len();

	while( aCurrent != aEnd && bCurrent != bEnd )
	{
		if( *aCurrent != *bCurrent )
		{
			// Check for varying space at EOL
			while( *aCurrent == ' ' || *aCurrent == '\t' )
			{
				if( ++aCurrent == aEnd )
				{ break; }
			}

			while( *bCurrent == ' ' || *bCurrent == '\t' )
			{
				if( ++bCurrent == bEnd )
				{ break; }
			}

			// Make sure it was at EOL
			if( ( *aCurrent != '\r' && *aCurrent != '\n' ) || ( *bCurrent != '\r' && *bCurrent != '\n' ) )
			{ return true; }
		}

		++aCurrent;
		++bCurrent;
	}

	while( aCurrent != aEnd )
	{
		if( *aCurrent != ' ' && *aCurrent != '\t' )
		{ return true; }

		++aCurrent;
	}

	while( bCurrent != bEnd )
	{
		if( *bCurrent != ' ' && *bCurrent != '\t' )
		{ return true; }

		++bCurrent;
	}

	return false;
}

void MadEditFrame::OnToolsAstyleFormat( wxCommandEvent& event )
{
	if( g_ActiveMadEdit == NULL ) { return; }

	wxString text;
	bool onlySelected = false;
	int leftBracesNumber = 0;

	if( g_ActiveMadEdit->IsSelected() )
	{
		wxString seltext;
		onlySelected = true;
		// Ajust to select the whole line
		leftBracesNumber = g_ActiveMadEdit->GetIndentCountByPos( g_ActiveMadEdit->GetSelectionBeginPos() );
		g_ActiveMadEdit->WholeLineSelection();
		g_ActiveMadEdit->GetSelText( seltext );

		for( int i = 0; i < leftBracesNumber; ++i )
		{
			text.Append( _T( '{' ) );
		}

		text.Append( seltext );
	}
	else
	{
		g_ActiveMadEdit->GetText( text, false );
	}

	wxString eolChars;

	switch( g_ActiveMadEdit->GetNewLineType() )
	{
	case nltDOS:  eolChars = wxT( "\r\n" ); break;

	case nltUNIX: eolChars = wxT( "\n" ); break;

	case nltMAC:  eolChars = wxT( "\r" ); break;

	default: break;
	}

	if( text.size() && text.Last() != _T( '\r' ) && text.Last() != _T( '\n' ) && !onlySelected )
	{
		text += eolChars;
	}

	wxString formattedText;

	if( g_ASFormatter == NULL )
	{
		g_ASFormatter = new astyle::ASFormatter();
	}

	// load settings
	FormatterSettings settings;
	settings.ApplyTo( *g_ASFormatter );
	ASStreamIterator *asi = new ASStreamIterator( g_ActiveMadEdit, text );
	g_ASFormatter->init( asi );
	int lineCounter = 0;

	while( g_ASFormatter->hasMoreLines() )
	{
		formattedText << wxString( g_ASFormatter->nextLine().c_str(), wxCSConv( g_ActiveMadEdit->GetEncodingName() ) );

		if( g_ASFormatter->hasMoreLines() )
		{ formattedText << eolChars; }

		++lineCounter;
	}

	if( onlySelected && leftBracesNumber > 0 )
	{
		while( leftBracesNumber > 0 )
		{
			--leftBracesNumber;
			formattedText = formattedText.SubString( formattedText.Find( _T( '{' ) ) + 1, formattedText.Length() );
		}

		formattedText = formattedText.SubString( formattedText.Find( eolChars ) + eolChars.Length(), formattedText.Length() );
	}

	bool changed = BuffersDiffer( formattedText, text );

	if( changed )
	{
		if( onlySelected )
		{
			g_ActiveMadEdit->ReplaceSelection( formattedText );
		}
		else
		{
			g_ActiveMadEdit->SetText( formattedText );
		}
	}

	delete asi;
}

void MadEditFrame::OnToolsXMLFormat( wxCommandEvent& event )
{
	static wxXmlDocument xmlDoc;

	if( g_ActiveMadEdit == NULL ) { return; }

	wxString text;
	g_ActiveMadEdit->GetText( text, false );

	if( !text.IsEmpty() )
	{
		wxStringInputStream instr( text );
		wxCSConv docConv( g_ActiveMadEdit->GetEncodingName() );
		xmlDoc.Load( instr, g_ActiveMadEdit->GetEncodingName() );

		if( xmlDoc.IsOk() )
		{
			wxConfigBase    *cfg = wxConfigBase::Get( false );
			wxString oldpath = cfg->GetPath();
			cfg->SetPath( wxT( "/xml" ) );
			long indentsize = cfg->ReadLong( wxT( "indentation" ), 4 );
			wxString xmlver( xmlDoc.GetVersion() );

			if( xmlver.IsEmpty() )
			{
				wxString ver( cfg->Read( wxT( "version" ), wxString( wxT( "1.0" ) ) ) );
				xmlDoc.SetVersion( ver );
			}

			wxStringOutputStream outstr( 0, docConv );
			xmlDoc.Save( outstr, ( int )indentsize );
			g_ActiveMadEdit->SetText( outstr.GetString() );
			cfg->SetPath( oldpath );
		}
	}
}

void MadEditFrame::OnWindowToggleWindow( wxCommandEvent& event )
{
	int count = int( m_Notebook->GetPageCount() );

	if( count <= 1 ) { return; }

	int selid = m_Notebook->GetSelection();
	g_CheckModTimeForReload = false;

	if( g_PrevPageID >= 0 &&
			g_PrevPageID <  count &&
			g_PrevPageID != selid )
	{
		m_Notebook->SetSelection( g_PrevPageID );
		g_PrevPageID = selid;
	}
	else
	{
		g_PrevPageID = selid;
		m_Notebook->AdvanceSelection( true );
	}

	MadEdit *madedit = ( MadEdit* )m_Notebook->GetPage( m_Notebook->GetSelection() );

	if( madedit != g_ActiveMadEdit )
	{
		wxAuiNotebookEvent event( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, m_Notebook->GetId() );
		event.SetSelection( m_Notebook->GetSelection() );
		event.SetOldSelection( g_PrevPageID );
		event.SetEventObject( this );
		OnNotebookPageChanged( event );
	}

	g_CheckModTimeForReload = true;
	g_ActiveMadEdit->ReloadByModificationTime();
}

void MadEditFrame::OnWindowPreviousWindow( wxCommandEvent& event )
{
	if( m_Notebook->GetPageCount() <= 1 ) { return; }

	g_PrevPageID = m_Notebook->GetSelection();
	g_CheckModTimeForReload = false;
	m_Notebook->AdvanceSelection( false );
	MadEdit *madedit = ( MadEdit* )m_Notebook->GetPage( m_Notebook->GetSelection() );

	if( madedit != g_ActiveMadEdit )
	{
		wxAuiNotebookEvent event( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, m_Notebook->GetId() );
		event.SetSelection( m_Notebook->GetSelection() );
		event.SetOldSelection( g_PrevPageID );
		event.SetEventObject( this );
		OnNotebookPageChanged( event );
	}

	g_CheckModTimeForReload = true;
	g_ActiveMadEdit->ReloadByModificationTime();
}
void MadEditFrame::OnWindowNextWindow( wxCommandEvent& event )
{
	if( m_Notebook->GetPageCount() <= 1 ) { return; }

	g_PrevPageID = m_Notebook->GetSelection();
	g_CheckModTimeForReload = false;
	m_Notebook->AdvanceSelection( true );
	MadEdit *madedit = ( MadEdit* )m_Notebook->GetPage( m_Notebook->GetSelection() );

	if( madedit != g_ActiveMadEdit )
	{
		wxAuiNotebookEvent event( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, m_Notebook->GetId() );
		event.SetSelection( m_Notebook->GetSelection() );
		event.SetOldSelection( g_PrevPageID );
		event.SetEventObject( this );
		OnNotebookPageChanged( event );
	}

	g_CheckModTimeForReload = true;
	g_ActiveMadEdit->ReloadByModificationTime();
}

void MadEditFrame::OnHelpAbout( wxCommandEvent& event )
{
	MadAboutDialog dlg( this );
	dlg.WxMemoAbout->AppendText( g_MadEdit_Version + wxT( "\n" ) +
							 g_MadEditMod_URL + wxT( "\n\n" ) +
							 _( "Download dictionary at\nhttp://extensions.openoffice.org/" ) + wxT( "\n\n" ) +
							 _( "Press OK to visit our HomePage." ) );
	dlg.WxMemoLicense->AppendText( g_MadEditModLicense );
	dlg.WxMemoCredits->AppendText( g_MadEditModCredits );
	// Hide Modaless Dialog
	HideModalessDialogs();

	if( dlg.ShowModal() == wxID_OK )
	{
#ifdef __WXGTK__
			const wxChar *browsers[]=
			{
				wxT("/usr/bin/firefox"),
				wxT("/usr/bin/mozilla"),
				wxT("/usr/bin/chromium"),
				wxT("/usr/bin/konqueror"),
# if defined(__APPLE__) && defined(__MACH__)
				wxT("/usr/bin/open"),
# endif
				wxT("/usr/kde/3.5/bin/konqueror"),
				wxT("/usr/kde/3.4/bin/konqueror"),
				wxT("/usr/kde/3.3/bin/konqueror"),
				wxT("/usr/kde/3.2/bin/konqueror"),
			};

		int idx = 0;
		int count = sizeof( browsers ) / sizeof( browsers[0] );

		do
		{
			if( wxFileExists( wxString( browsers[idx] ) ) )
			{ break; }
		}
		while( ++idx < count );

		if( idx < count )
		{
			wxExecute( wxString( browsers[idx] ) + wxT( ' ' ) + g_MadEditMod_URL );
		}
		else
		{
			wxLaunchDefaultBrowser( g_MadEditMod_URL );
		}

#else
		wxLaunchDefaultBrowser( g_MadEditMod_URL );
#endif
	}
}

void MadEditFrame::OnCopyCurrResult( wxCommandEvent& event )
{
	//wxTreeItemId id = m_FindInFilesResults->GetFocusedItem();
	wxTreeItemId id = m_FindInFilesResults->GetSelection();

	if( id.IsOk() && g_ActiveMadEdit )
	{
		wxString result = m_FindInFilesResults->GetItemText( id );
		g_ActiveMadEdit->CopyToClipboard( result );
	}
}

void MadEditFrame::OnCopyAllResults( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		wxTreeItemId RootId = m_FindInFilesResults->GetRootItem();
		wxString result( wxT( "" ) );

		if( RootId.IsOk() )
		{
			wxTreeItemIdValue cookie;
			wxTreeItemId id = m_FindInFilesResults->GetFirstChild( m_FindInFilesResults->GetRootItem(), cookie );

			while( id.IsOk() )
			{
				result += m_FindInFilesResults->GetItemText( id );
				wxTreeItemIdValue tmpCookie;
				wxTreeItemId tmpId = m_FindInFilesResults->GetFirstChild( id, tmpCookie );

				while( tmpId.IsOk() )
				{
					result += wxString( wxT( "\n	" ) ) + m_FindInFilesResults->GetItemText( tmpId );
					tmpId = m_FindInFilesResults->GetNextChild( id, tmpCookie );
				}

				id = m_FindInFilesResults->GetNextChild( m_FindInFilesResults->GetRootItem(), cookie );
				result += wxT( "\n" );
			}
		}

		if( result != wxString( wxT( "" ) ) )
		{ g_ActiveMadEdit->CopyToClipboard( result ); }
	}
}

void MadEditFrame::OnResetCurrResult( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		g_MainFrame->ResetFindInFilesResults();
		g_StatusBar->SetStatusText( wxEmptyString, 0 );
	}
}

void MadEditFrame::PurgeRecentFiles()
{
	int n = ( int ) m_RecentFiles->GetCount();

	for( int i = n - 1; i >= 0; --i )
	{ m_RecentFiles->RemoveFileFromHistory( ( size_t )i ); }
}

void MadEditFrame::PurgeRecentFonts()
{
	int n = ( int ) m_RecentFonts->GetCount();

	for( int i = n - 1; i >= 1; --i )
	{ m_RecentFonts->RemoveFileFromHistory( ( size_t )i ); }
}

void MadEditFrame::PurgeRecentEncodings()
{
	int n = ( int ) m_RecentEncodings->GetCount();

	for( int i = n - 1; i >= 1; --i )
	{ m_RecentEncodings->RemoveFileFromHistory( ( size_t )i ); }
}

void MadEditFrame::OnRightClickToolBar( wxAuiToolBarEvent& event )
{
	wxContextMenuEvent ctEvt( wxEVT_AUITOOLBAR_RIGHT_CLICK, event.GetId(), event.GetClickPoint() );
	g_MainFrame->OnContextMenu( ctEvt );
}

void MadEditFrame::OnContextMenu( wxContextMenuEvent& event )
{
#if wxUSE_MENUS

	if( g_Menu_FrameContext == NULL )
	{
		g_Menu_FrameContext = new wxMenu( ( long )0 );
		g_Menu_FrameContext->AppendCheckItem( menuToolBarsToggleAll, _( "Toggle Main Toolbar" ) );
		g_Menu_FrameContext->AppendSeparator();

		for( int i = tbSTANDARD; i < tbMAX; ++i )
		{
			g_Menu_FrameContext->AppendCheckItem( menuToolBar1 + i, g_ToolbarNames[i] );
		}
	}

	for( int i = tbSTANDARD; i < tbMAX; ++i )
	{
		int menuId = menuToolBar1 + i;

		if( m_ToolbarStatus[tbMAX] )
		{
			if( !g_Menu_FrameContext->IsEnabled( menuId ) )
			{ g_Menu_FrameContext->Enable( menuId, true ); }

			if( m_ToolbarStatus[i] )
			{
				if( !m_AuiManager.GetPane( WxToolBar[i] ).IsShown() )
				{
					m_ToolbarStatus[i] = false;
				}

				g_Menu_FrameContext->Check( menuId, m_ToolbarStatus[i] );
			}
			else
			{
				g_Menu_FrameContext->Check( menuId, false );
			}
		}
		else
		{
			g_Menu_FrameContext->Enable( menuId, false );
		}
	}

	PopupMenu( g_Menu_FrameContext );
#endif // wxUSE_MENUS
}

void MadEditFrame::HideQuickFindBar()
{
	m_AuiManager.GetPane( m_QuickSeachBar ).Hide();
	m_AuiManager.Update();
	m_ToolbarStatus[tbQSEARCH] = false;
	int i = tbSTANDARD;

	for( ; i < tbMAX; ++i )
	{
		if( m_ToolbarStatus[i] )
		{
			m_ToolbarStatus[tbMAX] = true;
			break;
		}
	}

	if( i == tbMAX )
	{ m_ToolbarStatus[tbMAX] = false; }
}

void MadEditFrame::OnShowSearchQuickFindBar( wxCommandEvent& event )
{
	if( !m_AuiManager.GetPane( m_QuickSeachBar ).IsShown() )
	{
		m_AuiManager.GetPane( m_QuickSeachBar ).Show();
		m_ToolbarStatus[tbQSEARCH] = true;
		m_ToolbarStatus[tbMAX] = true;
		m_AuiManager.Update();
	}

	m_QuickSearch->SetFocus();
}

void MadEditFrame::OnSearchQuickFind( wxCommandEvent& event )
{
	if( g_ActiveMadEdit )
	{
		if( m_SearchDirectionNext )
		{ OnSearchQuickFindNext( event ); }
		else
		{ OnSearchQuickFindPrevious( event ); }
	}
}

void MadEditFrame::OnSearchQuickFindPrevious( wxCommandEvent& event )
{
	m_SearchDirectionNext = false;

	if( m_QuickSearch && g_ActiveMadEdit )
	{
		if( m_QuickSearch->GetValue().IsEmpty() )
		{
			return;
		}

		if( event.GetEventType() == wxEVT_TEXT_ENTER )
		{
			if( wxNOT_FOUND == m_QuickSearch->FindString( m_QuickSearch->GetValue(), true ) )
			{
				m_QuickSearch->Insert( m_QuickSearch->GetValue(), 0 );
				g_RecentFindText->AddFileToHistory( m_QuickSearch->GetValue() );
			}
		}

		MadSearchResult sr;
		static bool reset_caretpos = false;
		static wxFileOffset lastCaret = 0;
		wxFileOffset rangeFrom = g_ActiveMadEdit->GetCaretPosition(), rangeTo = -1;

		if( event.GetEventType() == wxEVT_TEXT && g_ActiveMadEdit->IsSelected() )
		{
			rangeFrom = g_ActiveMadEdit->GetSelectionEndPos() + 1;
		}

		if( ( reset_caretpos && rangeFrom <= lastCaret ) && !g_ActiveMadEdit->IsModified() )
		{
			rangeFrom = g_ActiveMadEdit->GetFileSize();
			g_StatusBar->SetStatusText( wxT( "" ), 0 );
			reset_caretpos = false;
		}

		sr = g_ActiveMadEdit->FindTextPrevious( m_QuickSearch->GetValue(), m_CheckboxRegEx->GetValue(),
												m_CheckboxCaseSensitive->GetValue(), m_CheckboxWholeWord->GetValue(), rangeFrom, rangeTo );

		if( sr == SR_NO )
		{
			reset_caretpos = true;
			g_StatusBar->SetStatusText( _( "Passed the begin of the file" ), 0 );
			lastCaret = g_ActiveMadEdit->GetFileSize();
		}
		else
		{
			lastCaret = 0;
			//g_ActiveMadEdit->HighlightWords();
		}
	}
}

void MadEditFrame::OnSearchQuickFindNext( wxCommandEvent& event )
{
	m_SearchDirectionNext = true;

	if( m_QuickSearch && g_ActiveMadEdit )
	{
		if( m_QuickSearch->GetValue().IsEmpty() )
		{
			return;
		}

		if( event.GetEventType() == wxEVT_TEXT_ENTER )
		{
			if( wxNOT_FOUND == m_QuickSearch->FindString( m_QuickSearch->GetValue(), true ) )
			{
				m_QuickSearch->Insert( m_QuickSearch->GetValue(), 0 );
				g_RecentFindText->AddFileToHistory( m_QuickSearch->GetValue() );
			}
		}

		MadSearchResult sr;
		static bool reset_caretpos = false;
		static wxFileOffset lastCaret = 0;
		wxFileOffset rangeFrom = g_ActiveMadEdit->GetCaretPosition(), rangeTo = -1;

		if( event.GetEventType() == wxEVT_TEXT && g_ActiveMadEdit->IsSelected() )
		{
			rangeFrom = g_ActiveMadEdit->GetSelectionBeginPos();
		}

		if( ( reset_caretpos && rangeFrom >= lastCaret ) && !g_ActiveMadEdit->IsModified() )
		{
			rangeFrom = 0;
			g_StatusBar->SetStatusText( wxT( "" ), 0 );
			reset_caretpos = false;
		}

		sr = g_ActiveMadEdit->FindTextNext( m_QuickSearch->GetValue(), m_CheckboxRegEx->GetValue(),
											m_CheckboxCaseSensitive->GetValue(), m_CheckboxWholeWord->GetValue(), rangeFrom, rangeTo );

		if( sr == SR_NO )
		{
			reset_caretpos = true;
			g_StatusBar->SetStatusText( _( "Passed the end of the file" ), 0 );
			lastCaret = rangeFrom;
		}
		else
		{
			lastCaret = g_ActiveMadEdit->GetFileSize();
			//g_ActiveMadEdit->HighlightWords();
		}
	}
}

#if USE_GENERIC_TREECTRL
	BEGIN_EVENT_TABLE( MadTreeCtrl, wxGenericTreeCtrl )
#else
		BEGIN_EVENT_TABLE( MadTreeCtrl, wxTreeCtrl )
#endif
	// EVT_TREE_ITEM_MENU is the preferred event for creating context menus
	// on a tree control, because it includes the point of the click or item,
	// meaning that no additional placement calculations are required.
	EVT_TREE_ITEM_MENU( MadEditFrame::ID_FINDINFILESRESULTS, MadTreeCtrl::OnItemMenu )
END_EVENT_TABLE()

MadTreeCtrl::MadTreeCtrl( wxWindow *parent, const wxWindowID id,
						  const wxPoint& pos, const wxSize& size,
						  long style )
	: wxTreeCtrl( parent, id, pos, size, style )
{
}

void MadTreeCtrl::OnItemMenu( wxTreeEvent& event )
{
	wxTreeItemId itemId = event.GetItem();
	wxCHECK_RET( itemId.IsOk(), _( "Invalid item" ) );
	wxPoint clientpt = event.GetPoint();
	ShowMenu( itemId, clientpt );
}

void MadTreeCtrl::ShowMenu( wxTreeItemId id, const wxPoint& pt )
{
#if wxUSE_MENUS
	static wxMenu menu( ( long )0 );
	static bool needInit = true;

	if( needInit )
	{
		menu.Append( menuCopyCurResult, _( "&Copy Selected" ) );
		menu.Append( menuCopyAllResults, _( "Copy &All" ) );
		menu.Append( menuResetCurResult, _( "&Reset Results" ) );
		needInit = false;
	}

	PopupMenu( &menu, pt );
#endif // wxUSE_MENUS
}

