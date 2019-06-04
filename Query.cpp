// Query.cpp : implementation file
//

#include "stdafx.h"
#include "ATM.h"
#include "Query.h"
#include "ATMDlg.h"
#include "Record.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQuery dialog
extern CATMApp theApp;//声明全局对象
CQuery::CQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQuery)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pRecordset.CreateInstance(__uuidof(Recordset));
}


void CQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQuery)
	DDX_Control(pDX, IDC_STATIC_TIP, m_Tip);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQuery, CDialog)
	//{{AFX_MSG_MAP(CQuery)
	ON_BN_CLICKED(IDC_BTN_BACK, OnBtnBack)
	ON_BN_CLICKED(IDC_BTN_REMAINMONEY, OnBtnRemainmoney)
	ON_BN_CLICKED(IDC_BTN_HISTORY, OnBtnHistory)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQuery message handlers

void CQuery::OnBtnBack() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CQuery::OnBtnRemainmoney() 
{
	// TODO: Add your control notification handler code here
	CString SMoney, SCardno, Printinfo;
	_variant_t var;
	LPCSTR Strtemp;
	if(GetRecord() != TRUE)
		return;
	UpdateData();//千万要记住，更新控件数据
	var = m_pRecordset->GetCollect("Remoney");
	SMoney = (LPCSTR)_bstr_t(var);
    Strtemp = SMoney;
    Printinfo.Format("您的可用余额为: ");
    Printinfo += SMoney;
    Strtemp = Printinfo;
    m_Tip.SetWindowText (Strtemp);
}

void CQuery::OnBtnHistory() 
{
	// TODO: Add your control notification handler code here
	CRecord Dlg;
	Dlg.m_longCardno = m_longCardno;
	CDialog::ShowWindow (SW_HIDE );
	if(IDOK == Dlg.DoModal()) {
		CDialog::ShowWindow(SW_SHOWNORMAL);
	} else {
		Sleep(100);
		CDialog::OnCancel();
	}
}

void CQuery::InitData()
{
	if(!theApp.m_pConnection->State)
		theApp.InitDataBase();
	try {
		m_pRecordset->Open("SELECT * FROM UsrInfo ",theApp.m_pConnection.GetInterfacePtr(),
			adOpenDynamic,adLockOptimistic,adCmdText);
	} catch(_com_error *e) {
		AfxMessageBox(e->ErrorMessage());
	}
}
BOOL CQuery::GetRecord()
{
	_variant_t var;
    CString SCardno;
    long cardno ;
	// TODO: Add your control notification handler code here
	try {
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		// 读入库中各字段并加入列表框中
		while(!m_pRecordset->adoEOF) {   
			var = m_pRecordset->GetCollect("Cardno");
			if(var.vt != VT_NULL) {
				SCardno = (LPCSTR)_bstr_t(var);
				cardno = atol(SCardno);
			}
			if(cardno == m_longCardno)
				return TRUE;
			else
				m_pRecordset->MoveNext();
		}
		if(m_pRecordset->adoEOF) {
			m_Tip.SetWindowText("系统错误，请稍后重试!");
			return FALSE;
		}
	} catch(_com_error *e) {
		AfxMessageBox(e->ErrorMessage());
	} 
	return TRUE;
}

BOOL CQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitData();
    if(GetRecord()!=TRUE)
	  MessageBox("初始化错误2");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CQuery::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	Sleep(100);
	CDialog::OnCancel ();
}
