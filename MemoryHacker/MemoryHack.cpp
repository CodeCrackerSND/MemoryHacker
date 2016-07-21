// MemoryHack.cpp : implementation file
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
// MemoryHack dialog


MemoryHack::MemoryHack(CWnd* pParent /*=NULL*/)
	: CDialog(MemoryHack::IDD, pParent)
{
	//{{AFX_DATA_INIT(MemoryHack)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

MemoryHack& MemoryHack::operator=(MemoryHack& right)
{
// right contains value to be set
// this contains old value
(*this).m_hWnd = right.m_hWnd;
return *this;

}


void MemoryHack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MemoryHack)
	DDX_Control(pDX, IDC_LIST2, m_cListCtrl);
	DDX_Control(pDX, IDC_TYPE_COMBO, m_type);
	DDX_Control(pDX, IDC_BASE_COMBO, m_base);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MemoryHack, CDialog)
	//{{AFX_MSG_MAP(MemoryHack)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CUSTOMSEARCH_RAD, OnCustomsearchRad)
	ON_BN_CLICKED(IDC_FULLSEARCH_RAD, OnFullsearchRad)
	ON_BN_CLICKED(IDC_CUSTOMIZE_BTN, OnCustomizeBtn)
	ON_BN_CLICKED(IDC_SEARCH_BUT, OnSearchBut)
	ON_BN_CLICKED(IDC_READ_VALUES, OnReadValues)
	ON_BN_CLICKED(IDC_RNFBUT, OnRnfbut)
	ON_BN_CLICKED(IDC_PATCHBUT, OnPatchbut)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, OnRclickList2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MemoryHack message handlers

// these are needed for static members:
int MemoryHack::custom_count;
unsigned int MemoryHack::start_addresses[2000];
unsigned int MemoryHack::end_addresses[2000];

BOOL MemoryHack::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char window_title[500];
	this->GetWindowText(window_title,sizeof(window_title));
	strcat(window_title, processname);
	this->SetWindowText(window_title);

	CButton *m_ctlRadio = (CButton*) GetDlgItem(IDC_FULLSEARCH_RAD);
	m_ctlRadio->SetCheck(BST_CHECKED);// check IDC_FULLSEARCH_RAD

	CButton* pCustomizebtn = (CButton*)GetDlgItem(IDC_CUSTOMIZE_BTN);
	pCustomizebtn->EnableWindow(false);  // disable button


	MemoryHack::custom_count = 0;  // init custom count with 0

	// populate type combo:
	m_type.AddString("byte");
	m_type.AddString("word");
	int dword_index = m_type.AddString("dword");
	m_type.AddString("qword");
	m_type.AddString("bytes");
	m_type.AddString("ASCII string");
	m_type.AddString("UNICODE string");
	m_type.AddString("float");
	m_type.AddString("double");
	m_type.SetCurSel(dword_index);

	int dec_index = m_base.AddString("decimal");
	m_base.AddString("hexadecimal");
	m_base.SetCurSel(dec_index);

	DWORD dwStyle = m_cListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;

	// Setup the list control
	m_cListCtrl.SetExtendedStyle(dwStyle);

	// Create the columns
	CRect rect;
	m_cListCtrl.GetClientRect(&rect);
	int size = rect.Width()/2-16;
	m_cListCtrl.InsertColumn(0, _T("Address"), LVCFMT_LEFT, size);
	m_cListCtrl.InsertColumn(1, _T("Value"), LVCFMT_LEFT, size);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void MemoryHack::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	this->DestroyWindow();  // destroy the window
	CDialog::OnClose();
}

void MemoryHack::OnCustomsearchRad() 
{
	// TODO: Add your control notification handler code here
	MemoryHack::SetCustomizeBtnEnabled();
}

void MemoryHack::OnFullsearchRad() 
{
	// TODO: Add your control notification handler code here
	MemoryHack::SetCustomizeBtnEnabled();
}

void MemoryHack::SetCustomizeBtnEnabled()
{
CButton* pCustomizebtn = (CButton*)GetDlgItem(IDC_CUSTOMIZE_BTN);
CButton* pCustomsearchRad = (CButton*)GetDlgItem(IDC_CUSTOMSEARCH_RAD);
CButton* pFullsearchRad = (CButton*)GetDlgItem(IDC_FULLSEARCH_RAD);

if (pCustomsearchRad->GetCheck()==1)
pCustomizebtn->EnableWindow(true);  // enable button

if (pFullsearchRad->GetCheck()==1)
pCustomizebtn->EnableWindow(false);  // disable button

}

