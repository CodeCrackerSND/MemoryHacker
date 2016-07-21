// MemoryHackerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MemoryHacker.h"
#include "MemoryHackerDlg.h"
#include "GenericPurposeMethods.h"

#include "C:\Program Files (x86)\Microsoft SDK\include\Psapi.h"
#pragma comment (lib, "Psapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMemoryHackerDlg dialog

CMemoryHackerDlg::CMemoryHackerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMemoryHackerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMemoryHackerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMemoryHackerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMemoryHackerDlg)
	DDX_Control(pDX, IDC_LIST1, m_cListCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMemoryHackerDlg, CDialog)
	//{{AFX_MSG_MAP(CMemoryHackerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemoryHackerDlg message handlers

BOOL CMemoryHackerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	DWORD dwStyle = m_cListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;

	// Setup the list control
	m_cListCtrl.SetExtendedStyle(dwStyle);

	// Create the columns
	CRect rect;
	m_cListCtrl.GetClientRect(&rect);
	int size = rect.Width()/3-16;
	m_cListCtrl.InsertColumn(0, _T("ProcessName"), LVCFMT_LEFT, size*2);
	m_cListCtrl.InsertColumn(1, _T("pid"), LVCFMT_LEFT, size);

	RefreshProcessList();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMemoryHackerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMemoryHackerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


BOOL CMemoryHackerDlg::EnableDebugPrivileges()
{
    HANDLE tokenHandle;
    LUID luid;
    TOKEN_PRIVILEGES newPrivileges;

    if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &tokenHandle))
        return FALSE;

    if(!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid))
    {
        CloseHandle(tokenHandle);
        return FALSE;
    }

    newPrivileges.PrivilegeCount = 1;
    newPrivileges.Privileges[0].Luid = luid;
    newPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if(!AdjustTokenPrivileges(tokenHandle, FALSE, &newPrivileges, sizeof(newPrivileges), NULL, NULL))
    {
        CloseHandle(tokenHandle);
        return FALSE;
    }

   CloseHandle(tokenHandle);

   return TRUE;
}

void CMemoryHackerDlg::RefreshProcessList()
{

	m_cListCtrl.DeleteAllItems();  // clean old items!

	EnableDebugPrivileges();  // enable debug privileges for this process
    // Get the list of process identifiers.
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
    return;

    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof(DWORD);

    // The name and process identifier for each process.
    for ( i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[i] != 0 )
        {
        TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");


    // Get a handle to the process.
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, aProcesses[i] );

	// DWORD Error = GetLastError();
    // Get the process name.
    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), 
             &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName, 
                               sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }

    // Add the process name and identifier.
	LVITEM lvi;
	CString strItem;

	// Insert the first item
	lvi.mask =  LVIF_TEXT;
	lvi.iItem = m_cListCtrl.GetItemCount(); // this starts with 0!
	
	// insert subitem 0
	lvi.iSubItem = 0;
	lvi.pszText = (LPTSTR)(szProcessName);
	m_cListCtrl.InsertItem(&lvi);

	CString cpid;
	cpid.Format(_T("%d"), aProcesses[i]);
	// insert subitem 1
	lvi.iSubItem =1;
	lvi.pszText = (char*)LPCTSTR(cpid);
	m_cListCtrl.SetItem(&lvi);

    // Release the handle to the process.
    CloseHandle( hProcess );
        }
    }
}


void CMemoryHackerDlg::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
CMenu menu;
menu.LoadMenu(IDR_PROCESS_MENU); // our context menu
CMenu* pPopup = menu.GetSubMenu(0);

RECT rect;
GetWindowRect(&rect);
CPoint mousepos;
GetCursorPos(&mousepos);
pPopup->TrackPopupMenu(NULL,mousepos.x,mousepos.y, this); 

// The menu is a temporary MFC object, no need to delete it.
	*pResult = 0;
}

BOOL CMemoryHackerDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (HIWORD(wParam) == BN_CLICKED)  // if button clicked
    {
		switch(LOWORD(wParam))  // Retrieves the low-order word from the specified value.
        {
        case ID_PROCESS_MEMORYHACK:
		{
		if (!IsWindow(memoryhackdlg.m_hWnd)||!memoryhackdlg.IsWindowVisible())
		{
		
		MemoryHack m_pmhdialog = new MemoryHack(this);
		memoryhackdlg = m_pmhdialog;
		POSITION pos = m_cListCtrl.GetFirstSelectedItemPosition();
		int position = m_cListCtrl.GetNextSelectedItem(pos);
		
		memoryhackdlg.processname = m_cListCtrl.GetItemText(position, 0);  // item number, subitem number
		CString pid_str = m_cListCtrl.GetItemText(position, 1);  // 1 since we need process id
		memoryhackdlg.processid = GenericPurposeMethods::StringToNumber(pid_str.GetBuffer(pid_str.GetLength()));
		//testdlg.DoModal();  // not modal one!
		BOOL ret = memoryhackdlg.Create(IDD_MEMORYHACK_DIALOG,this);
		if (ret)   // If create not failed.
		memoryhackdlg.ShowWindow(SW_SHOWNORMAL);
		}
		
        break;
		}

		case ID_PROCESS_REFRESH:
		RefreshProcessList();
        break;

        }
		
    }

	return CDialog::OnCommand(wParam, lParam);
}
