///////////////////////////////////////////////////////////////////////////////
// vim:         ts=4 sw=4
// Name:        MadRecentlist.cpp
// Description: Porting Recent List from wxMEdit
// Author:      
// Licence:     GPL
///////////////////////////////////////////////////////////////////////////////

#include "MadRecentList.h"
#include <wx/menu.h>
#include <boost/locale/conversion.hpp>

// Ugly global
//extern char * ConvWC2MB(const wxString&);
bool MadRecentList::ItemEQ(const wxString& item1, const wxString& item2)
{
    if (m_caseSensitive)
        return item1 == item2;
    
    //std::string str1(ConvWC2MB(item1));
    //std::string str2(ConvWC2MB(item2));

    return (item1.Lower() == item2.Lower());
}

static const wxChar *s_MRUEntryFormat = wxT("&%d %s");

static inline wxChar* MYcopystring(const wxString& s)
{
    wxChar* copy = new wxChar[s.length() + 1];
    return wxStrcpy(copy, s.c_str());
}

// Recent List management
void MadRecentList::AddFileToHistory(const wxString& item)
{
    size_t i;

    // Check we don't already have this item
    for (i = 0; i < m_fileHistoryN; ++i)
    {
        if ( m_fileHistory[i] && ItemEQ(item, m_fileHistory[i]) )
        {
            // we do have it, move it to the top of the history
            RemoveFileFromHistory (i);
            AddFileToHistory (item);
            return;
        }
    }

    // if we already have a full history, delete the one at the end
    if ( m_fileMaxFiles == m_fileHistoryN )
    {
        RemoveFileFromHistory (m_fileHistoryN - 1);
        AddFileToHistory (item);
        return;
    }

    // Add to the project item history:
    // Move existing items (if any) down so we can insert item at beginning.
    if (m_fileHistoryN < m_fileMaxFiles)
    {
        wxList::compatibility_iterator node = m_fileMenus.GetFirst();
        while (node)
        {
            wxMenu* menu = (wxMenu*) node->GetData();
            if ( m_fileHistoryN == 0 && menu->GetMenuItemCount() )
            {
                menu->AppendSeparator();
            }
            menu->Append(GetBaseId()+m_fileHistoryN, _("[EMPTY]"));
            node = node->GetNext();
        }
        ++m_fileHistoryN;
    }
    // Shuffle items down
    for (i = (m_fileHistoryN-1); i > 0; --i)
    {
        m_fileHistory[i] = m_fileHistory[i-1];
    }
    m_fileHistory[0] = MYcopystring(item);

    for (i = 0; i < m_fileHistoryN; ++i)
    {
        if ( m_fileHistory[i] )
        {
            wxString itemInMenu = m_fileHistory[i];

            // we need to quote '&' characters which are used for mnemonics
            itemInMenu.Replace(_T("&"), _T("&&"));
            wxString buf;
            buf.Printf(s_MRUEntryFormat, i + 1, itemInMenu.c_str());
            wxList::compatibility_iterator node = m_fileMenus.GetFirst();
            while (node)
            {
                wxMenu* menu = (wxMenu*) node->GetData();
                menu->SetLabel(GetBaseId() + i, buf);
                node = node->GetNext();
            }
        }
    }
}


