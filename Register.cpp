// Register.cpp : implementation file
//

#include "stdafx.h"
#include "atm.h"
#include "Register.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Register dialog

extern CATMApp theApp;//����ȫ�ֶ���

Register::Register(CWnd* pParent /*=NULL*/)
	: CDialog(Register::IDD, pParent)
{
	//{{AFX_DATA_INIT(Register)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	this->m_strCarNO = _T("");
	this->m_strPwd = _T("");
	this->m_strName = _T("");
	this->m_strSex = _T("");
	this->m_strAddr = _T("");
	this->m_strPhone = _T("");
	this->m_strMoney = _T("");
}


void Register::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Register)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBOX_SEX, m_cb);
}


BEGIN_MESSAGE_MAP(Register, CDialog)
	//{{AFX_MSG_MAP(Register)
	ON_BN_CLICKED(IDC_BTN_CHECK, OnBtnCheck)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Register message handlers

void Register::OnBtnCheck() 
{
	// TODO: Add your control notification handler code here
	if (CheckCardNo()){
		AfxMessageBox("����ʹ��!");
	}else {
		AfxMessageBox("�����Ѵ���!");
	}
}

void Register::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (!CheckCardNo()){
		return ;
	} else {
		GetDlgItemText(IDC_EDIT_CARDNO, this->m_strCarNO);
		GetDlgItemText(IDC_EDIT_PWD, this->m_strPwd);
		GetDlgItemText(IDC_EDIT_NAME, this->m_strName);
		int nIndex = m_cb.GetCurSel();
		m_cb.GetLBText(nIndex, this->m_strSex);
		GetDlgItemText(IDC_EDIT_ADDR, this->m_strAddr);
		GetDlgItemText(IDC_EDIT_PHONE, this->m_strPhone);
		if (IsEmpty(m_strCarNO) || IsEmpty(m_strPwd) || IsEmpty(m_strName) 
				|| IsEmpty(m_strAddr) || IsEmpty(m_strPhone)){
			m_ctrlError.SetWindowText("��Ϣ��ȫ������ϸ���!");
			return ;
		}else {
			InsertData();
		}	
	}
}

void Register::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here
	Sleep(100);
	CDialog::OnCancel();
}


BOOL Register::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitData();
	m_cb.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Register::InitData() {
	if(!theApp.m_pConnection->State)
		theApp.InitDataBase();
	try {
		m_pRecordset->Open("SELECT * FROM UsrInfo ",theApp.m_pConnection.GetInterfacePtr(),
			adOpenDynamic,adLockOptimistic,adCmdText);
	} catch(_com_error *e){
		AfxMessageBox(e->ErrorMessage());
	} 
	
}

BOOL Register::CheckCardNo()
{
	_variant_t var;
    CString SCardno,SPwd,SUsrname,SUsrsex;
    long cardno;
	// TODO: Add your control notification handler code here
	UpdateData();//���¿ؼ�����

	GetDlgItemText(IDC_EDIT_CARDNO, SCardno);
	m_longCardno = atol(SCardno);
	try{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		while(!m_pRecordset->adoEOF){   
			var = m_pRecordset->GetCollect("Cardno");
			if(var.vt != VT_NULL){
				SCardno = (LPCSTR)_bstr_t(var);
				cardno = atol(SCardno);
			}
			if(cardno == m_longCardno){ 
				return false;
			}
			else
				m_pRecordset->MoveNext();
		}
		if(m_pRecordset->adoEOF){
			return true;
		}
	} catch(_com_error *e){
		AfxMessageBox(e->ErrorMessage());
	} 
	return true;
}

void Register::InsertData(){
	try{
		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("Cardno", _variant_t(this->m_strCarNO));
		m_pRecordset->PutCollect("Pwd", _variant_t(this->m_strPwd));
		m_pRecordset->PutCollect("Usrname", _variant_t(this->m_strName));
		if (m_strSex == "��"){
			m_pRecordset->PutCollect("Usrsex", _variant_t("0"));
		}else {
			m_pRecordset->PutCollect("Usrsex", _variant_t("1"));
		}
		m_pRecordset->PutCollect("Usraddr", _variant_t(this->m_strAddr));
		m_pRecordset->PutCollect("Usrphone", _variant_t(this->m_strPhone));
		m_pRecordset->PutCollect("Remoney", _variant_t("0"));
		m_pRecordset->Update();
		AfxMessageBox("����ɹ�!");
	}catch(_com_error *e){
		AfxMessageBox(e->ErrorMessage());
	} 
}

bool Register::IsEmpty(CString str){
	if (str == "") return true;
	else return false;
}
