// CustomizeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MemoryHacker.h"
#include "MemoryHack.h"
#include "CustomizeDlg.h"
#include "GenericPurposeMethods.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizeDlg dialog


CCustomizeDlg::CCustomizeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomizeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomizeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCustomizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizeDlg)
	DDX_Control(pDX, IDC_LIST1, m_cListCtrl);
	DDX_Control(pDX, IDC_STARTA_EDIT, m_endaddress);
	DDX_Control(pDX, IDC_ENDA_EDIT, m_startaddress);
	//}}AFX_DATA_MAP
}

CCustomizeDlg& CCustomizeDlg::operator=(CCustomizeDlg& right)
{
// right contains value to be set
// this contains old value
(*this).m_hWnd = right.m_hWnd;
return *this;

}


BEGIN_MESSAGE_MAP(CCustomizeDlg, CDialog)
	//{{AFX_MSG_MAP(CCustomizeDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_MODULE_BUT, OnModuleBut)
	ON_BN_CLICKED(IDC_BLOCK_BUT, OnBlockBut)
	ON_BN_CLICKED(IDC_PICK_START, OnPickStart)
	ON_BN_CLICKED(IDC_PICK_END, OnPickEnd)
	ON_BN_CLICKED(IDC_ADD_BUT, OnAddBut)
	ON_BN_CLICKED(IDC_CLEARALL_BUT, OnClearallBut)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizeDlg message handlers

void CCustomizeDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	this->DestroyWindow();  // destroy the window
	CDialog::OnClose();
}

void CCustomizeDlg::UpdateStartAddress(unsigned int address)
{
	char straddress[20];
	wsprintf(straddress,"%X", address);  // convert number to hex string
	
	int len = 8-strlen(straddress); // get the missing part size
	memmove(straddress+len,straddress,strlen(straddress)); // move the string characters to the end
	for ( int i = 0; i < len; i++ ) // fill the beginning characters with '0'
    straddress[i] = '0';

	straddress[8] = 0;  // place the 00 end char at the end of string!

	CWnd *pWnd = instance.GetDlgItem(IDC_STARTA_EDIT);
	pWnd->SetWindowText(straddress);

}

void CCustomizeDlg::UpdateEndAddress(unsigned int address)
{

	char straddress[20];
	wsprintf(straddress,"%X", address);  // convert number to hex string
	
	int len = 8-strlen(straddress); // get the missing part size
	memmove(straddress+len,straddress,strlen(straddress)); // move the string characters to the end
	for ( int i = 0; i < len; i++ ) // fill the beginning characters with '0'
    straddress[i] = '0';

	straddress[8] = 0;  // place the 00 end char at the end of string!

	CWnd *pWnd = instance.GetDlgItem(IDC_ENDA_EDIT);
	pWnd->SetWindowText(straddress);

}

CCustomizeDlg CCustomizeDlg::instance;  // need for static members

BOOL CCustomizeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//CCustomizeDlg m_pmhdialog = new CCustomizeDlg(this);
	instance = (CCustomizeDlg)this;
	instance.m_hWnd = this->m_hWnd;
	CCustomizeDlg::UpdateStartAddress(01);
	CCustomizeDlg::UpdateEndAddress(02);

	DWORD dwStyle = m_cListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;

	// Setup the list control
	m_cListCtrl.SetExtendedStyle(dwStyle);

	// Create the columns
	CRect rect;
	m_cListCtrl.GetClientRect(&rect);
	int size = rect.Width()/2-16;
	m_cListCtrl.InsertColumn(0, _T("Start Address"), LVCFMT_LEFT, size);
	m_cListCtrl.InsertColumn(1, _T("End Address"), LVCFMT_LEFT, size);

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomizeDlg::OnModuleBut() 
{
	// TODO: Add your control notification handler code here
		if (!IsWindow(modulesdlg.m_hWnd)||!modulesdlg.IsWindowVisible())
		{
		
		ModulesDlg m_pmodulesdialog = new ModulesDlg(this);
		modulesdlg = m_pmodulesdialog;		
		modulesdlg.processname = processname;
		modulesdlg.processid = processid;
		//testdlg.DoModal();  // not modal one!
		BOOL ret = modulesdlg.Create(IDD_MODULESDLG_DIALOG,this);
		if (ret)   // If create not failed.
		modulesdlg.ShowWindow(SW_SHOWNORMAL);
		}

}

