#include <python.h>

#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>
#include <boost/function.hpp>

#include <iostream>
#include <string>
#include <memory>

#include "MadEditFrame.h"
#include "MadEdit/MadEdit.h"

extern MadEdit *g_ActiveMadEdit;

namespace mad_py = ::boost::python;
#define UNFINISH
namespace mad_python
{
    class PyMadEdit
    {
        public:
            void GoToLine(int line)
            {
                if(line > 0)
                    g_ActiveMadEdit->GoToLine(line);
            }
            
            void SetSyntax(const wxString &title)
            {
                g_ActiveMadEdit->SetSyntax(title);
            }
            MadSyntax* GetSyntax()
            {
                return g_ActiveMadEdit->GetSyntax();
            }
            wxString GetSyntaxTitle()
            {
                return g_ActiveMadEdit->GetSyntaxTitle();
            }
            void ApplySyntaxAttributes(MadSyntax *syn, bool matchTitle)
            {
                g_ActiveMadEdit->ApplySyntaxAttributes(syn, matchTitle);
            }
            void LoadDefaultSyntaxScheme()
            {
                g_ActiveMadEdit->LoadDefaultSyntaxScheme();
            }
            void SetEncoding(const wxString &encname)
            {
                g_ActiveMadEdit->SetEncoding(encname);
            }
            wxString GetEncodingName()
            {
                return g_ActiveMadEdit->GetEncodingName();
            }
            wxString GetEncodingDescription()
            {
                return g_ActiveMadEdit->GetEncodingDescription();
            }
            MadEncodingType GetEncodingType()
            {
                return g_ActiveMadEdit->GetEncodingType();
            }
            bool GetRecordCaretMovements()
            {
                return g_ActiveMadEdit->GetRecordCaretMovements();
            }
            void SetRecordCaretMovements(bool value)
            {
                g_ActiveMadEdit->SetRecordCaretMovements(value);
            }

            void SetTextFont(const wxString &name, int size, bool forceReset)
            {
                g_ActiveMadEdit->SetTextFont(name, size, forceReset);
            }
            void SetHexFont(const wxString &name, int size, bool forceReset)
            {
                g_ActiveMadEdit->SetHexFont(name, size, forceReset);
            }

            mad_py::tuple GetTextFont(wxString &name, int &size)
            {
                wxString name;
                int size = 0;
                g_ActiveMadEdit->GetTextFont(name, size);
            }
            mad_py::tuple GetHexFont(wxString &name, int &size)
            {
                wxString name;
                int size = 0;
                g_ActiveMadEdit->GetHexFont(name, size);
                return mad_py::make_tuple(name, size);
            }

            wxFont GetFont()
            {
                return g_ActiveMadEdit->GetFont();
            }

            mad_py::tuple GetFontNameSize()
            {
                wxString name;
                int size = 0;
                g_ActiveMadEdit->GetFont(name, size);
                return mad_py::make_tuple(name, size);
            }
            void SetFontA(const wxString &name, int size)
            {
                g_ActiveMadEdit->SetFont(name, size);
            }

            bool SetFontB(const wxFont& font)
            {
                return g_ActiveMadEdit->SetFont(font);
            }

            void SetFixedWidthMode(bool mode)
            {
                g_ActiveMadEdit->SetFixedWidthMode(mode);
            }
            bool GetFixedWidthMode()
            {
                return g_ActiveMadEdit->GetFixedWidthMode();
            }

            void SetLineSpacing(int percent)
            {
                g_ActiveMadEdit->SetLineSpacing(percent);
            }
            long GetLineSpacing()
            {
                return g_ActiveMadEdit->GetLineSpacing();
            }

            void SetEditMode(MadEditMode mode)
            {
                g_ActiveMadEdit->SetEditMode(mode);
            }

            MadEditMode GetEditMode()
            {
                return g_ActiveMadEdit->GetEditMode();
            }

            void SetSingleLineMode(bool mode)
            {
                g_ActiveMadEdit->SetSingleLineMode(mode);
            }

            void SetTabColumns(long value)
            {
                g_ActiveMadEdit->SetTabColumns(value);
            }
            long GetTabColumns()
            {
                return g_ActiveMadEdit->GetTabColumns();
            }

            void SetIndentColumns(long value)
            {
                g_ActiveMadEdit->SetIndentColumns(value);
            }
            long GetIndentColumns()
            {
                return g_ActiveMadEdit->GetIndentColumns();
            }

            void SetInsertSpacesInsteadOfTab(bool value)
            {
                g_ActiveMadEdit->SetInsertSpacesInsteadOfTab(value);
            }
            bool GetInsertSpacesInsteadOfTab()
            {
                return g_ActiveMadEdit->GetInsertSpacesInsteadOfTab();
            }
            void SetWantTab(bool value)
            {
                g_ActiveMadEdit->SetWantTab(value);
            }
            bool GetWantTab()
            {
                return g_ActiveMadEdit->GetWantTab();
            }

            void SetWordWrapMode(MadWordWrapMode mode)
            {
                g_ActiveMadEdit->SetWordWrapMode(mode);
            }
            MadWordWrapMode GetWordWrapMode()
            {
                return g_ActiveMadEdit->GetWordWrapMode();
            }

