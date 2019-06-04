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

extern CATMApp theApp;//����ȫ�ֶ���

Deposit::Deposit(CWnd* pParent /*=NULL*/)
	: CDialog(Deposit::IDD, pParent)
{
	//{{AFX_DATA_INIT(Deposit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	//����ADO ���ݿ��ʵ��
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordConsume.CreateInstance(__uuidof(Recordset));

	//��ʼ����Ա����
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

/*���*/
void Deposit::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	try{
		int index = FindIndex();
		if (!Judge100Integer()){
			AfxMessageBox("��������ȷ�Ľ��:100��������!!!");
			GetDlgItem(IDC_EDIT_DEPOSIT)->SetWindowText("");
			return ;
		}
		this->m_strConMoney = this->m_strMoney;
		this->m_pRecordset->MoveFirst();
		m_pRecordset->Move(index);

		/*����Ǯ������Ѵ�����ӣ����������ݿ�����*/
		long money = GetSavedMoney();
		money += atol(m_strMoney);
		m_strMoney.Format("%ld", money);
		
		m_pRecordset->PutCollect("Remoney", _variant_t(m_strMoney));
		m_pRecordset->Update();
		AfxMessageBox("���ɹ�!");
		InsertConsumeRecord();
	}catch(_com_error *e){
		AfxMessageBox(e->ErrorMessage());
	}
}

/*�˳�*/
void Deposit::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	Sleep(100);
	CDialog::OnCancel();
}

/*��ʾ���˵�*/
void Deposit::OnBtnMainmenu() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_DEPOSIT)->SetWindowText("0");
	GetDlgItem(IDC_EDIT_DEPOSIT)->ShowWindow(SW_HIDE);
	CDialog::OnOK();
}

/*�ҵ����ݱ��иÿ��ŵ��кţ��Ա��޸�����*/
int Deposit::FindIndex(){
	_variant_t var;
	int index = 0;
    CString SCardno;
    long cardno;
	UpdateData();//���¿ؼ�����
	try{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		// ������и��ֶβ������б����
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

/*���û���Ϣ���ݿ��*/
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

/*�Ի�������ʼ������*/
BOOL Deposit::OnInitDialog() {
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitData();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*��ȡ�Ѵ���*/
long Deposit::GetSavedMoney(){
	_variant_t var;
	long money = 0;
    CString SCardno, SMoney;
    long cardno;
	UpdateData();//���¿ؼ�����
	try{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		// ������и��ֶβ������б����
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

/*�ж�����Ľ���Ƿ���100��������*/
bool Deposit::Judge100Integer(){
	GetDlgItemText(IDC_EDIT_DEPOSIT, this->m_strMoney);
	long money = atol(m_strMoney);
	if (0 == (money % 100)){
		return true;
	}else{
		return false;
	}
}

/*�����Ѽ�¼д��access���ݿ��UsrRecord����*/
void Deposit::InsertConsumeRecord(){
	UpdateData();//���¿ؼ�����
	try{
		/*����һ��*/
		m_pRecordConsume->AddNew();
		/*д�뿨��*/
		m_pRecordConsume->PutCollect("Cardno", _variant_t(this->m_longCardno));
		CTime t = CTime::GetCurrentTime();
		CString strInfo;
		strInfo += t.Format("%Y-%m-%d %H:%M:%S");
		/*д��ʱ��*/
		m_pRecordConsume->PutCollect("ConsumeDate", _variant_t(strInfo));
		strInfo = _T("");
		/*���ѽ��*/
		m_pRecordConsume->PutCollect("ConsumeMoney", _variant_t(this->m_strConMoney));
		/*��������*/
		m_pRecordConsume->PutCollect("ConsumeType", _variant_t("deposit"));
		m_pRecordConsume->Update();
	}catch(_com_error *e){
		AfxMessageBox(e->ErrorMessage());
	}
}

