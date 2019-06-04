// Getmoney.cpp : implementation file
//

#include "stdafx.h"
#include "ATM.h"
#include "Getmoney.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGetmoney dialog
extern CATMApp theApp;//����ȫ�ֶ���

CGetmoney::CGetmoney(CWnd* pParent /*=NULL*/)
	: CDialog(CGetmoney::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetmoney)
	m_longGetmoney = 0;
	//}}AFX_DATA_INIT
	/*����ADO ���ݿ��ʵ��*/
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordConsume.CreateInstance(__uuidof(Recordset));
	this->m_strConMoney = _T("");
}


void CGetmoney::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetmoney)
	/*�ؼ��󶨱���*/
	DDX_Control(pDX, IDC_STATIC_TIP, m_ctrlTip);
	DDX_Text(pDX, IDC_EDIT_GETMONEY, m_longGetmoney);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGetmoney, CDialog)
	//{{AFX_MSG_MAP(CGetmoney)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_PRINTINFO, OnBtnPrintinfo)
	ON_BN_CLICKED(IDC_BTN_100, OnBtn100)
	ON_BN_CLICKED(IDC_BTN_1000, OnBtn1000)
	ON_BN_CLICKED(IDC_BTN_300, OnBtn300)
	ON_BN_CLICKED(IDC_BTN_500, OnBtn500)
	ON_BN_CLICKED(IDC_BTN_800, OnBtn800)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_BACK, OnBtnBack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetmoney message handlers

/*ȡ��*/
void CGetmoney::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData();//���¿ؼ�����
	if(m_longGetmoney % 100 != 0 || m_longGetmoney == 0) {
		GetDlgItem(IDC_EDIT_GETMONEY)->SetWindowText("");
		return;
	}
	CGetmoney::CheckGetmoney();
	
}

/*100Ԫ��ť*/
void CGetmoney::OnBtn100() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_GETMONEY)->ShowWindow(SW_HIDE);
	m_ctrlTip.SetWindowText("");
	m_longGetmoney = 100;
	m_strConMoney.Format("%ld", 100);
	CGetmoney::CheckGetmoney();
}

void CGetmoney::OnBtn1000() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_GETMONEY)->ShowWindow(SW_HIDE);
	m_ctrlTip.SetWindowText("");
	m_longGetmoney = 1000;
	m_strConMoney.Format("%ld", 1000);
	CGetmoney::CheckGetmoney();
}

void CGetmoney::OnBtn300() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_GETMONEY)->ShowWindow(SW_HIDE);
	m_ctrlTip.SetWindowText("");
	m_longGetmoney = 300;
	m_strConMoney.Format("%ld", 300);
	CGetmoney::CheckGetmoney();
}

void CGetmoney::OnBtn500() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_GETMONEY)->ShowWindow(SW_HIDE);
	m_ctrlTip.SetWindowText("");
	m_longGetmoney = 500;
	m_strConMoney.Format("%ld", 500);
	CGetmoney::CheckGetmoney();
}

void CGetmoney::OnBtn800() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_GETMONEY)->ShowWindow(SW_HIDE);
	m_ctrlTip.SetWindowText("");
	m_longGetmoney = 800;
	m_strConMoney.Format("%ld", 800);
	CGetmoney::CheckGetmoney();
}

/*�����ݿ�*/
void CGetmoney::InitData()
{
	if(!theApp.m_pConnection->State)
		theApp.InitDataBase();
	try {
		/*UsrInfo*/
		m_pRecordset->Open("SELECT * FROM UsrInfo ",theApp.m_pConnection.GetInterfacePtr(),
			adOpenDynamic,adLockOptimistic,adCmdText);
		/*UsrRecord*/
		this->m_pRecordConsume->Open("SELECT * FROM UsrRecord ",theApp.m_pConnection.GetInterfacePtr(),
			adOpenDynamic,adLockOptimistic,adCmdText);
	} catch(_com_error *e) {
		AfxMessageBox(e->ErrorMessage());
	}  
}

/**/
BOOL CGetmoney::GetRecord()
{
	_variant_t var;
    CString SCardno,SPwd;
    long cardno ;
	try {
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		// ������и��ֶβ������б����
		while(!m_pRecordset->adoEOF) {   
			var = m_pRecordset->GetCollect("Cardno");
			if(var.vt != VT_NULL) {
				SCardno = (LPCSTR)_bstr_t(var);
				cardno = atol(SCardno);
			}
			if(cardno == m_longCardno) {
				//�ҵ�������Ӧ�ļ�¼��ֹͣ
				return true;
				break;
			} else{
				m_pRecordset->MoveNext();
			}		
		}
		if(m_pRecordset->adoEOF) {
			//����Ҳ�����¼����ʾ����
			m_ctrlTip.SetWindowText("ϵͳ�������Ժ�����!");
			return false;
		}
	} catch(_com_error *e) {
		AfxMessageBox(e->ErrorMessage());
	} 
	return true;
}

