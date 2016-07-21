// MemoryBlock.cpp : implementation file
//

#include "stdafx.h"
#include "MemoryHacker.h"
#include "MemoryBlock.h"
#include "GenericPurposeMethods.h"
#include "CustomizeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MemoryBlock dialog


MemoryBlock::MemoryBlock(CWnd* pParent /*=NULL*/)
	: CDialog(MemoryBlock::IDD, pParent)
{
	//{{AFX_DATA_INIT(MemoryBlock)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MemoryBlock::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MemoryBlock)
	DDX_Control(pDX, IDC_LIST1, m_cListCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MemoryBlock, CDialog)
	//{{AFX_MSG_MAP(MemoryBlock)
	ON_WM_CLOSE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MemoryBlock message handlers

MemoryBlock& MemoryBlock::operator=(MemoryBlock& right)
{
// right contains value to be set
// this contains old value
(*this).m_hWnd = right.m_hWnd;
return *this;

}

void MemoryBlock::GetVirtualMemories()
{

	vmem_counts = 0;
	valid_mems = new MEMORY_BASIC_INFORMATION[2000];  // 2000 should be enough

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processid);

	if (hProcess==NULL) return;

	unsigned int Start = 0;
    SYSTEM_INFO si;
	GetSystemInfo(&si);
	while (Start < (unsigned int)si.lpMaximumApplicationAddress)
    {
        MEMORY_BASIC_INFORMATION mbi;
        VirtualQueryEx( hProcess,
                        (void *)Start,
                        &mbi,
                        sizeof(MEMORY_BASIC_INFORMATION));

		// mbi.State == MEM_PRIVATE / MEM_IMAGE / MEM_MAPPED - never used
		// mbi.State == MEM_RESERVE / MEM_FREE - used but is not what we want
		// mbi.State == MEM_COMMIT - that's what we want
		//  && (mbi.Protect == PAGE_GUARD||mbi.Protect != PAGE_NOACCESS)

        if (mbi.State == MEM_COMMIT)
		{
		valid_mems[vmem_counts]=mbi;
		vmem_counts++;


		}

        if(Start + mbi.RegionSize < Start) break;
        Start += mbi.RegionSize;
    }  // end of while memory
	CloseHandle(hProcess);



} // end of GetVirtualMemories method


BOOL MemoryBlock::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	DWORD dwStyle = m_cListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;

	// Setup the list control
	m_cListCtrl.SetExtendedStyle(dwStyle);

	// Create the columns
	CRect rect;
	m_cListCtrl.GetClientRect(&rect);
	int size = rect.Width()/3-16;
	m_cListCtrl.InsertColumn(0, _T("Base Address"), LVCFMT_LEFT, size);
	m_cListCtrl.InsertColumn(1, _T("Size"), LVCFMT_LEFT, size);
	m_cListCtrl.InsertColumn(2, _T("Protection"), LVCFMT_LEFT, size);

	MemoryBlock::RefreshVirtualMemoriesList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void MemoryBlock::RefreshVirtualMemoriesList()
{
	m_cListCtrl.DeleteAllItems();  // clean old items!
	MemoryBlock::GetVirtualMemories();


	// Add the process name and identifier.
	for (int i=0;i<vmem_counts;i++)
	{
	LVITEM lvi;
	CString strItem;

	// Insert the first item
	lvi.mask =  LVIF_TEXT;
	lvi.iItem = m_cListCtrl.GetItemCount(); // this starts with 0!
	
	// insert subitem 0
	lvi.iSubItem = 0;


	char baseaddress[20];
	baseaddress[0] = 00;
	wsprintf(baseaddress,"%X",valid_mems[i].BaseAddress);  // convert number to hex string
	
	int len = 8-strlen(baseaddress); // get the missing part size
	memmove(baseaddress+len,baseaddress,strlen(baseaddress)); // move the string characters to the end
	for ( int j = 0; j < len; j++ ) // fill the beginning characters with '0'
    baseaddress[j] = '0';

	baseaddress[8] = 0;  // place the 00 end char at the end of string!

	lvi.pszText = (char*)LPCTSTR(baseaddress);
	m_cListCtrl.InsertItem(&lvi);

	char resionsize[20];
	wsprintf(resionsize,"%X",valid_mems[i].RegionSize);  // convert number to hex string
	
	len = 8-strlen(resionsize); // get the missing part size
	memmove(resionsize+len,resionsize,strlen(resionsize)); // move the string characters to the end
	for (j = 0; j < len; j++ ) // fill the beginning characters with '0'
    resionsize[j] = '0';

	resionsize[8] = 0;  // place the 00 end char at the end of string!

	// insert subitem 1
	lvi.iSubItem = 1;
	lvi.pszText = (char*)LPCTSTR(resionsize);
	m_cListCtrl.SetItem(&lvi);

	char memprot[20];
	wsprintf(memprot,"%X",valid_mems[i].Protect);

	TCHAR* prot_parsed = (TCHAR*)GenericPurposeMethods::GetMemoryProtectionInfo((unsigned int)valid_mems[i].Protect);
	TCHAR* prot_info = GenericPurposeMethods::JoinChars(memprot," (");
	prot_info = GenericPurposeMethods::JoinChars(prot_info,prot_parsed);
	prot_info = GenericPurposeMethods::JoinChars(prot_info,")");
	
	// insert subitem 2
	lvi.iSubItem = 2;
	lvi.pszText = (char*)LPCTSTR(prot_info);
	m_cListCtrl.SetItem(&lvi);



	}

}

void MemoryBlock::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	this->DestroyWindow();  // destroy the window
	CDialog::OnClose();
}

void MemoryBlock::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	 POSITION pos = m_cListCtrl.GetFirstSelectedItemPosition();
	 int position = m_cListCtrl.GetNextSelectedItem(pos);

	 if (position>=0)
	 {
	 unsigned int base_address = (unsigned int)valid_mems[position].BaseAddress;

	 if (settype == MemoryBlock::SetType::MemoryBlockT||settype == MemoryBlock::SetType::StartAddressT)
	 CCustomizeDlg::UpdateStartAddress((unsigned int)base_address);

	 unsigned int end_address = base_address+(unsigned int)valid_mems[position].RegionSize;
	 if (settype == MemoryBlock::SetType::MemoryBlockT)
	 CCustomizeDlg::UpdateEndAddress(end_address);

	 if (settype == MemoryBlock::SetType::EndAddressT)
	 CCustomizeDlg::UpdateEndAddress((unsigned int)base_address);


	 }

	*pResult = 0;
}