            void SetDisplayLineNumber(bool value)
            {
                g_ActiveMadEdit->SetDisplayLineNumber(value);
            }
            void SetShowEndOfLine(bool value)
            {
                g_ActiveMadEdit->SetShowEndOfLine(value);
            }
            void SetShowTabChar(bool value)
            {
                g_ActiveMadEdit->SetShowTabChar(value);
            }
            void SetShowSpaceChar(bool value)
            {
                g_ActiveMadEdit->SetShowSpaceChar(value);
            }
            void SetMarkActiveLine(bool value)
            {
                g_ActiveMadEdit->SetMarkActiveLine(value);
            }

            bool GetDisplayLineNumber()
            {
                return g_ActiveMadEdit->GetDisplayLineNumber();
            }
            bool GetShowEndOfLine()
            {
                return g_ActiveMadEdit->GetShowEndOfLine();
            }
            bool GetShowTabChar()
            {
                return g_ActiveMadEdit->GetShowTabChar();
            }
            bool GetShowSpaceChar()
            {
                return g_ActiveMadEdit->GetShowSpaceChar();
            }
            bool GetMarkActiveLine()
            {
                return g_ActiveMadEdit->GetMarkActiveLine();
            }

            void SetMarkBracePair(bool value)
            {
                g_ActiveMadEdit->SetMarkBracePair(value);
            }
            bool GetMarkBracePair()
            {
                return g_ActiveMadEdit->GetMarkBracePair();
            }

            long GetMaxColumns()
            {
                return g_ActiveMadEdit->GetMaxColumns();
            }
            void SetMaxColumns(long cols)
            {
                g_ActiveMadEdit->SetMaxColumns(cols);
            }

            bool GetAutoIndent()
            {
                return g_ActiveMadEdit->GetAutoIndent();
            }
            void SetAutoIndent(bool value)
            {
                g_ActiveMadEdit->SetAutoIndent(value);
            }

            void SetAutoCompletePair(bool value)
            {
                g_ActiveMadEdit->SetAutoCompletePair(value);
            }
            bool GetAutoCompletePair()
            {
                return g_ActiveMadEdit->GetAutoCompletePair();
            }

            void SetInsertMode(bool mode)  // true: insert, false: overwrite
            {
                g_ActiveMadEdit->SetInsertMode(mode);
            }
            bool GetInsertMode()
            {
                return g_ActiveMadEdit->GetInsertMode();
            }

            void SetCaretType(MadCaretType type)
            {
                g_ActiveMadEdit->SetCaretType(type);
            }

            bool GetMouseSelectToCopy()
            {
                return g_ActiveMadEdit->GetMouseSelectToCopy();
            }
            void SetMouseSelectToCopy(bool value)
            {
                g_ActiveMadEdit->SetMouseSelectToCopy(value);
            }
            bool GetMouseSelectToCopyWithCtrlKey()
            {
                return g_ActiveMadEdit->GetMouseSelectToCopyWithCtrlKey();
            }
            void SetMouseSelectToCopyWithCtrlKey(bool value)
            {
                g_ActiveMadEdit->SetMouseSelectToCopyWithCtrlKey(value);
            }

            bool GetMiddleMouseToPaste()
            {
                return g_ActiveMadEdit->GetMiddleMouseToPaste();
            }
            void SetMiddleMouseToPaste(bool value)
            {
                g_ActiveMadEdit->SetMiddleMouseToPaste(value);
            }

            int GetMaxWordWrapWidth()
            {
                return g_ActiveMadEdit->GetMaxWordWrapWidth();
            }
            int GetUCharWidth(ucs4_t uc)
            {
                return g_ActiveMadEdit->GetUCharWidth(uc);
            }
            int GetHexUCharWidth(ucs4_t uc)
            {
                return g_ActiveMadEdit->GetHexUCharWidth(uc);
            }
            int GetUCharType(ucs4_t uc)
            {
                return g_ActiveMadEdit->GetUCharType(uc);
            }

            // all are zero-based
            mad_py::tuple GetCaretPositionA()
            {
                int line = 0, subrow = 0;
                wxFileOffset column;
                g_ActiveMadEdit->GetCaretPosition(line, subrow, column);
                return mad_py::make_tuple(line, subrow, column);
            }
            wxFileOffset GetCaretPosition()
            {
                return g_ActiveMadEdit->GetCaretPosition();
            }
            wxString GetFileName()
            {
                return g_ActiveMadEdit->GetFileName();
            }
            wxFileOffset GetFileSize()
            {
                return g_ActiveMadEdit->GetFileSize();
            }

            bool IsSelected()
            {
                return g_ActiveMadEdit->IsSelected();
            }
            wxFileOffset GetSelectionSize()
            {
                return g_ActiveMadEdit->GetSelectionSize();
            }
            wxFileOffset GetSelectionBeginPos()
            {
                return g_ActiveMadEdit->GetSelectionBeginPos();
            }
            wxFileOffset GetSelectionEndPos()
            {
                return g_ActiveMadEdit->GetSelectionEndPos();
            }

            // return -1 for no selection
            mad_py::tuple GetSelectionLineId()
            {
                int beginline = -1, endline = -1;
                g_ActiveMadEdit->GetSelectionLineId(beginline, endline);
                return mad_py::make_tuple(beginline, endline);
            }

