#include <wx/wxprec.h>
#ifdef __BORLANDC__
        #pragma hdrstop
#endif
#ifndef WX_PRECOMP
        #include <wx/wx.h>
#endif

wxString g_MadEdit_Version( wxString(wxT("MadEdit-Mod 0.3.8 "))
#if defined(__WXMSW__)
#ifdef _WIN64
+ wxT("win64")
#else
+ wxT("win32")
#endif
#if _MSC_VER == 1400
+ wxT(" Visual Studio 2005")
#elif _MSC_VER == 1500
+ wxT(" Visual Studio 2008")
#elif _MSC_VER == 1600
+ wxT(" Visual Studio 2010")
#elif _MSC_VER == 1700
+ wxT(" Visual Studio 2012")
#elif _MSC_VER == 1800
+ wxT(" Visual Studio 2013")
#elif (_MSC_VER = 1900)
+ wxT(" Visual Studio 2015")
#else
#ifdef __GNUC__
+ wxT(" GCC ") + wxT(__VERSION__)
#else
+ wxT(" Unknown Compiler")
#endif
#endif
#elif defined(__WXMAC__)
+ wxT("MacOS")
#ifdef __GNUC__
    + wxT(" GCC ") + wxT(__VERSION__)
#else
    + wxT(" Unknown Compiler")
#endif
#else //Linux
#if defined(__x86_64__) || defined(__LP64__)
+ wxT("x86_x64")
#else
+ wxT("i686")
#endif
#ifdef __GNUC__
+ wxT(" GCC ") + wxT(__VERSION__)
#else
+ wxT(" Unknown Compiler")
#endif
#endif
+ wxT(" build ") + wxT(__TIME__) + wxT(" ") + wxT(__DATE__));

