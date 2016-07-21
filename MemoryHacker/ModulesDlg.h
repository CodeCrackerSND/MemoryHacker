#if !defined(AFX_MODULESDLG_H__DA24E17E_874B_41A1_A218_8A25A88F374F__INCLUDED_)
#define AFX_MODULESDLG_H__DA24E17E_874B_41A1_A218_8A25A88F374F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModulesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ModulesDlg dialog

class ModulesDlg : public CDialog
{
// Construction
public:
	ModulesDlg(CWnd* pParent = NULL);   // standard constructor
	ModulesDlg& operator=(ModulesDlg& right); // Overload Assignment Operator
	void RefreshModulesList();
	unsigned int GetModuleSize(HMODULE hMod);

	int processid;
	CString processname;

// Dialog Data
	//{{AFX_DATA(ModulesDlg)
	enum { IDD = IDD_MODULESDLG_DIALOG };
	CListCtrl	m_cListCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ModulesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ModulesDlg)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODULESDLG_H__DA24E17E_874B_41A1_A218_8A25A88F374F__INCLUDED_)
