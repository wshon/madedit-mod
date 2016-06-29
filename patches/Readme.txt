1. Fix wrong tap order of AUINoteBook http://trac.wxwidgets.org/attachment/ticket/10848/

2. The problem in MadEdit-0.2.9 (Win32 only):
    Use MadEdit open two new files, NoName1 and NoName2, the focus is on NoName2 now.
    Select [Convert File Encoding...] in Tools menu, and press OK to close the dialog.
    Then switch to NoName1, and reopen the [Convert File Encoding...] dialog.
    After pressing OK the focus will jump to NoName2, cannot convert the encoding of NoName1.


To fix it (if you want to rebuild MadEdit from source):
    The bug is in wxWidgets-2.8\src\msw\dialog.cpp (wxDialog::ShowModal()),
    add the code to line 306:

    m_oldFocus = FindFocus();

    now re-compile wxWidgets lib and link it with MadEdit.


The patch file:

Index: dialog.cpp
===================================================================
--- dialog.cpp	(revision 58854)
+++ dialog.cpp	(working copy)
@@ -303,6 +303,7 @@
 {
     wxASSERT_MSG( !IsModal(), _T("wxDialog::ShowModal() reentered?") );
 
+    m_oldFocus = FindFocus();
     m_endModalCalled = false;
 
     Show();


diff -r d:\wxWidgets-3.0.2-org\src\generic\scrlwing.cpp d:\wxWidgets-3.0.2\src\generic\scrlwing.cpp
282c282
<     else if ( evType == wxEVT_MOUSEWHEEL )
---
>     else if ((!processed) && evType == wxEVT_MOUSEWHEEL )

4.Fix selection not changed in inner-tab drag/reposition