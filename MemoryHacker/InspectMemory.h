#if !defined(AFX_INSPECTMEMORY_H__88778F85_6EF4_4F11_98D7_4C3BC40F62DD__INCLUDED_)
#define AFX_INSPECTMEMORY_H__88778F85_6EF4_4F11_98D7_4C3BC40F62DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InspectMemory.h : header file
//
#include "NewEdit.h"

/////////////////////////////////////////////////////////////////////////////
// InspectMemory dialog

class InspectMemory : public CDialog
{
// Construction
public:
	InspectMemory(CWnd* pParent = NULL);   // standard constructor
	InspectMemory& InspectMemory::operator=(InspectMemory& right);
	CString address_str;
	int processid;

// Dialog Data
	//{{AFX_DATA(InspectMemory)
	enum { IDD = IDD_INSPECTMEMORY_DIALOG };
	CEdit	m_result_edit;
	NewEdit	m_edit_2;
	NewEdit	m_edit1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(InspectMemory)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(InspectMemory)
	afx_msg void OnInspectbut();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSPECTMEMORY_H__88778F85_6EF4_4F11_98D7_4C3BC40F62DD__INCLUDED_)
