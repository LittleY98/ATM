// Transmoney.cpp : implementation file
//

#include "stdafx.h"
#include "ATM.h"
#include "Transmoney.h"
#include "ATMDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransmoney dialog
extern CATMApp theApp;//����ȫ�ֶ���

CTransmoney::CTransmoney(CWnd* pParent /*=NULL*/)
	: CDialog(CTransmoney::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransmoney)
	m_longTransinfo = 0;
	//}}AFX_DATA_INIT
	m_TryTime = 3;
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordConsume.CreateInstance(__uuidof(Recordset));
}


void CTransmoney::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransmoney)
	DDX_Control(pDX, IDC_STATIC_TIP, m_ctrlTip);
	DDX_Text(pDX, IDC_EDIT_TRANSINFO, m_longTransinfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransmoney, CDialog)
	//{{AFX_MSG_MAP(CTransmoney)
	ON_BN_CLICKED(IDC_BTN_BACK, OnBtnBack)
	ON_BN_CLICKED(IDC_BTN_CANCLE, OnBtnCancle)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_RETRY, OnBtnRetry)
	ON_BN_CLICKED(IDC_BTN_MOD, OnBtnMod)
	ON_BN_CLICKED(IDC_BTN_PRINTINFO, OnBtnPrintinfo)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransmoney message handlers

void CTransmoney::OnBtnBack() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_TRANSINFO)->SetWindowText("0");
	GetDlgItem(IDC_BTN_PRINTINFO)->ShowWindow(SW_HIDE);
	CDialog::OnOK();
}

void CTransmoney::OnBtnCancle() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_TRANSINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_OK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_MOD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_RETRY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_CANCLE)->ShowWindow(SW_HIDE);
	m_ctrlTip.SetWindowText("������ȡ��");
}

void CTransmoney::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	_variant_t var;
	LPCTSTR Transusrinfo;
	CString SMoney,SCardno,SUsrname;
	long RemainMoney,cardno;
	UpdateData();//���¿ؼ�����
	if(m_TryTime == 3) {
		try {
			if(!m_pRecordset->BOF)
				m_pRecordset->MoveFirst();
			// ������и��ֶβ������б����
			while(!m_pRecordset->adoEOF) {   
				var = m_pRecordset->GetCollect("Cardno");
				if(var.vt != VT_NULL) {
					SCardno = (LPCSTR)_bstr_t(var);
					cardno=atol(SCardno);
				}
				if(m_longTransinfo == m_longCardno) {
				   //���Լ�ת�˵Ĵ�����
				   m_ctrlTip.SetWindowText("�װ����û�,���������Լ�ת��,��˶Ժ�����!");
				   GetDlgItem(IDC_EDIT_TRANSINFO)->SetWindowText("");
					return ;
				}
				if(cardno == m_longTransinfo) {
                    var = m_pRecordset->GetCollect("Usrname");
					SUsrname = (LPCSTR)_bstr_t(var);
					SUsrname = SUsrname.Right(2);
					CString temp;
                    temp.Format("�Է�����Ϊ\n\t**");
                    temp += SUsrname;
                    Transusrinfo = temp;
					m_ctrlTip.SetWindowText(Transusrinfo);
					GetDlgItem(IDC_EDIT_TRANSINFO)->SetWindowText("0");
				    GetDlgItem(IDC_EDIT_TRANSINFO)->ShowWindow(SW_HIDE);
                    GetDlgItem(IDC_BTN_MOD)->ShowWindow(SW_HIDE);
					m_longTranscard = m_longTransinfo;
					break;
				}
				else
					m_pRecordset->MoveNext();
			}
			if(m_pRecordset->adoEOF) {
				//���뱾���в������û��Ŀ��ź�ĳ�����
				m_ctrlTip.SetWindowText("�޴˺���,��˶Ժ�����!");
				GetDlgItem(IDC_EDIT_TRANSINFO)->SetWindowText("");
				return ;
			}		
		} catch(_com_error *e) {
			AfxMessageBox(e->ErrorMessage());
		}
		m_TryTime--;
	} else if(m_TryTime == 2) {   
		m_ctrlTip.SetWindowText("��������");
		GetDlgItem(IDC_EDIT_TRANSINFO)->SetWindowText("");
		GetDlgItem(IDC_EDIT_TRANSINFO)->ShowWindow(SW_SHOWNORMAL);
		m_TryTime--;
	} else {   
		if(m_longTransinfo == 0) {
			m_ctrlTip.SetWindowText("�װ����û�,ת����Ҫ��Ч����,����������");
			GetDlgItem(IDC_EDIT_TRANSINFO)->SetWindowText("");
			return;
		}
		if(m_longRemainmoney >= m_longTransinfo) {
			//��ת�˽����Ƚ�
			//���¶Է���� 
			var = m_pRecordset->GetCollect("Remoney");
			SMoney = (LPCSTR)_bstr_t(var);
			RemainMoney = atol(SMoney);
			RemainMoney += m_longTransinfo;
			m_pRecordset->PutCollect("Remoney",_variant_t(RemainMoney));
			m_pRecordset->Update();
			//���µ�ǰ�û����
			m_pRecordset->MoveFirst();
			m_pRecordset->Move(m_Index);
			var = m_pRecordset->GetCollect("Remoney");
			SMoney = (LPCSTR)_bstr_t(var);
			RemainMoney = atol(SMoney);
			RemainMoney -= m_longTransinfo;
			m_pRecordset->PutCollect("Remoney",_variant_t(RemainMoney));
			m_pRecordset->Update();
			Sleep(1000);
			m_ctrlTip.SetWindowText("���������,��ѡ�����");
			InsertConsumeRecord();
			GetDlgItem(IDC_EDIT_TRANSINFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_OK)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_MOD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_RETRY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_PRINTINFO)->ShowWindow(SW_SHOWNORMAL);
		} else {
			m_ctrlTip.SetWindowText("�������,��˶Ժ����");
			GetDlgItem(IDC_EDIT_TRANSINFO)->SetWindowText("");
			return;
		}
	}	
}

