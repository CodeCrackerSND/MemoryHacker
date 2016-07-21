#if !defined(AFX_MEMORYBLOCK_H__501EDED6_DA94_4AB4_B454_F56BDEE562A2__INCLUDED_)
#define AFX_MEMORYBLOCK_H__501EDED6_DA94_4AB4_B454_F56BDEE562A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MemoryBlock.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MemoryBlock dialog

class MemoryBlock : public CDialog
{
// Construction
public:
	MemoryBlock(CWnd* pParent = NULL);   // standard constructor
	MemoryBlock& operator=(MemoryBlock& right); // Overload Assignment Operator
	void GetVirtualMemories();
	void RefreshVirtualMemoriesList();

	CString processname;
	int processid;
	int vmem_counts;
	MEMORY_BASIC_INFORMATION* valid_mems;

	enum SetType { MemoryBlockT, StartAddressT, EndAddressT };
	SetType settype;

// Dialog Data
	//{{AFX_DATA(MemoryBlock)
	enum { IDD = IDD_MEMORYBLOCK_DIALOG };
	CListCtrl	m_cListCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MemoryBlock)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MemoryBlock)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMORYBLOCK_H__501EDED6_DA94_4AB4_B454_F56BDEE562A2__INCLUDED_)
