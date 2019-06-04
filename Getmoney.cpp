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
extern CATMApp theApp;//声明全局对象

CGetmoney::CGetmoney(CWnd* pParent /*=NULL*/)
	: CDialog(CGetmoney::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetmoney)
	m_longGetmoney = 0;
	//}}AFX_DATA_INIT
	/*创建ADO 数据库的实例*/
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordConsume.CreateInstance(__uuidof(Recordset));
	this->m_strConMoney = _T("");
}


void CGetmoney::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetmoney)
	/*控件绑定变量*/
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

/*取款*/
void CGetmoney::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData();//更新控件数据
	if(m_longGetmoney % 100 != 0 || m_longGetmoney == 0) {
		GetDlgItem(IDC_EDIT_GETMONEY)->SetWindowText("");
		return;
	}
	CGetmoney::CheckGetmoney();
	
}

/*100元按钮*/
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

/*打开数据库*/
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
		// 读入库中各字段并加入列表框中
		while(!m_pRecordset->adoEOF) {   
			var = m_pRecordset->GetCollect("Cardno");
			if(var.vt != VT_NULL) {
				SCardno = (LPCSTR)_bstr_t(var);
				cardno = atol(SCardno);
			}
			if(cardno == m_longCardno) {
				//找到卡号相应的记录则停止
				return true;
				break;
			} else{
				m_pRecordset->MoveNext();
			}		
		}
		if(m_pRecordset->adoEOF) {
			//如果找不到记录则提示错误
			m_ctrlTip.SetWindowText("系统错误，请稍后重试!");
			return false;
		}
	} catch(_com_error *e) {
		AfxMessageBox(e->ErrorMessage());
	} 
	return true;
}

/*对话框对象初始化*/
BOOL CGetmoney::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitData();
	if(GetRecord() != TRUE) {
		m_ctrlTip.SetWindowText("系统错误,请选择返回,稍后重试");
	}
	GetDlgItem(IDC_BTN_PRINTINFO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_GETMONEY)->SetWindowText("");
	m_ctrlTip.ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*取款操作*/
void CGetmoney::CheckGetmoney()
{
	CString SMoney,SCardno;
	_variant_t var;
	long RemainMoney;
	/*获取已有金额*/
	var = m_pRecordset->GetCollect("Remoney");
	/*获取输入消费金额*/
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
		GetDlgItem(IDC_STATIC_INFO)->SetWindowText("正在处理,请等待");
		Sleep(2000);
		Invalidate();
		/*消费*/
		RemainMoney -= m_longGetmoney;
		/*更新数据库中的已存金额*/
		m_pRecordset->PutCollect("Remoney",_variant_t(RemainMoney));
		m_pRecordset->Update();
        GetDlgItem(IDC_STATIC_INFO)->SetWindowText("交易已完成,请选择其他操作");
		GetDlgItem(IDC_BTN_PRINTINFO)->ShowWindow(SW_SHOWNORMAL);
	} else {
		m_ctrlTip.SetWindowText("你的余额不足，请核对后继续");
		GetDlgItem(IDC_EDIT_GETMONEY)->SetWindowText("");
	}
	InsertConsumeRecord();
}

/*打印消费信息*/
void CGetmoney::OnBtnPrintinfo() 
{
	// TODO: Add your control notification handler code here
	CString tradeinfo,temp;
	LPCTSTR TradeInfo;
	CTime t = CTime::GetCurrentTime();
	GetDlgItem(IDC_STATIC_INFO)->ShowWindow(SW_HIDE);
	tradeinfo.Format("客户账号: %ld\n",m_longCardno);
	tradeinfo += t.Format("交易时间: %Y年%m月%d日%H:%M:%S\n");
	temp.Format("取款金额: %ld元",m_longGetmoney);
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

/*将消费记录写入数据库的UsrRecord表中*/
void CGetmoney::InsertConsumeRecord(){
	UpdateData();//更新控件数据
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