            int GetLineCount()
            {
                return g_ActiveMadEdit->GetLineCount();
            }

            void ConvertNewLineType(MadNewLineType type)
            {
                g_ActiveMadEdit->ConvertNewLineType(type);
            }
            void SetInsertNewLineType(MadNewLineType type)
            {
                g_ActiveMadEdit->SetInsertNewLineType(type);
            }

            MadNewLineType GetNewLineType()
            {
                return g_ActiveMadEdit->GetNewLineType();
            }

            MadNewLineType GetInsertNewLineType()
            {
                return g_ActiveMadEdit->GetInsertNewLineType();
            }

            bool IsModified()
            {
                return g_ActiveMadEdit->IsModified();
            }
            time_t GetModificationTime()
            {
                return g_ActiveMadEdit->GetModificationTime();
            }

            void SetReadOnly(bool value)
            {
                g_ActiveMadEdit->SetReadOnly(value);
            }
            bool IsReadOnly()
            {
                return g_ActiveMadEdit->IsReadOnly();
            }
            bool IsTextFile()
            {
                return g_ActiveMadEdit->IsTextFile();
            }

            void GetSelText(wxString &ws)
            {
                g_ActiveMadEdit->GetSelText(ws);
            }
            wxString GetText(bool ignoreBOM = true)
            {
                wxString ws;
                g_ActiveMadEdit->GetText(ws, ignoreBOM);
                return ws;
            }
            void SetText(const wxString &ws)
            {
                g_ActiveMadEdit->SetText(ws);
            }

            // line: zero based
            // return true for full line, false for partial line
            bool GetLine(wxString &ws, int line, size_t maxlen = 0, bool ignoreBOM = true)
            {
                return g_ActiveMadEdit->GetLine(ws, line, maxlen, ignoreBOM);
            }
            int GetLineByPos(const wxFileOffset &pos)
            {
                return g_ActiveMadEdit->GetLineByPos(pos);
            }

            void GetSelHexString(wxString &ws, bool withSpace)
            {
                g_ActiveMadEdit->GetSelHexString(ws, withSpace);
            }

            void GetWordFromCaretPos(wxString &ws)
            {
                g_ActiveMadEdit->GetWordFromCaretPos(ws);
            }

            void Delete()
            {
                g_ActiveMadEdit->Delete();
            }
            void CutLine()
            {
                g_ActiveMadEdit->CutLine();
            }
            void DeleteLine()
            {
                g_ActiveMadEdit->DeleteLine();
            }
            void InsertTabChar()
            {
                g_ActiveMadEdit->InsertTabChar();
            }
            void InsertDateTime()
            {
                g_ActiveMadEdit->InsertDateTime();
            }

            void HighlightWords()
            {
                g_ActiveMadEdit->HighlightWords();
            }

            void SelectAll()
            {
                g_ActiveMadEdit->SelectAll();
            }
            void CutToClipboard()
            {
                g_ActiveMadEdit->CutToClipboard();
            }
            void CopyToClipboardA()
            {
                g_ActiveMadEdit->CopyToClipboard();
            }
            void PasteFromClipboard()
            {
                g_ActiveMadEdit->PasteFromClipboard();
            }
            bool CanPaste()
            {
                return g_ActiveMadEdit->CanPaste();
            }
            void CopyToClipboardB(wxString & text)
            {
                g_ActiveMadEdit->CopyToClipboard(text);
            }

            bool CanUndo()
            {
                return g_ActiveMadEdit->CanUndo();
            }
            bool CanRedo()
            {
                return g_ActiveMadEdit->CanRedo();
            }
            void Undo()
            {
                g_ActiveMadEdit->Undo();
            }
            void Redo()
            {
                g_ActiveMadEdit->Redo();
            }

            void SetCaretPosition(wxFileOffset pos, wxFileOffset selbeg=-1, wxFileOffset selend=-1)
            {
                g_ActiveMadEdit->SetCaretPosition(pos, selbeg, selend);
            }

            bool HasBracePair()
            {
                return g_ActiveMadEdit->HasBracePair();
            }
            void GoToLeftBrace()
            {
                g_ActiveMadEdit->GoToLeftBrace();
            }
            void GoToRightBrace()
            {
                g_ActiveMadEdit->GoToRightBrace();
            }

            // search in [rangeFrom, rangeTo], default in [CaretPos, EndOfDoc]
            MadSearchResult FindTextNext(const wxString &text,
                                        bool bRegex, bool bCaseSensitive, bool bWholeWord,
                                        wxFileOffset rangeFrom = -1, wxFileOffset rangeTo = -1)
            {
                return g_ActiveMadEdit->FindTextNext(text, bRegex, bCaseSensitive, bWholeWord, rangeFrom, rangeTo);
            }
            // search in [rangeFrom, rangeTo], rangeFrom > rangeTo, default in [CaretPos, BeginOfDoc]
            MadSearchResult FindTextPrevious(const wxString &text,
                                        bool bRegex, bool bCaseSensitive, bool bWholeWord,
                                        wxFileOffset rangeFrom = -1, wxFileOffset rangeTo = -1)
            {
                return g_ActiveMadEdit->FindTextPrevious(text, bRegex, bCaseSensitive, bWholeWord, rangeFrom, rangeTo);
            }

