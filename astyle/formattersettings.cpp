/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 *
 * $Revision: 10188 $
 * $Id: formattersettings.cpp 10188 2015-04-06 11:50:06Z mortenmacfly $
 * $HeadURL: file:///svn/p/codeblocks/code/trunk/src/plugins/astyle/formattersettings.cpp $
 */

//#include <sdk.h>
#include "formattersettings.h"
#include "astylepredefinedstyles.h"
//#include <configmanager.h>
#include <wx/confbase.h>

FormatterSettings::FormatterSettings()
{
  //ctor
}

FormatterSettings::~FormatterSettings()
{
  //dtor
}

void FormatterSettings::ApplyTo(astyle::ASFormatter& formatter)
{
  // NOTE: Keep this in sync with DlgFormatterSettings::ApplyTo
  wxConfigBase	  *cfg=wxConfigBase::Get(false);
  wxString oldpath=cfg->GetPath();
  cfg->SetPath(wxT("/astyle"));
  //ConfigManager* cfg = Manager::Get()->GetConfigManager(_T("astyle"));

  long style = cfg->ReadLong(_T("/style"), aspsAllman);
  switch (style)
  {
    case aspsAllman: // Allman (ANSI)
      formatter.setFormattingStyle(astyle::STYLE_ALLMAN);
      break;

    case aspsJava: // Java
      formatter.setFormattingStyle(astyle::STYLE_JAVA);
      break;

    case aspsKr: // K&R
      formatter.setFormattingStyle(astyle::STYLE_KR);
      break;

    case aspsStroustrup: // Stroustrup
      formatter.setFormattingStyle(astyle::STYLE_STROUSTRUP);
      break;

    case aspsWhitesmith: // Whitesmith
      formatter.setFormattingStyle(astyle::STYLE_WHITESMITH);
      break;

    case aspsVTK: // VTK
      formatter.setFormattingStyle(astyle::STYLE_VTK);
      break;

    case aspsBanner: // Banner
      formatter.setFormattingStyle(astyle::STYLE_BANNER);
      break;

    case aspsGnu: // GNU
      formatter.setFormattingStyle(astyle::STYLE_GNU);
      break;

    case aspsLinux: // Linux
      formatter.setFormattingStyle(astyle::STYLE_LINUX);
      break;

    case aspsHorstmann: // Horstmann
      formatter.setFormattingStyle(astyle::STYLE_HORSTMANN);
      break;

    case asps1TBS: // 1TBS
      formatter.setFormattingStyle(astyle::STYLE_1TBS);
      break;

    case aspsGoogle: // Google
      formatter.setFormattingStyle(astyle::STYLE_GOOGLE);
      break;

    case aspsPico: // Pico
      formatter.setFormattingStyle(astyle::STYLE_PICO);
      break;

    case aspsLisp: // Lisp
      formatter.setFormattingStyle(astyle::STYLE_LISP);
      break;

    default: // Custom
      break;
  }

  formatter.setAttachClass(cfg->ReadBool(_T("/attach_classes"), false));
  formatter.setAttachExternC(cfg->ReadBool(_T("/attach_extern_c"), true));
  formatter.setAttachNamespace(cfg->ReadBool(_T("/attach_namespaces"), true));
  formatter.setAttachInline(cfg->ReadBool(_T("/attach_inlines"), true));

  bool value = cfg->ReadBool(_T("/force_tabs"), false);
  long spaceNum = cfg->ReadLong(_T("/indentation"), 4);
  if (cfg->ReadBool(_T("/use_tabs"), false))
    formatter.setTabIndentation(spaceNum, value);
  else
    formatter.setSpaceIndentation(spaceNum);

  formatter.setCaseIndent(cfg->ReadBool(_T("/indent_case"), true));
  formatter.setClassIndent(cfg->ReadBool(_T("/indent_classes"), false));
  formatter.setLabelIndent(cfg->ReadBool(_T("/indent_labels"), false));
  formatter.setModifierIndent(cfg->ReadBool(_T("/indent_modifiers"), false));
  formatter.setNamespaceIndent(cfg->ReadBool(_T("/indent_namespaces"), true));
  formatter.setSwitchIndent(cfg->ReadBool(_T("/indent_switches"), false));
  formatter.setPreprocBlockIndent(cfg->ReadBool(_T("/indent_preproc_block"), true));
  formatter.setPreprocDefineIndent(cfg->ReadBool(_T("/indent_preproc_define"), false));
  formatter.setPreprocConditionalIndent(cfg->ReadBool(_T("/indent_preproc_cond"), false));
  formatter.setIndentCol1CommentsMode(cfg->ReadBool(_T("/indent_col1_comments"), true));
  formatter.setMinConditionalIndentOption(cfg->ReadLong(_T("/min_conditional_indent"), 2));
  formatter.setMaxInStatementIndentLength(cfg->ReadLong(_T("/max_instatement_indent"), 40));

  formatter.setBreakClosingHeaderBracketsMode(cfg->ReadBool(_T("/break_closing"), true));
  formatter.setBreakElseIfsMode(cfg->ReadBool(_T("/break_elseifs"), true));
  formatter.setAddBracketsMode(cfg->ReadBool(_T("/add_brackets"), false));
  formatter.setAddOneLineBracketsMode(cfg->ReadBool(_T("/add_one_line_brackets"), true));
  formatter.setSingleStatementsMode(!cfg->ReadBool(_T("/keep_complex"), true));
  formatter.setRemoveBracketsMode(cfg->ReadBool(_T("/remove_brackets"), false));
  formatter.setBreakOneLineBlocksMode(!cfg->ReadBool(_T("/keep_blocks"), true));
  formatter.setTabSpaceConversionMode(cfg->ReadBool(_T("/convert_tabs"), true));
  formatter.setCloseTemplatesMode(cfg->ReadBool(_T("/close_templates"), false));
  formatter.setStripCommentPrefix(cfg->ReadBool(_T("/remove_comment_prefix"), false));

  if (cfg->ReadBool(_T("/break_lines"), false))
  {
    formatter.setMaxCodeLength(wxAtoi(cfg->Read(_T("/max_line_length"), wxString(wxT("256")))));
    formatter.setBreakAfterMode(cfg->ReadBool(_T("/break_after_mode"), false));
  }
  else
    //formatter.setMaxCodeLength(INT_MAX);
    formatter.setMaxCodeLength(4096); //DEFAULT_MAX_LINELEN

  formatter.setBreakBlocksMode(cfg->ReadBool(_T("/break_blocks"), true));
  formatter.setBreakClosingHeaderBlocksMode(cfg->ReadBool(_T("/break_blocks_all"), false));
  formatter.setOperatorPaddingMode(cfg->ReadBool(_T("/pad_operators"), true));
  formatter.setParensOutsidePaddingMode(cfg->ReadBool(_T("/pad_parentheses_out"), false));
  formatter.setParensInsidePaddingMode(cfg->ReadBool(_T("/pad_parentheses_in"), true));
  formatter.setParensHeaderPaddingMode(cfg->ReadBool(_T("/pad_header"), false));
  formatter.setParensUnPaddingMode(cfg->ReadBool(_T("/unpad_parentheses"), true));
  formatter.setDeleteEmptyLinesMode(cfg->ReadBool(_T("/delete_empty_lines"), true));
  formatter.setEmptyLineFill(cfg->ReadBool(_T("/fill_empty_lines"), false));

  wxString pointerAlign = cfg->Read(_T("/pointer_align"), wxEmptyString);
  if      (pointerAlign == _T("Type"))
    formatter.setPointerAlignment(astyle::PTR_ALIGN_TYPE);
  else if (pointerAlign == _T("Middle"))
    formatter.setPointerAlignment(astyle::PTR_ALIGN_MIDDLE);
  else if (pointerAlign == _T("Name"))
    formatter.setPointerAlignment(astyle::PTR_ALIGN_NAME);
  else
    formatter.setPointerAlignment(astyle::PTR_ALIGN_NONE);

  wxString referenceAlign = cfg->Read(_T("/reference_align"), wxEmptyString);
  if      (referenceAlign == _T("Type"))
    formatter.setReferenceAlignment(astyle::REF_ALIGN_TYPE);
  else if (referenceAlign == _T("Middle"))
    formatter.setReferenceAlignment(astyle::REF_ALIGN_MIDDLE);
  else if (referenceAlign == _T("Name"))
    formatter.setReferenceAlignment(astyle::REF_ALIGN_NAME);
  else
    formatter.setReferenceAlignment(astyle::REF_ALIGN_NONE);
  
  cfg->SetPath(oldpath);
}
