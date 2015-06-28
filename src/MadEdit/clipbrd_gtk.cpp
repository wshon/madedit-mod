#ifdef __WXGTK__
#if wxMAJOR_VERSION >= 3
#include "clipbrd_gtk_wx3.cpp"
#else
#include "clipbrd_gtk_wx2.cpp"
#endif
#endif // __WXGTK__
