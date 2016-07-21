// InspectMemory.cpp : implementation file
//

#include "stdafx.h"
#include "MemoryHacker.h"
#include "InspectMemory.h"
#include "GenericPurposeMethods.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// InspectMemory dialog


InspectMemory::InspectMemory(CWnd* pParent /*=NULL*/)
	: CDialog(InspectMemory::IDD, pParent)
{
	//{{AFX_DATA_INIT(InspectMemory)
	//}}AFX_DATA_INIT
}


void InspectMemory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InspectMemory)
	DDX_Control(pDX, IDC_EDIT_RESULT, m_result_edit);
	DDX_Control(pDX, IDC_EDIT_BRBYTES, m_edit_2);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(InspectMemory, CDialog)
	//{{AFX_MSG_MAP(InspectMemory)
	ON_BN_CLICKED(IDC_INSPECTBUT, OnInspectbut)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InspectMemory message handlers

void InspectMemory::OnInspectbut() 
{
	// TODO: Add your control notification handler code here
	
	char address_str[9];
	m_edit1.GetWindowText(address_str, 9);
	if (address_str[0]==0) return;

	char size_str[9];
	m_edit_2.GetWindowText(size_str, 9);
	if (size_str[0]==0) return;

	unsigned int caddress = GenericPurposeMethods::ConvertHexStringToInt(address_str);

	int size = GenericPurposeMethods::StringToNumber(size_str);

	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                               FALSE, processid);

	if (hProcess==NULL)
	return;


	unsigned long dwTotalRead;

	char* valuestr = new char[1];
	valuestr[0] = 00;

	unsigned char* valbytes = new unsigned char[size];
	int isok = ReadProcessMemory(hProcess, (LPVOID)caddress, valbytes,
							 size, &dwTotalRead);

	if (isok != 0)  // if read didn't failed
	{
	valuestr = GenericPurposeMethods::BytesToString(valbytes, size, CString(_T("bytes")).GetBuffer(0), CString(_T("hexadecimal")).GetBuffer(0));
	}
	else
	{
	valuestr = _T("Read failed!!!");
	}


m_result_edit.SetWindowText(valuestr);


}


InspectMemory& InspectMemory::operator=(InspectMemory& right)
{
// right contains value to be set
// this contains old value
(*this).m_hWnd = right.m_hWnd;
return *this;

}

BOOL InspectMemory::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_edit1.SetWindowText(address_str);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void InspectMemory::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	this->DestroyWindow();  // destroy the window
	CDialog::OnClose();
}
