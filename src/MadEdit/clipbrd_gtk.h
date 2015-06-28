#ifdef __WXGTK__
#include <wx/verstion.h>
#if wxMAJOR_VERSION >= 3
#include "clipbrd_gtk_wx3.h"
#else
#include "clipbrd_gtk_wx2.h"
#endif
#endif // __WXGTK__