            // search in [rangeFrom, rangeTo], default in [CaretPos, EndOfDoc]
            MadSearchResult FindHexNext(const wxString &hexstr, wxFileOffset rangeFrom = -1, wxFileOffset rangeTo = -1)
            {
                return g_ActiveMadEdit->FindHexNext(hexstr, rangeFrom, rangeTo);
            }
            // search in [rangeFrom, rangeTo], rangeFrom > rangeTo, default in [CaretPos, BeginOfDoc]
            MadSearchResult FindHexPrevious(const wxString &hexstr, wxFileOffset rangeFrom = -1, wxFileOffset rangeTo = -1)
            {
                return g_ActiveMadEdit->FindHexPrevious(hexstr, rangeFrom, rangeTo);
            }

            // replace the selected text that must match expr
            MadReplaceResult ReplaceText(const wxString &expr, const wxString &fmt,
                                         bool bRegex, bool bCaseSensitive, bool bWholeWord,
                                         wxFileOffset rangeFrom = -1, wxFileOffset rangeTo = -1)
            {
                return g_ActiveMadEdit->ReplaceText(expr, fmt, bRegex, bCaseSensitive, bWholeWord, rangeFrom, rangeTo);
            }
            MadReplaceResult ReplaceHex(const wxString &expr, const wxString &fmt,
                                         wxFileOffset rangeFrom = -1, wxFileOffset rangeTo = -1)
            {
                return g_ActiveMadEdit->ReplaceHex(expr, fmt, rangeFrom, rangeTo);
            }

            // return the replaced count or SR_EXPR_ERROR
            int ReplaceTextAll(const wxString &expr, const wxString &fmt,
                                bool bRegex, bool bCaseSensitive, bool bWholeWord,
                                vector<wxFileOffset> *pbegpos = NULL, vector<wxFileOffset> *pendpos = NULL,
                                wxFileOffset rangeFrom = -1, wxFileOffset rangeTo = -1)
            {
                return g_ActiveMadEdit->ReplaceTextAll(expr, fmt, bRegex, bCaseSensitive, bWholeWord, pbegpos, pendpos, rangeFrom, rangeTo);
            }
            int ReplaceHexAll(const wxString &expr, const wxString &fmt,
                                vector<wxFileOffset> *pbegpos = NULL, vector<wxFileOffset> *pendpos = NULL,
                                wxFileOffset rangeFrom = -1, wxFileOffset rangeTo = -1)
            {
                return g_ActiveMadEdit->ReplaceHexAll(expr, fmt, pbegpos, pendpos, rangeFrom, rangeTo);
            }

            // list the matched data to pbegpos & pendpos
            // return the found count or SR_EXPR_ERROR
            int FindTextAll(const wxString &expr,
                            bool bRegex, bool bCaseSensitive, bool bWholeWord, bool bFirstOnly,
                            vector<wxFileOffset> *pbegpos, vector<wxFileOffset> *pendpos,
                            wxFileOffset rangeFrom = -1, wxFileOffset rangeTo = -1)
            {
                return g_ActiveMadEdit->FindTextAll(expr, bRegex, bCaseSensitive, bWholeWord, bFirstOnly, pbegpos, pendpos, rangeFrom, rangeTo);
            }
            int FindHexAll(const wxString &expr, bool bFirstOnly,
                           vector<wxFileOffset> *pbegpos, vector<wxFileOffset> *pendpos,
                           wxFileOffset rangeFrom = -1, wxFileOffset rangeTo = -1)
            {
                return g_ActiveMadEdit->FindHexAll(expr, bFirstOnly, pbegpos, pendpos, rangeFrom, rangeTo);
            }

            bool LoadFromFile(const wxString &filename, const wxString &encoding = wxEmptyString)
            {
                return g_ActiveMadEdit->LoadFromFile(filename, encoding);
            }
            bool SaveToFile(const wxString &filename)
            {
                return g_ActiveMadEdit->SaveToFile(filename);
            }
            bool Reload()
            {
                return g_ActiveMadEdit->Reload();
            }
            // if the file is modified by another app, reload it.
            bool ReloadByModificationTime()
            {
                return g_ActiveMadEdit->ReloadByModificationTime();
            }
            // restore pos in Reload(), ConvertEncoding()
            void RestorePosition(wxFileOffset pos, int toprow)
            {
                g_ActiveMadEdit->RestorePosition(pos, toprow);
            }

            // write back to the original FileName
            // if FileName is empty, ask the user to get filename
            // return wxID_YES(Saved), wxID_NO(Not Saved), or wxID_CANCEL
            int Save(bool ask, const wxString &title, bool saveas)
            {
                return g_ActiveMadEdit->Save(ask, title, saveas);
            }

            // add: gogo, 21.09.2009
            void SetBookmark()
            {
                g_ActiveMadEdit->SetBookmark();
            }
            void GotoNextBookmark()
            {
                g_ActiveMadEdit->GotoNextBookmark();
            }
            void GotoPreviousBookmark()
            {
                g_ActiveMadEdit->GotoPreviousBookmark();
            }
            //----------
            void ConvertEncoding(const wxString &newenc, MadConvertEncodingFlag flag)
            {
                g_ActiveMadEdit->ConvertEncoding(newenc, flag);
            }
            void ConvertChinese(MadConvertEncodingFlag flag)
            {
                g_ActiveMadEdit->ConvertChinese(flag);
            }