void MemoryHack::OnCustomizeBtn() 
{
	// TODO: Add your control notification handler code here
	
		if (!IsWindow(customizedlg.m_hWnd)||!customizedlg.IsWindowVisible())
		{
		
		CCustomizeDlg m_cddialog = new CCustomizeDlg(this);
		customizedlg = m_cddialog;
		customizedlg.processname = processname;
		customizedlg.processid = processid;
		//testdlg.DoModal();  // not modal one!
		BOOL ret = customizedlg.Create(IDD_CUSTOMIZEDLG_DIALOG,this);
		if (ret)   // If create not failed.
		customizedlg.ShowWindow(SW_SHOWNORMAL);
		}

}

void MemoryHack::GetVirtualMemories()
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

bool MemoryHack::MemoryInRange(unsigned int address) 
{

for (int i=0;i<MemoryHack::custom_count;i++)
{
if (address>=MemoryHack::start_addresses[i]&&address<MemoryHack::end_addresses[i])
return true;
}

return false;
}

void MemoryHack::OnSearchBut() 
{
	// TODO: Add your control notification handler code here

	CWnd* statusWnd = GetDlgItem(IDC_STATUS_STATIC);

	int row = m_type.GetCurSel();
    if (row < 0)
	{
		statusWnd->SetWindowText(_T("No sel for type!"));
		return;
	}

    CString search_type;
    m_type.GetLBText(row, search_type);
	if (search_type.GetLength()==0)
	{
		statusWnd->SetWindowText(_T("Type text len can be 0!"));
		return;
	}

    row = m_base.GetCurSel();
    if(row < 0)
	{
		statusWnd->SetWindowText(_T("No sel for base!"));
		return;
	}

    CString base;
    m_base.GetLBText(row, base);
	if (base.GetLength()==0)
	{
		statusWnd->SetWindowText(_T("Base text len can be 0!"));
		return;
	}

	char value_to_search_str[500];
	GetDlgItem(IDC_VALUETOSEARCH_EDIT)->GetWindowText(value_to_search_str, 500);

	if (value_to_search_str[0]==0)
	{
		statusWnd->SetWindowText(_T("Value to search len can be 0!"));
		return;
	}

	m_cListCtrl.DeleteAllItems();  // clean old items!
	MemoryHack::GetVirtualMemories();

	//char end_address[500];
	//GetDlgItem(IDC_ENDA_EDIT)->GetWindowText(end_address, 9);
int search_len = 0;
unsigned char* to_search_val = GenericPurposeMethods::StringToBytes(value_to_search_str, search_type.GetBuffer(0), base.GetBuffer(0), &search_len);


	if (search_len==0)
	{
		statusWnd->SetWindowText(_T("Failed to convert value to search!"));
		return;
	}

	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                               FALSE, processid);


	if (hProcess==NULL)
	{
	statusWnd->SetWindowText(_T("Failed to open the process!"));
	return;
	}


bool Fullsearch = false;
bool Customsearch = false;

CButton* pCustomsearchRad = (CButton*)GetDlgItem(IDC_CUSTOMSEARCH_RAD);
CButton* pFullsearchRad = (CButton*)GetDlgItem(IDC_FULLSEARCH_RAD);

if (pCustomsearchRad->GetCheck()==1)
Customsearch = true;

