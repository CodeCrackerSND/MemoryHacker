#if !defined(AFX_CUSTOMIZEDLG_H__01CA843C_6019_4DBF_90EE_CDD5D6141932__INCLUDED_)
#define AFX_CUSTOMIZEDLG_H__01CA843C_6019_4DBF_90EE_CDD5D6141932__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomizeDlg.h : header file
//
#include "NewEdit.h"
#include "ModulesDlg.h"
#include "MemoryBlock.h"

/////////////////////////////////////////////////////////////////////////////
// CCustomizeDlg dialog

class CCustomizeDlg : public CDialog
{
// Construction
public:
	CCustomizeDlg(CWnd* pParent = NULL);   // standard constructor
	CCustomizeDlg& operator=(CCustomizeDlg& right); // Overload Assignment Operator

	int processid;
	CString processname;
	static CCustomizeDlg instance;

	ModulesDlg modulesdlg;
	MemoryBlock memblockdlg;

	void RefreshList();
	void RemoveSelected();
	static void UpdateStartAddress(unsigned int address);
	static void UpdateEndAddress(unsigned int address);



// Dialog Data
	//{{AFX_DATA(CCustomizeDlg)
	enum { IDD = IDD_CUSTOMIZEDLG_DIALOG };
	CListCtrl	m_cListCtrl;
	NewEdit	m_endaddress;
	NewEdit	m_startaddress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustomizeDlg)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnModuleBut();
	afx_msg void OnBlockBut();
	afx_msg void OnPickStart();
	afx_msg void OnPickEnd();
	afx_msg void OnAddBut();
	afx_msg void OnClearallBut();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZEDLG_H__01CA843C_6019_4DBF_90EE_CDD5D6141932__INCLUDED_)
