// MemoryHackerDlg.h : header file
//
#include "MemoryHack.h"

#if !defined(AFX_MEMORYHACKERDLG_H__C5ABA573_DCA3_4DB7_96B1_CF3E3D8C3779__INCLUDED_)
#define AFX_MEMORYHACKERDLG_H__C5ABA573_DCA3_4DB7_96B1_CF3E3D8C3779__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMemoryHackerDlg dialog

class CMemoryHackerDlg : public CDialog
{
// Construction
public:
	CMemoryHackerDlg(CWnd* pParent = NULL);	// standard constructor
	static BOOL EnableDebugPrivileges();

	MemoryHack memoryhackdlg;
// Dialog Data
	//{{AFX_DATA(CMemoryHackerDlg)
	enum { IDD = IDD_MEMORYHACKER_DIALOG };
	CListCtrl	m_cListCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemoryHackerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RefreshProcessList();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMemoryHackerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMORYHACKERDLG_H__C5ABA573_DCA3_4DB7_96B1_CF3E3D8C3779__INCLUDED_)
