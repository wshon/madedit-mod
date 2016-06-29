#ifndef _MAD_TRANSLATION_HELPER_H
#define _MAD_TRANSLATION_HELPER_H

#include <wx/wx.h>
#include <wx/intl.h>
#include <wx/dir.h>

class MadTranslationHelper : public wxDirTraverser
{
	wxString m_TransName;
	wxString m_SearchPath;
	wxString m_ConfigPath;
	wxLocale * m_Locale;
	bool m_UseNativeConfig;
	wxArrayLong m_Identifiers;
	wxArrayString m_Names;
public:
	MadTranslationHelper(wxString& trans_name, const wxString & search_path, bool use_native_config = true);
	~MadTranslationHelper();
	wxLocale * GetLocale();
	void GetInstalledLanguages(wxArrayString & names, wxArrayLong & identifiers);
	bool AskUserForLanguage(wxArrayString & names, wxArrayLong & identifiers);
	bool Load();
	void Save(bool bReset = false);

	const wxString & GetSearchPath();
	void SetSearchPath(wxString & value);

	const wxString & GetConfigPath();
	void SetConfigPath(wxString &);
	virtual wxDirTraverseResult OnFile(const wxString& WXUNUSED(filename))
    {
         return wxDIR_CONTINUE;
    }
    virtual wxDirTraverseResult OnDir(const wxString& dirname);
};

#endif
