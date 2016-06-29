#include "MadTranslationHelper.h"
#include <wx/dir.h>
#include <wx/config.h>
#include <wx/fileconf.h>
#include <wx/filename.h>

extern wxString g_MadEditAppDir, g_MadEditHomeDir;

MadTranslationHelper::MadTranslationHelper(wxString& trans_name, 
										 const wxString & search_path,
										 bool use_native_config)
: m_TransName(trans_name), m_SearchPath(search_path), 
m_ConfigPath(wxEmptyString), m_Locale(NULL), m_UseNativeConfig(use_native_config)
{
	wxASSERT(!search_path.IsEmpty());
	if(m_SearchPath.IsEmpty())
	{
		m_SearchPath = g_MadEditHomeDir+wxT("locale/");
	}
}

MadTranslationHelper::~MadTranslationHelper()
{
	Save();
	if(m_Locale)
	{
		wxDELETE(m_Locale);
	}
}

wxLocale * MadTranslationHelper::GetLocale()
{
	return m_Locale;
}

const wxString & MadTranslationHelper::GetSearchPath()
{
	return m_SearchPath;
}

void MadTranslationHelper::SetSearchPath(wxString & value)
{
	m_SearchPath = value;
	wxASSERT(!m_SearchPath.IsEmpty());
	if(m_SearchPath.IsEmpty())
	{
		m_SearchPath = g_MadEditHomeDir+wxT("locale/");
	}
}

const wxString & MadTranslationHelper::GetConfigPath()
{
	return m_ConfigPath;
}

void MadTranslationHelper::SetConfigPath(wxString & value)
{
	m_ConfigPath = value;
}

bool MadTranslationHelper::Load()
{
#if 0
	wxConfigBase * config = wxConfigBase::Get(false);
	
	wxString strlang;
	cfg->Read(wxT("/MadEdit/Language"), &strlang);
	wxArrayString names;
	wxArrayLong identifiers;
	GetInstalledLanguages(names, identifiers);
	for(size_t i = 0; i < identifiers.Count(); i++)
	{
		if(identifiers[i] == language)
		{
			if(m_Locale) wxDELETE(m_Locale);
			m_Locale = new wxLocale;
			m_Locale->Init(identifiers[i]);
			m_Locale->AddCatalogLookupPathPrefix(m_SearchPath);
			m_Locale->AddCatalog(m_TransName);
			return true;
		}
	}
	#endif
	return false;
}

void MadTranslationHelper::Save(bool bReset)
{
#if 0
	wxConfigBase * config = wxConfigBase::Get(false);

	long language = wxLANGUAGE_DEFAULT;
	if(!bReset)
	{
		if(m_Locale)
		{
			language = m_Locale->GetLanguage();
		}
	}	
	config->DeleteEntry(wxT("wxTranslation"));
	config->SetPath(wxT("wxTranslation"));
	config->Write(wxT("wxTranslationLanguage"), m_Locale->GetLanguageName(language) );
	config->Flush();
	delete config;
#endif
}

 wxDirTraverseResult MadTranslationHelper::OnDir(const wxString& dirname)
{
	const wxLanguageInfo * langinfo;
	langinfo = wxLocale::FindLanguageInfo(dirname.AfterLast(wxFileName::GetPathSeparator()));
	if(langinfo != NULL)
	{
		wxLogTrace(wxTraceMask(), _("SEARCHING FOR %s"),
			wxString(dirname+wxFileName::GetPathSeparator()+
			m_TransName+wxT(".mo")).GetData());
		if(wxFileExists(dirname+wxFileName::GetPathSeparator()+
			m_TransName+wxT(".mo")))
		{
			m_Names.Add(langinfo->Description);
			m_Identifiers.Add(langinfo->Language);
		}
	}
	return wxDIR_CONTINUE;
}


void MadTranslationHelper::GetInstalledLanguages(wxArrayString & names, 
												wxArrayLong & identifiers)
{
	wxString filename;	
	m_Names.Clear();
	m_Identifiers.Clear();	
	wxString name = wxLocale::GetLanguageName(wxLANGUAGE_DEFAULT);
	if(!name.IsEmpty())
	{
		names.Add(_("Default"));
		identifiers.Add(wxLANGUAGE_DEFAULT);		
	}
	if(!wxDir::Exists(m_SearchPath)) 
	{
		wxLogTrace(wxTraceMask(), _("Directory %s DOES NOT EXIST !!!"),
			m_SearchPath.GetData());
		return;
	}
	wxDir dir(m_SearchPath);
	int flags=wxDIR_DIRS;
	dir.Traverse(*this, wxEmptyString, flags);
	identifiers = m_Identifiers;
	names = m_Names;
}

bool MadTranslationHelper::AskUserForLanguage(wxArrayString & names, 
											 wxArrayLong & identifiers)
{
	wxCHECK_MSG(names.Count() == identifiers.Count(), false, 
		_("Array of language names and identifiers should have the same size."));
	long index = wxGetSingleChoiceIndex(_("Select the language"), 
			_("Language"), names);
	if(index != -1)
	{
		if(m_Locale)
		{
			wxDELETE(m_Locale);
		}
		m_Locale = new wxLocale;
		m_Locale->Init(identifiers[index]);
		m_Locale->AddCatalogLookupPathPrefix(m_SearchPath);
		wxLogTrace(wxTraceMask(), 
			_("MadTranslationHelper: Path Prefix = \"%s\""), 
			m_SearchPath.GetData());
		m_Locale->AddCatalog(m_TransName);
		wxLogTrace(wxTraceMask(), 
			_("MadTranslationHelper: Catalog Name = \"%s\""), 
			m_TransName.GetData());
		return true;
	}
	return false;
}
