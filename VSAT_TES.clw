; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAbonentDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "VSAT_TES.h"

ClassCount=8
Class1=CVSAT_TESApp
Class2=CVSAT_TESDlg

ResourceCount=9
Resource2=IDD_INIT_COM
Resource3=IDD_CONFIG_DLG
Resource1=IDR_MAINFRAME
Class3=CTerminalDlg
Resource4=IDD_ABON_DIALOG
Class4=COtborDlg
Resource5=IDD_TERMINAL_DLG
Class5=CConfigDlg
Resource6=IDD_DIrOpenDialog
Class6=CAbonentDlg
Resource7=IDD_OTBOR_DLG
Class7=CDirOpenDialog
Resource8=IDD_VSAT_TES_DIALOG
Class8=CInitComDlg
Resource9=IDR_MENU1

[CLS:CVSAT_TESApp]
Type=0
HeaderFile=VSAT_TES.h
ImplementationFile=VSAT_TES.cpp
Filter=N
LastObject=CVSAT_TESApp

[CLS:CVSAT_TESDlg]
Type=0
HeaderFile=VSAT_TESDlg.h
ImplementationFile=VSAT_TESDlg.cpp
Filter=D
LastObject=ID_PUSK
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_VSAT_TES_DIALOG]
Type=1
Class=CVSAT_TESDlg
ControlCount=4
Control1=ID_PUSK,button,1342242816
Control2=ID_STOP,button,1342242816
Control3=IDC_PAUSE,static,1342308352
Control4=IDC_TAB,SysTabControl32,1342177280

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_DIR_OPEN
Command2=ID_TEMP_DIR
Command3=ID_FILE_FREQ
CommandCount=3

[CLS:CTerminalDlg]
Type=0
HeaderFile=TerminalDlg.h
ImplementationFile=TerminalDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CTerminalDlg
VirtualFilter=dWC

[DLG:IDD_TERMINAL_DLG]
Type=1
Class=CTerminalDlg
ControlCount=21
Control1=IDC_STATIC,static,1342308352
Control2=IDC_ISDONE,static,1342312961
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SYN,static,1342247425
Control5=IDC_STATIC,button,1342210823
Control6=IDC_STATIC,static,1342308353
Control7=IDC_FREQ_C,static,1342312961
Control8=IDC_STATIC,static,1342308354
Control9=IDC_ID_CALL,static,1342312961
Control10=ID_CALL_NEW,static,1342308865
Control11=IDC_FREQ_Cnew,static,1342308865
Control12=IDC_FREQ_Anew,static,1342308865
Control13=IDC_STATIC,button,1342177287
Control14=IDC_VKL,static,1342308353
Control15=IDC_FREQ_A,static,1342312961
Control16=IDC_ID_ANSWER,static,1342312961
Control17=ID_ANSWER_NEW,static,1342308865
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308354
Control20=IDC_STATIC,static,1342308352
Control21=IDC_ZES,static,1342312961

[CLS:COtborDlg]
Type=0
HeaderFile=OtborDlg.h
ImplementationFile=OtborDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=COtborDlg
VirtualFilter=dWC

[DLG:IDD_OTBOR_DLG]
Type=1
Class=COtborDlg
ControlCount=3
Control1=IDC_STATIC,button,1342177287
Control2=IDC_IDEN_OTBOR,button,1342246915
Control3=IDC_COD_OTBOR,button,1342246915

[DLG:IDD_CONFIG_DLG]
Type=1
Class=CConfigDlg
ControlCount=35
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,button,1342178055
Control3=IDC_RADIO_4HHz,button,1342308361
Control4=IDC_RADIO_11HHz,button,1342177289
Control5=IDC_STATIC,button,1342178055
Control6=IDC_RADIO,button,1342308361
Control7=IDC_RADIO2,button,1342177289
Control8=IDC_STATIC,button,1342178055
Control9=IDC_ZANOS,button,1342373891
Control10=IDC_COD,edit,1350631552
Control11=IDC_Txt_Cod,static,1342308352
Control12=IDC_FREQ,edit,1350631552
Control13=IDC_Txt_Freq,static,1342308352
Control14=IDC_STEP,edit,1350631552
Control15=IDC_Txt_Step,static,1342308352
Control16=IDC_STATIC,button,1342178055
Control17=IDC_SPEED,edit,1350631553
Control18=IDC_Txt_Speed1,static,1342177280
Control19=IDC_Chek_Del,button,1342242819
Control20=IDC_MinSize,msctls_trackbar32,1342242840
Control21=IDC_Txt_Min,static,1342308352
Control22=IDC_SizeTempMin,static,1342308353
Control23=IDC_MaxSize,msctls_trackbar32,1342242840
Control24=IDC_Chek_Max,button,1342242819
Control25=IDC_Txt_Max,static,1342308352
Control26=IDC_SizeTempMax,static,1342308353
Control27=IDC_Txt_Seans,static,1342308352
Control28=IDC_NumSeans,static,1342312449
Control29=IDC_Txt_Disk,static,1342308352
Control30=IDC_FreeDisk,static,1342312449
Control31=IDC_TXT_PATH,static,1342308352
Control32=IDC_PATH,static,1342312960
Control33=IDC_SPEED2,edit,1350631553
Control34=IDC_TXT_SPEED2,static,1342308352
Control35=IDC_TXT_SPEED,static,1342308352

[CLS:CConfigDlg]
Type=0
HeaderFile=ConfigDlg.h
ImplementationFile=ConfigDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CConfigDlg
VirtualFilter=dWC

[DLG:IDD_ABON_DIALOG]
Type=1
Class=CAbonentDlg
ControlCount=15
Control1=IDC_STATIC,static,1342308352
Control2=IDC_ISDONE1,static,1342312961
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SYN1,static,1342312961
Control5=IDC_SYN2,static,1342312961
Control6=IDC_ISDONE2,static,1342312961
Control7=IDC_STATIC,button,1342177671
Control8=IDC_STATIC,static,1342308353
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_QUAL1,static,1342312961
Control12=IDC_QUAL2,static,1342312961
Control13=IDC_FileName1,static,1342312961
Control14=IDC_FileName2,static,1342312961
Control15=IDC_STATIC,static,1342308353

[CLS:CAbonentDlg]
Type=0
HeaderFile=AbonentDlg.h
ImplementationFile=AbonentDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_FileName1
VirtualFilter=dWC

[DLG:IDD_DIrOpenDialog]
Type=1
Class=CDirOpenDialog
ControlCount=5
Control1=IDC_FolderLabel,static,1342308364
Control2=IDC_TreeDir,SysTreeView32,1350631447
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_StaticFolderName,static,1342308352

[CLS:CDirOpenDialog]
Type=0
HeaderFile=diropendlg.h
ImplementationFile=diropendlg.cpp
BaseClass=CDialog
LastObject=CDirOpenDialog

[DLG:IDD_INIT_COM]
Type=1
Class=CInitComDlg
ControlCount=3
Control1=IDC_TXT,static,1342308353
Control2=IDC_STATIC,button,1342178055
Control3=IDC_PROGRESS,msctls_progress32,1350565888

[CLS:CInitComDlg]
Type=0
HeaderFile=InitComDlg.h
ImplementationFile=InitComDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CInitComDlg
VirtualFilter=dWC

