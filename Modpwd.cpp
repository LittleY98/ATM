// Modpwd.cpp : implementation file
//

#include "stdafx.h"
#include "atm.h"
#include "Modpwd.h"
#include "ATMDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModpwd dialog
extern CATMApp theApp;//声明全局对象

CModpwd::CModpwd(CWnd* pParent /*=NULL*/)
	: CDialog(CModpwd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModpwd)
	m_longInputPwd = 0;
	//}}AFX_DATA_INIT
	TryTime = 3;
	m_pRecordset.CreateInstance(__uuidof(Recordset));
}


void CModpwd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModpwd)
	DDX_Control(pDX, IDC_STATIC_TIP, m_ctrlTip);
	DDX_Text(pDX, IDC_EDIT_PWD, m_longInputPwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModpwd, CDialog)
	//{{AFX_MSG_MAP(CModpwd)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_MOD, OnBtnMod)
	ON_BN_CLICKED(IDC_BTN_BACK, OnBtnBack)
	ON_BN_CLICKED(IDC_BTN_CANCLE, OnBtnCancle)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModpwd message handlers

void CModpwd::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	static long InputPwd;
	static type = 0;//输入密码类型，原密码和新密码
	UpdateData();//千万要记住，更新控件数据
	if(type == 0) {   
		if(TryTime == 0) {
			//密码重试只允许3次机会
			m_ctrlTip.SetWindowText("密码输入错误次数过多，卡已锁定,请稍后重试!");
			return;
		}
		if(m_longInputPwd==m_longPwd) {   
			//检验原密码输入是否正确
			m_ctrlTip.SetWindowText("请输入新密码");
			GetDlgItem(IDC_EDIT_PWD)->SetWindowText("");
			TryTime = 1;
			type = 1;
			return;
		} else {
			m_ctrlTip.SetWindowText("原密码错误，请核对后重试!");
			GetDlgItem(IDC_EDIT_PWD)->SetWindowText("");
			TryTime--;
		}
	} else {
		if(TryTime == 1) {   
			//输入新密码
			InputPwd = m_longInputPwd;
			m_ctrlTip.SetWindowText("请输入新密码");
			GetDlgItem(IDC_EDIT_PWD)->SetWindowText("");
			TryTime = 2;
		} else {
			if(InputPwd == m_longInputPwd)//新密码两次输入一致，修改成功
			{
					m_pRecordset->PutCollect("Pwd",_variant_t(InputPwd));
					m_pRecordset->Update();
                    m_ctrlTip.SetWindowText("正在处理,请等待");
					Sleep(2000);
					m_ctrlTip.SetWindowText("密码修改成功,请妥善保存");
					GetDlgItem(IDC_EDIT_PWD)->ShowWindow(SW_HIDE);
                    GetDlgItem(IDC_BTN_CANCLE)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_BTN_MOD)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_BTN_OK)->ShowWindow(SW_HIDE);
					return;
			} else {
					m_ctrlTip.SetWindowText("两次密码不一致,请重新输入新密码!");
					GetDlgItem(IDC_EDIT_PWD)->SetWindowText("");
                    TryTime = 1;//新密码两次输入不一致,继续输入新密码
			}
		}
	}
}

void CModpwd::OnBtnMod() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_PWD)->SetWindowText("");
}

void CModpwd::OnBtnBack() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}
void CModpwd::InitData()
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
BOOL CModpwd::GetRecord()
{
	_variant_t var;
    CString SCardno,SPwd;
    long cardno;
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
			if(cardno==m_longCardno) {   
				var = m_pRecordset->GetCollect("Pwd");
				SPwd = (LPCSTR)_bstr_t(var);
				m_longPwd = atol(SPwd);
				return TRUE;
			} else
				m_pRecordset->MoveNext();
		}
		if(m_pRecordset->adoEOF) {
			m_ctrlTip.SetWindowText("系统错误，请稍后重试!");
			return FALSE;
		}
	} catch(_com_error *e) {
		AfxMessageBox(e->ErrorMessage());
	} 
	return TRUE;
}

BOOL CModpwd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitData();
	GetRecord();
	GetDlgItem(IDC_EDIT_PWD)->SetWindowText("");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CModpwd::OnBtnCancle() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CModpwd::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	Sleep(100);
	CDialog::OnCancel ();
}
