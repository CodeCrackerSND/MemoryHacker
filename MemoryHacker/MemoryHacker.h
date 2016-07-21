// MemoryHacker.h : main header file for the MEMORYHACKER application
//

#if !defined(AFX_MEMORYHACKER_H__F4A35146_CD97_41C6_9C61_9DC5665E0343__INCLUDED_)
#define AFX_MEMORYHACKER_H__F4A35146_CD97_41C6_9C61_9DC5665E0343__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMemoryHackerApp:
// See MemoryHacker.cpp for the implementation of this class
//

class CMemoryHackerApp : public CWinApp
{
public:
	CMemoryHackerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemoryHackerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMemoryHackerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMORYHACKER_H__F4A35146_CD97_41C6_9C61_9DC5665E0343__INCLUDED_)