void CTransmoney::InitData()
{
	if(!theApp.m_pConnection->State)
		theApp.InitDataBase();
	try {
		m_pRecordset->Open("SELECT * FROM UsrInfo ",theApp.m_pConnection.GetInterfacePtr(),
			adOpenDynamic,adLockOptimistic,adCmdText);
		this->m_pRecordConsume->Open("SELECT * FROM UsrRecord ",theApp.m_pConnection.GetInterfacePtr(),
			adOpenDynamic,adLockOptimistic,adCmdText);
	} catch(_com_error *e) {
		AfxMessageBox(e->ErrorMessage());
	}
}

BOOL CTransmoney::GetRecord()
{
	_variant_t var;
    CString SCardno,SUsrname,SUsrsex,temp;
	int sex;
    long cardno ;
	CString SMoney;
	// TODO: Add your control notification handler code here
	try {
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		m_Index = 0;
		// ������и��ֶβ������б����
		while(!m_pRecordset->adoEOF) {   
			var = m_pRecordset->GetCollect("Cardno");
			if(var.vt != VT_NULL) {
				SCardno = (LPCSTR)_bstr_t(var);
				cardno=atol(SCardno);
			}
			if(cardno == m_longCardno) {
				var = m_pRecordset->GetCollect("Usrname");
				SUsrname = (LPCSTR)_bstr_t(var);
				SUsrname = SUsrname.Left(2);
				var = m_pRecordset->GetCollect("Usrsex");
				SUsrsex = (LPCSTR)_bstr_t(var);
				sex=atoi(SUsrsex);
				if(sex == 0)
				  temp.Format("����");
				else
				  temp.Format("Ůʿ");
				SUsrname += temp;
				m_UsrInfo = SUsrname;
				m_UsrInfo += "\n\t";
				var = m_pRecordset->GetCollect("Remoney");
				SMoney = (LPCSTR)_bstr_t(var);
				m_longRemainmoney = atol(SMoney);
				break;
			} else {
				m_Index++;
				m_pRecordset->MoveNext();
			}
		}
		if(m_pRecordset->adoEOF) {
			m_ctrlTip.SetWindowText("ϵͳ�������Ժ�����!");
			return FALSE;
		}
	} catch(_com_error *e) {
		AfxMessageBox(e->ErrorMessage());
	}
	return TRUE;
}

BOOL CTransmoney::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitData();
	GetRecord();
	GetDlgItem(IDC_BTN_PRINTINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_TRANSINFO)->SetWindowText("");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTransmoney::OnBtnRetry() 
{
	// TODO: Add your control notification handler code here
	m_TryTime = 3;
    m_ctrlTip.SetWindowText("������Է��˺�");
	GetDlgItem(IDC_EDIT_TRANSINFO)->ShowWindow(SW_SHOWNORMAL);
    GetDlgItem(IDC_EDIT_TRANSINFO)->SetWindowText("");
}

void CTransmoney::OnBtnMod()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_TRANSINFO)->SetWindowText("");
}

void CTransmoney::OnBtnPrintinfo() 
{
	// TODO: Add your control notification handler code here
	CTime t = CTime::GetCurrentTime();
	CString tradeinfo,temp;
	LPCTSTR TradeInfo;
    tradeinfo.Format("�ͻ��˺�: %ld\n",m_longCardno);
	tradeinfo += t.Format("����ʱ��: %Y��%m��%d��%H:%M:%S\n");
	temp.Format("ת���˺�: %ld\nת�˽��: %ldԪ\n",m_longTranscard,m_longTransinfo);
    tradeinfo += temp;
    TradeInfo = tradeinfo;
	m_ctrlTip.SetWindowText(TradeInfo);
	GetDlgItem(IDC_BTN_PRINTINFO)->ShowWindow(SW_HIDE);
}

void CTransmoney::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	Sleep(100);
	CDialog::OnCancel ();
}

void CTransmoney::InsertConsumeRecord(){
	UpdateData();//���¿ؼ�����	
	try{
		m_pRecordConsume->AddNew();
		m_pRecordConsume->PutCollect("Cardno", _variant_t(this->m_longCardno));
		CTime t = CTime::GetCurrentTime();
		CString strInfo;
		strInfo += t.Format("%Y-%m-%d %H:%M:%S");

		m_pRecordConsume->PutCollect("ConsumeDate", _variant_t(strInfo));
		strInfo = _T("");
		m_pRecordConsume->PutCollect("ConsumeMoney", _variant_t(m_longTransinfo));
		m_pRecordConsume->PutCollect("ConsumeType", _variant_t("transfer"));
		m_pRecordConsume->PutCollect("ColCardNO", _variant_t(m_longTranscard));
		m_pRecordConsume->Update();
	}catch(_com_error *e){
		AfxMessageBox(e->ErrorMessage());
	}
}