void CCustomizeDlg::OnBlockBut() 
{
	// TODO: Add your control notification handler code here
		if (!IsWindow(memblockdlg.m_hWnd)||!memblockdlg.IsWindowVisible())
		{
		
		MemoryBlock m_pmodulesdialog = new MemoryBlock(this);
		memblockdlg = m_pmodulesdialog;		
		memblockdlg.processname = processname;
		memblockdlg.processid = processid;
		memblockdlg.settype = MemoryBlock::SetType::MemoryBlockT;
		//testdlg.DoModal();  // not modal one!
		BOOL ret = memblockdlg.Create(IDD_MEMORYBLOCK_DIALOG,this);
		if (ret)   // If create not failed.
		memblockdlg.ShowWindow(SW_SHOWNORMAL);
		}
}

void CCustomizeDlg::OnPickStart() 
{
	// TODO: Add your control notification handler code here
		if (!IsWindow(memblockdlg.m_hWnd)||!memblockdlg.IsWindowVisible())
		{
		
		MemoryBlock m_pmodulesdialog = new MemoryBlock(this);
		memblockdlg = m_pmodulesdialog;		
		memblockdlg.processname = processname;
		memblockdlg.processid = processid;
		memblockdlg.settype = MemoryBlock::SetType::StartAddressT;
		//testdlg.DoModal();  // not modal one!
		BOOL ret = memblockdlg.Create(IDD_MEMORYBLOCK_DIALOG,this);
		if (ret)   // If create not failed.
		memblockdlg.ShowWindow(SW_SHOWNORMAL);
		}
}

void CCustomizeDlg::OnPickEnd() 
{
	// TODO: Add your control notification handler code here
		if (!IsWindow(memblockdlg.m_hWnd)||!memblockdlg.IsWindowVisible())
		{
		
		MemoryBlock m_pmodulesdialog = new MemoryBlock(this);
		memblockdlg = m_pmodulesdialog;		
		memblockdlg.processname = processname;
		memblockdlg.processid = processid;
		memblockdlg.settype = MemoryBlock::SetType::EndAddressT;
		//testdlg.DoModal();  // not modal one!
		BOOL ret = memblockdlg.Create(IDD_MEMORYBLOCK_DIALOG,this);
		if (ret)   // If create not failed.
		memblockdlg.ShowWindow(SW_SHOWNORMAL);
		}
}

void CCustomizeDlg::RefreshList()
{

	// Add the memory custom search:
	for (int i=0;i<MemoryHack::custom_count;i++)
	{
	LVITEM lvi;
	CString strItem;

	// Insert the first item
	lvi.mask =  LVIF_TEXT;
	lvi.iItem = m_cListCtrl.GetItemCount(); // this starts with 0!
	
	// insert subitem 0
	lvi.iSubItem = 0;

	char startaddress[20];
	wsprintf(startaddress,"%X",MemoryHack::start_addresses[i]);  // convert number to hex string
	
	int len = 8-strlen(startaddress); // get the missing part size
	memmove(startaddress+len,startaddress,strlen(startaddress)); // move the string characters to the end
	for ( int j = 0; j < len; j++ ) // fill the beginning characters with '0'
    startaddress[j] = '0';

	startaddress[8] = 0;  // place the 00 end char at the end of string!

	lvi.pszText = (LPTSTR)(startaddress);
	m_cListCtrl.InsertItem(&lvi);



	// insert subitem 1
	lvi.iSubItem = 1;

	char endaddress[20];
	wsprintf(endaddress,"%X",MemoryHack::end_addresses[i]);  // convert number to hex string
	
	len = 8-strlen(endaddress); // get the missing part size
	memmove(endaddress+len,endaddress,strlen(endaddress)); // move the string characters to the end
	for (j = 0; j < len; j++ ) // fill the beginning characters with '0'
    endaddress[j] = '0';

	endaddress[8] = 0;  // place the 00 end char at the end of string!

	lvi.pszText = (char*)LPCTSTR(endaddress);

	m_cListCtrl.SetItem(&lvi);

	}

}

