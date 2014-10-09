///////////////////////////////////////////////////////////////////////////////
// vim:         ts=4 sw=4
// Name:        MadRecentList.h
// Description: Porting Recent List from wxMedit
// Author:      
// Licence:     GPL
///////////////////////////////////////////////////////////////////////////////

#ifndef _MAD_RECENT_LIST_H_
#define _MAD_RECENT_LIST_H_

#include <wx/docview.h>

class MadRecentList: public wxFileHistory
{
public:
    static inline bool OSCaseSensitive()
    {
#ifdef __WXMSW__
        return false;
#else
        return true;
#endif
    }

    MadRecentList(bool caseSensitive=OSCaseSensitive(), size_t maxFiles = 9, wxWindowID idBase = wxID_FILE1)
        : wxFileHistory(maxFiles, idBase), m_caseSensitive(caseSensitive)
    {}

    virtual void AddFileToHistory(const wxString& file);
private:
    bool ItemEQ(const wxString& item1, const wxString& item2);

    bool m_caseSensitive;
};

#endif //_MAD_RECENT_LIST_H_

