// Deposit.cpp : implementation file
//

#include "stdafx.h"
#include "atm.h"
#include "Deposit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Deposit dialog

extern CATMApp theApp;//声明全局对象

Deposit::Deposit(CWnd* pParent /*=NULL*/)
	: CDialog(Deposit::IDD, pParent)
{
	//{{AFX_DATA_INIT(Deposit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	//创建ADO 数据库的实例
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordConsume.CreateInstance(__uuidof(Recordset));

	//初始化成员变量
	this->m_strCarNO = _T("");
	this->m_strPwd = _T("");
	this->m_strName = _T("");
	this->m_strSex = _T("");
	this->m_strAddr = _T("");
	this->m_strPhone = _T("");
	this->m_strMoney = _T("");
	this->m_strConMoney = _T("");
}


void Deposit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Deposit)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Deposit, CDialog)
	//{{AFX_MSG_MAP(Deposit)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_MAINMENU, OnBtnMainmenu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Deposit message handlers

/*存款*/
void Deposit::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	try{
		int index = FindIndex();
		if (!Judge100Integer()){
			AfxMessageBox("请输入正确的金额:100的整数倍!!!");
			GetDlgItem(IDC_EDIT_DEPOSIT)->SetWindowText("");
			return ;
		}
		this->m_strConMoney = this->m_strMoney;
		this->m_pRecordset->MoveFirst();
		m_pRecordset->Move(index);

		/*将存钱金额与已存金额相加，并更新数据库数据*/
		long money = GetSavedMoney();
		money += atol(m_strMoney);
		m_strMoney.Format("%ld", money);
		
		m_pRecordset->PutCollect("Remoney", _variant_t(m_strMoney));
		m_pRecordset->Update();
		AfxMessageBox("存款成功!");
		InsertConsumeRecord();
	}catch(_com_error *e){
		AfxMessageBox(e->ErrorMessage());
	}
}

/*退出*/
void Deposit::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	Sleep(100);
	CDialog::OnCancel();
}

/*显示主菜单*/
void Deposit::OnBtnMainmenu() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_DEPOSIT)->SetWindowText("0");
	GetDlgItem(IDC_EDIT_DEPOSIT)->ShowWindow(SW_HIDE);
	CDialog::OnOK();
}

/*找到数据表中该卡号的行号，以便修改数据*/
int Deposit::FindIndex(){
	_variant_t var;
	int index = 0;
    CString SCardno;
    long cardno;
	UpdateData();//更新控件数据
	try{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		// 读入库中各字段并加入列表框中
		while(!m_pRecordset->adoEOF){  
			var = m_pRecordset->GetCollect("Cardno");
			if(var.vt != VT_NULL){
				SCardno = (LPCSTR)_bstr_t(var);
				cardno = atol(SCardno);
			}
			if(cardno == m_longCardno){   
				break;
			} else{
				index++;
				m_pRecordset->MoveNext();
			}
		}
	} catch(_com_error *e){
		AfxMessageBox(e->ErrorMessage());
	} 
	return index;
}

/*打开用户信息数据库表*/
void Deposit::InitData() {
	if(!theApp.m_pConnection->State)
		theApp.InitDataBase();
	try {
		/*UsrInfo*/
		m_pRecordset->Open("SELECT * FROM UsrInfo ",theApp.m_pConnection.GetInterfacePtr(),
			adOpenDynamic,adLockOptimistic,adCmdText);
		/*UsrRecord*/
		this->m_pRecordConsume->Open("SELECT * FROM UsrRecord ",theApp.m_pConnection.GetInterfacePtr(),
			adOpenDynamic,adLockOptimistic,adCmdText);
	} catch(_com_error *e){
		AfxMessageBox(e->ErrorMessage());
	} 
}

/*对话框对象初始化操作*/
BOOL Deposit::OnInitDialog() {
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitData();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*获取已存金额*/
long Deposit::GetSavedMoney(){
	_variant_t var;
	long money = 0;
    CString SCardno, SMoney;
    long cardno;
	UpdateData();//更新控件数据
	try{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		// 读入库中各字段并加入列表框中
		while(!m_pRecordset->adoEOF){  
			var = m_pRecordset->GetCollect("Cardno");
			if(var.vt != VT_NULL){
				SCardno = (LPCSTR)_bstr_t(var);
				cardno = atol(SCardno);
			}
			if(cardno == m_longCardno){   
				var = m_pRecordset->GetCollect("Remoney");
				if (var.vt != VT_NULL){
					SMoney = (LPCSTR)_bstr_t(var);
					money = atol(SMoney);
				}
				break;
			} else{
				m_pRecordset->MoveNext();
			}
		}
	} catch(_com_error *e){
		AfxMessageBox(e->ErrorMessage());
	} 
	return money;
}

/*判断输入的金额是否是100的整数倍*/
bool Deposit::Judge100Integer(){
	GetDlgItemText(IDC_EDIT_DEPOSIT, this->m_strMoney);
	long money = atol(m_strMoney);
	if (0 == (money % 100)){
		return true;
	}else{
		return false;
	}
}

/*将消费记录写入access数据库的UsrRecord表中*/
void Deposit::InsertConsumeRecord(){
	UpdateData();//更新控件数据
	try{
		/*增加一行*/
		m_pRecordConsume->AddNew();
		/*写入卡号*/
		m_pRecordConsume->PutCollect("Cardno", _variant_t(this->m_longCardno));
		CTime t = CTime::GetCurrentTime();
		CString strInfo;
		strInfo += t.Format("%Y-%m-%d %H:%M:%S");
		/*写入时间*/
		m_pRecordConsume->PutCollect("ConsumeDate", _variant_t(strInfo));
		strInfo = _T("");
		/*消费金额*/
		m_pRecordConsume->PutCollect("ConsumeMoney", _variant_t(this->m_strConMoney));
		/*消费类型*/
		m_pRecordConsume->PutCollect("ConsumeType", _variant_t("deposit"));
		m_pRecordConsume->Update();
	}catch(_com_error *e){
		AfxMessageBox(e->ErrorMessage());
	}
}