if (pFullsearchRad->GetCheck()==1)
Fullsearch = true;

	unsigned long dwTotalRead;
	unsigned char* buf;


	for (int i=0;i<vmem_counts;i++)
	{

buf = new unsigned char[valid_mems[i].RegionSize];
int isok = ReadProcessMemory(hProcess, (LPVOID)valid_mems[i].BaseAddress, buf,
							 valid_mems[i].RegionSize, &dwTotalRead);

if (isok != 0)  // if read didn't failed
{


	for (int k=0;k<(int)valid_mems[i].RegionSize;k++)
	{
	unsigned int faddress = (unsigned int)valid_mems[i].BaseAddress+(unsigned int)k;

	if (Customsearch&&!MemoryHack::MemoryInRange(faddress))
	continue;

	if (buf[k]==to_search_val[0])
	{  // if first byte there:

	bool are_equal = true;
	for (int l=0;l<search_len;l++)
	{

	if ((k+l)>=(int)valid_mems[i].RegionSize)
	{  // if k+l (index) bigger or equal then buf size
	are_equal = false;
	break;
	}


	if (buf[k+l]!=to_search_val[l])
	{
	are_equal = false;
	break;
	}

	}

	if (are_equal)
	{  // if something found

	LVITEM lvi;
	CString strItem;

	// Insert the first item
	lvi.mask =  LVIF_TEXT;
	lvi.iItem = m_cListCtrl.GetItemCount(); // this starts with 0!
	
	// insert subitem 0
	lvi.iSubItem = 0;

	char baseaddress[20];
	baseaddress[0] = 00;
	wsprintf(baseaddress,"%X",faddress);  // convert number to hex string
	
	int len = 8-strlen(baseaddress); // get the missing part size
	memmove(baseaddress+len,baseaddress,strlen(baseaddress)); // move the string characters to the end
	for ( int j = 0; j < len; j++ ) // fill the beginning characters with '0'
	baseaddress[j] = '0';

	baseaddress[8] = 0;  // place the 00 end char at the end of string!

	lvi.pszText = (char*)LPCTSTR(baseaddress);
	m_cListCtrl.InsertItem(&lvi);


	char* valuestr = new char[1];
	valuestr[0] = 00;

	unsigned char* valbytes = new unsigned char[search_len];
	int isok = ReadProcessMemory(hProcess, (LPVOID)faddress, valbytes,
							 search_len, &dwTotalRead);

	if (isok != 0)  // if read didn't failed
	{
	valuestr = GenericPurposeMethods::BytesToString(valbytes,search_len, search_type.GetBuffer(0), base.GetBuffer(0));
	}

	// insert subitem 1
	lvi.iSubItem = 1;
	lvi.pszText = (char*)LPCTSTR(valuestr);
	m_cListCtrl.SetItem(&lvi);


	}

	}  // end of if first byte equal



	} // end of for valid_mems[i].RegionSize!

}  // end of isok

delete[] buf;

	}



	CloseHandle(hProcess);


}

void MemoryHack::OnReadValues() 
{
	// TODO: Add your control notification handler code here

	CWnd* statusWnd = GetDlgItem(IDC_STATUS_STATIC);

	int row = m_type.GetCurSel();
    if (row < 0)
	{
		statusWnd->SetWindowText(_T("No sel for type!"));
		return;
	}

    CString search_type;
    m_type.GetLBText(row, search_type);
	if (search_type.GetLength()==0)
	{
		statusWnd->SetWindowText(_T("Type text len can be 0!"));
		return;
	}

    row = m_base.GetCurSel();
    if(row < 0)
	{
		statusWnd->SetWindowText(_T("No sel for base!"));
		return;
	}

    CString base;
    m_base.GetLBText(row, base);
	if (base.GetLength()==0)
	{
		statusWnd->SetWindowText(_T("Base text len can be 0!"));
		return;
	}

	char value_to_search_str[500];
	GetDlgItem(IDC_VALUETOSEARCH_EDIT)->GetWindowText(value_to_search_str, 500);

	if (value_to_search_str[0]==0)
	{
		statusWnd->SetWindowText(_T("Value to search len can be 0!"));
		return;
	}

int nLastItem = m_cListCtrl.GetItemCount();	//gets the number of ListView items in the CListCtrl

	if (nLastItem<=0)
	{
		statusWnd->SetWindowText(_T("List doesn't contain any address!!!"));
		return;
	}

int search_len = 0;
unsigned char* to_search_val = GenericPurposeMethods::StringToBytes(value_to_search_str, search_type.GetBuffer(0), base.GetBuffer(0), &search_len);


	if (search_len==0)
	{
		statusWnd->SetWindowText(_T("Failed to convert value to search!"));
		return;
	}

	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                               FALSE, processid);


	if (hProcess==NULL)
	{
	statusWnd->SetWindowText(_T("Failed to open the process!"));
	return;
	}

unsigned long dwTotalRead;

