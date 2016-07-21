#if !defined(AFX_NEWEDIT_H__C7ADE44F_91C6_4741_BE27_5A11F8D50BAF__INCLUDED_)
#define AFX_NEWEDIT_H__C7ADE44F_91C6_4741_BE27_5A11F8D50BAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// NewEdit window

class NewEdit : public CEdit
{
// Construction
public:
	NewEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NewEdit)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~NewEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(NewEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWEDIT_H__C7ADE44F_91C6_4741_BE27_5A11F8D50BAF__INCLUDED_)
