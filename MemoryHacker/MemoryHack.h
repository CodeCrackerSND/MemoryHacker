#if !defined(AFX_MEMORYHACK_H__79FD0C8B_C9D1_43F7_AA43_3BAF860553AA__INCLUDED_)
#define AFX_MEMORYHACK_H__79FD0C8B_C9D1_43F7_AA43_3BAF860553AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MemoryHack.h : header file
//

#include "CustomizeDlg.h"
#include "InspectMemory.h"

/////////////////////////////////////////////////////////////////////////////
// MemoryHack dialog

class MemoryHack : public CDialog
{
// Construction
public:
	MemoryHack(CWnd* pParent = NULL);   // standard constructor
	MemoryHack& operator=(MemoryHack& right); // Overload Assignment Operator
	void GetVirtualMemories();
	void PatchAddresses();
	void CopySelected();
	void RemoveSelected();
	void PatchSelected();
	void GetSelectedIndexes();
	void InspectMemoryMethod();

	static int custom_count;
	static unsigned int start_addresses[2000];
	static unsigned int end_addresses[2000];

	bool MemoryInRange(unsigned int address);

	int vmem_counts;
	MEMORY_BASIC_INFORMATION* valid_mems;

	void SetCustomizeBtnEnabled();
	int processid;
	CString processname;
	CCustomizeDlg customizedlg;
	InspectMemory inspectdlg;
	//int MemoryHack::custom_count = 0;

// Dialog Data
	//{{AFX_DATA(MemoryHack)
	enum { IDD = IDD_MEMORYHACK_DIALOG };
	CListCtrl	m_cListCtrl;
	CComboBox	m_type;
	CComboBox	m_base;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MemoryHack)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MemoryHack)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnCustomsearchRad();
	afx_msg void OnFullsearchRad();
	afx_msg void OnCustomizeBtn();
	afx_msg void OnSearchBut();
	afx_msg void OnReadValues();
	afx_msg void OnRnfbut();
	afx_msg void OnPatchbut();
	afx_msg void OnRclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMORYHACK_H__79FD0C8B_C9D1_43F7_AA43_3BAF860553AA__INCLUDED_)