for (int i=0;i<nLastItem;i++)
{

TCHAR szBuffer[1024];
DWORD cchBuf(1024);
LVITEM lvi;
lvi.iItem = i;
lvi.iSubItem = 0;  // subitem 1: address!
lvi.mask = LVIF_TEXT;
lvi.pszText = szBuffer;
lvi.cchTextMax = cchBuf;
m_cListCtrl.GetItem(&lvi);

unsigned int caddress = GenericPurposeMethods::ConvertHexStringToInt(lvi.pszText);

	char* valuestr = new char[1];
	valuestr[0] = 00;

	unsigned char* valbytes = new unsigned char[search_len];
	int isok = ReadProcessMemory(hProcess, (LPVOID)caddress, valbytes,
							 search_len, &dwTotalRead);

	if (isok != 0)  // if read didn't failed
	{
	valuestr = GenericPurposeMethods::BytesToString(valbytes,search_len, search_type.GetBuffer(0), base.GetBuffer(0));
	}
	else
	{
	valuestr = _T("Read failed!!!");
	}

lvi.iItem = i;
lvi.iSubItem = 1;  // subitem 1: value!
lvi.mask = LVIF_TEXT;
lvi.pszText = szBuffer;
lvi.cchTextMax = cchBuf;
m_cListCtrl.GetItem(&lvi);
lvi.pszText = valuestr;
m_cListCtrl.SetItem(&lvi);


}
CloseHandle(hProcess);
}

void MemoryHack::OnRnfbut() 
{
	// TODO: Add your control notification handler code here
	CWnd* statusWnd = GetDlgItem(IDC_STATUS_STATIC);

	int row = m_type.GetCurSel();
    if (row < 0)
	{
		statusWnd->SetWindowText(_T("No sel for type!"));
		return;
	}

    CString search_type;
    m_type.GetLBText(row, search_type);
	if (search_type.GetLength()==0)
	{
		statusWnd->SetWindowText(_T("Type text len can be 0!"));
		return;
	}

    row = m_base.GetCurSel();
    if(row < 0)
	{
		statusWnd->SetWindowText(_T("No sel for base!"));
		return;
	}

    CString base;
    m_base.GetLBText(row, base);
	if (base.GetLength()==0)
	{
		statusWnd->SetWindowText(_T("Base text len can be 0!"));
		return;
	}

	char value_to_search_str[500];
	GetDlgItem(IDC_VALUETOSEARCH_EDIT)->GetWindowText(value_to_search_str, 500);

	if (value_to_search_str[0]==0)
	{
		statusWnd->SetWindowText(_T("Value to search len can be 0!"));
		return;
	}

int nLastItem = m_cListCtrl.GetItemCount();	//gets the number of ListView items in the CListCtrl

	if (nLastItem<=0)
	{
		statusWnd->SetWindowText(_T("List doesn't contain any address!!!"));
		return;
	}

int search_len = 0;
unsigned char* to_search_val = GenericPurposeMethods::StringToBytes(value_to_search_str, search_type.GetBuffer(0), base.GetBuffer(0), &search_len);


	if (search_len==0)
	{
		statusWnd->SetWindowText(_T("Failed to convert value to search!"));
		return;
	}

	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                               FALSE, processid);


	if (hProcess==NULL)
	{
	statusWnd->SetWindowText(_T("Failed to open the process!"));
	return;
	}

unsigned long dwTotalRead;

int* items_to_remove = new int[nLastItem];
int remove_count = 0;

for (int i=0;i<nLastItem;i++)
{

TCHAR szBuffer[1024];
DWORD cchBuf(1024);
LVITEM lvi;
lvi.iItem = i;
lvi.iSubItem = 0;  // subitem 1: address!
lvi.mask = LVIF_TEXT;
lvi.pszText = szBuffer;
lvi.cchTextMax = cchBuf;
m_cListCtrl.GetItem(&lvi);

unsigned int caddress = GenericPurposeMethods::ConvertHexStringToInt(lvi.pszText);

	char* valuestr = new char[1];
	valuestr[0] = 00;

	unsigned char* valbytes = new unsigned char[search_len];
	int isok = ReadProcessMemory(hProcess, (LPVOID)caddress, valbytes,
							 search_len, &dwTotalRead);

	if (isok != 0)  // if read didn't failed
	{
	
	bool AreEqual = true;

	for (int j=0;j<search_len;j++)
	{

	if (to_search_val[j]!=valbytes[j])
	{
	AreEqual = false;
	break;
	} // if end
	
	}  // for end

	if (!AreEqual)
	{
	items_to_remove[remove_count]=i;
	remove_count++;
	}

	}  // if isok Read



}  // For end

for (int j=remove_count-1;j>=0;j--)  // remove not found items:
{
m_cListCtrl.DeleteItem(items_to_remove[j]);

}

