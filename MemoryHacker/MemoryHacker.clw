; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=InspectMemory
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MemoryHacker.h"

ClassCount=8
Class1=CMemoryHackerApp
Class2=CMemoryHackerDlg

ResourceCount=10
Resource1=IDR_MAINFRAME
Resource2=IDD_INSPECTMEMORY_DIALOG
Resource3=IDD_MEMORYHACKER_DIALOG
Class3=MemoryHack
Resource4=IDD_MEMORYBLOCK_DIALOG
Class4=NewEdit
Class5=CCustomizeDlg
Resource5=IDD_MEMORYHACK_DIALOG
Resource6=IDR_PROCESS_MENU
Class6=ModulesDlg
Class7=MemoryBlock
Resource7=IDD_CUSTOMIZEDLG_DIALOG
Resource8=IDR_CUSTOM_MENU
Resource9=IDD_MODULESDLG_DIALOG
Class8=InspectMemory
Resource10=IDR_MEMHACKMENU

[CLS:CMemoryHackerApp]
Type=0
HeaderFile=MemoryHacker.h
ImplementationFile=MemoryHacker.cpp
Filter=N

[CLS:CMemoryHackerDlg]
Type=0
HeaderFile=MemoryHackerDlg.h
ImplementationFile=MemoryHackerDlg.cpp
Filter=D
LastObject=CMemoryHackerDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_MEMORYHACKER_DIALOG]
Type=1
Class=CMemoryHackerDlg
ControlCount=1
Control1=IDC_LIST1,SysListView32,1350631425

[MNU:IDR_PROCESS_MENU]
Type=1
Class=?
Command1=ID_PROCESS_MEMORYHACK
Command2=ID_PROCESS_REFRESH
CommandCount=2

[DLG:IDD_MEMORYHACK_DIALOG]
Type=1
Class=MemoryHack
ControlCount=17
Control1=IDC_FULLSEARCH_RAD,button,1342177289
Control2=IDC_CUSTOMSEARCH_RAD,button,1342177289
Control3=IDC_CUSTOMIZE_BTN,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_TYPE_COMBO,combobox,1344339970
Control6=IDC_STATIC,static,1342308352
Control7=IDC_BASE_COMBO,combobox,1344340226
Control8=IDC_STATIC,static,1342308352
Control9=IDC_VALUETOSEARCH_EDIT,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_NEWVALEDIT,edit,1350631552
Control12=IDC_SEARCH_BUT,button,1342242816
Control13=IDC_STATUS_STATIC,static,1342308352
Control14=IDC_LIST2,SysListView32,1350631425
Control15=IDC_READ_VALUES,button,1342242816
Control16=IDC_RNFBUT,button,1342242816
Control17=IDC_PATCHBUT,button,1342242816

[CLS:MemoryHack]
Type=0
HeaderFile=MemoryHack.h
ImplementationFile=MemoryHack.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LIST2
VirtualFilter=dWC

[DLG:IDD_CUSTOMIZEDLG_DIALOG]
Type=1
Class=CCustomizeDlg
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STARTA_EDIT,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_ENDA_EDIT,edit,1350631552
Control5=IDC_PICK_START,button,1342242816
Control6=IDC_PICK_END,button,1342242816
Control7=IDC_MODULE_BUT,button,1342242816
Control8=IDC_BLOCK_BUT,button,1342242816
Control9=IDC_ADD_BUT,button,1342242816
Control10=IDC_CLEARALL_BUT,button,1342242816
Control11=IDC_LIST1,SysListView32,1350631425

[CLS:CCustomizeDlg]
Type=0
HeaderFile=CustomizeDlg.h
ImplementationFile=CustomizeDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_ADD_BUT
VirtualFilter=dWC

[CLS:NewEdit]
Type=0
HeaderFile=NewEdit.h
ImplementationFile=NewEdit.cpp
BaseClass=CEdit
Filter=W
LastObject=ID_PROCESS_MEMORYHACK

[DLG:IDD_MODULESDLG_DIALOG]
Type=1
Class=ModulesDlg
ControlCount=1
Control1=IDC_LIST1,SysListView32,1350631425

[CLS:ModulesDlg]
Type=0
HeaderFile=ModulesDlg.h
ImplementationFile=ModulesDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST1

[DLG:IDD_MEMORYBLOCK_DIALOG]
Type=1
Class=MemoryBlock
ControlCount=1
Control1=IDC_LIST1,SysListView32,1350631425

[CLS:MemoryBlock]
Type=0
HeaderFile=MemoryBlock.h
ImplementationFile=MemoryBlock.cpp
BaseClass=CDialog
Filter=D
LastObject=MemoryBlock
VirtualFilter=dWC

[MNU:IDR_CUSTOM_MENU]
Type=1
Class=?
Command1=ID_CUSTOMMENU_REMOVESELECTED
CommandCount=1

[MNU:IDR_MEMHACKMENU]
Type=1
Class=?
Command1=ID_COPYSELECTED
Command2=ID_REMOVESELECTED
Command3=ID_PATCHSELECTED
Command4=ID_INSPECTMEMORY
CommandCount=4

[DLG:IDD_INSPECTMEMORY_DIALOG]
Type=1
Class=InspectMemory
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_BRBYTES,edit,1350631552
Control5=IDC_INSPECTBUT,button,1342242816
Control6=IDC_EDIT_RESULT,edit,1352728708
Control7=IDC_STATIC,static,1342308352

[CLS:InspectMemory]
Type=0
HeaderFile=InspectMemory.h
ImplementationFile=InspectMemory.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=InspectMemory