            bool HasBOM()
            {
                return g_ActiveMadEdit->HasBOM();
            }
            void ToggleBOM()
            {
                g_ActiveMadEdit->ToggleBOM();
            }

            void IncreaseDecreaseIndent(bool incIndent)
            {
                g_ActiveMadEdit->IncreaseDecreaseIndent(incIndent);
            }
            bool HasLineComment()
            {
                return g_ActiveMadEdit->HasLineComment();
            }
            void CommentUncomment(bool comment)
            {
                g_ActiveMadEdit->CommentUncomment(comment);
            }

            void ToUpperCase()
            {
                g_ActiveMadEdit->ToUpperCase();
            }
            void ToLowerCase()
            {
                g_ActiveMadEdit->ToLowerCase();
            }
            void InvertCase()
            {
                g_ActiveMadEdit->InvertCase();
            }
            void ToHalfWidth(bool ascii=true, bool japanese=true, bool korean=true, bool other=true)
            {
                g_ActiveMadEdit->ToHalfWidth(ascii, japanese, korean, other);
            }
            void ToFullWidth(bool ascii=true, bool japanese=true, bool korean=true, bool other=true)
            {
                g_ActiveMadEdit->ToFullWidth(ascii, japanese, korean, other);
            }

            void TrimTrailingSpaces()
            {
                g_ActiveMadEdit->TrimTrailingSpaces();
            }

            // startline<0 : sort all lines otherwise sort [beginline, endline]
            void SortLines(MadSortFlags flags, int beginline, int endline)
            {
                g_ActiveMadEdit->SortLines(flags, beginline, endline);
            }

            // convert WordWraps to NewLine-chars in the SelText or whole file
            void ConvertWordWrapToNewLine()
            {
                g_ActiveMadEdit->ConvertWordWrapToNewLine();
            }
            // convert NewLine-chars to WordWraps in the SelText
            void ConvertNewLineToWordWrap()
            {
                g_ActiveMadEdit->ConvertNewLineToWordWrap();
            }

            void ConvertSpaceToTab()
            {
                g_ActiveMadEdit->ConvertSpaceToTab();
            }
            void ConvertTabToSpace()
            {
                g_ActiveMadEdit->ConvertTabToSpace();
            }

            void CopyAsHexString(bool withSpace)
            {
                g_ActiveMadEdit->CopyAsHexString(withSpace);
            }