/*�Ի�������ʼ��*/
BOOL CGetmoney::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitData();
	if(GetRecord() != TRUE) {
		m_ctrlTip.SetWindowText("ϵͳ����,��ѡ�񷵻�,�Ժ�����");
	}
	GetDlgItem(IDC_BTN_PRINTINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_GETMONEY)->SetWindowText("");
	m_ctrlTip.ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*ȡ�����*/
void CGetmoney::CheckGetmoney()
{
	CString SMoney,SCardno;
	_variant_t var;
	long RemainMoney;
	/*��ȡ���н��*/
	var = m_pRecordset->GetCollect("Remoney");
	/*��ȡ�������ѽ��*/
	GetDlgItemText(IDC_EDIT_GETMONEY, this->m_strConMoney);
	SMoney = (LPCSTR)_bstr_t(var);
	RemainMoney = atol(SMoney);
	if(RemainMoney >= m_longGetmoney) {
		m_ctrlTip.SetWindowText("");
        GetDlgItem(IDC_STATIC_INFO)->SetWindowText("");
		GetDlgItem(IDC_EDIT_GETMONEY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_100)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_300)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_500)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_800)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_1000)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_OK)->ShowWindow(SW_HIDE);

		CDC  *pDC = GetDC();
		CDC compatibledc;
		CRect rect;
		GetClientRect(&rect);
		pDC->BitBlt(160, 160, rect.Width(), rect.Height(), &compatibledc, 0, 0, SRCCOPY);
		GetDlgItem(IDC_STATIC_INFO)->SetWindowText("���ڴ���,��ȴ�");
		Sleep(2000);
		Invalidate();
		/*����*/
		RemainMoney -= m_longGetmoney;
		/*�������ݿ��е��Ѵ���*/
		m_pRecordset->PutCollect("Remoney",_variant_t(RemainMoney));
		m_pRecordset->Update();
        GetDlgItem(IDC_STATIC_INFO)->SetWindowText("���������,��ѡ����������");
		GetDlgItem(IDC_BTN_PRINTINFO)->ShowWindow(SW_SHOWNORMAL);
	} else {
		m_ctrlTip.SetWindowText("������㣬��˶Ժ����");
		GetDlgItem(IDC_EDIT_GETMONEY)->SetWindowText("");
	}
	InsertConsumeRecord();
}

/*��ӡ������Ϣ*/
void CGetmoney::OnBtnPrintinfo() 
{
	// TODO: Add your control notification handler code here
	CString tradeinfo,temp;
	LPCTSTR TradeInfo;
	CTime t = CTime::GetCurrentTime();
	GetDlgItem(IDC_STATIC_INFO)->ShowWindow(SW_HIDE);
	tradeinfo.Format("�ͻ��˺�: %ld\n",m_longCardno);
	tradeinfo += t.Format("����ʱ��: %Y��%m��%d��%H:%M:%S\n");
	temp.Format("ȡ����: %ldԪ",m_longGetmoney);
    tradeinfo += temp;
    TradeInfo = tradeinfo;
    m_ctrlTip.ShowWindow(SW_SHOWNORMAL);
	m_ctrlTip.SetWindowText(TradeInfo);
	GetDlgItem(IDC_BTN_PRINTINFO)->ShowWindow(SW_HIDE);
}

void CGetmoney::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	Sleep(100);
	CDialog::OnCancel ();
}

void CGetmoney::OnBtnBack() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_GETMONEY)->SetWindowText("0");
	GetDlgItem(IDC_EDIT_GETMONEY)->ShowWindow(SW_HIDE);
	CDialog::OnOK();
}

/*�����Ѽ�¼д�����ݿ��UsrRecord����*/
void CGetmoney::InsertConsumeRecord(){
	UpdateData();//���¿ؼ�����
	try{
		m_pRecordConsume->AddNew();
		m_pRecordConsume->PutCollect("Cardno", _variant_t(this->m_longCardno));
		CTime t = CTime::GetCurrentTime();
		CString strInfo;
		strInfo += t.Format("%Y-%m-%d %H:%M:%S");
		m_pRecordConsume->PutCollect("ConsumeDate", _variant_t(strInfo));
		strInfo = _T("");
		m_pRecordConsume->PutCollect("ConsumeMoney", _variant_t(m_strConMoney));
		m_pRecordConsume->PutCollect("ConsumeType", _variant_t("withdrawals"));
		m_pRecordConsume->Update();
	}catch(_com_error *e){
		AfxMessageBox(e->ErrorMessage());
	}
}