void CCustomizeDlg::OnAddBut() 
{
	// TODO: Add your control notification handler code here
	char start_address[9];
	GetDlgItem(IDC_STARTA_EDIT)->GetWindowText(start_address, 9);

	char end_address[9];
	GetDlgItem(IDC_ENDA_EDIT)->GetWindowText(end_address, 9);

if (strlen(start_address)<=0||strlen(end_address)<=0)
return;

unsigned int start_address_c = GenericPurposeMethods::ConvertHexStringToInt(start_address);
unsigned int end_address_c = GenericPurposeMethods::ConvertHexStringToInt(end_address);

	LVITEM lvi;
	CString strItem;

	// Insert the first item
	lvi.mask =  LVIF_TEXT;
	lvi.iItem = m_cListCtrl.GetItemCount(); // this starts with 0!

	// insert subitem 0
	lvi.iSubItem = 0;
	lvi.pszText = (LPTSTR)(start_address);
	m_cListCtrl.InsertItem(&lvi);

	// insert subitem 1
	lvi.iSubItem = 1;
	lvi.pszText = (char*)LPCTSTR(end_address);
	m_cListCtrl.SetItem(&lvi);


MemoryHack::start_addresses[MemoryHack::custom_count] = start_address_c;
MemoryHack::end_addresses[MemoryHack::custom_count] = end_address_c;
MemoryHack::custom_count++; // increment custom count

}

void CCustomizeDlg::OnClearallBut() 
{
	// TODO: Add your control notification handler code here

	m_cListCtrl.DeleteAllItems();  // clean old items!
	MemoryHack::custom_count = 0;

}

void CCustomizeDlg::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
CMenu menu;
menu.LoadMenu(IDR_CUSTOM_MENU); // our context menu
CMenu* pPopup = menu.GetSubMenu(0);

RECT rect;
GetWindowRect(&rect);
CPoint mousepos;
GetCursorPos(&mousepos);
pPopup->TrackPopupMenu(NULL,mousepos.x,mousepos.y, this); 

// The menu is a temporary MFC object, no need to delete it.
	*pResult = 0;
}

BOOL CCustomizeDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (HIWORD(wParam) == BN_CLICKED)  // if button clicked
    {
		switch(LOWORD(wParam))  // Retrieves the low-order word from the specified value.
        {
        case ID_CUSTOMMENU_REMOVESELECTED:
		{
		RemoveSelected();
		break;
		}

		}

	}

	return CDialog::OnCommand(wParam, lParam);
}

void CCustomizeDlg::RemoveSelected()
{
int selectcount = 0;
int* selected_indexes = new int[2000];

int nRow = m_cListCtrl.GetNextItem(-1, LVNI_SELECTED);
while (nRow != -1)
{

if (nRow<MemoryHack::custom_count)  // if valid add it!
{
selected_indexes[selectcount]=nRow;
selectcount++;
}

nRow = m_cListCtrl.GetNextItem(nRow, LVNI_SELECTED);
}

if (selectcount == 0) return;

	for (int i=selectcount-1;i>=0;i--)
	{
	
	for (int j=selected_indexes[i];j<MemoryHack::custom_count;j++)
	{
    
	MemoryHack::start_addresses[j] = MemoryHack::start_addresses[j+1];
	MemoryHack::end_addresses[j] = MemoryHack::end_addresses[j+1];

	}

	}

	MemoryHack::custom_count = MemoryHack::custom_count-selectcount;

	for (i=selectcount-1;i>=0;i--)
	{
	 m_cListCtrl.DeleteItem(selected_indexes[i]);  // delete item from ClistCtrl
	}


}