            void WordCount(bool selection, int &wordCount, int &charCount, int &spaceCount,
                           int &halfWidthCount, int &fullWidthCount, int &lineCount,
                           wxArrayString *detail)
            {
                g_ActiveMadEdit->WordCount(selection, wordCount, charCount, spaceCount, halfWidthCount, fullWidthCount, lineCount, detail);
            }
    };
}

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(FindTextNext_member_overloads, FindTextNext, 4, 6)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(FindTextPrevious_member_overloads, FindTextPrevious, 4, 6)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(FindHexNext_member_overloads, FindHexNext, 1, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(FindHexPrevious_member_overloads, FindHexPrevious, 1, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(ReplaceText_member_overloads, ReplaceText, 5, 7)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(ReplaceHex_member_overloads, ReplaceHex, 2, 4)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(ReplaceTextAll_member_overloads, ReplaceTextAll, 5, 9)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(ReplaceHexAll_member_overloads, ReplaceHexAll, 2, 6)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(FindTextAll_member_overloads, FindTextAll, 7, 9)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(FindHexAll_member_overloads, FindHexAll, 4, 6)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(LoadFromFile_member_overloads, LoadFromFile, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(ToHalfWidth_member_overloads, ToHalfWidth, 0, 4)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(ToFullWidth_member_overloads, ToFullWidth, 0, 4)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(SetCaretPosition_member_overloads, SetCaretPosition, 1, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(GetLine_member_overloads, GetLine, 2, 4)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(GetText_member_overloads, GetText, 0, 1)

BOOST_PYTHON_MODULE(madpython)
{
    using namespace mad_python;
    using namespace mad_py;

    class_<PyMadEdit>("MadEdit", "This class is a collection of wrapper functions of MadEdit.")
        .def("GoToLine", &PyMadEdit::GoToLine, "Go To Line of current file")
        .def("SetSyntax", &PyMadEdit::SetSyntax, "")
        .def("GetSyntax", &PyMadEdit::GetSyntax, return_value_policy<reference_existing_object>(), "")
        .def("GetSyntaxTitle", &PyMadEdit::GetSyntaxTitle, return_value_policy<return_by_value>(), "")
        .def("ApplySyntaxAttributes", &PyMadEdit::ApplySyntaxAttributes, "")
        .def("LoadDefaultSyntaxScheme", &PyMadEdit::LoadDefaultSyntaxScheme, "")
        .def("SetEncoding", &PyMadEdit::SetEncoding, "")
        .def("GetEncodingName", &PyMadEdit::GetEncodingName, return_value_policy<return_by_value>(), "")
        .def("GetEncodingDescription", &PyMadEdit::GetEncodingDescription, return_value_policy<return_by_value>(), "")
        .def("GetEncodingType", &PyMadEdit::GetEncodingType, return_value_policy<return_by_value>(), "")
        .def("GetRecordCaretMovements", &PyMadEdit::GetRecordCaretMovements, return_value_policy<return_by_value>(), "")
        .def("SetRecordCaretMovements", &PyMadEdit::SetRecordCaretMovements, return_value_policy<return_by_value>(), "")
        .def("SetTextFont", &PyMadEdit::SetTextFont, "")
        .def("SetHexFont", &PyMadEdit::SetHexFont, "")
        .def("GetTextFont", &PyMadEdit::GetTextFont, "")
        .def("GetHexFont", &PyMadEdit::GetHexFont, "")
        .def("GetFont", &PyMadEdit::GetFont, return_value_policy<return_by_value>(), "Doc")
        .def("GetFontNameSize", &PyMadEdit::GetFontNameSize, return_value_policy<return_by_value>(), "Doc")
        .def("SetFixedWidthMode", &PyMadEdit::SetFixedWidthMode, "")
        .def("GetFixedWidthMode", &PyMadEdit::GetFixedWidthMode, "")
        .def("SetLineSpacing", &PyMadEdit::SetLineSpacing, "")
        .def("GetLineSpacing", &PyMadEdit::GetLineSpacing, "")
        .def("SetEditMode", &PyMadEdit::SetEditMode, "")
        .def("GetEditMode", &PyMadEdit::GetEditMode, return_value_policy<return_by_value>(), "")
        .def("SetSingleLineMode", &PyMadEdit::SetSingleLineMode, "")
        .def("SetTabColumns", &PyMadEdit::SetTabColumns, "")
        .def("GetTabColumns", &PyMadEdit::GetTabColumns, "")
        .def("SetIndentColumns", &PyMadEdit::SetIndentColumns, "")
        .def("GetIndentColumns", &PyMadEdit::GetIndentColumns, "")
        .def("SetInsertSpacesInsteadOfTab", &PyMadEdit::SetInsertSpacesInsteadOfTab, "")
        .def("GetInsertSpacesInsteadOfTab", &PyMadEdit::GetInsertSpacesInsteadOfTab, "")
        .def("SetWantTab", &PyMadEdit::SetWantTab, "")
        .def("GetWantTab", &PyMadEdit::GetWantTab, "")
        .def("SetWordWrapMode", &PyMadEdit::SetWordWrapMode, "")
        .def("GetWordWrapMode", &PyMadEdit::GetWordWrapMode, "")
        .def("SetDisplayLineNumber", &PyMadEdit::SetDisplayLineNumber, "")
        .def("SetShowEndOfLine", &PyMadEdit::SetShowEndOfLine, "")
        .def("SetShowTabChar", &PyMadEdit::SetShowTabChar, "")
        .def("SetShowSpaceChar", &PyMadEdit::SetShowSpaceChar, "")
        .def("SetMarkActiveLine", &PyMadEdit::SetMarkActiveLine, "")
        .def("GetDisplayLineNumber", &PyMadEdit::GetDisplayLineNumber, "")
        .def("GetShowEndOfLine", &PyMadEdit::GetShowEndOfLine, "")
        .def("GetShowTabChar", &PyMadEdit::GetShowTabChar, "")
        .def("GetShowSpaceChar", &PyMadEdit::GetShowSpaceChar, "")
        .def("GetMarkActiveLine", &PyMadEdit::GetMarkActiveLine, "")
        .def("SetMarkBracePair", &PyMadEdit::SetMarkBracePair, "")
        .def("GetMarkBracePair", &PyMadEdit::GetMarkBracePair, "")
        .def("GetMaxColumns", &PyMadEdit::GetMaxColumns, "")
        .def("SetMaxColumns", &PyMadEdit::SetMaxColumns, "")
        .def("GetAutoIndent", &PyMadEdit::GetAutoIndent, "")
        .def("SetAutoIndent", &PyMadEdit::SetAutoIndent, "")
        .def("SetAutoCompletePair", &PyMadEdit::SetAutoCompletePair, "")
        .def("GetAutoCompletePair", &PyMadEdit::GetAutoCompletePair, "")
        .def("SetInsertMode", &PyMadEdit::SetInsertMode, "")
        .def("GetInsertMode", &PyMadEdit::GetInsertMode, "")

        .def("SetCaretType", &PyMadEdit::SetCaretType, "")
        .def("GetMouseSelectToCopy", &PyMadEdit::GetMouseSelectToCopy, "")
        .def("SetMouseSelectToCopy", &PyMadEdit::SetMouseSelectToCopy, "")
        .def("GetMouseSelectToCopyWithCtrlKey", &PyMadEdit::GetMouseSelectToCopyWithCtrlKey, "")
        .def("SetMouseSelectToCopyWithCtrlKey", &PyMadEdit::SetMouseSelectToCopyWithCtrlKey, "")
        .def("GetMiddleMouseToPaste", &PyMadEdit::GetMiddleMouseToPaste, "")
        .def("SetMiddleMouseToPaste", &PyMadEdit::SetMiddleMouseToPaste, "")
        .def("GetMaxWordWrapWidth", &PyMadEdit::GetMaxWordWrapWidth, "")
        .def("GetUCharWidth", &PyMadEdit::GetUCharWidth, "")
        .def("GetHexUCharWidth", &PyMadEdit::GetHexUCharWidth, "")
        .def("GetUCharType", &PyMadEdit::GetUCharType, "")

        .def("GetCaretPositionA", &PyMadEdit::GetCaretPositionA, return_value_policy<return_by_value>(), "")
        .def("GetCaretPosition", &PyMadEdit::GetCaretPosition, return_value_policy<return_by_value>(), "")
        .def("GetFileName", &PyMadEdit::GetFileName, return_value_policy<return_by_value>(), "")
        .def("GetFileSize", &PyMadEdit::GetFileSize, return_value_policy<return_by_value>(), "")
        .def("IsSelected", &PyMadEdit::IsSelected, "")
        .def("GetSelectionSize", &PyMadEdit::GetSelectionSize, return_value_policy<return_by_value>(), "")
        .def("GetSelectionBeginPos", &PyMadEdit::GetSelectionBeginPos, return_value_policy<return_by_value>(), "")
        .def("GetSelectionEndPos", &PyMadEdit::GetSelectionEndPos, return_value_policy<return_by_value>(), "")
        .def("GetSelectionLineId", &PyMadEdit::GetSelectionLineId, return_value_policy<return_by_value>(), "")
        .def("GetLineCount", &PyMadEdit::GetLineCount, "")
        .def("ConvertNewLineType", &PyMadEdit::ConvertNewLineType, "")
        .def("SetInsertNewLineType", &PyMadEdit::SetInsertNewLineType, "")
        .def("GetNewLineType", &PyMadEdit::GetNewLineType, "")
        .def("GetInsertNewLineType", &PyMadEdit::GetInsertNewLineType, "")
        .def("IsModified", &PyMadEdit::IsModified, "")
        .def("GetModificationTime", &PyMadEdit::GetModificationTime, "")
        .def("SetReadOnly", &PyMadEdit::SetReadOnly, "")
        .def("IsReadOnly", &PyMadEdit::IsReadOnly, "")
        .def("IsTextFile", &PyMadEdit::IsTextFile, "")
        .def("GetSelText", &PyMadEdit::GetSelText, "")
        .def("SetText", &PyMadEdit::SetText, "")
        .def("GetLineByPos", &PyMadEdit::GetLineByPos, "")
        .def("GetSelHexString", &PyMadEdit::GetSelHexString, "")
        .def("GetWordFromCaretPos", &PyMadEdit::GetWordFromCaretPos, "")

        .def("Delete", &PyMadEdit::Delete, "")
        .def("CutLine", &PyMadEdit::CutLine, "")
        .def("DeleteLine", &PyMadEdit::DeleteLine, "")
        .def("InsertTabChar", &PyMadEdit::InsertTabChar, "")
        .def("InsertDateTime", &PyMadEdit::InsertDateTime, "")
        .def("HighlightWords", &PyMadEdit::HighlightWords, "")
        .def("SelectAll", &PyMadEdit::SelectAll, "")

        .def("CutToClipboard", &PyMadEdit::CutToClipboard, "")

        .def("PasteFromClipboard", &PyMadEdit::PasteFromClipboard, "")

        .def("CanPaste", &PyMadEdit::CanPaste, "")
        .def("CanUndo", &PyMadEdit::CanUndo, return_value_policy<return_by_value>(), "")

        .def("CanRedo", &PyMadEdit::CanRedo, return_value_policy<return_by_value>(), "")
        .def("Undo", &PyMadEdit::Undo, "")
        .def("Redo", &PyMadEdit::Redo, "")

        .def("HasBracePair", &PyMadEdit::HasBracePair, return_value_policy<return_by_value>(), "")
        .def("GoToLeftBrace", &PyMadEdit::GoToLeftBrace, "")
        .def("GoToRightBrace", &PyMadEdit::GoToRightBrace, "")
        .def("SaveToFile", &PyMadEdit::SaveToFile, "")
        .def("Reload", &PyMadEdit::Reload, "")
        .def("ReloadByModificationTime", &PyMadEdit::ReloadByModificationTime, "")
        .def("RestorePosition", &PyMadEdit::RestorePosition, "")
        .def("Save", &PyMadEdit::Save, "")
        .def("SetBookmark", &PyMadEdit::SetBookmark, "")
        .def("GotoNextBookmark", &PyMadEdit::GotoNextBookmark, "")
        .def("GotoPreviousBookmark", &PyMadEdit::GotoPreviousBookmark, "")
        .def("ConvertEncoding", &PyMadEdit::ConvertEncoding, "")
        .def("ConvertChinese", &PyMadEdit::ConvertChinese, "")
        .def("HasBOM", &PyMadEdit::HasBOM, "")
        .def("ToggleBOM", &PyMadEdit::ToggleBOM, "")
        .def("IncreaseDecreaseIndent", &PyMadEdit::IncreaseDecreaseIndent, "")
        .def("HasLineComment", &PyMadEdit::HasLineComment, "")
        .def("CommentUncomment", &PyMadEdit::CommentUncomment, "")
        .def("ToUpperCase", &PyMadEdit::ToUpperCase, "")
        .def("ToLowerCase", &PyMadEdit::ToLowerCase, "")

        .def("InvertCase", &PyMadEdit::InvertCase, "")
        .def("TrimTrailingSpaces", &PyMadEdit::TrimTrailingSpaces, "")
        .def("SortLines", &PyMadEdit::SortLines, "")
        .def("ConvertWordWrapToNewLine", &PyMadEdit::ConvertWordWrapToNewLine, "")
        .def("ConvertNewLineToWordWrap", &PyMadEdit::ConvertNewLineToWordWrap, "")
        .def("ConvertSpaceToTab", &PyMadEdit::ConvertSpaceToTab, "")
        .def("ConvertTabToSpace", &PyMadEdit::ConvertTabToSpace, "")
        .def("CopyAsHexString", &PyMadEdit::CopyAsHexString, "")
        .def("WordCount", &PyMadEdit::WordCount, "")
        .def("SetFontA", &PyMadEdit::SetFontA, "Doc")
        .def("SetFontB", &PyMadEdit::SetFontB, "Doc")
        .def("CopyToClipboardA", &PyMadEdit::CopyToClipboardA, "")
        .def("CopyToClipboardB", &PyMadEdit::CopyToClipboardB, "")
        .def("FindTextNext", &PyMadEdit::FindTextNext, FindTextNext_member_overloads( args("text", "bRegex", "bCaseSensitive", "bWholeWord", "rangeFrom", "rangeTo"), "Doc string" )[return_value_policy<return_by_value>()])

        .def("FindTextPrevious", &PyMadEdit::FindTextPrevious, FindTextPrevious_member_overloads( args("text", "bRegex", "bCaseSensitive", "bWholeWord", "rangeFrom", "rangeTo"), "Doc string" )[return_value_policy<return_by_value>()])
        .def("FindHexNext", &PyMadEdit::FindHexNext, FindHexNext_member_overloads( args("hexstr", "rangeFrom", "rangeTo"), "Doc string" )[return_value_policy<return_by_value>()])
        .def("FindHexPrevious", &PyMadEdit::FindHexPrevious, FindHexPrevious_member_overloads( args("hexstr", "rangeFrom", "rangeTo"), "Doc string" )[return_value_policy<return_by_value>()])
        .def("ReplaceText", &PyMadEdit::ReplaceText, ReplaceText_member_overloads( args("expr", "fmt", "bRegex", "bCaseSensitive", "bWholeWord", "rangeFrom", "rangeTo"), "Doc string" )[return_value_policy<return_by_value>()])
        .def("ReplaceHex", &PyMadEdit::ReplaceHex, ReplaceHex_member_overloads( args("expr", "fmt", "rangeFrom", "rangeTo"), "Doc string" )[return_value_policy<return_by_value>()])
        .def("ReplaceTextAll", &PyMadEdit::ReplaceTextAll, ReplaceTextAll_member_overloads( args("expr", "fmt", "bRegex", "bCaseSensitive", "bWholeWord", "pbegpos", "pendpos", "rangeFrom", "rangeTo"), "Doc string" )[return_value_policy<return_by_value>()])
        .def("ReplaceHexAll", &PyMadEdit::ReplaceHexAll, ReplaceHexAll_member_overloads( args("expr", "fmt", "pbegpos", "pendpos", "rangeFrom", "rangeTo"), "Doc string" )[return_value_policy<return_by_value>()])
        .def("FindTextAll", &PyMadEdit::FindTextAll, FindTextAll_member_overloads( args("expr", "fmt", "bRegex", "bCaseSensitive", "bWholeWord", "pbegpos", "pendpos", "rangeFrom", "rangeTo"), "Doc string" )[return_value_policy<return_by_value>()])
        .def("FindHexAll", &PyMadEdit::FindHexAll, FindHexAll_member_overloads( args("expr", "bFirstOnly", "pbegpos", "pendpos", "rangeFrom", "rangeTo"), "Doc string" )[return_value_policy<return_by_value>()])
        .def("LoadFromFile", &PyMadEdit::LoadFromFile, LoadFromFile_member_overloads( args("filename", "encoding"), "Doc string" )[return_value_policy<return_by_value>()])

        .def("ToHalfWidth", &PyMadEdit::ToHalfWidth, ToHalfWidth_member_overloads( args("ascii", "japanese", "korean", "other"), "Doc string" ))
        .def("ToFullWidth", &PyMadEdit::ToFullWidth, ToFullWidth_member_overloads( args("ascii", "japanese", "korean", "other"), "Doc string" ))
        .def("SetCaretPosition", &PyMadEdit::SetCaretPosition, SetCaretPosition_member_overloads( args("pos", "selbeg", "selend"), "Doc string" ))
        .def("GetLine", &PyMadEdit::GetLine, GetLine_member_overloads( args("ws", "line", "maxlen", "ignoreBOM"), "Doc string" )[return_value_policy<return_by_value>()])

        .def("GetText", &PyMadEdit::GetText, GetText_member_overloads( args("ignoreBOM"), "Doc string" )[return_value_policy<return_by_value>()])

        ;
}

