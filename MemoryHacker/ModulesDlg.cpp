// ModulesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MemoryHacker.h"
#include "ModulesDlg.h"
#include "GenericPurposeMethods.h"
#include "CustomizeDlg.h"

#include "C:\Program Files (x86)\Microsoft SDK\include\Psapi.h"
#pragma comment (lib, "Psapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ModulesDlg dialog


ModulesDlg::ModulesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ModulesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ModulesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ModulesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ModulesDlg)
	DDX_Control(pDX, IDC_LIST1, m_cListCtrl);
	//}}AFX_DATA_MAP
}

ModulesDlg& ModulesDlg::operator=(ModulesDlg& right)
{
// right contains value to be set
// this contains old value
(*this).m_hWnd = right.m_hWnd;
return *this;

}

BEGIN_MESSAGE_MAP(ModulesDlg, CDialog)
	//{{AFX_MSG_MAP(ModulesDlg)
	ON_WM_CLOSE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ModulesDlg message handlers

void ModulesDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	this->DestroyWindow();  // destroy the window
	CDialog::OnClose();
}

TCHAR fullmodulenames[1024][MAX_PATH];
TCHAR shortmodulenames[1024][MAX_PATH];
HMODULE modules_address[1024];
int modulecount;

void ModulesDlg::RefreshModulesList()
{
	m_cListCtrl.DeleteAllItems();  // clean old items!
	
	modulecount = 0;
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processid);

	if (hProcess==NULL) return;

	HMODULE hMods[1024];
	DWORD cbNeeded;


	// Get a list of all the modules in this process.
    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
    {

		for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ )
        {
            TCHAR szModName[MAX_PATH];
            // Get the full path to the module's file.
            if ( GetModuleFileNameEx( hProcess, hMods[i], szModName,
                                      sizeof(szModName) / sizeof(TCHAR)))
            {

				for (int j=0;j<(sizeof(szModName) / sizeof(TCHAR));j++)
				fullmodulenames[modulecount][j] = szModName[j];

				modules_address[modulecount] = hMods[i];

				TCHAR* psname = GenericPurposeMethods::GetShortModuleName(fullmodulenames[modulecount]);
				for (int k=0;k<(sizeof(szModName) / sizeof(TCHAR));k++)
				shortmodulenames[modulecount][k] = psname[k];

				modulecount++;

            }
		}

	}

	CloseHandle(hProcess);

	
	// Add the process name and identifier.
	for (int i=0;i<modulecount;i++)
	{
	LVITEM lvi;
	CString strItem;

	// Insert the first item
	lvi.mask =  LVIF_TEXT;
	lvi.iItem = m_cListCtrl.GetItemCount(); // this starts with 0!
	
	// insert subitem 0
	lvi.iSubItem = 0;
	lvi.pszText = (LPTSTR)(shortmodulenames[i]);
	m_cListCtrl.InsertItem(&lvi);

	char baseaddress[20];
	wsprintf(baseaddress,"%X",hMods[i]);  // convert number to hex string
	
	int len = 8-strlen(baseaddress); // get the missing part size
	memmove(baseaddress+len,baseaddress,strlen(baseaddress)); // move the string characters to the end
	for ( int i = 0; i < len; i++ ) // fill the beginning characters with '0'
    baseaddress[i] = '0';

	baseaddress[8] = 0;  // place the 00 end char at the end of string!

	// insert subitem 1
	lvi.iSubItem = 1;
	lvi.pszText = (char*)LPCTSTR(baseaddress);
	m_cListCtrl.SetItem(&lvi);

	}

}


BOOL ModulesDlg::OnInitDialog() 
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
	m_cListCtrl.InsertColumn(0, _T("Module Name"), LVCFMT_LEFT, size*2);
	m_cListCtrl.InsertColumn(1, _T("Base Address"), LVCFMT_LEFT, size);

	RefreshModulesList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ModulesDlg::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	 POSITION pos = m_cListCtrl.GetFirstSelectedItemPosition();
	 int position = m_cListCtrl.GetNextSelectedItem(pos);

	 if (position>=0)
	 {
		HMODULE hmod = modules_address[position];
		CCustomizeDlg::UpdateStartAddress((unsigned int)hmod);
		unsigned int size = ModulesDlg::GetModuleSize(hmod);
		unsigned int end_address = (unsigned int)hmod+size;
		CCustomizeDlg::UpdateEndAddress(end_address);
	 }

	*pResult = 0;
}


unsigned int ModulesDlg::GetModuleSize(HMODULE hMod)
{

unsigned int speed = 0x1000;
		
try
{
SYSTEM_INFO* pSI = new SYSTEM_INFO();
GetSystemInfo(pSI);
speed = pSI->dwPageSize;
}
catch(...)  // catch any exception
{
}


HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                               FALSE, processid);
if (hProcess==NULL) return 0;

unsigned char* tempbuf= new unsigned char[04];
unsigned long dwTotalRead;

unsigned int base_address = (unsigned int)hMod+0x03C;
int isok = ReadProcessMemory(hProcess, (LPVOID)base_address, tempbuf, 04, &dwTotalRead);
if (isok == 0) return 0;  // if read failed return 0

int PEOffset = GenericPurposeMethods::UnsignedArrayToUInt(tempbuf, 0);
if (PEOffset==0) return 0;

base_address = (unsigned int)hMod+PEOffset+0x0F8+20;
isok = ReadProcessMemory(hProcess, (LPVOID)base_address, tempbuf, 04, &dwTotalRead);
if (isok == 0) return 0;  // if read failed return

unsigned int RawOfFirstSection = GenericPurposeMethods::UnsignedArrayToUInt(tempbuf, 0);
unsigned int offset=0;

unsigned int sizetocopy = RawOfFirstSection;
if (sizetocopy>speed) sizetocopy=(unsigned int)speed;
if (sizetocopy==0) sizetocopy = speed;

offset=offset+RawOfFirstSection;

unsigned char* PeHeader = new byte[sizetocopy];
isok = ReadProcessMemory(hProcess, (LPVOID)hMod, PeHeader, sizetocopy, &dwTotalRead);
if (isok == 0) return 0;  // if read failed return

unsigned int nrofsection = GenericPurposeMethods::UnsignedArrayToShort(PeHeader, PEOffset+0x06);

base_address = (unsigned int)hMod+PEOffset+0x28;
isok = ReadProcessMemory(hProcess, (LPVOID)base_address, tempbuf, 04, &dwTotalRead);
if (isok == 0) return 0;  // if read failed return 0

unsigned int modulesize = 0;

			for (int i = nrofsection-1; i >= 0; --i)
            {
			unsigned int virtualsize = GenericPurposeMethods::UnsignedArrayToUInt(PeHeader, PEOffset+0x0F8+0x28*i+8);
            unsigned int virtualAddress = GenericPurposeMethods::UnsignedArrayToUInt(PeHeader, PEOffset+0x0F8+0x28*i+0xC);
			if (virtualAddress!=0)
			{
			modulesize = virtualsize+virtualAddress;
			break;
			}
			}

CloseHandle(hProcess);

return modulesize;

}

