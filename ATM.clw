; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRecord
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "atm.h"
LastPage=0

ClassCount=10
Class1=CATMApp
Class2=CATMDlg
Class3=Deposit
Class4=CGetmoney
Class5=CMainmenu
Class6=CModpwd
Class7=CQuery
Class8=Register
Class9=CTransmoney

ResourceCount=9
Resource1=IDD_DIALOG_TRANSMONEY
Resource2=IDD_DIALOG_MAINMENU
Resource3=IDD_DIALOG_GETMONEY
Resource4=IDD_DIALOG_QUERY
Resource5=IDD_DIALOG_REGISTER
Resource6=IDD_DIALOG_DEPOSIT
Resource7=IDD_DIALOG_Mod
Resource8=IDD_ATM_DIALOG
Class10=CRecord
Resource9=IDD_DIALOG_RECORD

[CLS:CATMApp]
Type=0
BaseClass=CWinApp
HeaderFile=ATM.h
ImplementationFile=ATM.cpp
LastObject=IDC_LIST

[CLS:CATMDlg]
Type=0
BaseClass=CDialog
HeaderFile=ATMDlg.h
ImplementationFile=ATMDlg.cpp

[CLS:Deposit]
Type=0
BaseClass=CDialog
HeaderFile=Deposit.h
ImplementationFile=Deposit.cpp

[CLS:CGetmoney]
Type=0
BaseClass=CDialog
HeaderFile=Getmoney.h
ImplementationFile=Getmoney.cpp
LastObject=CGetmoney

[CLS:CMainmenu]
Type=0
BaseClass=CDialog
HeaderFile=Mainmenu.h
ImplementationFile=Mainmenu.cpp

[CLS:CModpwd]
Type=0
BaseClass=CDialog
HeaderFile=Modpwd.h
ImplementationFile=Modpwd.cpp

[CLS:CQuery]
Type=0
BaseClass=CDialog
HeaderFile=Query.h
ImplementationFile=Query.cpp

[CLS:Register]
Type=0
BaseClass=CDialog
HeaderFile=Register.h
ImplementationFile=Register.cpp

[CLS:CTransmoney]
Type=0
BaseClass=CDialog
HeaderFile=Transmoney.h
ImplementationFile=Transmoney.cpp

[DLG:IDD_ATM_DIALOG]
Type=1
Class=CATMDlg
ControlCount=11
Control1=IDC_EDIT_CARDNO,edit,1350639744
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_BTN_MOD,button,1342251008
Control5=IDC_BTN_OK,button,1342251009
Control6=IDC_EDIT_PWD,edit,1350639776
Control7=IDC_STATIC_TIP,static,1342308352
Control8=IDC_BTN_EXIT,button,1342251008
Control9=IDC_STATIC,static,1342308353
Control10=IDC_STATIC_DATE,static,1342308352
Control11=IDC_BTN_REGISTER,button,1342251008

[DLG:IDD_DIALOG_DEPOSIT]
Type=1
Class=Deposit
ControlCount=7
Control1=IDC_STATIC_INFO,static,1342308353
Control2=IDC_EDIT_DEPOSIT,edit,1350631552
Control3=IDC_STATIC_TIP,static,1342308352
Control4=IDC_STATIC_MONEYTIPS,static,1342308352
Control5=IDC_BTN_OK,button,1342242816
Control6=IDC_BTN_EXIT,button,1342242816
Control7=IDC_BTN_MAINMENU,button,1342242816

[DLG:IDD_DIALOG_GETMONEY]
Type=1
Class=CGetmoney
ControlCount=14
Control1=IDC_STATIC,static,1342177806
Control2=IDC_STATIC_INFO,static,1342308353
Control3=IDC_EDIT_GETMONEY,edit,1350631552
Control4=IDC_BTN_OK,button,1342251009
Control5=IDC_BTN_BACK,button,1342251008
Control6=IDC_STATIC_TIP,static,1342308352
Control7=IDC_BTN_PRINTINFO,button,1342251008
Control8=IDC_BTN_100,button,1342242816
Control9=IDC_BTN_300,button,1342242816
Control10=IDC_BTN_500,button,1342242816
Control11=IDC_BTN_800,button,1342242816
Control12=IDC_BTN_1000,button,1342242816
Control13=IDC_BTN_EXIT,button,1342251008
Control14=IDC_STATIC_MONEYTIPS,static,1342308352

[DLG:IDD_DIALOG_MAINMENU]
Type=1
Class=CMainmenu
ControlCount=7
Control1=IDC_BTN_QUERY,button,1342251008
Control2=IDC_BTN_GETMONEY,button,1342251008
Control3=IDC_BTN_MODPWD,button,1342251008
Control4=IDC_BTN_TRANSMONEY,button,1342251008
Control5=IDC_BTN_EXIT,button,1342251008
Control6=IDC_STATIC_TIP,static,1342308352
Control7=IDC_BTN_DEPOSIT,button,1342251008

[DLG:IDD_DIALOG_Mod]
Type=1
Class=CModpwd
ControlCount=7
Control1=IDC_STATIC_TIP,static,1342308353
Control2=IDC_EDIT_PWD,edit,1350631584
Control3=IDC_BTN_BACK,button,1342251008
Control4=IDC_BTN_MOD,button,1342251008
Control5=IDC_BTN_OK,button,1342251009
Control6=IDC_BTN_CANCLE,button,1342251008
Control7=IDC_BTN_EXIT,button,1342251008

[DLG:IDD_DIALOG_QUERY]
Type=1
Class=CQuery
ControlCount=5
Control1=IDC_STATIC_TIP,static,1342308353
Control2=IDC_BTN_BACK,button,1342251008
Control3=IDC_BTN_REMAINMONEY,button,1342254848
Control4=IDC_BTN_HISTORY,button,1342251008
Control5=IDC_BTN_EXIT,button,1342251008

[DLG:IDD_DIALOG_REGISTER]
Type=1
Class=Register
ControlCount=15
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_CARDNO,edit,1350631552
Control3=IDC_BTN_CHECK,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_PWD,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_NAME,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_ADDR,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_PHONE,edit,1350631552
Control13=IDC_COMBOX_SEX,combobox,1344340226
Control14=IDC_BTN_OK,button,1342242816
Control15=IDC_BTN_CANCEL,button,1342242816

[DLG:IDD_DIALOG_TRANSMONEY]
Type=1
Class=CTransmoney
ControlCount=8
Control1=IDC_STATIC_TIP,static,1342308353
Control2=IDC_EDIT_TRANSINFO,edit,1350631552
Control3=IDC_BTN_OK,button,1342251009
Control4=IDC_BTN_EXIT,button,1342251008
Control5=IDC_BTN_PRINTINFO,button,1342251008
Control6=IDC_BTN_BACK,button,1342251008
Control7=IDC_BTN_RETRY,button,1342251008
Control8=IDC_BTN_MOD,button,1342251008

[DLG:IDD_DIALOG_RECORD]
Type=1
Class=CRecord
ControlCount=3
Control1=IDC_LIST,SysListView32,1350631429
Control2=IDC_BTN_MAINMENU,button,1342242816
Control3=IDC_BTN_WRITE,button,1342242816

[CLS:CRecord]
Type=0
HeaderFile=Record.h
ImplementationFile=Record.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST

