// NewEdit.cpp : implementation file
//

#include "stdafx.h"
#include "MemoryHacker.h"
#include "NewEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// NewEdit

NewEdit::NewEdit()
{
}

NewEdit::~NewEdit()
{
}


BEGIN_MESSAGE_MAP(NewEdit, CEdit)
	//{{AFX_MSG_MAP(NewEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NewEdit message handlers

void NewEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
if (islower(nChar)) nChar -=32;  // MAKE CHAR UPPER IF IS LOWER

if ((nChar>=48&&nChar<=57)||(nChar>=65&&nChar<=70))
DefWindowProc(WM_CHAR, nChar,0);

if (nChar == VK_BACK||nChar == VK_DELETE)  // if backslash or delete key
DefWindowProc(WM_CHAR, nChar,0);

	// Originaly calls this:
	//CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void NewEdit::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	this->SetLimitText(8);  // set max text lenght to 8
	CEdit::PreSubclassWindow();
}
