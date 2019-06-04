// Mainmenu.cpp : implementation file
//

#include "stdafx.h"
#include "ATM.h"
#include "Mainmenu.h"
#include "Getmoney.h"
#include "Query.h"
#include "Transmoney.h"
#include "Modpwd.h"
#include "ATMDlg.h"
#include "Deposit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainmenu dialog

CMainmenu::CMainmenu(CWnd* pParent /*=NULL*/)
	: CDialog(CMainmenu::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainmenu)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMainmenu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainmenu)
	DDX_Control(pDX, IDC_STATIC_TIP, m_ctrlTip);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainmenu, CDialog)
	//{{AFX_MSG_MAP(CMainmenu)
	ON_BN_CLICKED(IDC_BTN_GETMONEY, OnBtnGetmoney)
	ON_BN_CLICKED(IDC_BTN_QUERY, OnBtnQuery)
	ON_BN_CLICKED(IDC_BTN_TRANSMONEY, OnBtnTransmoney)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_MODPWD, OnBtnModpwd)
	ON_BN_CLICKED(IDC_BTN_DEPOSIT, OnBtnDeposit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainmenu message handlers

/*取款按钮事件*/
void CMainmenu::OnBtnGetmoney() 
{
	// TODO: Add your control notification handler code here
	CGetmoney Dlg;
	Dlg.m_longCardno = m_longCardno;
	CDialog::ShowWindow(SW_HIDE );
	if(IDOK == Dlg.DoModal()) {
		CDialog::ShowWindow(SW_SHOWNORMAL);
	} else {
		Sleep(100);
		CDialog::OnCancel();
	}
}

/*查询按钮事件*/
void CMainmenu::OnBtnQuery() 
{
	// TODO: Add your control notification handler code here
	CQuery Dlg;
    Dlg.m_longCardno = m_longCardno;
    CDialog::ShowWindow (SW_HIDE );
	if(IDOK == Dlg.DoModal()) {
		CDialog::ShowWindow(SW_SHOWNORMAL);
	} else {
		Sleep(100);
		CDialog::OnCancel();
	}
}

/*转账按钮事件*/
void CMainmenu::OnBtnTransmoney() 
{
	// TODO: Add your control notification handler code here
	CTransmoney  Dlg;
    Dlg.m_longCardno = m_longCardno;
	CDialog::ShowWindow(SW_HIDE );
	if(IDOK == Dlg.DoModal()) {
		CDialog::ShowWindow(SW_SHOWNORMAL);
	} else {
		Sleep(100);
		CDialog::OnCancel();
	}
}

void CMainmenu::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	Sleep(100);
	CDialog::OnCancel();
}

 void CMainmenu::OnBtnModpwd() 
 {
 	// TODO: Add your control notification handler code here
 	CModpwd  Dlg;
 	Dlg.m_longCardno = m_longCardno;
	CDialog::ShowWindow(SW_HIDE);
 	if(IDOK == Dlg.DoModal()) {
		CDialog::ShowWindow(SW_SHOWNORMAL);
	} else {
		Sleep(100);
		CDialog::OnCancel();
	}
 }

BOOL CMainmenu::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	LPCTSTR Info;
	Info = UsrInfo;
	m_ctrlTip.SetWindowText(Info);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMainmenu::OnBtnDeposit() 
{
	// TODO: Add your control notification handler code here
	Deposit Dlg;
	Dlg.m_longCardno = m_longCardno;
	CDialog::ShowWindow(SW_HIDE);
	if(IDOK == Dlg.DoModal()){
		CDialog::ShowWindow(SW_SHOWNORMAL);
	} else {
		Sleep(100);
		CDialog::OnCancel();
	}
}