CloseHandle(hProcess);

}

int patches_count;
unsigned int* items_to_patch;

void MemoryHack::OnPatchbut() 
{
	// TODO: Add your control notification handler code here
	int nLastItem = m_cListCtrl.GetItemCount();	//gets the number of ListView items in the CListCtrl
	patches_count = 0;
	items_to_patch = new unsigned int[nLastItem];

for (int i=0;i<nLastItem;i++)
{

TCHAR szBuffer[1024];
DWORD cchBuf(1024);
LVITEM lvi;
lvi.iItem = i;
lvi.iSubItem = 0;  // subitem 1: address!
lvi.mask = LVIF_TEXT;
lvi.pszText = szBuffer;
lvi.cchTextMax = cchBuf;
m_cListCtrl.GetItem(&lvi);

items_to_patch[i] = GenericPurposeMethods::ConvertHexStringToInt(lvi.pszText);
patches_count++;
	}

PatchAddresses();  // do the actual patching!

	delete[] items_to_patch;
}

void MemoryHack::PatchAddresses()
{

	CWnd* statusWnd = GetDlgItem(IDC_STATUS_STATIC);

	int row = m_type.GetCurSel();
    if (row < 0)
	{
		statusWnd->SetWindowText(_T("No sel for type!"));
		return;
	}

    CString search_type;
    m_type.GetLBText(row, search_type);
	if (search_type.GetLength()==0)
	{
		statusWnd->SetWindowText(_T("Type text len can be 0!"));
		return;
	}

    row = m_base.GetCurSel();
    if(row < 0)
	{
		statusWnd->SetWindowText(_T("No sel for base!"));
		return;
	}

    CString base;
    m_base.GetLBText(row, base);
	if (base.GetLength()==0)
	{
		statusWnd->SetWindowText(_T("Base text len can be 0!"));
		return;
	}

	char patch_str[500];
	GetDlgItem(IDC_NEWVALEDIT)->GetWindowText(patch_str, 500);

	if (patch_str[0]==0)
	{
		statusWnd->SetWindowText(_T("New Value len can be 0!"));
		return;
	}

	if (patches_count<=0)
	{
		statusWnd->SetWindowText(_T("No Address to be patched!!!"));
		return;
	}

int patch_len = 0;
unsigned char* value_to_set = GenericPurposeMethods::StringToBytes(patch_str, search_type.GetBuffer(0), base.GetBuffer(0), &patch_len);


	if (patch_len==0)
	{
		statusWnd->SetWindowText(_T("Failed to convert New value!"));
		return;
	}

	HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS,
                               FALSE, processid);


	if (hProcess==NULL)
	{
	statusWnd->SetWindowText(_T("Failed to open the process!"));
	return;
	}

for (int i=0;i<patches_count;i++)
{

if (!WriteProcessMemory(hProcess, (LPVOID)items_to_patch[i], value_to_set, patch_len, NULL)) 
{

DWORD oldprotect;  // set new access to PAGE_EXECUTE_READWRITE
VirtualProtect((LPVOID)items_to_patch[i], patch_len, PAGE_EXECUTE_READWRITE, &oldprotect);

int iswriteok = WriteProcessMemory(hProcess, (LPVOID)items_to_patch[i], value_to_set, patch_len, NULL);

//int wtf = GetLastError();
// ERROR_INVALID_PARAMETER
// 87 (0x57)
// The parameter is incorrect.


DWORD protectX;  // restore access!
VirtualProtect((LPVOID)items_to_patch[i], patch_len, oldprotect, &protectX);

}

}

CloseHandle(hProcess);

}

void MemoryHack::OnRclickList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
CMenu menu;
menu.LoadMenu(IDR_MEMHACKMENU); // our context menu
CMenu* pPopup = menu.GetSubMenu(0);

RECT rect;
GetWindowRect(&rect);
CPoint mousepos;
GetCursorPos(&mousepos);
pPopup->TrackPopupMenu(NULL,mousepos.x,mousepos.y, this); 

// The menu is a temporary MFC object, no need to delete it.
	*pResult = 0;
}

int selectcount = 0;
int* selected_indexes;

void MemoryHack::GetSelectedIndexes()
{

selectcount = 0;
selected_indexes = new int[2000];

int nRow = m_cListCtrl.GetNextItem(-1, LVNI_SELECTED);
while (nRow != -1)
{

selected_indexes[selectcount]=nRow;
selectcount++;

nRow = m_cListCtrl.GetNextItem(nRow, LVNI_SELECTED);
}

}

void MemoryHack::CopySelected()
{
GetSelectedIndexes();
if (selectcount<=0) return; // nothing to do!

CString formated = _T("");

for (int i=0;i<selectcount;i++)
{

TCHAR szBuffer[1024];
DWORD cchBuf(1024);
LVITEM lvi;
lvi.iItem = selected_indexes[i];
lvi.iSubItem = 0;  // subitem 1: address!
lvi.mask = LVIF_TEXT;
lvi.pszText = szBuffer;
lvi.cchTextMax = cchBuf;
m_cListCtrl.GetItem(&lvi);
formated = formated+lvi.pszText+_T("\t");

lvi.iItem = selected_indexes[i];;
lvi.iSubItem = 1;  // subitem 1: value!
lvi.mask = LVIF_TEXT;
lvi.pszText = szBuffer;
lvi.cchTextMax = cchBuf;
m_cListCtrl.GetItem(&lvi);

formated = formated+lvi.pszText+_T("\r\n");;

	}

 void* glob = GlobalAlloc(GMEM_FIXED,formated.GetLength());
 memcpy(glob,formated,formated.GetLength());

 OpenClipboard();  // hwnd set to NULL
 EmptyClipboard(); // sets clipboard ownership to NULL (?)

SetClipboardData(CF_TEXT, glob);  // fails (??)
CloseClipboard();
GlobalFree(glob);

}

void MemoryHack::RemoveSelected()
{
GetSelectedIndexes();
if (selectcount<=0) return; // nothing to do!

	for (int i=selectcount-1;i>=0;i--)
	{
	 m_cListCtrl.DeleteItem(selected_indexes[i]);  // delete item from ClistCtrl
	}
}

void MemoryHack::PatchSelected()
{
GetSelectedIndexes();
if (selectcount<=0) return; // nothing to do!

	patches_count = 0;
	items_to_patch = new unsigned int[selectcount];

for (int i=0;i<selectcount;i++)
{

TCHAR szBuffer[1024];
DWORD cchBuf(1024);
LVITEM lvi;
lvi.iItem = selected_indexes[i];
lvi.iSubItem = 0;  // subitem 1: address!
lvi.mask = LVIF_TEXT;
lvi.pszText = szBuffer;
lvi.cchTextMax = cchBuf;
m_cListCtrl.GetItem(&lvi);

items_to_patch[i] = GenericPurposeMethods::ConvertHexStringToInt(lvi.pszText);
patches_count++;
	}

PatchAddresses();  // do the actual patching!

	delete[] items_to_patch;

}

void MemoryHack::InspectMemoryMethod()
{
int selected_index = m_cListCtrl.GetNextItem(-1, LVNI_SELECTED);

if (selected_index != -1)
{

TCHAR szBuffer[1024];
DWORD cchBuf(1024);
LVITEM lvi;
lvi.iItem = selected_index;
lvi.iSubItem = 0;  // subitem 0: address!
lvi.mask = LVIF_TEXT;
lvi.pszText = szBuffer;
lvi.cchTextMax = cchBuf;
m_cListCtrl.GetItem(&lvi);

		if (!IsWindow(inspectdlg.m_hWnd)||!inspectdlg.IsWindowVisible())
		{
		
		inspectdlg = (InspectMemory)(new InspectMemory(this));
		//inspectdlg = m_pinspectdialog;	
		inspectdlg.processid = processid;
		inspectdlg.address_str = lvi.pszText;

		//testdlg.DoModal();  // not modal one!
		BOOL ret = inspectdlg.Create(IDD_INSPECTMEMORY_DIALOG,this);
		if (ret)   // If create not failed.
		inspectdlg.ShowWindow(SW_SHOWNORMAL);
		}


}

}

BOOL MemoryHack::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (HIWORD(wParam) == BN_CLICKED)  // if button clicked
    {
		switch(LOWORD(wParam))  // Retrieves the low-order word from the specified value.
        {
        case ID_COPYSELECTED:
		CopySelected();
		break;
		
		case ID_REMOVESELECTED:
		RemoveSelected();
		break;

		case ID_PATCHSELECTED:
		PatchSelected();
		break;

		case ID_INSPECTMEMORY:
		InspectMemoryMethod();
		break;

		}

		}

	return CDialog::OnCommand(wParam, lParam);
}
